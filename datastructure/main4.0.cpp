
/*包含头文件*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*宏定义*/

#define MAXN 100+10

/*类型定义*/

typedef char ElementType;//树结点

struct TreeNode{//
    ElementType Element;
    struct TreeNode * Left;
    struct TreeNode * Right;
};

typedef struct TreeNode * NodeT;
typedef struct TreeNode * BinaryTree;


struct StackNode{//栈结点
    ElementType Element;
    struct StackNode * Next;
};

typedef struct StackNode * NodeS;
typedef NodeS Stack;

/*栈的基本操作*/

int IsStackEmpty(Stack S){//判断栈是否为空
    return S->Next==NULL;
}

void Push(ElementType x,Stack &S){//将元素压栈
    NodeS temp;
    temp=(NodeS)malloc(sizeof(struct StackNode));
    if(S==NULL)
        printf("Push函数中栈指针为空\n");
    else{
        temp->Element=x;
        temp->Next=S->Next;
        S->Next=temp;
    }
}

void Pop(Stack S){//弹出栈顶元素
    NodeS temp;
    if(IsStackEmpty(S)) printf("Pop函数中栈指针为空\n");
    else{
        temp=S->Next;
        S->Next=S->Next->Next;
        free(temp);
    }
}

void DestoryStack(Stack S){//释放栈的内存空间
    if(S==NULL) printf("DestoryStack函数中栈指针为空\n");
    else{
        while(!IsStackEmpty(S))
            Pop(S);
    }
}

Stack CreateStack(){//创建栈
    Stack S;
    S=(NodeS)malloc(sizeof(struct StackNode));
    if(S==NULL){
        printf("CreateStack函数中申请堆区内存失败\n");
        exit(1);
    }
    else{
        S->Next=NULL;
        DestoryStack(S);
        return S;
    }
}

void PrintStack(Stack S){//打印栈
    if(S==NULL){
        printf("打印栈时，发现栈并不存在\n");
        return;
    }
    else S=S->Next;
    while (S!=NULL) {
        printf("%c",S->Element);
        S=S->Next;
    }
    printf("\n");
}

/*树的基本操作*/

BinaryTree DestoryTree(BinaryTree T){//释放二叉树的存储空间
    if (T!=NULL) {
        DestoryTree(T->Left);
        DestoryTree(T->Right);
        free(T);
    }
    return NULL;
}

/*和本题有关的函数*/

BinaryTree CreateBinaryTree(ElementType Pre[],long PreS,long PreE,ElementType In[],long InS,long InE){//根据前序和中序遍历创建二叉树
    if(InS>InE) return NULL;
    
    long i;
    
    for (i=InS; i<InE&&In[i]!=Pre[PreS]; i++);
    
    if(i>InE){
        printf("输入的前序和中序遍历序列存在问题，程序终止\n");
        exit(1);
    }
    
    NodeT temp=(NodeT)malloc(sizeof(struct TreeNode));
    if (temp==NULL) {
        printf("CreateBinaryTree函数申请堆区内存失败\n");
        exit(1);
    }
    
    temp->Element=Pre[PreS];
    temp->Left=CreateBinaryTree(Pre, PreS+1, PreS+i-InS, In, InS, i-1);
    temp->Right=CreateBinaryTree(Pre, PreS+i-InS+1, PreE, In, i+1, InE);
    return temp;
}

void PrintPostOrder(BinaryTree T){//打印后序遍历的结果
    if(T!=NULL){
        PrintPostOrder(T->Left);
        PrintPostOrder(T->Right);
        printf("%c",T->Element);
    }
}

int TreeDepth(BinaryTree T){//计算树的深度
    int Ldepth,Rdepth;
    if(T!=NULL){
        Ldepth=TreeDepth(T->Left);
        Rdepth=TreeDepth(T->Right);
        return Ldepth>=Rdepth?Ldepth+1:Rdepth+1;
    }
    return 0;
}

void PrintLevel(BinaryTree T,int Level){//打印二叉树的某一层
    if(T==NULL||Level<0) return;
    if (Level==1) {
        printf("%c",T->Element);
        return;
    }
    PrintLevel(T->Left, Level-1);
    PrintLevel(T->Right, Level-1);
}

void LevelTra(BinaryTree T){//层次遍历二叉树
    if(T==NULL) return;
    
    int i;
    
    for (i=1; i<TreeDepth(T)+1; i++)
        PrintLevel(T,i);
}

int FindTarget(BinaryTree T,Stack &S,ElementType target){//查找目标元素
    if (T==NULL) return 0;
    
    if (T->Element==target) {
        Push(T->Element, S);//找到该结点，压栈
        return 1;
    }
    else{
        if(FindTarget(T->Left, S, target)){
            Push(T->Element, S);//压栈
            return 1;
        }
        if(FindTarget(T->Right, S, target)){
            Push(T->Element, S);//压栈
            return 1;
        }
        return 0;
    }
}

/*检错函数*/

int LengthEqual(ElementType Pre[],ElementType In[]){//判读两字符串长度是否相等
    if(strlen(Pre)==strlen(In)) return 1;
    else{printf("输入字符长度不等\n");return 0;}
}

int AllUpper(ElementType Pre[],ElementType In[]){//判断字符串中元素是否均为大写字母
    int i;
    for (i=0; i<strlen(Pre)&&(Pre[i]<='Z'&&Pre[i]>='A')&&(In[i]<='Z'&&In[i]>='A'); i++);
    if(i==strlen(Pre)) return 1;
    else{printf("输入格式错误，输入字符应均为大写字母\n");return 0;}
}

int NoRepeat(ElementType Pre[],ElementType In[]){//判断字符串中是否有重复元素
    unsigned long i,j=strlen(Pre);
    for (i=0; i<strlen(Pre)&&j==strlen(Pre); i++)
        for (j=i+1; j<strlen(Pre)&&Pre[i]!=Pre[j]&&In[i]!=In[j]; j++);
    if(i==j&&i==strlen(Pre)) return 1;
    else{printf("输入格式错误，字母不应有重复\n");return 0;}
}

int AllCorresponding(ElementType Pre[],ElementType In[]){//判断两字符串字母是否匹配
    int Alphabet1[26],Alphabet2[26];
    int i;
    
    memset(Alphabet1, 0, sizeof(Alphabet1));
    memset(Alphabet2, 0, sizeof(Alphabet2));
    
    for (i=0; i<strlen(Pre); Alphabet1[Pre[i]-'A']=1,Alphabet2[In[i]-'A']=1,i++);
    for (i=0; i<26&&Alphabet1[i]==Alphabet2[i]; i++);
    
    if (i==26) return 1;
    else{printf("输入的两个序列字符不匹配\n");return 0;}
    
}

int IsLegal(ElementType Pre[],ElementType In[]){//判断输入是否合法
    return LengthEqual(Pre,In)
        && AllUpper(Pre,In)
        && NoRepeat(Pre,In)
        && AllCorresponding(Pre,In);
}

/*主函数*/

int main(int argc, const char * argv[]) {
    ElementType Pre[MAXN],In[MAXN];//记录前序和中序遍历
    ElementType target;//记录查找的目标元素
    
    BinaryTree T=NULL;
    Stack S=CreateStack();
    
    memset(Pre, '\0', sizeof(Pre));
    memset(In, '\0', sizeof(In));
    
    printf("请输入该二叉树的前序遍历：\n");
    scanf("%s%*c",Pre);
    printf("请输入该二叉树的中序遍历：\n");
    scanf("%s%*c",In);
    
    if(IsLegal(Pre,In)){//判断是否合法并构建概树
        T=CreateBinaryTree(Pre,0,strlen(Pre)-1,
                           In,0,strlen(In)-1);
        if (T==NULL) {
            printf("输入的前序和中序遍历序列可能存在错误,程序终止\n");
            exit(1);
        }
    }
    else{
        printf("输入有误，程序终止\n");
        return 0;
    }
    
    printf("后序遍历为：\n");
    PrintPostOrder(T);printf("\n");
    printf("按层次遍历为：\n");
    LevelTra(T);printf("\n");
    
    printf("请输入要查找的结点值：\n");
    scanf("%c%*c",&target);
    if(FindTarget(T,S,target)){
        printf("路径为：\n");
        PrintStack(S);
    }
    else printf("未找到目标元素\n");
    
    DestoryTree(T);//销毁动态分配的内存空间
    DestoryStack(S);
    
    return 0;
}
