/*C++������ƣ�      ʵ���� 1���绰����     format:2015-09-14��     coder�����壻      class��2014211302��     studentID:2014211182*/
#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdlib>
#include<cstring>
using namespace std;
class phoneBook{																			//�����ࣺ�绰�� 
	public:																					//���г�Ա 
		phoneBook(){}																		//���캯�� 
		~phoneBook(){}																		//�������� 
																							//fstream�п������캯����˽�г�Ա������ʹ�ò�����
																							 
		int enterChoice(){																	//�������˵�ѡ������û���ѡ�� 
			int menuChoice;
			cout<<"\nPlease enter your choice\n"
			"1-add information of contacts\n"
			"2-delete information of contacts\n"
			"3-search phone number of contacts\n"
			"4-store information to a target file\n"
			"5-end the program\n";
			cin>>menuChoice;
			return menuChoice;
		}
		
		void getFileName(){																	//����������绰���� 
			cout<<"Please input the name of the phone book:";
			cin>>filename;
		}
		
		int readin(){																		//���������绰�����ݴ�ָ���ļ��ж��뵽�ڴ� 
			file.open(filename, ios::in);													//ͨ����Ա����open������ʽ���ļ�
			if(!file){  																	//���ļ�ʧ�ܣ��˳� 
				cout<<"Failed to open "<<filename<<"!"<<endl;
				return -1;
			}
			else{																			//���ļ��ɹ� 
				int count=0;
				while(!file.eof() && count<1000){															//���ļ�ָ��δ��ĩβ 
					file>>name[count];														//�������������� 
					file>>number[count];													//���绰����������� 
					count++;
				}
				if(count == 1000){
					cout<<"The phonebook is full."<<endl;
				}
				file.close();																//�ر��ļ� 
				return count;
			}
		}
		
		void addInfo(){																		//�������û�����ͨ�����룬��������͵绰���� 
			file.open(filename, ios::out | ios::app);										//ͨ����Ա����open��д��ʽ���ļ��������ļ�ָ���Ƶ��ļ�ĩβ 
			if(!file){  																	//���ļ�ʧ�ܣ��˳� 
				cout<<"Failed to open "<<filename<<"!"<<endl;
				return;
			}
			else{  																			//���ļ��ɹ�
				char addname[20], addnumber[20];
				cout<<"Please input the name of the contact you want to add:";				 
				cin>>addname;
				cout<<"Please input the number of the contact you want to add:";
				cin>>addnumber;
				file<<addname<<" "<<addnumber<<"\n";										//д���ļ� 
				file.close();																//�ر��ļ� 
				return;
			}
		}
		
		void searchInfo(){																	//�������û�����������������Ҳ������� 
			int count=readin();																//���ú��������绰�����ݴ�ָ���ļ��ж��뵽�ڴ�
			if(count == -1){  																//���ļ�ʧ�� 
				return;
			}
			else{ 																			//���ļ��ɹ� 
				char tarName[20];
				cout<<"Please input the name of the contact you want to search:";			//�û�����Ҫ���ҵ����� 
				cin>>tarName;
				int i;
				for(i=0; i<count; i++){														//��������������� 
					if(strcmp(name[i], tarName) == 0){										//�Ƚ��ַ��������ҵ����˳�ѭ�� 
						break;
					}
				}
				if(strcmp(name[i], tarName) != 0){											//δ�ҵ� 
					cout<<"There isn't such a contact named "<<tarName<<endl;
				}
				else{																		//�ҵ� 
					cout<<"The number of the contact you search is: "<<number[i]<<endl;
				}
				return;
			}
		}
		
		void deleteInfo(){																	//������ɾ�������͵绰���� 
			int count=readin();																//���ú��������绰�����ݴ�ָ���ļ��ж��뵽�ڴ�
			if(count == -1){  																//���ļ�ʧ�� 
				return;
			}
			else{																			//���ļ��ɹ� 
				char tarName[20];
				cout<<"Please input the name of the contact you want to delete:";			//�û�����Ҫɾ�������� 
				cin>>tarName;
				
				int i;
				for(i = 0; i < count; i++){													//��������������� 
					if(strcmp(name[i], tarName) == 0){										//�Ƚ��ַ��������ҵ����˳�ѭ�� 
						break;
					}
				}
				if(strcmp(name[i], tarName) != 0){											//δ�ҵ� 
					cout<<"There isn't such a contact named "<<tarName<<endl;
				}
				else{																		//�ҵ� 
					for(; i<count-1; i++){													//������𣬰Ѻ������������ǰ��һλ 
						strcpy(name[i], name[i+1]);	
						strcpy(number[i], number[i+1]);
					}
					name[i][0]='\0';														//�����������Ϊ�� 
					number[i][0]='\0';
					file.open(filename, ios::out);											//ͨ����Ա����open��д�ķ�ʽ���ļ� 
					if(!file){																//���ļ�ʧ�� 
						cout<<"Failed to open "<<filename<<"!"<<endl;
						return;
					}
					else{																	//���ļ��ɹ� 
						for(int i=0; i < count-1; i++){										//�������ν�����д��ԭ�����ļ��� 
							file<<name[i]<<" "<<number[i]<<"\n";
						}
						cout<<"We've deleted this contact successfully."<<endl;
						file.close();														//�ر��ļ� 
					}
				}
				return;
			}
		}
		
		void storeInfo(){																	//���������绰��������ָ���ļ��� 
			file.open(filename, ios::in);													//ͨ����Ա����open������ʽ���ļ�
			if(!file){																		//���ļ��ɹ� 
				cout<<"Failed to open "<<filename<<"!"<<endl;
				return;
			}
			else{																			//���ļ�ʧ�� 
				ofstream outfile;															//�����ļ�������д�ļ� 
				char outfilename[20], str[80];
				cout<<"Please input the name of the file, where you want to store the phone book: ";
				cin>>outfilename;
				outfile.open(outfilename);													//ͨ����Ա����open��д��ʽ���ļ� 
				if(!outfile){																//���ļ����ɹ� 
					cout<<"Failed to open "<<outfilename<<"!"<<endl;
					return;
				}
				else{																		//���ļ��ɹ� 
					while(file.getline(str, 80)){											//��file�ļ�������ݵ��ַ����������ַ���������д��outfile�ļ� 
					 	outfile<<str<<"\n";
					}
					outfile.close();														//�ر��ļ� 
				}
				file.close();																//�ر��ļ�										
				return;
			}
		}
		
	private:																				//˽�г�Ա 
		char filename[20];																	//�ļ��� 
		char name[1000][20], number[1000][20];												//��ϵ���������绰 
		fstream file;																		//�ļ�������
};

int main()
{
	phoneBook p;																			//����绰�� 
	int choice;																				//�˵�ѡ�� 
	p.getFileName();																		//���ʵ绰��p�ĳ�Ա����������绰���� 
	while((choice=p.enterChoice()) != 5){ 													//���û�δѡ���˳� 
		switch(choice){
			case 1:
				p.addInfo();																//��������͵绰���� 
				break;
			case 2:
				p.deleteInfo();																//ɾ�������͵绰����
				break;
			case 3:
				p.searchInfo();																//����������������Ҳ�������
				break;
			case 4:
				p.storeInfo();																//������ָ���ļ���
				break;
			case 5:
				break;																		//�˳� 
			default:
				cout<<"\nError!\nPlease enter a valid number!\n";							//�Ƿ����� 
				cin.clear();																//��������� 
				cin.ignore(1024, '\n');
				break;	
		}
	}
	return 0;
}
