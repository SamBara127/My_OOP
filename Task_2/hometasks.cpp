// hometasks.cpp: определяет точку входа для приложения.
//

#include "hometasks.h"

void error_throw(bool error)
{
	if (error == false)
	{
		std::cout << "Error!";
		exit(0);
	}
}

bool digits(std::string str)
{
	int cnt = 0;
	std::string clr = {};
	for (int i = 0; i < str.size(); i++)
	{
		if (isdigit(str[i]))
		{
			cnt++;
			clr.push_back(str[i]);
		}
	}
	return cnt == 11 ? true : false;
}

bool check_number(std::string num)
{
	bool emp = false, seven = false, line = false,lmem = false, bracket = false;
	for (int i = 0; i < num.size(); i++)
	{
		// проверка на допустимые символы 
		if (num[i] != ' ')
		{
			if (isalpha(num[i]) && num[i] != '-' && num[i] != '(' && num[i] != ')') return false;
			// проверка на пробелы и семерку после плюса
			if (seven == true && num[i] != '7') return false; else seven = false;
			// проверка на дубликат линий
			if (line == true && num[i] == '-') return false; else line = false;
		} // проверка на линию в конце
		else lmem = false;

		switch (num[i])
		{

		case '+':
			emp = true;
			seven = true;
			break;

		case '8':
			emp = true;

			break;

		case '-':
			if (emp == false) return false;
			line = true;
			lmem = true;
			break;

		case '(':
			bracket = true;
			break;

		case ')':
			bracket = false;
			break;

		default:
			if (emp == false && num[i] != ' ') return false;
			break;
		}
	}
	if (bracket == true) return false;
	if (lmem == true) return false;
	if (emp == false) return false;
}

void print(std::string str)
{
	int cnt = 0;
	bool plus = false;
	std::string clr = {};
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '+') plus = true;

		if (isdigit(str[i]))
		{
			cnt++;
			clr.push_back(str[i]);
		}
	}
	plus == true ? std::cout << '+' << clr << '\n' : std::cout << clr << '\n';
}

int main()
{
	std::string numb = {};
	std::cout << "Input your number: ";
	std::getline(std::cin, numb);
	error_throw(digits(numb));
	error_throw(check_number(numb));
	print(numb);
	return 0;
}
