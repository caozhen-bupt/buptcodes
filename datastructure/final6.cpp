

/*����ͷ�ļ�*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*��������*/

#define MAXN 10000

/*���Ͷ���*/

typedef int ElementType;

/*��������*/

int A1[MAXN],A2[MAXN],B1[MAXN],B2[MAXN],C1[MAXN],C2[MAXN];

/*������������Ӻ���*/

void InsertSort(ElementType A[],int begin, int end){//��������
    int i,j;
    ElementType temp;
    for (i=begin+1; i<end-begin+1; i++) {
        temp=A[i];
        for (j=i; j>0&&A[j-1]>temp; j--)
            A[j]=A[j-1];
        A[j]=temp;
    }
}

void QuickSort(int A[],int begin,int end,int flag){//��ͨ��������
    clock_t start=clock();
    int i=begin,j=end;
    int temp=A[i];
    while (i<j) {
        while (A[j]>=temp&&i<j)
            j--;
        A[i]=A[j];
        while (A[i]<=temp&&i<j)
            i++;
        A[j]=A[i];
    }
    A[i]=temp;
    if(i-1>begin){
        if(i-1-begin<=20) InsertSort(A, begin, i-1);//����С��20ֱ�Ӳ�������
        else QuickSort(A, begin, i-1, 0);
    }
    if(end>i+1){
        if(end-i-1<=20) InsertSort(A, i+1, end);//����С��20ֱ�Ӳ�������
        else QuickSort(A, i+1, end, 0);
    }
    if(flag) printf("��ͨ�������������ʱ��Ϊ��%f ��\n",(double)(clock()-start)/CLOCKS_PER_SEC);
}

void BitSwap(int & a,int & b){//λ����ʵ�ֽ���
    a=a^b; b=b^a; a=a^b;
}

int SelectMiddle(int A[],int begin,int end){//ѡȡ�м����ŦԪ��
    int middle=begin+((end-begin)>>1);
    if(A[middle]>A[end]) BitSwap(A[middle], A[end]);
    if(A[begin]>A[end]) BitSwap(A[begin], A[end]);
    if(A[middle]>A[begin]) BitSwap(A[middle], A[begin]);
    return A[begin];
    
}

void SelectQuickSort(int A[],int begin,int end,int flag){//����ȡ�з��Ż���Ŀ�������
    clock_t start=clock();
    int i=begin,j=end;
    int temp=SelectMiddle(A,begin,end);
    while (i<j) {
        while (A[j]>=temp&&i<j)
            j--;
        A[i]=A[j];
        while (A[i]<=temp&&i<j)
            i++;
        A[j]=A[i];
    }
    A[i]=temp;
    if(i-1>begin){
        if(i-1-begin<=20) InsertSort(A, begin, i-1);//����С��20ֱ�Ӳ�������
        else QuickSort(A, begin, i-1, 0);
    }
    if(end>i+1){
        if(end-i-1<=20) InsertSort(A, i+1, end);//����С��20ֱ�Ӳ�������
        else QuickSort(A, i+1, end, 0);
    }
    if(flag) printf("����ȡ���Ż���Ŀ������������ʱ��Ϊ��%f ��\n",(double)(clock()-start)/CLOCKS_PER_SEC);
}

void CreateArray(){//�����鸳ֵ
    int i;
    time_t t;
    srand((unsigned)time(&t));
    for (i=0; i<10000; i++) {
        A1[i]=i;        A2[i]=A1[i];//����
        B1[i]=10000-i;  B2[i]=B1[i];//����
        C1[i]=rand();   C2[i]=C1[i];//���
    }
}

/*������*/

int main(int argc, const char * argv[]) {
    
    CreateArray();//�����鸳ֵ
    
    printf("��������Ϊ������Ϊ10000��˳������\n");
    QuickSort(A1, 0, 10000-1, 1);
    SelectQuickSort(A2, 0, 10000-1, 1);
    
    printf("\n��������Ϊ������Ϊ10000����������\n");
    QuickSort(B1, 0, 10000-1, 1);
    SelectQuickSort(B2, 0, 10000-1, 1);
    
    printf("\n��������Ϊ������Ϊ10000�ģ����������ɵ�����\n");
    QuickSort(C1, 0, 10000-1, 1);
    SelectQuickSort(C2, 0, 10000-1, 1);
    
    return 0;
}
