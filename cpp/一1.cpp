/*C++������ƣ�      ʵ��һ 1���¼۸���Ϸ��     format:2015-09-10��     coder�����壻      class��2014211302��     studentID:2014211182*/ 
#include<iostream>
#include<time.h>												/*����ʹ����time�����⺯��*/ 
#include<stdlib.h>												/*����ʹ���������*/ 
#include<string.h>												//���ڵ�����strlen()���� 
using namespace std;											/*�����ռ��ʹ��*/
																/*���庯�������ж����������ַ����Ƿ���һ���Ϸ����������򷵻�1�������򷵻�0������������鼰�����λ��*/ 
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
	int num, guessNum = -1, i, n, flag;							/*num�����ֵĴ�С��guessNum���û��²������*/
	char *validnum;
	validnum=new char[n];
	if(validnum == 0){
		cout<<"failed to distribute space to array."<<endl;
		exit(0);
	}
	else{
	
																/*��������Ӻ����������num�Ĵ�С*/
		srand(time(NULL));
		num = rand()%1000+1;
		
		cout<<"Please input the number you guess, which is between 1 and 1000."<<endl;
																/*ѭ�������û��²�����֣���num�Ƚϲ���ʾ��ֱ�����*/
		for(; guessNum != num; ){
			cin>>validnum;										//�����û��²���� 
			n=strlen(validnum);									//nΪ�����С 
			flag=judgeNum(validnum, n);							//���ú��� 
																/*�������ݺϷ�*/ 
			if(flag == 1){
																/*���Ϸ����ݴ��ַ���ת��������*/ 
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
																/*�������ݲ��Ϸ�*/ 
			else if(flag == 0)
			{
				cout<<"Please input a valid number."<<endl;
			}
		}
																/*����*/
		cout<<"You are correct! Congratulations!"<<endl;
		delete [] validnum;
	}
	return 0;
}
