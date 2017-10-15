/*C++������ƣ�      ʵ���� 2�����󣨶�����     format:2015-09-09��     coder�����壻      class��2014211302��     studentID:2014211182*/ 
#include<iostream>
using namespace std;
const int ROW=4;
const int COL=5;
class matrix{																			//��������� 
	public:
		matrix(int num = 0){															//�������Ĺ��캯���������Ǿ����С���Լ���ʼ���ľ����Ԫ�ص�ֵ����Ҫ��̬���������������飻
			reset(ROW, COL, num);
		}
		matrix(const matrix &t){														//�������캯�� 
			*this = t;
		}
		void reset(int LINES, int ROWS, int num) {										//���������ڶ�̬�����ڴ�͸�ֵ 
			row = LINES;
			col = ROWS;
			arr = new int*[row];														//���ö�ά���� 
			for(int i = 0; i < row; i++) {
				arr[i] = new int[col];
			}
			for(int i = 0; i < row; i++) {												//��ֵ 
				for(int j = 0; j < col; j++) {
					arr[i][j] = num;
				}
			}
		}
		void free() {																	//���������������̬�ڴ� 
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
		~matrix(){																		//�������� 
			free();
		}
																						//������� 
		void getMatrix(){ 
			for(row=0;row<ROW;row++){
				for(col=0;col<COL;col++){
					cin>>arr[row][col];
				}
			}
		}
																						//������� 
		void showMatrix(){
			for(row=0;row<ROW;row++){
				for(col=0;col<COL;col++){
					cout.width(6);
					cout<<arr[row][col];
				}
				cout<<endl;
			}
		}
																						//����ӷ� 
		void addMatrix(const matrix & b, matrix &c){
			for(row=0;row<ROW;row++){
				for(col=0;col<COL;col++){
					c.arr[row][col]=arr[row][col]+b.arr[row][col];
				}
			}
			return;
		}
																						//������� 
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
	matrix A1, A2, A3;																	//����ָ������ָ��

	cout<<"Please input the elements of matrix A1:"<<endl;
	A1.getMatrix();																		//�������A1 
	cout<<"Please input the elements of matrix A2:"<<endl;
	A2.getMatrix();																		//�������A2 
	A1.addMatrix(A2, A3);																//�������ĺ� 
	cout<<"The addition of matrix is:"<<endl;
	A3.showMatrix();																	//�������ĺ� 
	
	A1.subtractMatrix(A2, A3);															//�������Ĳ� 
	cout<<"The subtract of matrix is:"<<endl;
	A3.showMatrix();																	//�������Ĳ� 
		
	return 0;
}
