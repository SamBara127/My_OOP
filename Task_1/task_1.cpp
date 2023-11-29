// task_1.cpp: определяет точку входа для приложения.
//

#include "task_1.h"
#include "graphic.h"

using namespace std;

void square_equation(double& a, double& b, double& c, double* x1, double* x2)
{
	double r1 = 0, r2 = 0;
	double dis = (b * b) - 4 * a * c;
	if (dis > 0)
	{
		r1 = ((b * (-1)) + sqrt(dis)) / (2 * a);
		r2 = ((b * (-1)) - sqrt(dis)) / (2 * a);
		cout << "Корня 2: " << r1 << " И " << r2 << '\n';
		x1 = &r1;
		x2 = &r2;
		plot_graph2(a, b, c, *x1, *x2);
	}
	else if (dis == 0)
	{
		r1 = (b * (-1)) / (2 * a);
		cout << "Корень 1: " << r1 << '\n';
		x1 = &r1;
		plot_graph2(a, b, c, *x1, *x1);
	} 
	else
	{
		cout << "Корней нет: " << r1 << '\n';
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	double a = 0, b = 0, c = 0;
	double* x1=nullptr,* x2=nullptr;
	cout << "Введите числа 'a', 'b', 'c': ";
	cin >> a >> b >> c;
	square_equation(a, b, c, x1, x2);
	return 0;
}
