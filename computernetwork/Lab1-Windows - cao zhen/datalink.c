#include <stdio.h>
#include <string.h>

#include "protocol.h"
#include "datalink.h"

#define MAX_SEQ 15
#define NR_BUFS 8
#define DATA_TIMER  12000													//���ݳ�ʱʱ��
#define ACK_TIMER  1200														//ACK��ʱʱ��
#define inc(k) if(k < MAX_SEQ) k++; else k=0;

typedef enum{false,true} bool;
typedef unsigned char seq_nr;
bool no_nak=true;															//�Ƿ�δ����nak�ı��
static int phl_ready = 0;						
							//������Ƿ���׼���õı��
typedef struct
{
	unsigned char data[PKT_LEN];
}packet;

struct FRAME																//����֡�ṹ��
{ 
    unsigned char kind; 
    seq_nr ack;
    seq_nr seq;
    packet info; 
    unsigned int  padding;
};

static bool between(seq_nr a, seq_nr b, seq_nr c)							//�ж��Ƿ����봰��
{
	return (((a <= b)&&(b < c))||((c < a)&&(a <= b))||((b < c)&&(c < a)));
}
static void put_frame(unsigned char *frame, int len)						//��֡����֡β�����������
{
    *(unsigned int *)(frame + len) = crc32(frame, len);						//CRC32У��
    send_frame(frame, len + 4);												//CRC��4λУ��λ
    phl_ready = 0;															//��������
}

static void send_data_frame(unsigned char fk,seq_nr frame_nr,seq_nr frame_expected,packet buffer[])//����֡
{
	struct FRAME s;
	s.kind = fk;
	s.seq = frame_nr;
	s.ack = (frame_expected + MAX_SEQ) % (MAX_SEQ+1);

    if(fk == FRAME_DATA)
		memcpy(s.info.data, buffer[frame_nr % NR_BUFS].data, PKT_LEN);
	if(fk == FRAME_NAK) {
		no_nak=false;
	}
	if(fk==FRAME_DATA) {
		put_frame((unsigned char *)&s, 3 + PKT_LEN);						//KIND 1λ��SEQ 1λ��ACK 1λ��DATA240~256λ
        start_timer(frame_nr, DATA_TIMER);
		dbg_frame("Send DATA %d %d, ID %d\n", s.seq, s.ack, *(short *)s.info.data);
	}
	if(fk==FRAME_NAK||fk==FRAME_ACK) {
		put_frame((unsigned char *)&s, 2);									//KIND 1λ��ACK 1λ
	}
	stop_ack_timer;
}

int main(int argc, char **argv)
{
    int event, arg, len = 0, i;												
	//event�¼���arg��ȡ������ʱ�¼��Ķ�ʱ����ţ�len֡����i����ѭ��

	seq_nr ack_expected;													//���ʹ����½�
	seq_nr next_frame_to_send;												//���ʹ����Ͻ�
	seq_nr frame_expected;													//���մ����½�
	seq_nr too_far;															//���մ����Ͻ�
	struct FRAME r;															//֡
	packet out_buf[NR_BUFS];												//���ͻ���
	packet in_buf[NR_BUFS];													//���ջ���
	bool arrived[NR_BUFS];													//��ǽ��ܻ����Ƿ�ռ��
	seq_nr nbuffered;														//���ʹ��ڵĴ�С
 
	disable_network_layer();
	ack_expected = 0;
	next_frame_to_send = 0;
	frame_expected = 0;
	too_far = NR_BUFS;
	nbuffered = 0;

	for(i = 0; i < NR_BUFS; i++) {
		arrived[i] = false;
	}

	protocol_init(argc, argv); 
    lprintf("Designed by Cao Zhen, build: " __DATE__"  "__TIME__"\n");
	
    while(true) {
        event = wait_for_event(&arg);
		switch (event) {
			case NETWORK_LAYER_READY:
				nbuffered++;
				get_packet(out_buf[next_frame_to_send % NR_BUFS].data);
				send_data_frame(FRAME_DATA, next_frame_to_send, frame_expected, out_buf);
				inc(next_frame_to_send);
				break;

			case PHYSICAL_LAYER_READY:
				phl_ready = 1;
				break;

			case FRAME_RECEIVED: 
				len = recv_frame((unsigned char *)&r, sizeof r);
				if (len < 5 || crc32((unsigned char *)&r, len) != 0) {
					dbg_event("**** Receiver Error, Bad CRC Checksum\n");
					if(no_nak) {
						send_data_frame(FRAME_NAK, 0, frame_expected, out_buf);
					}
					break;
				}
				
				if (r.kind == FRAME_DATA) {
				
					if (r.seq != frame_expected && no_nak) {
						send_data_frame(FRAME_NAK, 0, frame_expected, out_buf);
					}else{
						start_ack_timer(ACK_TIMER);
					}
					if(between(frame_expected, r.seq, too_far) && (arrived[r.seq%NR_BUFS] == false)) {
						arrived[r.seq % NR_BUFS] = true;
						in_buf[r.seq % NR_BUFS] = r.info;
						while(arrived[frame_expected % NR_BUFS]) {
							put_packet(in_buf[frame_expected % NR_BUFS].data, len-7);
							no_nak = true;
							arrived[frame_expected % NR_BUFS] = false;
							inc(frame_expected);
							inc(too_far);
							start_ack_timer(ACK_TIMER);
						}
					}
				} 
				if ((r.kind == FRAME_NAK) && between(ack_expected, (r.ack + 1) % (MAX_SEQ + 1), next_frame_to_send)) {
					send_data_frame(FRAME_DATA, (r.ack + 1) % (MAX_SEQ + 1), frame_expected, out_buf);
				}
				while(between(ack_expected, r.ack, next_frame_to_send)) {
					nbuffered--;
					stop_timer(ack_expected);
					inc(ack_expected);
				}
				break; 

			case ACK_TIMEOUT:
				dbg_event("---- ACK %d timeout\n", arg); 
				send_data_frame(FRAME_ACK, 0, frame_expected, out_buf);
				break;

			case DATA_TIMEOUT:
				dbg_event("---- DATA %d timeout\n", arg); 
				send_data_frame(FRAME_DATA, arg, frame_expected, out_buf);
				break;
		}

        if ((nbuffered < NR_BUFS) && phl_ready) {
            enable_network_layer();
		}
        else {
            disable_network_layer();
		} 
   }
}