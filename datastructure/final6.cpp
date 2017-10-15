

/*包含头文件*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*常量定义*/

#define MAXN 10000

/*类型定义*/

typedef int ElementType;

/*声明数组*/

int A1[MAXN],A2[MAXN],B1[MAXN],B2[MAXN],C1[MAXN],C2[MAXN];

/*排序函数及相关子函数*/

void InsertSort(ElementType A[],int begin, int end){//插入排序
    int i,j;
    ElementType temp;
    for (i=begin+1; i<end-begin+1; i++) {
        temp=A[i];
        for (j=i; j>0&&A[j-1]>temp; j--)
            A[j]=A[j-1];
        A[j]=temp;
    }
}

void QuickSort(int A[],int begin,int end,int flag){//普通快速排序
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
        if(i-1-begin<=20) InsertSort(A, begin, i-1);//长度小于20直接插入排序
        else QuickSort(A, begin, i-1, 0);
    }
    if(end>i+1){
        if(end-i-1<=20) InsertSort(A, i+1, end);//长度小于20直接插入排序
        else QuickSort(A, i+1, end, 0);
    }
    if(flag) printf("普通快速排序的运行时间为：%f 秒\n",(double)(clock()-start)/CLOCKS_PER_SEC);
}

void BitSwap(int & a,int & b){//位运算实现交换
    a=a^b; b=b^a; a=a^b;
}

int SelectMiddle(int A[],int begin,int end){//选取中间的枢纽元素
    int middle=begin+((end-begin)>>1);
    if(A[middle]>A[end]) BitSwap(A[middle], A[end]);
    if(A[begin]>A[end]) BitSwap(A[begin], A[end]);
    if(A[middle]>A[begin]) BitSwap(A[middle], A[begin]);
    return A[begin];
    
}

void SelectQuickSort(int A[],int begin,int end,int flag){//三者取中法优化后的快速排序
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
        if(i-1-begin<=20) InsertSort(A, begin, i-1);//长度小于20直接插入排序
        else QuickSort(A, begin, i-1, 0);
    }
    if(end>i+1){
        if(end-i-1<=20) InsertSort(A, i+1, end);//长度小于20直接插入排序
        else QuickSort(A, i+1, end, 0);
    }
    if(flag) printf("三者取中优化后的快速排序的运行时间为：%f 秒\n",(double)(clock()-start)/CLOCKS_PER_SEC);
}

void CreateArray(){//对数组赋值
    int i;
    time_t t;
    srand((unsigned)time(&t));
    for (i=0; i<10000; i++) {
        A1[i]=i;        A2[i]=A1[i];//正序
        B1[i]=10000-i;  B2[i]=B1[i];//逆序
        C1[i]=rand();   C2[i]=C1[i];//随机
    }
}

/*主函数*/

int main(int argc, const char * argv[]) {
    
    CreateArray();//对数组赋值
    
    printf("待排序列为：长度为10000的顺序数组\n");
    QuickSort(A1, 0, 10000-1, 1);
    SelectQuickSort(A2, 0, 10000-1, 1);
    
    printf("\n待排序列为：长度为10000的逆序数组\n");
    QuickSort(B1, 0, 10000-1, 1);
    SelectQuickSort(B2, 0, 10000-1, 1);
    
    printf("\n待排序列为：长度为10000的，由随机数组成的数组\n");
    QuickSort(C1, 0, 10000-1, 1);
    SelectQuickSort(C2, 0, 10000-1, 1);
    
    return 0;
}
