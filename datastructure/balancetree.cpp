/*头文件*/ 

#include <iostream> 
#include <malloc.h> 

using namespace std; 

/*常量定义*/
  
#define LH +1  //左子树高   
#define EH 0   //子树等高   
#define RH -1  //右子树高  

/*二叉树结构体体定义 */ 
 
typedef struct BSTNode{   
   int data;   
   int bf;     //结点的平衡因子    
   struct BSTNode *lchild,*rchild; //左右孩子指针    
}BSTNode,*BSTree; 

  
/*右旋处理函数*/  
 
void R_Rotate(BSTree &p)      
{   
    BSTree lc=p->lchild;  //lc指向的p的左子树根结点    
    p->lchild=lc->rchild; //lc的右子树挂接为p的左子树    
    lc->rchild=p;        //p指向新的根结点    
    p=lc;   
}   


/*左旋处理函数*/ 
 
void L_Rotate(BSTree &p)
{   
    BSTree rc=p->rchild;   
    p->rchild=rc->lchild;//rc指向的p的右子树根结点    
    rc->lchild=p;        //rc的左子树挂接为p的右子树    
    p=rc;                //p指向新的根结点   
}   


/*左平衡旋转函数*/

void LeftBalance(BSTree &T)    
{   
    BSTree lc,rd;   
    lc=T->lchild;  //lc指向T的左子树根结点    
    switch(lc->bf){//检查T的左子树的平衡度,并作相应的平衡处理    
       case LH:    //新结点插入在T的左孩子的左子树上,作单右旋处理    
          T->bf=lc->bf=EH;   
          R_Rotate(T);   
          break;   
       case RH:    //新结点插入在T的左孩子的右子树上,做双旋处理    
          rd=lc->rchild;   
          switch(rd->bf){  //修改T及其左孩子的平衡因子    
             case LH://左高 
				 T->bf=RH;
				 lc->bf=EH;
				 break;  
				  
             case EH://平衡 
				 T->bf=lc->bf=EH;
				 break;   
				 
             case RH://右高 
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


/*右平衡旋转函数*/ 
 
void RightBalance(BSTree &T)  
{   
     BSTree rc,ld;   
     rc=T->rchild;//rc指向*T的右子树根结点   
     switch(rc->bf){//检查*T的右子树的平衡度,并作相应的平衡处理    
        case RH://新结点插入在*T的右孩子的右子树上,作单左旋处理    
           T->bf=rc->bf=EH;   
           L_Rotate(T);   
           break;   
        case LH://新结点插入在*T的右孩子的左子树上,做双旋处理    
           ld=rc->lchild;   
           switch(ld->bf){//修改*T及其左孩子的平衡因子   
              case LH://左高 
				  T->bf=EH;
				  rc->bf=RH;
				  break;   
				  
              case EH://平衡 
				  T->bf=rc->bf=EH;
				  break; 
				    
              case RH://右高 
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

/*创建平衡二叉树函数 */

int InsertAVL(BSTree &T,int e,int &taller)   
{   
    if(!T){        //插入新结点   
       T=(BSTree)malloc(sizeof(BSTNode));   
       T->data=e;   
       T->lchild=T->rchild=NULL; 
		 
       T->bf=EH;   
       taller=1;   
    }   
    else{   
       if(T->data==e){ //树中已存在和e相同的关键字的结点    
          taller=0;    //不插入    
          return 0;    
       }   
       if(T->data>e){  //继续在T的左子树中进行搜索    
          if(!InsertAVL(T->lchild,e,taller))   
             return 0; //未插入    
          if(taller){  //已插入到T的左子树中且左子树长高    
             switch(T->bf){ //检查T的平衡度    
                case LH: //原来左子树比右子树高,做左平衡处理    
                   LeftBalance(T);   
                   taller=0;   
                   break;   
                case EH: //原来左右子树等高,现因左子树长高而使树增高    
                   T->bf=LH;   
                   taller=1;   
                   break;   
                case RH: //原来右子树比左子树高,现在左右子树等高    
                   T->bf=EH;   
                   taller=0;   
                   break;   
             }   
          }   
       }   
       else{        //继续在T的右子树中进行搜索    
          if(!InsertAVL(T->rchild,e,taller))   
             return 0; //未插入    
          if(taller){ //已插入到T的右子树中且右子树长高   
             switch(T->bf){ //检查T的平衡度   
                case LH:  //原来左子树比右子树高,现在左右子树等高     
                   T->bf=EH;   
                   taller=0;   
                   break;   
                case EH: //原来左右子树等高,现因右子树长高而使树增高    
                   T->bf=RH;   
                   taller=1;   
                   break;   
                case RH:  //原来右子树比左子树高,做右平衡处理    
                   RightBalance(T);   
                   taller=0;   
                   break;   
             }   
          }   
       }   
    }   
    return 1;   
}   
   

/*访问结点函数*/

void visit(int a) 
{
	cout<<a<<" ";
}

/*逆中序遍历打印函数*/
	 
void PrintTree(BSTree T)
	 {
	 	if(T)
	 	{
	 		
	 		PrintTree(T->rchild);
	 		visit(T->data);
	 		PrintTree(T->lchild);
	 	}
	 }
	 
	  
/*主函数	*/ 

int main()    
{   
    BSTree T=NULL;   
       
    int total=0,taller,input[50],i=0; 
    cout<<"Please input the key words sequence:(end by -1)"<<endl;//提示输入  
     
    cin>>input[0];    
    while(input[i]!=-1){         //读取关键字 存入数组   
       i++;   
       cin>>input[i];   
    }   
    i=0;    
    while(input[i]!=-1){   
        taller=0;                //初始化   
        if(InsertAVL(T,input[i],taller)){   //插入一个关键字    
          total++;   
          cout<<"Enter No."<<total<<"element"<<endl;    
          PrintTree(T);          //逆中序打印树    
          cout<<endl;   
        }   
        i++;   
    }   
    system("pause");   
    return 0;   
}   
