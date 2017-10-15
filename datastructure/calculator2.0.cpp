#include<iostream>
#include<cstdlib>
#include<cmath>
using namespace std;

const int STACK_INIT_SIZE=100;
const int STACK_INCREMENT=10;

//栈 
class stack
{
	public:
		stack(){}
		~stack(){}
	protected:
		int stacksize;//栈的大小 
};

//存入数的栈 
class stackN: public stack
{
	public:
		stackN(){//构造函数 
			InitStack();
		}
		~stackN(){//析构函数 
			DestroyStack();
		} 
		void InitStack(){//初始化 
			base  = (float *)malloc(STACK_INIT_SIZE*sizeof(float));
			if(!base){
				exit(1);
			}
			top = base;
			stacksize = STACK_INIT_SIZE;
		}
		int GetTop(float &e){//得到栈顶元素e 
			if(base == top){
				return 0;
			}
			e = *(top - 1);
			return 1;
		}
		int Push(float e){//压入 
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
		int Pop(float &e){//弹出 
			if(base == top){
				return 0;
			}
			e = * --top;
			return 1;
		}
		void DestroyStack(){//销毁栈 
			free(base);
		}
		void clearStack(){//将栈置为空栈 
			while(base != top){
				top--;
			}
		}
		int EmptyStack(){//判断栈是否为空 
			if(top == base){//是，返回1 
				return 1;
			}
			else{//不是，返回0 
				return 0;
			}
		}
		int StackLengh(){//栈的元素个数 
			return (top - base);
		}
	private: 
		float *base;//指向栈底 
		float *top; //指向栈顶 
};

//存入运算符的栈 
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

//对于数的操作，按字符读入数字，然后把他们转化成一个浮点数，存储在栈中 
int number(stackN &N, char *str, int &i)//N是数的栈，str数组是字符串，i是读到的字符下标 
{
	//如果是有效的数字，返回1 
	if(str[i] >= '0' && str[i] <= '9'){
		float snum, num;
		snum = num = 0;
		while(str[i] >= '0' && str[i] <= '9'){
			num = num*10 + str[i]-'0';
			i++;
		}
		if(str[i] == '.'){//是小数 
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
	
	//如果不是有效的数字，返回0 
	else return 0;
}

//对于运算符的操作，运用后缀表达式 
int operate(stackOP &S, stackN &N, char *str, int &i)//S是运算符的栈，N是数的栈，str数组是字符串，i是读到的字符下标 
{
	char e;
	int c[300];
	float num, a, b;
	
	//运算符优先级的设置 
	c['('] = c['='] = 0;
	c['+'] = c['-'] = 1;
	c['*'] = c['/'] = 2;
	c['^'] = 3;
	
	//如果是有效的运算符，返回1 
	if(str[i] == '(' || str[i] == ')' || str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^' || str[i] == '='){
		if( str[i] == ')'){ //右括号，抛出栈中元素直到左括号 
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
		else if((S.GetTop(e) && c[str[i]] > c[e]) || str[i] == '(' || !(S.GetTop(e))){ //不是右括号，且优先级大于栈顶元素，压入运算符 
			S.Push(str[i]); 
		}
		else if(S.GetTop(e) && c[str[i]] <= c[e]){ //优先级小于等于栈顶元素，抛出栈顶元素直到优先级大于栈顶元素，压入运算符 
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
	//不是有效的运算符，返回0 
	else return 0;
}

int compute(char * str, int &i, float &value, int times);//由于FUNction函数中要调用它，故在此前先声明 

//对函数的处理，包括sin，cos，ln和log 
int FUNction(stackN &N, char *str, int &i)//N是数的栈，str数组是字符串，i是读到的字符下标 
{
	int flagC = 0;//标志，函数类型 
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
	if(flagC){//有函数
		i++;
		float num;
		if(compute(str, i, num, 2)){//对于f(x)的x的计算 
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
		else return 0;//等同于无效 
	}
	else return 0;
}

//用于处理各种函数的调用关系，计算器计算的结果 
int compute(char * str, int &i, float &value, int times)//str数组是字符串，i是读到的字符下标，value是计算的结果，times用于告知是：是主函数中调用的为1，是FUNction函数中调用的为2 
{
	stackOP S;
	stackN N;
	char e;
	int flag = 0;//用于判断FUNtion函数中调用的compute内的operate是否执行 
	if(times == 1){//主函数中调用的 
		for(;str[i] != '\0' && i < 1000 && !(N.StackLengh() == 1 && S.StackLengh() == 1 && S.GetTop(e) && e == '='); ){
			if(number(N, str, i) || operate(S, N, str, i) || FUNction(N, str, i));
			else return 0;
		}
	}
	else if(times == 2){//FUNction函数中调用的 
		for(; str[i] != '\0' && i < 1000 && !(N.StackLengh() == 1 && S.StackLengh() == 0);){
			if(number(N, str, i) || (flag = operate(S, N, str, i)) || FUNction(N, str, i)){
				if(flag){//执行operate 
					S.GetTop(e);
					if(e != '(') return 0;//函数后的运算符不为左括号则是无效操作 
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
	str = new char[1000]; //申请动态内存
	if(!str){
		cout<<"Fail to apply memory"<<endl;
		exit(0);
	} 
	
	cin.getline(str, 1000);//读入字符串 
	valid = compute(str, i, value, 1);//返回compute判断的是否有效 
	if(valid) cout<<"The value of the formula is: "<<value<<endl;
	else cout<<"INPUT ERROR!"<<endl;
	
	delete []str;//清除动态内存 
	return 0;
}
