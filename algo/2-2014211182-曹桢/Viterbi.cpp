#include<stdio.h>
#include "Conio.h"
#define N 7
#include "math.h"
#include <stdlib.h>
#include<time.h>
#define randomize() srand((unsigned)time(NULL))

int encode(unsigned int *symbols, /*�������*/unsigned int *data, /*��������*/unsigned int nbytes, /*nbytes=n/16,nΪʵ���������ֵ���Ŀ*/unsigned int startstate /*�����ʼ��״̬*/)
{
	unsigned int j;
	unsigned int input,a1=0,a2=0,a3=0,a4=0,a5=0,a6=0;
	for(j=0;j<nbytes;j++)
	{
		input=*data;
		data++;
		*symbols = input^a1^a2^a3^a6; //c1(171)
		symbols++;
		*symbols = input^a2^a3^a5^a6; //c2(133)
		symbols++;
		a2=a1;
		a1=input; 
	}
	return 0;
}

int trandistance(int m, int state1, int state2)

/*����m���state1��state2ʱ������ŵĺ�������,���state1�޷���state2���������

ֵΪ100*/
{
	int sym,sym1,sym2;
	int c; 
	sym1=((state2>>1)&1)^(state2&1)^(state1&1);
	sym2=((state2>>1)&1)^(state1&1);
	sym=(sym1<<1) | sym2;
	if ( ((state1&2)>>1)==(state2&1))
	   c=((m&1)^(sym&1))+(((m>> 1)&1)^((sym >> 1)&1));
	else
	   c=10000;	
	return c;
}

int traninput(int a,int b) /*״̬��a��bʱ��������ķ���*/
{
	int c;
	c=((b&2)>>1);
	return c;
}

int tranoutput(int a,int b) /*״̬��a��bʱ���������ķ���*/
{
	int c,s1,s2;
	s1=(a&1)^((a&2)>>1)^((b&2)>>1);
	s2=(a&1)^((b&2)>>1);
	c=(s1<<1)|s2;
	return c;
}
void viterbi(int initialstate, /*�����������ʼ״̬*/int *viterbiinput, /*������������������*/int *viterbioutput /*�����������������*/ ) 
{

	struct sta /*��������ͼ��ÿһ��Ϊһ���ṹ��,��Ԫ�ذ���*/
	{ 
	   int met; /*ת�Ƶ���״̬�ۼƵĶ���ֵ*/ 
	   int value; /*������� */ 
	   struct sta *last; /*��ָ��ǰһ��״̬��ָ��*/ 
	}; 
    struct sta state[4][N];
    struct sta *g,*head; 
    int i,j,p,q,t,r,u,l; 
	for(i=0;i<4;i++)
	{
		for(j=0;j<N;j++)
		   state[i][j].met=0;
	} /* ��ʼ��ÿ��״̬�Ķ���ֵ*/ 
	 	 
	for(l=0;l<4;l++) 
	{ 
		state[l][0].met=trandistance(*viterbiinput,initialstate,l); 
		state[l][0].value=traninput(initialstate,l);
	    state[l][0].last=NULL;
    } 
	viterbiinput++; /*��չ��һ���Ҵ�·��*/
	for(t=1;t<N;t++) 
	{ 
	    for(p=0;p<4;p++)
		{ 
			state[p][t].met=state[0][t-1].met+trandistance(*viterbiinput,0,p); 
			state[p][t].value=traninput(0,p); 
			state[p][t].last=&state[0][t-1]; 
			for(q=0;q<4;q++)
			{ 
			   if(state[q][t-1].met+trandistance(*viterbiinput,q,p)<state[p][t].met) 
			   {
			       state[p][t].met=state[q][t-1].met+trandistance(*viterbiinput,q,p); 
			       state[p][t].value=traninput(q,p);
			       state[p][t].last=&state[q][t-1]; 
			   } 
		    } 
		} 
		viterbiinput++;
        state[l][0].last=NULL; 
	} 
	viterbiinput++; /*��չ��һ���Ҵ�·��*/ 
	for(t=1;t<N;t++)
	{
		  for(p=0;p<4;p++) 
		  { 
			   state[p][t].met=state[0][t-1].met+trandistance(*viterbiinput,0,p); 
			   state[p][t].value=traninput(0,p);
			   state[p][t].last=&state[0][t-1]; 
			   for(q=0;q<4;q++)
			   { 
					if(state[q][t-1].met+trandistance(*viterbiinput,q,p)<state[p][t].met) 
					{
						state[p][t].met=state[q][t-1].met+trandistance(*viterbiinput,q,p); 
						state[p][t].value=traninput(q,p); 
						state[p][t].last=&state[q][t-1]; 
					}
			   }
		  } 
		  viterbiinput++;
    }/*�����ʣ����Ҵ�·��*/
    r=state[0][N-1].met; /*�ҳ�n�������ֵ��С��״̬׼������·��*/ 
    g=&state[0][N-1]; 
	for(u=N;u>0;u--) /*��ǰ�ݹ���ҳ������Ȼ·�� */
	{ 
	    *(viterbioutput+(u-1))=g->value; 
	    g=g->last; 
	} /* for(u=0;u<8;u++) *(viterbioutput+u)=state[u][2].met; */ /*���г�������ڼ���n�е� ����ֵ*/
} 
void decode(unsigned int *input, int *output,int n) 
{ 
	int viterbiinput[100]; 
	int j;
	for(j=0;j<n+2;j++) 
	{ 
	   viterbiinput[j]=(input[j*2]<<1)|input[j*2+1];
	} 
    viterbi(0,viterbiinput,output);
} 
int main() 
{

	unsigned int encodeinput[100],wrong[10]={0,0,0,0,0,0,0,0,0,0},encodeoutput[100]; 
	int n=5,i,m,j=0,decodeinput[100],decodeoutput[100];
    randomize();
    for(i=0; i<n; i++) 
       encodeinput[i]=rand()%2;
   encodeinput[n]= encodeinput[n+1]=0; 
   encode(encodeoutput,encodeinput,n+2,0);
   printf("the input of encoder is :\n"); //��ϢԴ�������Ϣ�루��������� 
   for(i=0;i<n; i++) printf("%2d",encodeinput[i]); 
   printf("\n"); 
   printf("the output of encoder is :\n"); //����֮������ľ���� 
   for(i=0;i<(n+2)*2;i++) 
   { 
       printf("%2d",encodeoutput[i]); 
       if(i%20==19) printf("\n");
   } printf("\n"); 
    system("PAUSE") ;
}

