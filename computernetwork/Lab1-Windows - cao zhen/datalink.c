#include <stdio.h>
#include <string.h>

#include "protocol.h"
#include "datalink.h"

#define MAX_SEQ 15
#define NR_BUFS 8
#define DATA_TIMER  12000													//数据超时时间
#define ACK_TIMER  1200														//ACK超时时间
#define inc(k) if(k < MAX_SEQ) k++; else k=0;

typedef enum{false,true} bool;
typedef unsigned char seq_nr;
bool no_nak=true;															//是否未发送nak的标记
static int phl_ready = 0;						
							//物理层是否能准备好的标记
typedef struct
{
	unsigned char data[PKT_LEN];
}packet;

struct FRAME																//数据帧结构体
{ 
    unsigned char kind; 
    seq_nr ack;
    seq_nr seq;
    packet info; 
    unsigned int  padding;
};

static bool between(seq_nr a, seq_nr b, seq_nr c)							//判断是否落入窗口
{
	return (((a <= b)&&(b < c))||((c < a)&&(a <= b))||((b < c)&&(c < a)));
}
static void put_frame(unsigned char *frame, int len)						//将帧加上帧尾，送入物理层
{
    *(unsigned int *)(frame + len) = crc32(frame, len);						//CRC32校验
    send_frame(frame, len + 4);												//CRC，4位校验位
    phl_ready = 0;															//物理层就绪
}

static void send_data_frame(unsigned char fk,seq_nr frame_nr,seq_nr frame_expected,packet buffer[])//发送帧
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
		put_frame((unsigned char *)&s, 3 + PKT_LEN);						//KIND 1位，SEQ 1位，ACK 1位，DATA240~256位
        start_timer(frame_nr, DATA_TIMER);
		dbg_frame("Send DATA %d %d, ID %d\n", s.seq, s.ack, *(short *)s.info.data);
	}
	if(fk==FRAME_NAK||fk==FRAME_ACK) {
		put_frame((unsigned char *)&s, 2);									//KIND 1位，ACK 1位
	}
	stop_ack_timer;
}

int main(int argc, char **argv)
{
    int event, arg, len = 0, i;												
	//event事件，arg获取产生超时事件的定时器编号，len帧长，i用于循环

	seq_nr ack_expected;													//发送窗口下界
	seq_nr next_frame_to_send;												//发送窗口上界
	seq_nr frame_expected;													//接收窗口下界
	seq_nr too_far;															//接收窗口上界
	struct FRAME r;															//帧
	packet out_buf[NR_BUFS];												//发送缓存
	packet in_buf[NR_BUFS];													//接收缓存
	bool arrived[NR_BUFS];													//标记接受缓存是否被占用
	seq_nr nbuffered;														//发送窗口的大小
 
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