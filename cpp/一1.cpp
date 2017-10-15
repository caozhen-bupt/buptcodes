/*C++程序设计；      实验一 1、猜价格游戏；     format:2015-09-10；     coder：曹桢；      class：2014211302；     studentID:2014211182*/ 
#include<iostream>
#include<time.h>												/*由于使用了time（）库函数*/ 
#include<stdlib.h>												/*由于使用了随机数*/ 
#include<string.h>												//由于调用了strlen()函数 
using namespace std;											/*命名空间的使用*/
																/*定义函数用于判断这个输入的字符串是否是一个合法整数；是则返回1，不是则返回0；传入参数数组及数组的位数*/ 
int judgeNum(char *validnum, int n)
{
	int result, i, flag;
	for(i=0, flag=1; flag==1 && validnum[i]!='\0' ;i++){
		if(validnum[i] < '0' || validnum[i] > '9'){
			flag=0;
		}
	}
	result=flag;
	return result;
}
int main()
{
	int num, guessNum = -1, i, n, flag;							/*num是数字的大小，guessNum是用户猜测的数字*/
	char *validnum;
	validnum=new char[n];
	if(validnum == 0){
		cout<<"failed to distribute space to array."<<endl;
		exit(0);
	}
	else{
	
																/*用随机种子和随机数设置num的大小*/
		srand(time(NULL));
		num = rand()%1000+1;
		
		cout<<"Please input the number you guess, which is between 1 and 1000."<<endl;
																/*循环读入用户猜测的数字，与num比较并提示，直到相等*/
		for(; guessNum != num; ){
			cin>>validnum;										//读入用户猜测的数 
			n=strlen(validnum);									//n为数组大小 
			flag=judgeNum(validnum, n);							//调用函数 
																/*输入数据合法*/ 
			if(flag == 1){
																/*将合法数据从字符串转化成整型*/ 
				for(i = 0, guessNum = 0; i < n; i++){
					guessNum = guessNum*10+(validnum[i]-'0');
				}
				if(guessNum > 1000 || guessNum < 1){
					cout<<"Please note that the number you input should be from 1 to 1000."<<endl;
				}
				else{
					if(guessNum < num){
						cout<<"The number you guessed is smaller than the one.Please input a bigger number."<<endl;
					}
					else if(guessNum > num){
						cout<<"The number you guessed is bigger than the one.Please input a smaller number."<<endl;
					}
				}
			}
																/*输入数据不合法*/ 
			else if(flag == 0)
			{
				cout<<"Please input a valid number."<<endl;
			}
		}
																/*猜中*/
		cout<<"You are correct! Congratulations!"<<endl;
		delete [] validnum;
	}
	return 0;
}
