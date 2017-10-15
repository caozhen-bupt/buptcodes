/*C++������ƣ�      ʵ��� 3����Ԫ��     format:2015-09-08��     coder�����壻      class��2014211302��     studentID:2014211182*/ 
#include<iostream>
using namespace std;
																				/*������Car*/ 
class Car;
																				/*������Boat������˽�����ԡ�������*/ 
class Boat{
	public:
		Boat(){
			weight=0;
		}
		~Boat(){}
	private:
		double weight;
	friend double TotalWeight(Boat &b, Car &c);									/*������Ԫ��ʹ�ú������Է���Boat���˽������weight*/ 
}; 
																				/*������Car������˽�����ԡ�������*/ 
class Car{
	public:
		Car(){
			weight=0;
		}
		~Car(){}
	private:
		double weight;
	friend double TotalWeight(Boat &b, Car &c);									/*������Ԫ��ʹ�ú������Է���Car���˽������weight*/ 
};
																				/*����Car��Boat��������*/ 
double TotalWeight(Boat &b, Car &c)
{
	double total;
	cout<<"Please input the weight of the boat and that of the car."<<endl;
	cin>>b.weight>>c.weight;
	if(b.weight>=0 && c.weight>=0){
		total=b.weight+c.weight;
		return total;
	}
	else{
		return -1;
	}
}
int main()
{
	Boat b;
	Car c;
	double sum;
	sum=TotalWeight(b, c);
	if(sum == -1 || sum == 0){													//��Ϊ�������ַ��ȷǷ����� 
		cout<<"Please input valid weight."<<endl;
	}
	else{
		cout<<"The total of the weight is: "<<sum<<endl;
	}
	return 0;
}
