/*C++������ƣ�      ʵ���� 1����ʽIO��һ����     format:2015-09-13��     coder�����壻      class��2014211302��     studentID:2014211182*/
#include<iostream>
#include<fstream>
#include<iomanip>
#include<climits>
using namespace std;
int main()
{
	ofstream outfile1("file1.txt");                            	//�����ļ��������ù��캯�����ļ��������������½� 
	if(!outfile1){												//�����ļ����ɹ����������ʾ���˳� 
		cout<<"failed to open file1.txt!"<<endl;
		exit(0);
	}
	else{														//���ļ��ɹ� 
		int a;
		unsigned int b; 
		long int c;
		float d;
		char ch[80];
		
		cout<<"Please input an int: ";
		cin>>a;
		cin.clear();											//��ջ����� 
		cin.ignore(1024,'\n');
		cout<<"Please input an unsigned int: ";
		cin>>b;
		cin.clear();											//��ջ����� 
		cin.ignore(1024,'\n');
		cout<<"Please input a long int: ";
		cin>>c;
		cin.clear();											//��ջ����� 
		cin.ignore(1024,'\n');
		cout<<"Please input a float: ";
		cin>>d;
		cin.clear();											//��ջ�����
		cin.ignore(1024,'\n');
		cout<<"Please input a string: ";
		cin>>ch;
		outfile1<<a<<endl;
		outfile1<<b<<endl;
		outfile1<<c<<endl;
		outfile1<<d<<endl;
		outfile1<<ch<<endl;
		outfile1<<"dec: "<<dec<<b<<endl;						//ʮ���� 
		outfile1<<"oct: "<<oct<<b<<endl;						//�˽��� 
		outfile1<<"hex: "<<hex<<b<<endl;						//ʮ������ 
		outfile1<<setiosflags(ios::fixed)<<setprecision(6)<<d<<endl;						//���ø�����λ��
		outfile1<<setw(10)<<dec<<a<<endl;						//�������Ϳ�� 
		outfile1.close();										//�ر��ļ� 
	}
	return 0;
}
