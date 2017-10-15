/*C++程序设计；      实验六 1、流式IO（一）；     format:2015-09-13；     coder：曹桢；      class：2014211302；     studentID:2014211182*/
#include<iostream>
#include<fstream>
#include<iomanip>
#include<climits>
using namespace std;
int main()
{
	ofstream outfile1("file1.txt");                            	//定义文件流对象，用构造函数打开文件，若不存在则新建 
	if(!outfile1){												//若打开文件不成功，则输出提示并退出 
		cout<<"failed to open file1.txt!"<<endl;
		exit(0);
	}
	else{														//打开文件成功 
		int a;
		unsigned int b; 
		long int c;
		float d;
		char ch[80];
		
		cout<<"Please input an int: ";
		cin>>a;
		cin.clear();											//清空缓冲区 
		cin.ignore(1024,'\n');
		cout<<"Please input an unsigned int: ";
		cin>>b;
		cin.clear();											//清空缓冲区 
		cin.ignore(1024,'\n');
		cout<<"Please input a long int: ";
		cin>>c;
		cin.clear();											//清空缓冲区 
		cin.ignore(1024,'\n');
		cout<<"Please input a float: ";
		cin>>d;
		cin.clear();											//清空缓冲区
		cin.ignore(1024,'\n');
		cout<<"Please input a string: ";
		cin>>ch;
		outfile1<<a<<endl;
		outfile1<<b<<endl;
		outfile1<<c<<endl;
		outfile1<<d<<endl;
		outfile1<<ch<<endl;
		outfile1<<"dec: "<<dec<<b<<endl;						//十进制 
		outfile1<<"oct: "<<oct<<b<<endl;						//八进制 
		outfile1<<"hex: "<<hex<<b<<endl;						//十六进制 
		outfile1<<setiosflags(ios::fixed)<<setprecision(6)<<d<<endl;						//设置浮点数位数
		outfile1<<setw(10)<<dec<<a<<endl;						//设置整型宽度 
		outfile1.close();										//关闭文件 
	}
	return 0;
}
