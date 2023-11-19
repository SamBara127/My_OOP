// Laboratory_2.cpp: определяет точку входа для приложения.
//

#include "Laboratory_2.h"
#include "circ_buf.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	CircularBuffer buf(10, 'A');
	//buf.rotate(3);
	buf.render();
	buf.set_capacity(12);
	buf.render();
	buf.push_back('K');
	buf.insert(9, 'D');
	buf.pop_front();
	buf.insert(9, 'D');
	buf.render();
	buf.erase(8, 10);
	buf.render();
	
	return 0;
}
