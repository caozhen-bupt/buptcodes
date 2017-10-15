#include <iostream>  
using namespace std;  
  
int Queen[100][8] = {0}; 
int Q[8]={0}; 
int Count = 0;  
int All=1; 
  
void print()  //打印结果函数 
{  
    int num,i;  
     
     for(i= 0;i< Count;i ++)//遍历全部92种情况 
     {
     
    if(Queen[i][0]!=-1)//不是衍生解则打印 
    {
    cout<<"第"<<All<<"种："<<endl; 
	for(num = 0; num <8; num ++)   //遍历 
	{  
	 cout<<num+1<<"行"<<Queen[i][num]+1<<"列 ";
	 
     }
     cout<<endl;
     cout<<endl;
     All++;         
		 
    }  
}
  
}  
  
int determine(int i, int y)  //判断位置是否正确 
{  
    int x;  
    int num;  
  
    for(x = 0; x < i; x ++)    
	{  
        num = Q[x];  
  
        if(y == num||(x + num) == (i + y)||(x - num) == (i - y)) //在同一行、同一列、在斜线上 
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
        if(determine(x, i)) //位置正确 
		{  
		    Q[x]=i;
 
            
            if(7 == x) //全部 有合适位置 
			{  
                 
                for(j=0;j<8;j++)
                {
                	Queen[Count][j]=Q[j];//当前组位置存入数组 
                }
				Count ++; //结果数增加
  
                return;  
                
            }  
           
			
			eight_queen(x + 1);  //递归到后一个 
           Q[x] = 0;
//			Queen[Count][x]=Q[x];  
            
            
        }  
    }  
} 
int check(int a[],int b[])//判断是否是衍生解函数 
{
	int i,flag=1;
	
	for(i=0;i<8;i++)
	{
		if(b[i]!=a[i])//有不同则返回0； 
		{
			flag=0;
		}
	}
	if(flag==1)//是衍生解则返回1 
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
 
 for(i= 0;i< num-1;i++)//遍历所有解 
 {
 	if(Queen[i][0]!=-1)//是之前没有被排除的情况则进行比较 
 	{
 		for(j= 0;j< 8;j++)//求出这组位置的所有7种衍生解 
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

		 for(k= i+1;k< num;k++)//从全部位置情况中当前组的后一种 开始比较 
 			{  
 			   if(Queen[k][0]!=-1)//如果没有被排除过 
 			   {
	 			   	if(check(Queen[k],a)||check(Queen[k],b)||check(Queen[k],c)||check(Queen[k],d)||check(Queen[k],e)||check(Queen[k],f)||check(Queen[k],g))//进行比较，只要有一种满足情况就排除 
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
    eight_queen(0); //递归求所有位置情况 
    reduce();//排除衍生解 
	print();//打印 
    cout<<"一共 "<<All-1<<"种。"<<endl;  
    
    return 0;  
}  
