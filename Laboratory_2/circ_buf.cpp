#include"circ_buf.h"

CircularBuffer::CircularBuffer()
{
	std::cout << "Создание кольцевого буфера...";
	main_buff.buffer = new value_type[1];
	main_buff.size = 0;
	main_buff.capacity = 1;
	main_buff.head = 0;
	main_buff.tail = 0;
	std::cout << "     OK!\n";
}

CircularBuffer::~CircularBuffer()
{
	std::cout << "Удаление кольцевого буфера...";
	delete[] main_buff.buffer;
	main_buff.capacity = 0;
	main_buff.size = 0;
	main_buff.head = 0;
	main_buff.tail = 0;
	std::cout << "     OK!\n";
}

CircularBuffer::CircularBuffer(const CircularBuffer& cb)
{
	std::cout << "Создание копии кольцевого буфера...";
	main_buff.buffer = new value_type[cb.main_buff.capacity];
	main_buff.capacity = cb.main_buff.capacity;
	main_buff.size = cb.main_buff.size;
	main_buff.head = cb.main_buff.head;
	main_buff.tail = cb.main_buff.tail;
	for (int i = 0; i < main_buff.capacity; i++)
	{
		main_buff.buffer[i] = cb.main_buff.buffer[i];
	}
	std::cout << "     OK!\n";
}

CircularBuffer::CircularBuffer(CircularBuffer&& cb) noexcept
{
	std::cout << "Перемещение кольцевого буфера...";
	main_buff.buffer = new value_type[cb.main_buff.capacity];
	main_buff.capacity = cb.main_buff.capacity;
	main_buff.size = cb.main_buff.size;
	main_buff.head = cb.main_buff.head;
	main_buff.tail = cb.main_buff.tail;
	for (int i = 0; i < main_buff.capacity; i++)
	{
		main_buff.buffer[i] = cb.main_buff.buffer[i];
	}
	delete[] cb.main_buff.buffer;
	cb.main_buff.capacity = 0;
	cb.main_buff.size = 0;
	cb.main_buff.head = 0;
	cb.main_buff.tail = 0;
	std::cout << "     OK!\n";
}

CircularBuffer::CircularBuffer(int capacity)
{
	std::cout << "Создание кольцевого буфера с емкостью = " << capacity << " ...";
	main_buff.buffer = new value_type[capacity];
	main_buff.capacity = capacity;
	main_buff.size = 0;
	main_buff.head = 0;
	main_buff.tail = 0;
	std::cout << "     OK!\n";
}

CircularBuffer::CircularBuffer(int capacity, const value_type& elem)
{
	std::cout << "Создание кольцевого буфера с емкостью = " << capacity << " и элементами = '" << elem << "' ...";
	main_buff.buffer = new value_type[capacity];
	main_buff.capacity = capacity;
	main_buff.head = 0;
	main_buff.size = main_buff.capacity;
	for (int i = 0; i < main_buff.capacity; i++)
	{
		main_buff.buffer[i] = elem;
	}
	main_buff.tail = main_buff.capacity - 1;
	std::cout << "     OK!\n";
}

value_type& CircularBuffer::operator[](int i)
{
	return main_buff.buffer[i];
}

const value_type& CircularBuffer::operator[](int i) const
{
	return main_buff.buffer[i];
}

value_type& CircularBuffer::at(int i)
{
	if (i < 0 || i >= main_buff.capacity)
	{
		throw std::out_of_range("Index out of range");
	}
	return main_buff.buffer[i];
}

const value_type& CircularBuffer::at(int i) const
{
	if (i < 0 || i >= main_buff.capacity)
	{
		throw std::out_of_range("Index out of range");
	}
	return main_buff.buffer[i];
}

value_type& CircularBuffer::front()
{
	return main_buff.buffer[main_buff.head];
}

value_type& CircularBuffer::back()
{
	return main_buff.buffer[main_buff.tail];
}

const value_type& CircularBuffer::front() const
{
	return main_buff.buffer[main_buff.head];
}

const value_type& CircularBuffer::back() const
{
	return main_buff.buffer[main_buff.tail];
}

value_type* CircularBuffer::linearize()
{
	value_type temp = NULL;
	if (main_buff.head != 0)
	{
		if (main_buff.head < main_buff.capacity / 2)
		{
			while (main_buff.head != 0)
			{
				temp = main_buff.buffer[0];
				for (int i = 0; i < main_buff.capacity - 1; i++)
				{
					main_buff.buffer[i] = main_buff.buffer[i + 1];
				}
				main_buff.buffer[main_buff.capacity - 1] = temp;
				main_buff.head = (main_buff.head - 1 + main_buff.capacity) % main_buff.capacity;
				main_buff.tail = (main_buff.tail - 1 + main_buff.capacity) % main_buff.capacity;
			}
		}
		else
		{
			while (main_buff.head != 0)
			{
				temp = main_buff.buffer[main_buff.capacity - 1];
				for (int i = main_buff.capacity - 1; i > 0; i--)
				{
					main_buff.buffer[i] = main_buff.buffer[i - 1];
				}
				main_buff.buffer[0] = temp;
				main_buff.head = (main_buff.head + 1) % main_buff.capacity;
				main_buff.tail = (main_buff.tail + 1) % main_buff.capacity;
			}
		}
	}
	return &main_buff.buffer[0];
}

bool CircularBuffer::is_linearized() const
{
	if (main_buff.head == 0)
		return true;
	else
		return false;
}

void CircularBuffer::rotate(int new_begin)
{
	assert((new_begin >= 0 && new_begin < main_buff.capacity));
	value_type temp = NULL;
	int begin = new_begin;
	if (begin != 0)
	{
		if (begin < main_buff.capacity / 2)
		{
			while (begin != 0)
			{
				temp = main_buff.buffer[0];
				for (int i = 0; i < main_buff.capacity - 1; i++)
				{
					main_buff.buffer[i] = main_buff.buffer[i + 1];
				}
				main_buff.buffer[main_buff.capacity - 1] = temp;
				main_buff.head = (main_buff.head - 1 + main_buff.capacity) % main_buff.capacity;
				main_buff.tail = (main_buff.tail - 1 + main_buff.capacity) % main_buff.capacity;
				begin--;
			}
		}
		else
		{
			while (begin != 0)
			{
				temp = main_buff.buffer[main_buff.capacity - 1];
				for (int i = main_buff.capacity - 1; i > 0; i--)
				{
					main_buff.buffer[i] = main_buff.buffer[i - 1];
				}
				main_buff.buffer[0] = temp;
				main_buff.head = (main_buff.head + 1) % main_buff.capacity;
				main_buff.tail = (main_buff.tail + 1) % main_buff.capacity;
				begin++;
				if (begin > main_buff.capacity - 1) begin = 0;
			}
		}
	}
}

void CircularBuffer::render()
{
	std::cout << "\nBUFFER : ";
	for (int i = 0; i < main_buff.capacity - 1; i++)
	{
		std::cout << i << '(' << main_buff.buffer[i] << ')' << " -> ";
	}
	std::cout << main_buff.capacity - 1 << '(' << main_buff.buffer[main_buff.capacity - 1] << ")\n";
	std::cout << "WHITCH HEAD = " << main_buff.head << "; TAIL = " << main_buff.tail << "; SIZE = " << main_buff.size << "\n\n";
	std::cout << "RESULT : {";
	for (int i = 0; i < main_buff.size - 1; i++)
	{
		std::cout << main_buff.buffer[(main_buff.head + i) % main_buff.capacity] << " , ";
	}
	if (this->empty())
		std::cout << "}\n\n";
	else
		std::cout << main_buff.buffer[main_buff.tail] << "}\n\n";
}

int CircularBuffer::size() const
{
	return main_buff.size;
}

bool CircularBuffer::empty() const
{
	return main_buff.size == 0 ? true : false;
}

bool CircularBuffer::full() const
{
	return main_buff.size == main_buff.capacity ? true : false;
}

int CircularBuffer::reserve() const
{
	return main_buff.capacity - main_buff.size;
}

int CircularBuffer::capacity() const
{
	return main_buff.capacity;
}

void CircularBuffer::set_capacity(int new_capacity)
{
	if (new_capacity > main_buff.capacity)
	{
		value_type* temp = new value_type[new_capacity];
		int old_iter = 0;
		for (int i = 0; i < main_buff.capacity; i++)
		{
			old_iter = (i + main_buff.head) % main_buff.capacity;
			temp[i] = main_buff.buffer[old_iter];
		}
		main_buff.head = 0;
		main_buff.tail = main_buff.size - 1;
		delete[] main_buff.buffer;
		main_buff.buffer = temp;
		main_buff.capacity = new_capacity;
	}
	else if (new_capacity < main_buff.capacity)
	{
		assert(!(new_capacity < main_buff.size));// Loss data!!!
		value_type* temp = new value_type[new_capacity];
		int old_iter = 0;
		for (int i = 0; i < new_capacity; i++)
		{
			old_iter = (i + main_buff.head) % main_buff.capacity;
			temp[i] = main_buff.buffer[old_iter];
		}
		main_buff.head = 0;
		main_buff.tail = main_buff.size - 1;
		delete[] main_buff.buffer;
		main_buff.buffer = temp;
		main_buff.capacity = new_capacity;
	}
}

void CircularBuffer::resize(int new_size, const value_type& item)
{
	set_capacity(new_size);
	for (int i = main_buff.size; i < main_buff.capacity; i++)
	{
		main_buff.buffer[i] = item;
	}
	main_buff.tail = main_buff.capacity - 1;
	main_buff.size = main_buff.capacity;
}

CircularBuffer& CircularBuffer::operator=(const CircularBuffer& cb)
{
	this->main_buff = cb.main_buff;
	return *this;
}

void CircularBuffer::swap(CircularBuffer& cb)
{
	Buffer temp;
	temp = main_buff;
	main_buff = cb.main_buff;
	cb.main_buff = temp;
}

void CircularBuffer::push_front(const value_type& item)
{
	if (this->empty())
	{
		main_buff.buffer[main_buff.head] = item;
		main_buff.size++;
	}
	else
	{
		main_buff.head = (main_buff.head - 1 + main_buff.capacity) % main_buff.capacity;
		main_buff.buffer[main_buff.head] = item;
		main_buff.size++;
		if (main_buff.size > main_buff.capacity) main_buff.size = main_buff.capacity;
	}
}

void CircularBuffer::push_back(const value_type& item)
{
	if (this->empty())
	{
		main_buff.buffer[main_buff.head] = item;
		main_buff.size++;
	}
	else
	{
		main_buff.tail = (main_buff.tail + 1) % main_buff.capacity;
		main_buff.buffer[main_buff.tail] = item;
		main_buff.size++;
		if (main_buff.size > main_buff.capacity) main_buff.size = main_buff.capacity;
	}
}

void CircularBuffer::pop_back()
{
	if (!(this->empty()))
	{
		main_buff.tail = (main_buff.tail - 1 + main_buff.capacity) % main_buff.capacity;
		main_buff.size--;
	}
}

void CircularBuffer::pop_front()
{
	if (!(this->empty()))
	{
		main_buff.head = (main_buff.head + 1) % main_buff.capacity;
		main_buff.size--;
	}
}

void CircularBuffer::insert(int pos, const value_type& item)
{
	int index = pos;
	if (index < 0 || index >= main_buff.size) {
		throw std::out_of_range("Index out of range");
	}
	if (this->full()) {
		throw std::out_of_range("Buffer is full");
	}
	// Расчет позиции вставки в циклическом буфере
	int insertPos = (main_buff.head + index) % main_buff.capacity;

	// Сдвигаем элементы, начиная с позиции вставки, на один вперед
	for (int i = main_buff.size; i > index; --i)
	{
		main_buff.buffer[(main_buff.head + i) % main_buff.capacity] = main_buff.buffer[(main_buff.head + i - 1) % main_buff.capacity];
	}

	// Вставляем новый элемент
	main_buff.tail = (main_buff.tail + 1) % main_buff.capacity;
	main_buff.buffer[insertPos] = item;
	main_buff.size++;
}

void CircularBuffer::clear()
{
	main_buff.size = 0;
	main_buff.head = 0;
	main_buff.tail = 0;
}

void CircularBuffer::erase(int first, int last)
{
	if (first > last)
	{
		throw std::out_of_range("Invalid index");
	}
	if (first < 0 || first >= main_buff.size || last < 0 || last >= main_buff.size) {
		throw std::out_of_range("Index out of range");
	}
	if (empty())
	{
		throw std::out_of_range("Buffer is empty!");
	}

	int F_Pos = (main_buff.head + first - 1) % main_buff.capacity;
	int L_Pos = (main_buff.head + last - 1) % main_buff.capacity;

	for (int i = 0; i < main_buff.size - L_Pos; i++)
	{
		main_buff.buffer[(F_Pos + i) % main_buff.capacity] = main_buff.buffer[(L_Pos + i) % main_buff.capacity];
	}
	main_buff.size -= L_Pos - F_Pos;
}

bool operator==(const CircularBuffer& a, const CircularBuffer& b)
{
	if (a.size() == b.size() && a.capacity() == b.capacity()) return false;
	for (int i = 0; i < a.size(); i++)
	{
		if (a[(a.front() + i)] != b[(b.front() + i)]) return false;
	}
	return true;
}

bool operator!=(const CircularBuffer& a, const CircularBuffer& b)
{
	return !(a == b);
}
