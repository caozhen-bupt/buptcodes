/*C++������ƣ�  ʵ���� 1����Point�����أ����ͨD�D�����  format:2015-09-12�� coder�����壻  class��2014211302��  studentID:2014211182*/
#include<iostream>
#include<math.h>
using namespace std;
class Point{
	public:
																				/*���캯��*/ 
		Point(int X=0, int Y=0){
			x=X;
			y=Y;
			cout<<"������Point�Ĺ��캯��"<<endl;
		}
		Point(const Point &t){													//�������캯�� 
			*this = t;
		}
																				/*��������*/
		~Point(){ 
			cout<<"������Point����������"<<endl; 
		}
																				/*���������*/ 
		friend istream& operator >>(istream &input, Point &A){
			cin >> A.x >> A.y;
			return input;
		}
		friend ostream& operator <<(ostream &output, Point &A){
			cout<<"("<<A.x<<", "<<A.y<<")"<<endl;
			return output;
		}
		Point & operator ++(){													//ʵ��++a 
			x++;
			y++;
			return *this;														//���ص������� 
		}
		const Point operator ++(int){											//ʵ��a++ ,���ã�int�������֣��������ޱ��������ɣ�ʵ�ֺ��õ�++ 
			Point temp = *this;
			++(*this);
			return temp;
		}
		Point & operator --(){													//ʵ��--a 
			x--;
			y--;
			return *this;
		}
		const Point operator --(int){											//ʵ��a--,���ã�int�������֣�ʵ�ֺ��õ�-- 
			Point temp = *this;
			--(*this);
			return temp;
		}
	private:
		double x, y;															/*��������*/ 
};
int main()
{
	Point A, B;
	cout<<"Please input the coordinate of A: ";
	cin>>A;
	B=A++;																		//B=A.operator++(1) 
	cout<<B;
	
	cout<<"Please input the coordinate of A: ";
	cin>>A;
	B=++A;																		//B=A.operator++()
	cout<<B;
	
	cout<<"Please input the coordinate of A: ";
	cin>>A;
	B=A--;
	cout<<B;
	
	cout<<"Please input the coordinate of A: ";
	cin>>A;
	B=--A;
	cout<<B;
	
	return 0;
} 
