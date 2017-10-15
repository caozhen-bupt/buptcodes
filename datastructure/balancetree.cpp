/*ͷ�ļ�*/ 

#include <iostream> 
#include <malloc.h> 

using namespace std; 

/*��������*/
  
#define LH +1  //��������   
#define EH 0   //�����ȸ�   
#define RH -1  //��������  

/*�������ṹ���嶨�� */ 
 
typedef struct BSTNode{   
   int data;   
   int bf;     //����ƽ������    
   struct BSTNode *lchild,*rchild; //���Һ���ָ��    
}BSTNode,*BSTree; 

  
/*����������*/  
 
void R_Rotate(BSTree &p)      
{   
    BSTree lc=p->lchild;  //lcָ���p�������������    
    p->lchild=lc->rchild; //lc���������ҽ�Ϊp��������    
    lc->rchild=p;        //pָ���µĸ����    
    p=lc;   
}   


/*����������*/ 
 
void L_Rotate(BSTree &p)
{   
    BSTree rc=p->rchild;   
    p->rchild=rc->lchild;//rcָ���p�������������    
    rc->lchild=p;        //rc���������ҽ�Ϊp��������    
    p=rc;                //pָ���µĸ����   
}   


/*��ƽ����ת����*/

void LeftBalance(BSTree &T)    
{   
    BSTree lc,rd;   
    lc=T->lchild;  //lcָ��T�������������    
    switch(lc->bf){//���T����������ƽ���,������Ӧ��ƽ�⴦��    
       case LH:    //�½�������T�����ӵ���������,������������    
          T->bf=lc->bf=EH;   
          R_Rotate(T);   
          break;   
       case RH:    //�½�������T�����ӵ���������,��˫������    
          rd=lc->rchild;   
          switch(rd->bf){  //�޸�T�������ӵ�ƽ������    
             case LH://��� 
				 T->bf=RH;
				 lc->bf=EH;
				 break;  
				  
             case EH://ƽ�� 
				 T->bf=lc->bf=EH;
				 break;   
				 
             case RH://�Ҹ� 
				 T->bf=EH;
				 lc->bf=LH;
				 break;   
          }   
          rd->bf=EH;   
          L_Rotate(T->lchild);   
          R_Rotate(T);   
          break;   
    }   
}   


/*��ƽ����ת����*/ 
 
void RightBalance(BSTree &T)  
{   
     BSTree rc,ld;   
     rc=T->rchild;//rcָ��*T�������������   
     switch(rc->bf){//���*T����������ƽ���,������Ӧ��ƽ�⴦��    
        case RH://�½�������*T���Һ��ӵ���������,������������    
           T->bf=rc->bf=EH;   
           L_Rotate(T);   
           break;   
        case LH://�½�������*T���Һ��ӵ���������,��˫������    
           ld=rc->lchild;   
           switch(ld->bf){//�޸�*T�������ӵ�ƽ������   
              case LH://��� 
				  T->bf=EH;
				  rc->bf=RH;
				  break;   
				  
              case EH://ƽ�� 
				  T->bf=rc->bf=EH;
				  break; 
				    
              case RH://�Ҹ� 
				  T->bf=LH;
				  rc->bf=EH;
				  break;   
           }   
           ld->bf=EH;   
           R_Rotate(T->rchild);   
           L_Rotate(T);   
           break;   
     }   
}  

/*����ƽ����������� */

int InsertAVL(BSTree &T,int e,int &taller)   
{   
    if(!T){        //�����½��   
       T=(BSTree)malloc(sizeof(BSTNode));   
       T->data=e;   
       T->lchild=T->rchild=NULL; 
		 
       T->bf=EH;   
       taller=1;   
    }   
    else{   
       if(T->data==e){ //�����Ѵ��ں�e��ͬ�Ĺؼ��ֵĽ��    
          taller=0;    //������    
          return 0;    
       }   
       if(T->data>e){  //������T���������н�������    
          if(!InsertAVL(T->lchild,e,taller))   
             return 0; //δ����    
          if(taller){  //�Ѳ��뵽T����������������������    
             switch(T->bf){ //���T��ƽ���    
                case LH: //ԭ������������������,����ƽ�⴦��    
                   LeftBalance(T);   
                   taller=0;   
                   break;   
                case EH: //ԭ�����������ȸ�,�������������߶�ʹ������    
                   T->bf=LH;   
                   taller=1;   
                   break;   
                case RH: //ԭ������������������,�������������ȸ�    
                   T->bf=EH;   
                   taller=0;   
                   break;   
             }   
          }   
       }   
       else{        //������T���������н�������    
          if(!InsertAVL(T->rchild,e,taller))   
             return 0; //δ����    
          if(taller){ //�Ѳ��뵽T����������������������   
             switch(T->bf){ //���T��ƽ���   
                case LH:  //ԭ������������������,�������������ȸ�     
                   T->bf=EH;   
                   taller=0;   
                   break;   
                case EH: //ԭ�����������ȸ�,�������������߶�ʹ������    
                   T->bf=RH;   
                   taller=1;   
                   break;   
                case RH:  //ԭ������������������,����ƽ�⴦��    
                   RightBalance(T);   
                   taller=0;   
                   break;   
             }   
          }   
       }   
    }   
    return 1;   
}   
   

/*���ʽ�㺯��*/

void visit(int a) 
{
	cout<<a<<" ";
}

/*�����������ӡ����*/
	 
void PrintTree(BSTree T)
	 {
	 	if(T)
	 	{
	 		
	 		PrintTree(T->rchild);
	 		visit(T->data);
	 		PrintTree(T->lchild);
	 	}
	 }
	 
	  
/*������	*/ 

int main()    
{   
    BSTree T=NULL;   
       
    int total=0,taller,input[50],i=0; 
    cout<<"Please input the key words sequence:(end by -1)"<<endl;//��ʾ����  
     
    cin>>input[0];    
    while(input[i]!=-1){         //��ȡ�ؼ��� ��������   
       i++;   
       cin>>input[i];   
    }   
    i=0;    
    while(input[i]!=-1){   
        taller=0;                //��ʼ��   
        if(InsertAVL(T,input[i],taller)){   //����һ���ؼ���    
          total++;   
          cout<<"Enter No."<<total<<"element"<<endl;    
          PrintTree(T);          //�������ӡ��    
          cout<<endl;   
        }   
        i++;   
    }   
    system("pause");   
    return 0;   
}   
