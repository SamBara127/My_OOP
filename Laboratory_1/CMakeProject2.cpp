// CMakeProject2.cpp: определяет точку входа для приложения.
//

#include "CMakeProject2.h"

bool cmp(const std::pair<std::string, int>& p1, const std::pair<std::string, int>& p2)
{
	return p1.second > p2.second;
}

int main(int argc,char** argv)
{
	//argc = 3;
	//argv[0] = "CMakeProject2.exe";
	//argv[1] = "input.txt";
	//argv[2] = "output.txt";
	setlocale(0, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int x = 0;
	if (argc < 3) 
	{
		std::cerr << "Слишком мало параметров!" << std::endl;
		std::cerr << ">>Прервано!" << std::endl;
		exit(1);
	} else if (argc > 3)
	{
		std::cerr << "Слишком много параметров!" << std::endl;
		std::cerr << ">>Прервано!" << std::endl;
		exit(1);
	}
	std::ifstream fin(argv[1]);
	if (fin.fail())
	{
		std::cerr << "Входной файл отсутсвует в данной директории!" << std::endl;
		std::cerr << ">>Прервано!" << std::endl;
		exit(1);
	}
	std::ofstream fout(argv[2]);
	std::string valf;
	std::string vor;
    int32_t i = 0, a = 0,k=0,fl=0;
	std::getline(fin, valf);
	if (!valf.length() && fin.eof())
	{
		std::cout << "Невозможно записать данные: файл пустой" << std::endl;
		std::cout << ">>Прервано!" << std::endl;
		exit(0);
	}
	std::cout << "Обработка данных:";
	std::map<std::string, int> m;
	int con = 0, cont = 0, conta = 0, sum = 0, it =0;
	while (1)
	{
		if (fin.eof()) break;
		if (valf.length() == 0)
		{
			std::getline(fin, valf);
			continue;
		}
		fl = 1;
		a = valf.length();
		while (i != a)
		{
			if (isalnum(valf[i]) && fl == 1) k = i;
			if (isalnum(valf[i])) fl = 0;
			if ((!isalnum(valf[i])) && fl == 0)
			{
				for (int j = k; j < i; j++)
				{
					vor += valf[j];
				}
				if (m.find(vor) == m.end())/// убрать для ускорения работы
				{
					m.insert(std::pair<std::string, int>(vor, 1));
				}
				else
				{
					m[vor]++;
				}
				//std::cout << vor << std::endl;
				vor = "";
				k = i + 1;
				fl = 1;
			}
			i++;
		}
		if (fl == 0)
		{
			for (int j = k; j < i; j++)
			{
				vor += valf[j];
			}
			if (m.find(vor) == m.end())
			{
				m.insert(std::pair<std::string, int>(vor, 1));
			}
			else
			{
				m[vor]++;
			}
			//std::cout << vor << std::endl;
		}
		vor = "";
		k = 0;
		i = 0;
		if (fin.eof()) break;
		std::getline(fin, valf);
		it++;
		//std::cout << "ITER_LINE -> " << it << " = " << valf << '\n';
	}

	std::vector<std::pair<std::string, int> > v(m.begin(), m.end());
	sort(v.begin(), v.end(), cmp);

	//for (int i = 0; i < v.size(); ++i)
	//	std::cout << v[i].first << " : " << v[i].second << std::endl;

	fout << "WORDS:,";

	for (int i = 0; i < v.size(); ++i)
	{
		fout << v[i].first << ',';
	}
	fout << '\n';
	fout << "FREQ:,";
	for (int i = 0; i < v.size(); ++i)
	{
		fout << v[i].second << ',';
		sum += v[i].second;
	}
	fout << '\n';
	fout << "FREQ(%):,";
	for (int i = 0; i < v.size(); ++i)
	{
		fout << (v[i].second * 100) / sum << ',';
	}
	/*
	for (auto it = m.begin(); it != m.end(); ++it)// скопировать в вектор и с помощью sort просортировать
	{
		if (it->second > con) con = it->second;
	}
	cont = con;
	conta = con;
	fout << "WORDS:,";
	while (con != 0)
	{
		for (auto it = m.begin(); it != m.end(); ++it)
		{
			if (it->second == con)
			{
				fout << it->first << ',';
			}
		}
		con--;
	}
	fout << '\n';
	fout << "FREQ:,";
	while (cont != 0)
	{
		for (auto it = m.begin(); it != m.end(); ++it)
		{
			if (it->second == cont)
			{
				fout << it->second << ',';
				sum += it->second;
			}
		}
		cont--;
	}
	fout << '\n';
	fout << "FREQ(%):,";
	while (conta != 0)
	{
		for (auto it = m.begin(); it != m.end(); ++it)
		{
			if (it->second == conta)
			{
				fout << (it->second * 100) / sum << ',';
			}
		}
		conta--;
	}
	*/
	std::cout << '\n';

	/*
	for (auto it = m.begin(); it != m.end(); ++it)
	{
		std::cout << it->first << " : " << it->second << std::endl;
	}
	*/
	std::cout << ">>Успешно!" << std::endl;
	return 0;	
}