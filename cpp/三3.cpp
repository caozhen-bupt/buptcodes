/*C++������ƣ�    ʵ���� 3������������     format:2015-09-12��     coder�����壻      class��2014211302��     studentID:2014211182*/
#include<iostream>
#include<cstdlib>
using namespace std;
class matrix{
	public:
		matrix() {																		//���������Ĺ��캯��
			arr = NULL;
			lines = rows = 0;
			flag = 0;
		}
		matrix(int LINES, int ROWS, int num = 0){										//�������Ĺ��캯���������Ǿ����С���Լ���ʼ���ľ����Ԫ�ص�ֵ����Ҫ��̬���������������飻
			reset( LINES, ROWS, num );
			flag = 1;
		}
		matrix(const matrix &t){														//�������캯�� 
			*this = t;
		}
		void reset(int LINES, int ROWS, int num) {										//���������ڶ�̬�����ڴ�͸�ֵ 
			lines = LINES;
			rows = ROWS;
			arr = new int*[lines];														//���ö�ά���� 
			for(int i = 0; i < lines; i++) {
				arr[i] = new int[rows];
			}
			for(int i = 0; i < lines; i++) {											//��ֵ 
				for(int j = 0; j < rows; j++) {
					arr[i][j] = num;
				}
			}
		}
		void free() {																	//���������������̬�ڴ� 
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
		~matrix(){																		//�������� 
			free();
		}
		friend istream& operator >>(istream &input, const matrix &C){					//���ز�����>> 
			for(int i = 0; i < C.lines; i++){
				for(int j = 0; j < C.rows; j++){
					cin>>C.arr[i][j];
				}
			}
			return input;
		}
		friend ostream& operator <<(ostream &output, const matrix &C){					//���ز�����<<
			for(int i = 0; i < C.lines; i++){
				for(int j = 0; j < C.rows; j++){
					cout.width(6);
					cout<<C.arr[i][j];
				}
				cout<<endl;
			}
			return output;
		}
		
																						//����ӷ� ���ز����� + ʵ������������ӵĹ���,�����������һ�������࣬����������С��ͬ
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
		
																						//������� ���ز����� - ʵ��������������Ĺ���,�����������һ�������࣬����������С��ͬ
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
		
																						//���� ������ = 
		matrix& operator=(const matrix &t){ 
		    this->rows = t.rows; 
		    this->lines = t.lines;
		    if(flag != 0 && flag != 1){
		    	this->arr = NULL;
		    }
			if( this != &t){															//���Ը�ֵ 
				this->free();															//�����Ԫ���ڴ� 
				this->reset(t.lines, t.rows, 0);										//�������ڴ� 
				for(int i = 0; i < lines; i++){											//��ֵ 
					for(int j = 0; j < rows; j++){
						arr[i][j] = t.arr[i][j];
					}
				}
			}
			return *this;																//���ر��� 
		}
	private:
		int **arr, lines, rows, flag;
};

int main()
{
																						//������������Ĵ�С�����ڳ�ʼ�� 
	int line1=0, row1=0, line2=0, row2=0;
	cout<<"Please input the lines and rows of matrix A1:";
	cin>>line1>>row1;
	cout<<"Please input the lines and rows of matrix A2:";
	cin>>line2>>row2;
	
																						//������������A1��A2��A3
	matrix A1(line1, row1), A2(line2, row2), A3, A4;
	cout<<"Please input the elements of matrix A1:"<<endl;
	cin>>A1;																			//ʵ�ֲ����� >> ������  
	cout<<"Please input the elements of matrix A2:"<<endl;
	cin>>A2;																			//ʵ�ֲ����� >> ������  
	A3 = A1 + A2;
	cout<<"A1 + A2 = "<<endl<<A3;
	A4 = A3;
	cout<<"A4 = "<<endl<<A4;
	A3 = A1 - A2;
	cout<<"A1 - A2 = "<<endl<<A3;
	A4 = A3;
	cout<<"A4 = "<<endl<<A4;
	
																						//������������Ĵ�С�����ڳ�ʼ�� 
	cout<<"Please input the lines and rows of matrix pA1:";
	cin>>line1>>row1;
	cout<<"Please input the lines and rows of matrix pA2:";
	cin>>line2>>row2;
	
																						//��new��̬��������������Ķ���pA1��pA1��pA3��pA4�� 
	matrix *pA1, *pA2, *pA3, *pA4;
	pA1=new matrix(line1, row1);
	pA2=new matrix(line2, row2);
	pA3=new matrix;
	pA4=new matrix;
	if(pA1 == 0 || pA2 == 0|| pA3 == 0){												//�������ڴ治�ɹ� 
		cout<<"failed to distribute space to matrix."<<endl;
		exit(0);
	}
	else{																				//�����ڴ�ɹ� 
		cout<<"Please input the elements of matrix pA1:"<<endl;
		cin>>*pA1;																		//�������A1 
		cout<<"Please input the elements of matrix pA2:"<<endl;
		cin>>*pA2;																		//�������A2 
		*pA3 = *pA1 + *pA2;
		cout<<"*pA1 + *pA2 = "<<endl<<*pA3;
		*pA4 = *pA3;
		cout<<"*pA4 = "<<endl<<*pA4;
		*pA3 = *pA1 - *pA2;
		cout<<"*pA1 - *pA2 = "<<endl<<*pA3;
		*pA4 = *pA3;
		cout<<"*pA4 = "<<endl<<*pA4;
																						//�ͷ�pA1��pA1��pA3
		delete pA1;
		delete pA2;
		delete pA3;
	}
	return 0;
}
