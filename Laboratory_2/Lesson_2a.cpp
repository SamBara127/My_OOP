// Lesson_2a.cpp: определяет точку входа для приложения.
//

#include "Lesson_2a.h"
#include "circ_buf.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	CircularBuffer buf(10, 'A');
	//CircularBuffer buf_2(buf);
	CircularBuffer buf_2(10);
	//buf_2.rotate(5);
	std::cout << buf_2.front() << "\n";
	std::cout << buf_2.back() << "\n";
	std::cout << buf_2.size() << "\n";
	buf_2.render();
	for (int i = 0; i < 5; i++)
	{
		buf_2.push_back('T');
		std::cout << buf_2.front() << "\n";
		std::cout << buf_2.back() << "\n";
		std::cout << buf_2.size() << "\n";
		buf_2.render();
	}
	for (int i = 0; i < 3; i++)
	{
		buf_2.push_front('I');
		std::cout << buf_2.front() << "\n";
		std::cout << buf_2.back() << "\n";
		std::cout << buf_2.size() << "\n";
		buf_2.render();
	}
	buf_2.clear();
	std::cout << buf_2.front() << "\n";
	std::cout << buf_2.back() << "\n";
	std::cout << buf_2.size() << "\n";
	buf_2.render();
	return 0;
}
