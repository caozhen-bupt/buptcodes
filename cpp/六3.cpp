/*C++������ƣ�      ʵ���� 3����ʽIO��������     format:2015-09-14��     coder�����壻      class��2014211302��     studentID:2014211182*/
#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdlib>
using namespace std;
int main()
{
	char infname[256], outfname[256];
	ifstream infile;													//�����ļ������� �����ļ� 
	ofstream outfile;													//�����ļ������� ��д�ļ� 
	char str[80];
	int count;
	
	cout<<"Please input the name of the infile:";
	cin>>infname;
	infile.open(infname);												//ʹ�ó�Ա����open��Ҫ�����ļ� 
	 
	if(!infile){														//��ʧ�ܣ��˳� 
		cout<<"Failed to open "<<infname<<"!"<<endl;
		exit(1);
	}
	else{																//�򿪳ɹ� 
		cout<<"Please input the name of the outfile:";
		cin>>outfname;
		outfile.open(outfname);											//ʹ�ó�Ա����open��Ҫд���ļ� 
		if(!outfile){													//��ʧ�ܣ��˳� 
			cout<<"Failed to open "<<outfname<<"!"<<endl;
			exit(2);
		}
		else{
			count=1;
			while(infile.getline(str, 80)){								//���ļ�δ���� �����ļ����ݵ��ַ��� 
				outfile<<count<<"�� ";									//д�к� 
				outfile<<str<<endl;										//д�ַ������ļ� 
				count++;
			}
			infile.close();												//�ر��ļ� 
			outfile.close();
		}
	}
	return 0;
}
