/*C++������ƣ�      ʵ���� 1������һ����     format:2015-09-09��     coder�����壻      class��2014211302��     studentID:2014211182*/ 
#include<iostream>
using namespace std;
const int ROW=4;
const int COL=5;
class matrix{
	public:
		matrix(int i=0){																		//��һ�������Ĺ��캯�� 
			for(row=0;row<ROW;row++){
				for(col=0;col<COL;col++){
					arr[row][col]=i;
				}
			}
		}
		~matrix(){}																				//�������� 
		
																								/*�������*/ 
		void getMatrix(){
			for(row=0;row<ROW;row++){
				for(col=0;col<COL;col++){
					cin>>arr[row][col];
				}
			}
		}
		
																								/*�������*/ 
		void showMatrix(){
			for(row=0;row<ROW;row++){
				for(col=0;col<COL;col++){
					cout.width(6);
					cout<<arr[row][col];
				}
				cout<<endl;
			}
		}
		
																								/*�������*/
		void addMatrix(matrix a, matrix b, matrix &c){
			for(row=0;row<ROW;row++){
				for(col=0;col<COL;col++){
					c.arr[row][col]=a.arr[row][col]+b.arr[row][col];
				}
			}
		}
		
																								/*�������*/ 
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
	matrix A1(0), A2(0), A3;																	//��������ͳ�ʼ�� 
	cout<<"Please input the elements of matrix A1:"<<endl;
	A1.getMatrix();																				//�������A1 
	cout<<"Please input the elements of matrix A2:"<<endl;
	A2.getMatrix();																				//�������A2 
	A3.addMatrix(A1, A2, A3);																	//������� 
	cout<<"The addition of matrix is:"<<endl;
	A3.showMatrix();																			//�������ĺ� 
	A3.subtractMatrix(A1, A2, A3);																//������� 
	cout<<"The subtraction of matrix is:"<<endl;
	A3.showMatrix();																			//�������Ĳ� 
	return 0;
}
