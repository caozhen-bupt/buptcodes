/*C++程序设计；    实验三 3、矩阵（三）；     format:2015-09-12；     coder：曹桢；      class：2014211302；     studentID:2014211182*/
#include<iostream>
#include<cstdlib>
using namespace std;
class matrix{
	public:
		matrix() {																		//不带参数的构造函数
			arr = NULL;
			lines = rows = 0;
			flag = 0;
		}
		matrix(int LINES, int ROWS, int num = 0){										//带参数的构造函数：参数是矩阵大小，以及初始化的矩阵各元素的值，需要动态申请存贮矩阵的数组；
			reset( LINES, ROWS, num );
			flag = 1;
		}
		matrix(const matrix &t){														//拷贝构造函数 
			*this = t;
		}
		void reset(int LINES, int ROWS, int num) {										//函数：用于动态分配内存和赋值 
			lines = LINES;
			rows = ROWS;
			arr = new int*[lines];														//设置二维数组 
			for(int i = 0; i < lines; i++) {
				arr[i] = new int[rows];
			}
			for(int i = 0; i < lines; i++) {											//赋值 
				for(int j = 0; j < rows; j++) {
					arr[i][j] = num;
				}
			}
		}
		void free() {																	//函数：用于清除动态内存 
			if(arr != NULL) {
				for(int i = 0; i < lines; i++) {
					if(arr[i] != NULL) {
						delete []arr[i];
					}
				}
				delete []arr;
			}
			arr = NULL;
		}
		~matrix(){																		//析构函数 
			free();
		}
		friend istream& operator >>(istream &input, const matrix &C){					//重载操作符>> 
			for(int i = 0; i < C.lines; i++){
				for(int j = 0; j < C.rows; j++){
					cin>>C.arr[i][j];
				}
			}
			return input;
		}
		friend ostream& operator <<(ostream &output, const matrix &C){					//重载操作符<<
			for(int i = 0; i < C.lines; i++){
				for(int j = 0; j < C.rows; j++){
					cout.width(6);
					cout<<C.arr[i][j];
				}
				cout<<endl;
			}
			return output;
		}
		
																						//矩阵加法 重载操作符 + 实现两个矩阵相加的功能,结果保存在另一个矩阵类，但必须矩阵大小相同
		matrix operator+(const matrix &b){
			if(lines == b.lines && rows == b.rows){
				matrix c(lines, rows, 0);
                for(int i = 0; i < lines; i++){
                    for(int j = 0; j < rows; j++){
                        c.arr[i][j] = arr[i][j]+b.arr[i][j];
                    }
                }
                return c;
            }
			else{
                cout << "The two matrices have different lines or rows, so we cannot compute" << endl;
                exit(0);
            }
		}
		
																						//矩阵减法 重载操作符 - 实现两个矩阵相减的功能,结果保存在另一个矩阵类，但必须矩阵大小相同
		matrix operator-(const matrix &b){
			if(lines == b.lines && rows == b.rows){
				matrix c(lines, rows, 0);
                for(int i = 0; i < lines; i++){
                    for(int j = 0; j < rows; j++){
                        c.arr[i][j] = arr[i][j]-b.arr[i][j];
                    }
                }
                return c;
            }
			else{
                cout << "The two matrices have different lines or rows, so we cannot compute." << endl;
                exit(0);
            }
		}
		
																						//重载 操作符 = 
		matrix& operator=(const matrix &t){ 
		    this->rows = t.rows; 
		    this->lines = t.lines;
		    if(flag != 0 && flag != 1){
		    	this->arr = NULL;
		    }
			if( this != &t){															//非自赋值 
				this->free();															//清除旧元素内存 
				this->reset(t.lines, t.rows, 0);										//分配新内存 
				for(int i = 0; i < lines; i++){											//赋值 
					for(int j = 0; j < rows; j++){
						arr[i][j] = t.arr[i][j];
					}
				}
			}
			return *this;																//返回别名 
		}
	private:
		int **arr, lines, rows, flag;
};

int main()
{
																						//读入两个矩阵的大小，用于初始化 
	int line1=0, row1=0, line2=0, row2=0;
	cout<<"Please input the lines and rows of matrix A1:";
	cin>>line1>>row1;
	cout<<"Please input the lines and rows of matrix A2:";
	cin>>line2>>row2;
	
																						//定义三个矩阵：A1、A2、A3
	matrix A1(line1, row1), A2(line2, row2), A3, A4;
	cout<<"Please input the elements of matrix A1:"<<endl;
	cin>>A1;																			//实现操作符 >> 的重载  
	cout<<"Please input the elements of matrix A2:"<<endl;
	cin>>A2;																			//实现操作符 >> 的重载  
	A3 = A1 + A2;
	cout<<"A1 + A2 = "<<endl<<A3;
	A4 = A3;
	cout<<"A4 = "<<endl<<A4;
	A3 = A1 - A2;
	cout<<"A1 - A2 = "<<endl<<A3;
	A4 = A3;
	cout<<"A4 = "<<endl<<A4;
	
																						//读入两个矩阵的大小，用于初始化 
	cout<<"Please input the lines and rows of matrix pA1:";
	cin>>line1>>row1;
	cout<<"Please input the lines and rows of matrix pA2:";
	cin>>line2>>row2;
	
																						//用new动态创建三个矩阵类的对象：pA1、pA1、pA3、pA4； 
	matrix *pA1, *pA2, *pA3, *pA4;
	pA1=new matrix(line1, row1);
	pA2=new matrix(line2, row2);
	pA3=new matrix;
	pA4=new matrix;
	if(pA1 == 0 || pA2 == 0|| pA3 == 0){												//若申请内存不成功 
		cout<<"failed to distribute space to matrix."<<endl;
		exit(0);
	}
	else{																				//申请内存成功 
		cout<<"Please input the elements of matrix pA1:"<<endl;
		cin>>*pA1;																		//输入矩阵A1 
		cout<<"Please input the elements of matrix pA2:"<<endl;
		cin>>*pA2;																		//输入矩阵A2 
		*pA3 = *pA1 + *pA2;
		cout<<"*pA1 + *pA2 = "<<endl<<*pA3;
		*pA4 = *pA3;
		cout<<"*pA4 = "<<endl<<*pA4;
		*pA3 = *pA1 - *pA2;
		cout<<"*pA1 - *pA2 = "<<endl<<*pA3;
		*pA4 = *pA3;
		cout<<"*pA4 = "<<endl<<*pA4;
																						//释放pA1、pA1、pA3
		delete pA1;
		delete pA2;
		delete pA3;
	}
	return 0;
}
