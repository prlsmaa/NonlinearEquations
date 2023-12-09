#include <iostream>
#include <fstream>
using namespace std;

void readfile(ifstream& file,double& x0,double& eps, int& k, int& m)
{
	file >> x0;//начальное приближение
	file >> eps;//точность
	file >> k;//кол-во итераций
	file >> m;//кол-во отрезков
}
void writefile(ofstream& file, int ier, int l, double xx)
{
	switch (ier)
	{
	case 0:
		file << "IER 0. Решение найдено." << endl;
		file << "Число итераций: " << l << endl;
		file << "Найденное решение: " << xx << endl;
		break;
	case 1:
		file << "IER 1. Превышено число итераций." << endl;
		break;
	case 2:
		file << "IER 2. Встречено деление на 0." << endl;
		break;
	}
}

double f1(double x)
{
	return x * x * x - 27;
}
double df1(double x)
{
	return 3 * x*x;
}
double f2(double x)
{
	return exp(x*x)-1;
}
double df2(double x)
{
	return 2*x*exp(x * x);
}
double f3(double x)
{
	return x*x-16;
}
double df3(double x)
{
	return 2*x;
}
double f4(double x)
{
	return sin(x);
}
double df4(double x)
{
	return cos(x);
}
typedef double(*function)(double x);
double solution(double x0, double eps, int& ier, int k, int m, int& l, function f, function df)
{
	int i = 0;
	double xk1=0;
	double xk = x0;
	double d_f = df(x0);
	if (d_f != 0)
	{
		xk1 = xk - f(xk) / d_f;
		i++;
		while (abs(xk1 - xk) > eps&& i < k)
		{
			xk = xk1;
			if ((i + 1) % m == 0)
			{
				d_f = df(xk);
			}
			if (d_f != 0)
			{
				xk1 = xk - f(xk) / d_f;
				i++;
			}
			else
			{
				ier = 2;
			}
		}
		if (i >= k)
		{
			ier = 1;
		}
	}
	else
	{
		ier = 2;
	}
	l = i;
	return xk1;
}


int main()
{
	setlocale(LC_ALL, "RUS");
	int i;
	cout << "Введите номер теста." << endl;
	cin >> i;
	string test;
	if (i == 1)
	{
		test = "test1.txt";
	}
	else
	{
		if (i == 2)
		{
			test = "test2.txt";
		}
		else
		{
			if (i == 3)
			{
				test = "test3.txt";
			}
			else
			{
				if (i == 4)
				{
					test = "test4.txt";
				}
				else
				{
					cout << "Теста с таким номером нет." << endl;
				}
			}
		}
	}
	ifstream input(test);
	double x0=0, eps=0;
	int k=0, m=0;
	readfile(input, x0, eps, k, m);
	int ier=0, l=0;
	double xx;
	if (i == 1)
	{
		xx = solution(x0, eps, ier, k, m, l,f1,df1);
		if(ier==0)
			cout << f1(xx) << endl;
	}
	else
	{
		if (i == 2)
		{
			xx = solution(x0, eps, ier, k, m, l,f2,df2);
			if (ier == 0)
				cout << f2(xx) << endl;
		}
		else
		{
			if (i == 3)
			{
				xx = solution(x0, eps, ier, k, m, l,f3,df3);
				if (ier == 0)
					cout << f3(xx) << endl;
			}
			else
			{
				if (i == 4)
				{
					xx = solution(x0, eps, ier, k, m, l,f4,df4);
					if (ier == 0)
						cout << f4(xx) << endl;
				}
			}
		}
	}
	ofstream output("output.txt");
	writefile(output, ier, l, xx);
	system("pause");
	return 0;
}