/*C++程序设计；      实验六 3、流式IO（三）；     format:2015-09-14；     coder：曹桢；      class：2014211302；     studentID:2014211182*/
#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdlib>
using namespace std;
int main()
{
	char infname[256], outfname[256];
	ifstream infile;													//定义文件流对象 ，读文件 
	ofstream outfile;													//定义文件流对象 ，写文件 
	char str[80];
	int count;
	
	cout<<"Please input the name of the infile:";
	cin>>infname;
	infile.open(infname);												//使用成员函数open打开要读的文件 
	 
	if(!infile){														//打开失败，退出 
		cout<<"Failed to open "<<infname<<"!"<<endl;
		exit(1);
	}
	else{																//打开成功 
		cout<<"Please input the name of the outfile:";
		cin>>outfname;
		outfile.open(outfname);											//使用成员函数open打开要写的文件 
		if(!outfile){													//打开失败，退出 
			cout<<"Failed to open "<<outfname<<"!"<<endl;
			exit(2);
		}
		else{
			count=1;
			while(infile.getline(str, 80)){								//若文件未读完 ，读文件内容到字符串 
				outfile<<count<<"、 ";									//写行号 
				outfile<<str<<endl;										//写字符串到文件 
				count++;
			}
			infile.close();												//关闭文件 
			outfile.close();
		}
	}
	return 0;
}
