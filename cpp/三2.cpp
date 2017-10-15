/*C++程序设计；      实验三 2、矩阵（二）；     format:2015-09-09；     coder：曹桢；      class：2014211302；     studentID:2014211182*/ 
#include<iostream>
using namespace std;
const int ROW=4;
const int COL=5;
class matrix{																			//定义矩阵类 
	public:
		matrix(int num = 0){															//带参数的构造函数：参数是矩阵大小，以及初始化的矩阵各元素的值，需要动态申请存贮矩阵的数组；
			reset(ROW, COL, num);
		}
		matrix(const matrix &t){														//拷贝构造函数 
			*this = t;
		}
		void reset(int LINES, int ROWS, int num) {										//函数：用于动态分配内存和赋值 
			row = LINES;
			col = ROWS;
			arr = new int*[row];														//设置二维数组 
			for(int i = 0; i < row; i++) {
				arr[i] = new int[col];
			}
			for(int i = 0; i < row; i++) {												//赋值 
				for(int j = 0; j < col; j++) {
					arr[i][j] = num;
				}
			}
		}
		void free() {																	//函数：用于清除动态内存 
			if(arr != NULL) {
				for(int i = 0; i < row; i++) {
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
																						//输入矩阵 
		void getMatrix(){ 
			for(row=0;row<ROW;row++){
				for(col=0;col<COL;col++){
					cin>>arr[row][col];
				}
			}
		}
																						//输出矩阵 
		void showMatrix(){
			for(row=0;row<ROW;row++){
				for(col=0;col<COL;col++){
					cout.width(6);
					cout<<arr[row][col];
				}
				cout<<endl;
			}
		}
																						//矩阵加法 
		void addMatrix(const matrix & b, matrix &c){
			for(row=0;row<ROW;row++){
				for(col=0;col<COL;col++){
					c.arr[row][col]=arr[row][col]+b.arr[row][col];
				}
			}
			return;
		}
																						//矩阵减法 
		void subtractMatrix(const matrix & b, matrix &c){
			for(row=0;row<ROW;row++){
				for(col=0;col<COL;col++){
					c.arr[row][col]=arr[row][col]-b.arr[row][col];
				}
			}
			return;
		}
	private:
		int **arr, row, col;
};
int main()
{
	matrix A1, A2, A3;																	//定义指向矩阵的指针

	cout<<"Please input the elements of matrix A1:"<<endl;
	A1.getMatrix();																		//输入矩阵A1 
	cout<<"Please input the elements of matrix A2:"<<endl;
	A2.getMatrix();																		//输入矩阵A2 
	A1.addMatrix(A2, A3);																//计算矩阵的和 
	cout<<"The addition of matrix is:"<<endl;
	A3.showMatrix();																	//输出矩阵的和 
	
	A1.subtractMatrix(A2, A3);															//计算矩阵的差 
	cout<<"The subtract of matrix is:"<<endl;
	A3.showMatrix();																	//输出矩阵的差 
		
	return 0;
}
