#include <iostream>  
using namespace std;  
  
int Queen[100][8] = {0}; 
int Q[8]={0}; 
int Count = 0;  
int All=1; 
  
void print()  //��ӡ������� 
{  
    int num,i;  
     
     for(i= 0;i< Count;i ++)//����ȫ��92����� 
     {
     
    if(Queen[i][0]!=-1)//�������������ӡ 
    {
    cout<<"��"<<All<<"�֣�"<<endl; 
	for(num = 0; num <8; num ++)   //���� 
	{  
	 cout<<num+1<<"��"<<Queen[i][num]+1<<"�� ";
	 
     }
     cout<<endl;
     cout<<endl;
     All++;         
		 
    }  
}
  
}  
  
int determine(int i, int y)  //�ж�λ���Ƿ���ȷ 
{  
    int x;  
    int num;  
  
    for(x = 0; x < i; x ++)    
	{  
        num = Q[x];  
  
        if(y == num||(x + num) == (i + y)||(x - num) == (i - y)) //��ͬһ�С�ͬһ�С���б���� 
		{
		return 0;  
		} 
            
    }  
     return 1;  
}  
  
  
  
void eight_queen(int x)  
{  
    int i,j;  
  
    for(i = 0; i < 8; i++)
	{  
        if(determine(x, i)) //λ����ȷ 
		{  
		    Q[x]=i;
 
            
            if(7 == x) //ȫ�� �к���λ�� 
			{  
                 
                for(j=0;j<8;j++)
                {
                	Queen[Count][j]=Q[j];//��ǰ��λ�ô������� 
                }
				Count ++; //���������
  
                return;  
                
            }  
           
			
			eight_queen(x + 1);  //�ݹ鵽��һ�� 
           Q[x] = 0;
//			Queen[Count][x]=Q[x];  
            
            
        }  
    }  
} 
int check(int a[],int b[])//�ж��Ƿ��������⺯�� 
{
	int i,flag=1;
	
	for(i=0;i<8;i++)
	{
		if(b[i]!=a[i])//�в�ͬ�򷵻�0�� 
		{
			flag=0;
		}
	}
	if(flag==1)//���������򷵻�1 
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void reduce()
{
 
 int i,j,k,l,a[8]={0},b[8]={0},c[8]={0},d[8]={0},e[8]={0},f[8]={0},g[8]={0};
 int num,row;
 
 num=Count;
 
 for(i= 0;i< num-1;i++)//�������н� 
 {
 	if(Queen[i][0]!=-1)//��֮ǰû�б��ų����������бȽ� 
 	{
 		for(j= 0;j< 8;j++)//�������λ�õ�����7�������� 
 		{
 			row=Queen[i][j];
            a[row]=7-j;
 			b[7-row]=j;
            c[7-j]=7-row;
			d[j]=7-row;
			e[7-j]=row;
			f[row]=j;
			g[7-row]=7-j;
 		}

		 for(k= i+1;k< num;k++)//��ȫ��λ������е�ǰ��ĺ�һ�� ��ʼ�Ƚ� 
 			{  
 			   if(Queen[k][0]!=-1)//���û�б��ų��� 
 			   {
	 			   	if(check(Queen[k],a)||check(Queen[k],b)||check(Queen[k],c)||check(Queen[k],d)||check(Queen[k],e)||check(Queen[k],f)||check(Queen[k],g))//���бȽϣ�ֻҪ��һ������������ų� 
		 			{
		 				Queen[k][0]=-1;
		 			}   	
 				
			   }
 				
 			   
 		
 			}
 	}
 }
} 
  
  
  
int main()  
{  
    eight_queen(0); //�ݹ�������λ����� 
    reduce();//�ų������� 
	print();//��ӡ 
    cout<<"һ�� "<<All-1<<"�֡�"<<endl;  
    
    return 0;  
}  
