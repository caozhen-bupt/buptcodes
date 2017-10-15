/*C++程序设计；      实验三 1、矩阵（一）；     format:2015-09-09；     coder：曹桢；      class：2014211302；     studentID:2014211182*/ 
#include<iostream>
using namespace std;
const int ROW=4;
const int COL=5;
class matrix{
	public:
		matrix(int i=0){																		//带一个参数的构造函数 
			for(row=0;row<ROW;row++){
				for(col=0;col<COL;col++){
					arr[row][col]=i;
				}
			}
		}
		~matrix(){}																				//析构函数 
		
																								/*输入矩阵*/ 
		void getMatrix(){
			for(row=0;row<ROW;row++){
				for(col=0;col<COL;col++){
					cin>>arr[row][col];
				}
			}
		}
		
																								/*输出矩阵*/ 
		void showMatrix(){
			for(row=0;row<ROW;row++){
				for(col=0;col<COL;col++){
					cout.width(6);
					cout<<arr[row][col];
				}
				cout<<endl;
			}
		}
		
																								/*矩阵相加*/
		void addMatrix(matrix a, matrix b, matrix &c){
			for(row=0;row<ROW;row++){
				for(col=0;col<COL;col++){
					c.arr[row][col]=a.arr[row][col]+b.arr[row][col];
				}
			}
		}
		
																								/*矩阵相减*/ 
		void subtractMatrix(matrix a, matrix b, matrix &c){
			for(row=0;row<ROW;row++){
				for(col=0;col<COL;col++){
					c.arr[row][col]=a.arr[row][col]-b.arr[row][col];
				}
			}
		}
	private:
		int arr[ROW][COL], row, col;
};
int main()
{
	matrix A1(0), A2(0), A3;																	//类的声明和初始化 
	cout<<"Please input the elements of matrix A1:"<<endl;
	A1.getMatrix();																				//输入矩阵A1 
	cout<<"Please input the elements of matrix A2:"<<endl;
	A2.getMatrix();																				//输入矩阵A2 
	A3.addMatrix(A1, A2, A3);																	//矩阵相加 
	cout<<"The addition of matrix is:"<<endl;
	A3.showMatrix();																			//输出矩阵的和 
	A3.subtractMatrix(A1, A2, A3);																//矩阵相减 
	cout<<"The subtraction of matrix is:"<<endl;
	A3.showMatrix();																			//输出矩阵的差 
	return 0;
}
