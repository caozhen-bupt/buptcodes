/*C++程序设计；      实验七 1、电话本；     format:2015-09-14；     coder：曹桢；      class：2014211302；     studentID:2014211182*/
#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdlib>
#include<cstring>
using namespace std;
class phoneBook{																			//定义类：电话簿 
	public:																					//公有成员 
		phoneBook(){}																		//构造函数 
		~phoneBook(){}																		//析构函数 
																							//fstream中拷贝构造函数是私有成员，若不使用不定义
																							 
		int enterChoice(){																	//函数：菜单选项，返回用户的选择 
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
		
		void getFileName(){																	//函数：读入电话簿名 
			cout<<"Please input the name of the phone book:";
			cin>>filename;
		}
		
		int readin(){																		//函数：将电话簿内容从指定文件中读入到内存 
			file.open(filename, ios::in);													//通过成员函数open按读方式打开文件
			if(!file){  																	//打开文件失败，退出 
				cout<<"Failed to open "<<filename<<"!"<<endl;
				return -1;
			}
			else{																			//打开文件成功 
				int count=0;
				while(!file.eof() && count<1000){															//若文件指针未到末尾 
					file>>name[count];														//将姓名读进数组 
					file>>number[count];													//将电话号码读进数组 
					count++;
				}
				if(count == 1000){
					cout<<"The phonebook is full."<<endl;
				}
				file.close();																//关闭文件 
				return count;
			}
		}
		
		void addInfo(){																		//函数：用户可以通过输入，添加姓名和电话号码 
			file.open(filename, ios::out | ios::app);										//通过成员函数open按写方式打开文件，并将文件指针移到文件末尾 
			if(!file){  																	//打开文件失败，退出 
				cout<<"Failed to open "<<filename<<"!"<<endl;
				return;
			}
			else{  																			//打开文件成功
				char addname[20], addnumber[20];
				cout<<"Please input the name of the contact you want to add:";				 
				cin>>addname;
				cout<<"Please input the number of the contact you want to add:";
				cin>>addnumber;
				file<<addname<<" "<<addnumber<<"\n";										//写入文件 
				file.close();																//关闭文件 
				return;
			}
		}
		
		void searchInfo(){																	//函数：用户输入姓名，程序查找并输出结果 
			int count=readin();																//调用函数：将电话簿内容从指定文件中读入到内存
			if(count == -1){  																//打开文件失败 
				return;
			}
			else{ 																			//打开文件成功 
				char tarName[20];
				cout<<"Please input the name of the contact you want to search:";			//用户输入要查找的姓名 
				cin>>tarName;
				int i;
				for(i=0; i<count; i++){														//遍历数组查找姓名 
					if(strcmp(name[i], tarName) == 0){										//比较字符串：若找到，退出循环 
						break;
					}
				}
				if(strcmp(name[i], tarName) != 0){											//未找到 
					cout<<"There isn't such a contact named "<<tarName<<endl;
				}
				else{																		//找到 
					cout<<"The number of the contact you search is: "<<number[i]<<endl;
				}
				return;
			}
		}
		
		void deleteInfo(){																	//函数：删除姓名和电话号码 
			int count=readin();																//调用函数：将电话簿内容从指定文件中读入到内存
			if(count == -1){  																//打开文件失败 
				return;
			}
			else{																			//打开文件成功 
				char tarName[20];
				cout<<"Please input the name of the contact you want to delete:";			//用户输入要删除的姓名 
				cin>>tarName;
				
				int i;
				for(i = 0; i < count; i++){													//遍历数组查找姓名 
					if(strcmp(name[i], tarName) == 0){										//比较字符串：若找到，退出循环 
						break;
					}
				}
				if(strcmp(name[i], tarName) != 0){											//未找到 
					cout<<"There isn't such a contact named "<<tarName<<endl;
				}
				else{																		//找到 
					for(; i<count-1; i++){													//从这个起，把后面的数组依次前移一位 
						strcpy(name[i], name[i+1]);	
						strcpy(number[i], number[i+1]);
					}
					name[i][0]='\0';														//设置最后数组为空 
					number[i][0]='\0';
					file.open(filename, ios::out);											//通过成员函数open按写的方式打开文件 
					if(!file){																//打开文件失败 
						cout<<"Failed to open "<<filename<<"!"<<endl;
						return;
					}
					else{																	//打开文件成功 
						for(int i=0; i < count-1; i++){										//重新依次将数组写入原本的文件中 
							file<<name[i]<<" "<<number[i]<<"\n";
						}
						cout<<"We've deleted this contact successfully."<<endl;
						file.close();														//关闭文件 
					}
				}
				return;
			}
		}
		
		void storeInfo(){																	//函数：将电话簿保存在指定文件中 
			file.open(filename, ios::in);													//通过成员函数open按读方式打开文件
			if(!file){																		//打开文件成功 
				cout<<"Failed to open "<<filename<<"!"<<endl;
				return;
			}
			else{																			//打开文件失败 
				ofstream outfile;															//定义文件流对象，写文件 
				char outfilename[20], str[80];
				cout<<"Please input the name of the file, where you want to store the phone book: ";
				cin>>outfilename;
				outfile.open(outfilename);													//通过成员函数open按写方式打开文件 
				if(!outfile){																//打开文件不成功 
					cout<<"Failed to open "<<outfilename<<"!"<<endl;
					return;
				}
				else{																		//打开文件成功 
					while(file.getline(str, 80)){											//从file文件里读内容到字符串，并把字符串的内容写进outfile文件 
					 	outfile<<str<<"\n";
					}
					outfile.close();														//关闭文件 
				}
				file.close();																//关闭文件										
				return;
			}
		}
		
	private:																				//私有成员 
		char filename[20];																	//文件名 
		char name[1000][20], number[1000][20];												//联系人姓名，电话 
		fstream file;																		//文件流对象
};

int main()
{
	phoneBook p;																			//定义电话簿 
	int choice;																				//菜单选项 
	p.getFileName();																		//访问电话簿p的成员函数，读入电话簿名 
	while((choice=p.enterChoice()) != 5){ 													//若用户未选择退出 
		switch(choice){
			case 1:
				p.addInfo();																//添加姓名和电话号码 
				break;
			case 2:
				p.deleteInfo();																//删除姓名和电话号码
				break;
			case 3:
				p.searchInfo();																//输入姓名，程序查找并输出结果
				break;
			case 4:
				p.storeInfo();																//保存在指定文件中
				break;
			case 5:
				break;																		//退出 
			default:
				cout<<"\nError!\nPlease enter a valid number!\n";							//非法输入 
				cin.clear();																//清除缓冲区 
				cin.ignore(1024, '\n');
				break;	
		}
	}
	return 0;
}
