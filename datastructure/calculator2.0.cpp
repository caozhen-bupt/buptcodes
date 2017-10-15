#include<iostream>
#include<cstdlib>
#include<cmath>
using namespace std;

const int STACK_INIT_SIZE=100;
const int STACK_INCREMENT=10;

//ջ 
class stack
{
	public:
		stack(){}
		~stack(){}
	protected:
		int stacksize;//ջ�Ĵ�С 
};

//��������ջ 
class stackN: public stack
{
	public:
		stackN(){//���캯�� 
			InitStack();
		}
		~stackN(){//�������� 
			DestroyStack();
		} 
		void InitStack(){//��ʼ�� 
			base  = (float *)malloc(STACK_INIT_SIZE*sizeof(float));
			if(!base){
				exit(1);
			}
			top = base;
			stacksize = STACK_INIT_SIZE;
		}
		int GetTop(float &e){//�õ�ջ��Ԫ��e 
			if(base == top){
				return 0;
			}
			e = *(top - 1);
			return 1;
		}
		int Push(float e){//ѹ�� 
			if(top - base >= stacksize){
				base = (float*)realloc(base,(stacksize+STACK_INCREMENT)*sizeof(float));
				if(!base){
					exit(2);
				}
				top = base + stacksize;
				stacksize += STACK_INCREMENT;
			}
			*top++ = e;
			return 1;
		}
		int Pop(float &e){//���� 
			if(base == top){
				return 0;
			}
			e = * --top;
			return 1;
		}
		void DestroyStack(){//����ջ 
			free(base);
		}
		void clearStack(){//��ջ��Ϊ��ջ 
			while(base != top){
				top--;
			}
		}
		int EmptyStack(){//�ж�ջ�Ƿ�Ϊ�� 
			if(top == base){//�ǣ�����1 
				return 1;
			}
			else{//���ǣ�����0 
				return 0;
			}
		}
		int StackLengh(){//ջ��Ԫ�ظ��� 
			return (top - base);
		}
	private: 
		float *base;//ָ��ջ�� 
		float *top; //ָ��ջ�� 
};

//�����������ջ 
class stackOP: public stack
{
	public:
		stackOP(){
			InitStack();
		}
		~stackOP(){
			DestroyStack();
		}
		void InitStack(){
			base = (char *)malloc(STACK_INIT_SIZE*sizeof(char));
			if(!base){
				exit(1);
			}
			top = base;
			stacksize = STACK_INIT_SIZE;
		}
		int GetTop(char &e){
			if(base == top){
				return 0;
			}
			e = *(top - 1);
			return 1;
		}
		int Push(char e){
			if(top - base >= stacksize){
				base = (char*)realloc(base,(stacksize+STACK_INCREMENT)*sizeof(char));
				if(!base){
					exit(2);
				}
				top = base + stacksize;
				stacksize += STACK_INCREMENT;
			}
			*top++ = e;
			return 1;
		}
		int Pop(char &e){
			if(base == top){
				return 0;
			}
			e = * --top;
			return 1;
		}
		void DestroyStack(){
			free(base);
		}
		void clearStack(){
			while(base != top){
				top--;
			}
		}
		int EmptyStack(){
			if(top == base){
				return 1;
			}
			else{
				return 0;
			}
		}
		int StackLengh(){
			return (top - base);
		}
	private:
		char *base;
		char *top;
};

//�������Ĳ��������ַ��������֣�Ȼ�������ת����һ�����������洢��ջ�� 
int number(stackN &N, char *str, int &i)//N������ջ��str�������ַ�����i�Ƕ������ַ��±� 
{
	//�������Ч�����֣�����1 
	if(str[i] >= '0' && str[i] <= '9'){
		float snum, num;
		snum = num = 0;
		while(str[i] >= '0' && str[i] <= '9'){
			num = num*10 + str[i]-'0';
			i++;
		}
		if(str[i] == '.'){//��С�� 
			i++;
			int pos=0;
			while(str[i] >= '0' && str[i] <= '9'){
				snum = snum*10 + str[i]-'0';
				pos--;
				i++;
			}
			snum = num + snum*pow(10, pos);
			N.Push(snum);
		}
		else{
			N.Push(num);
		}
		return 1;
	}
	
	//���������Ч�����֣�����0 
	else return 0;
}

//����������Ĳ��������ú�׺���ʽ 
int operate(stackOP &S, stackN &N, char *str, int &i)//S���������ջ��N������ջ��str�������ַ�����i�Ƕ������ַ��±� 
{
	char e;
	int c[300];
	float num, a, b;
	
	//��������ȼ������� 
	c['('] = c['='] = 0;
	c['+'] = c['-'] = 1;
	c['*'] = c['/'] = 2;
	c['^'] = 3;
	
	//�������Ч�������������1 
	if(str[i] == '(' || str[i] == ')' || str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^' || str[i] == '='){
		if( str[i] == ')'){ //�����ţ��׳�ջ��Ԫ��ֱ�������� 
			S.Pop(e);
			while(e != '('){
				N.Pop(b);
				N.Pop(a);
				switch(e){
					case '+':
						num = a + b;
						N.Push(num);
						break;
					case '-':
						num = a - b;
						N.Push(num);
						break;
					case '*':
						num = a * b;
						N.Push(num);
						break;
					case '/':
						num = a / b;
						N.Push(num);
						break;
					case '^':
						num = pow(a, b);
						N.Push(num);
						break;
					default:
						break;
				}
				S.Pop(e);
			}
		}
		else if((S.GetTop(e) && c[str[i]] > c[e]) || str[i] == '(' || !(S.GetTop(e))){ //���������ţ������ȼ�����ջ��Ԫ�أ�ѹ������� 
			S.Push(str[i]); 
		}
		else if(S.GetTop(e) && c[str[i]] <= c[e]){ //���ȼ�С�ڵ���ջ��Ԫ�أ��׳�ջ��Ԫ��ֱ�����ȼ�����ջ��Ԫ�أ�ѹ������� 
			while(S.GetTop(e) && c[str[i]] <= c[e]){
				N.Pop(b);
				N.Pop(a);
				S.Pop(e);
				switch(e){
					case '+':
						num = a + b;
						N.Push(num);
						break;
					case '-':
						num = a - b;
						N.Push(num);
						break;
					case '*':
						num = a * b;
						N.Push(num);
						break;
					case '/':
						num = a / b;
						N.Push(num);
						break;
					case '^':
						num = pow(a, b);
						N.Push(num);
						break;
					default:
						break;
				}
			}
			S.Push(str[i]);
		}
		i++;
		return 1;
	}
	//������Ч�������������0 
	else return 0;
}

int compute(char * str, int &i, float &value, int times);//����FUNction������Ҫ�����������ڴ�ǰ������ 

//�Ժ����Ĵ�������sin��cos��ln��log 
int FUNction(stackN &N, char *str, int &i)//N������ջ��str�������ַ�����i�Ƕ������ַ��±� 
{
	int flagC = 0;//��־���������� 
	if(str[i] == 's' && str[++i] == 'i' && str[++i] == 'n'){
		flagC = 1;
	}
	else if(str[i] == 'c' && str[++i] == 'o' && str[++i] == 's'){
		flagC = 2;
	}
	else if(str[i] == 'l'){
		i++;
		if(str[i] == 'n'){
			flagC = 3;
		}
		else if(str[i] == 'o' && str[++i] == 'g'){
			flagC = 4;
		}
	}
	if(flagC){//�к���
		i++;
		float num;
		if(compute(str, i, num, 2)){//����f(x)��x�ļ��� 
			switch(flagC){
				case 1:
					N.Push(sin(num));
					break;
				case 2:
					N.Push(cos(num));
					break;
				case 3:
					N.Push(log(num));
					break;
				case 4:
					N.Push(log10(num));
					break;
				default:
					break;
			}
			return 1;
		}
		else return 0;//��ͬ����Ч 
	}
	else return 0;
}

//���ڴ�����ֺ����ĵ��ù�ϵ������������Ľ�� 
int compute(char * str, int &i, float &value, int times)//str�������ַ�����i�Ƕ������ַ��±꣬value�Ǽ���Ľ����times���ڸ�֪�ǣ����������е��õ�Ϊ1����FUNction�����е��õ�Ϊ2 
{
	stackOP S;
	stackN N;
	char e;
	int flag = 0;//�����ж�FUNtion�����е��õ�compute�ڵ�operate�Ƿ�ִ�� 
	if(times == 1){//�������е��õ� 
		for(;str[i] != '\0' && i < 1000 && !(N.StackLengh() == 1 && S.StackLengh() == 1 && S.GetTop(e) && e == '='); ){
			if(number(N, str, i) || operate(S, N, str, i) || FUNction(N, str, i));
			else return 0;
		}
	}
	else if(times == 2){//FUNction�����е��õ� 
		for(; str[i] != '\0' && i < 1000 && !(N.StackLengh() == 1 && S.StackLengh() == 0);){
			if(number(N, str, i) || (flag = operate(S, N, str, i)) || FUNction(N, str, i)){
				if(flag){//ִ��operate 
					S.GetTop(e);
					if(e != '(') return 0;//��������������Ϊ������������Ч���� 
				}
				else if(N.StackLengh() == 1 && S.StackLengh() == 0){
					break;
				}
			}
			else return 0;
		}
	}
	N.Pop(value);
	return 1;
}

int main()
{
	float value;
	char * str;
	int valid;
	int i = 0;
	
	cout<<"Please input the formula you want to compute(end with '='):";
	str = new char[1000]; //���붯̬�ڴ�
	if(!str){
		cout<<"Fail to apply memory"<<endl;
		exit(0);
	} 
	
	cin.getline(str, 1000);//�����ַ��� 
	valid = compute(str, i, value, 1);//����compute�жϵ��Ƿ���Ч 
	if(valid) cout<<"The value of the formula is: "<<value<<endl;
	else cout<<"INPUT ERROR!"<<endl;
	
	delete []str;//�����̬�ڴ� 
	return 0;
}
