
/*����ͷ�ļ�*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*�궨��*/

#define MAXN 100+10

/*���Ͷ���*/

typedef char ElementType;//�����

struct TreeNode{//
    ElementType Element;
    struct TreeNode * Left;
    struct TreeNode * Right;
};

typedef struct TreeNode * NodeT;
typedef struct TreeNode * BinaryTree;


struct StackNode{//ջ���
    ElementType Element;
    struct StackNode * Next;
};

typedef struct StackNode * NodeS;
typedef NodeS Stack;

/*ջ�Ļ�������*/

int IsStackEmpty(Stack S){//�ж�ջ�Ƿ�Ϊ��
    return S->Next==NULL;
}

void Push(ElementType x,Stack &S){//��Ԫ��ѹջ
    NodeS temp;
    temp=(NodeS)malloc(sizeof(struct StackNode));
    if(S==NULL)
        printf("Push������ջָ��Ϊ��\n");
    else{
        temp->Element=x;
        temp->Next=S->Next;
        S->Next=temp;
    }
}

void Pop(Stack S){//����ջ��Ԫ��
    NodeS temp;
    if(IsStackEmpty(S)) printf("Pop������ջָ��Ϊ��\n");
    else{
        temp=S->Next;
        S->Next=S->Next->Next;
        free(temp);
    }
}

void DestoryStack(Stack S){//�ͷ�ջ���ڴ�ռ�
    if(S==NULL) printf("DestoryStack������ջָ��Ϊ��\n");
    else{
        while(!IsStackEmpty(S))
            Pop(S);
    }
}

Stack CreateStack(){//����ջ
    Stack S;
    S=(NodeS)malloc(sizeof(struct StackNode));
    if(S==NULL){
        printf("CreateStack��������������ڴ�ʧ��\n");
        exit(1);
    }
    else{
        S->Next=NULL;
        DestoryStack(S);
        return S;
    }
}

void PrintStack(Stack S){//��ӡջ
    if(S==NULL){
        printf("��ӡջʱ������ջ��������\n");
        return;
    }
    else S=S->Next;
    while (S!=NULL) {
        printf("%c",S->Element);
        S=S->Next;
    }
    printf("\n");
}

/*���Ļ�������*/

BinaryTree DestoryTree(BinaryTree T){//�ͷŶ������Ĵ洢�ռ�
    if (T!=NULL) {
        DestoryTree(T->Left);
        DestoryTree(T->Right);
        free(T);
    }
    return NULL;
}

/*�ͱ����йصĺ���*/

BinaryTree CreateBinaryTree(ElementType Pre[],long PreS,long PreE,ElementType In[],long InS,long InE){//����ǰ��������������������
    if(InS>InE) return NULL;
    
    long i;
    
    for (i=InS; i<InE&&In[i]!=Pre[PreS]; i++);
    
    if(i>InE){
        printf("�����ǰ�������������д������⣬������ֹ\n");
        exit(1);
    }
    
    NodeT temp=(NodeT)malloc(sizeof(struct TreeNode));
    if (temp==NULL) {
        printf("CreateBinaryTree������������ڴ�ʧ��\n");
        exit(1);
    }
    
    temp->Element=Pre[PreS];
    temp->Left=CreateBinaryTree(Pre, PreS+1, PreS+i-InS, In, InS, i-1);
    temp->Right=CreateBinaryTree(Pre, PreS+i-InS+1, PreE, In, i+1, InE);
    return temp;
}

void PrintPostOrder(BinaryTree T){//��ӡ��������Ľ��
    if(T!=NULL){
        PrintPostOrder(T->Left);
        PrintPostOrder(T->Right);
        printf("%c",T->Element);
    }
}

int TreeDepth(BinaryTree T){//�����������
    int Ldepth,Rdepth;
    if(T!=NULL){
        Ldepth=TreeDepth(T->Left);
        Rdepth=TreeDepth(T->Right);
        return Ldepth>=Rdepth?Ldepth+1:Rdepth+1;
    }
    return 0;
}

void PrintLevel(BinaryTree T,int Level){//��ӡ��������ĳһ��
    if(T==NULL||Level<0) return;
    if (Level==1) {
        printf("%c",T->Element);
        return;
    }
    PrintLevel(T->Left, Level-1);
    PrintLevel(T->Right, Level-1);
}

void LevelTra(BinaryTree T){//��α���������
    if(T==NULL) return;
    
    int i;
    
    for (i=1; i<TreeDepth(T)+1; i++)
        PrintLevel(T,i);
}

int FindTarget(BinaryTree T,Stack &S,ElementType target){//����Ŀ��Ԫ��
    if (T==NULL) return 0;
    
    if (T->Element==target) {
        Push(T->Element, S);//�ҵ��ý�㣬ѹջ
        return 1;
    }
    else{
        if(FindTarget(T->Left, S, target)){
            Push(T->Element, S);//ѹջ
            return 1;
        }
        if(FindTarget(T->Right, S, target)){
            Push(T->Element, S);//ѹջ
            return 1;
        }
        return 0;
    }
}

/*�����*/

int LengthEqual(ElementType Pre[],ElementType In[]){//�ж����ַ��������Ƿ����
    if(strlen(Pre)==strlen(In)) return 1;
    else{printf("�����ַ����Ȳ���\n");return 0;}
}

int AllUpper(ElementType Pre[],ElementType In[]){//�ж��ַ�����Ԫ���Ƿ��Ϊ��д��ĸ
    int i;
    for (i=0; i<strlen(Pre)&&(Pre[i]<='Z'&&Pre[i]>='A')&&(In[i]<='Z'&&In[i]>='A'); i++);
    if(i==strlen(Pre)) return 1;
    else{printf("�����ʽ���������ַ�Ӧ��Ϊ��д��ĸ\n");return 0;}
}

int NoRepeat(ElementType Pre[],ElementType In[]){//�ж��ַ������Ƿ����ظ�Ԫ��
    unsigned long i,j=strlen(Pre);
    for (i=0; i<strlen(Pre)&&j==strlen(Pre); i++)
        for (j=i+1; j<strlen(Pre)&&Pre[i]!=Pre[j]&&In[i]!=In[j]; j++);
    if(i==j&&i==strlen(Pre)) return 1;
    else{printf("�����ʽ������ĸ��Ӧ���ظ�\n");return 0;}
}

int AllCorresponding(ElementType Pre[],ElementType In[]){//�ж����ַ�����ĸ�Ƿ�ƥ��
    int Alphabet1[26],Alphabet2[26];
    int i;
    
    memset(Alphabet1, 0, sizeof(Alphabet1));
    memset(Alphabet2, 0, sizeof(Alphabet2));
    
    for (i=0; i<strlen(Pre); Alphabet1[Pre[i]-'A']=1,Alphabet2[In[i]-'A']=1,i++);
    for (i=0; i<26&&Alphabet1[i]==Alphabet2[i]; i++);
    
    if (i==26) return 1;
    else{printf("��������������ַ���ƥ��\n");return 0;}
    
}

int IsLegal(ElementType Pre[],ElementType In[]){//�ж������Ƿ�Ϸ�
    return LengthEqual(Pre,In)
        && AllUpper(Pre,In)
        && NoRepeat(Pre,In)
        && AllCorresponding(Pre,In);
}

/*������*/

int main(int argc, const char * argv[]) {
    ElementType Pre[MAXN],In[MAXN];//��¼ǰ����������
    ElementType target;//��¼���ҵ�Ŀ��Ԫ��
    
    BinaryTree T=NULL;
    Stack S=CreateStack();
    
    memset(Pre, '\0', sizeof(Pre));
    memset(In, '\0', sizeof(In));
    
    printf("������ö�������ǰ�������\n");
    scanf("%s%*c",Pre);
    printf("������ö����������������\n");
    scanf("%s%*c",In);
    
    if(IsLegal(Pre,In)){//�ж��Ƿ�Ϸ�����������
        T=CreateBinaryTree(Pre,0,strlen(Pre)-1,
                           In,0,strlen(In)-1);
        if (T==NULL) {
            printf("�����ǰ�������������п��ܴ��ڴ���,������ֹ\n");
            exit(1);
        }
    }
    else{
        printf("�������󣬳�����ֹ\n");
        return 0;
    }
    
    printf("�������Ϊ��\n");
    PrintPostOrder(T);printf("\n");
    printf("����α���Ϊ��\n");
    LevelTra(T);printf("\n");
    
    printf("������Ҫ���ҵĽ��ֵ��\n");
    scanf("%c%*c",&target);
    if(FindTarget(T,S,target)){
        printf("·��Ϊ��\n");
        PrintStack(S);
    }
    else printf("δ�ҵ�Ŀ��Ԫ��\n");
    
    DestoryTree(T);//���ٶ�̬������ڴ�ռ�
    DestoryStack(S);
    
    return 0;
}
