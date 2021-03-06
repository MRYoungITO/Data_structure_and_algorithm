#include <stdio.h>
#include <iostream>
#include "expression.h"

using namespace std;

//比较lhs 的优先级是否不高于rhs，rhs 表示栈顶的符号
bool isLarger(const int& lhs, const int& rhs) {

	if ((rhs == '+' || rhs == '-') && (lhs == '*' || lhs == '/')) {
		return true;
	}

	return false;
}

int operate(int left, int right, int op) { //对运算符求值

	int result = 0;
	cout << "left:" << left << " right:" << right << (char)op << endl;
	switch (op)
	{
	case '+':
		result = left + right;
		break;
	case '-':
		result = left - right;
		break;
	case '*':
		result = left * right;
		break;
	case '/':
		result = left / right;
		break;
	default:
		break;
	}
	cout << "result: " << result << endl;

	return result;
}

int calculate(string input)
{
	SqStack data_stack; //操作数堆栈
	SqStack opt_stack; //运算符堆栈 
	int status = 0; //0-接受左操作数1-接受运算符"+-*/" 2-接受右操作数
	int ldata = 0, rdata = 0;
	char last_opt = '\0';

	//初始化栈：操作数和操作符
	InitStack(data_stack);
	InitStack(opt_stack);

	for (int i = 0; i < input.length(); i++) {
		if (isspace(input[i])) continue; //空格键等忽略掉
		switch (status) {
		case 0:
			if (isdigit(input[i])) {
				ldata *= 10;
				ldata += input[i] - '0';
			}
			else {
				cout << "得到左操作数:" << ldata << endl;
				PushStack(data_stack, ldata); //左操作数入栈
				i--;
				status = 1;
			}
			break;
		case 1:
			if (input[i] == '+' || input[i] == '-' || input[i] == '*' ||
				input[i] == '/') {
				if (IsEmpty(opt_stack)) { //第一个运算符,暂时不做任何处理，运算符先入栈保存
					cout << "符号栈为空" << endl;
					PushStack(opt_stack, input[i]); //操作符入栈
					cout << "符号" << (char)input[i] << "入栈" << endl;
					status = 2;
				}
				else { //非第一个运算符，则与之前的运算符比较优先级
					cout << "isLarger:" << (char)(*GetTop(opt_stack)) << " &" << input[i] << endl;
					if (isLarger(input[i], *GetTop(opt_stack))) {
						cout << "true" << endl;
						PushStack(opt_stack, input[i]); //操作符入栈
						cout << "符号" << (char)input[i] << "入栈" << endl;
						status = 2;
						rdata = 0;
					}
					else { //当前运算符的优先级不高于前一个运算符，则计算前一个运算符的值
						int left = 0, right = 0;
						int opt;
						cout << "false" << endl;
						do {
							PopStack(data_stack, right);
							PopStack(data_stack, left);
							PopStack(opt_stack, opt);
							cout << "符号" << (char)opt << "出栈" << endl;
							cout << "计算前一个运算符" << (char)opt << endl;
							int result = operate(left, right, opt);
							PushStack(data_stack, result);
						} while (!IsEmpty(opt_stack) && !isLarger(input[i],
							*GetTop(opt_stack)));

						PushStack(opt_stack, input[i]);
						cout << "符号" << (char)input[i] << "入栈" << endl;
						status = 2;
						rdata = 0;
					}
				}
			}
			else if (input[i] == '=') {//计算结果
				int opt, result;
				do {
					PopStack(data_stack, rdata);
					PopStack(data_stack, ldata);
					PopStack(opt_stack, opt);
					result = operate(ldata, rdata, opt);
					PushStack(data_stack, result);
				} while (!IsEmpty(opt_stack));
				return result;
			}
			else {
				cerr << "输入运算符错误！" << endl;
			}
			break;
		case 2:
			if (isdigit(input[i])) {
				rdata *= 10;
				rdata += input[i] - '0';
			}
			else {
				cout << "得到右操作数:" << rdata << endl;
				PushStack(data_stack, rdata); //右操作数入栈
				i--;
				status = 1;
			}
			break;
		}
	}
	return -1;//最后的结果为栈顶元素
}

int main(int argc, char const* argv[])
{
	string str = "12+3*6/3+4*5=";
	cout << calculate(str) << endl;
	system("pause");
	return 0;
}