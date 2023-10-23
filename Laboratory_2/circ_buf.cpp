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
	delete main_buff.buffer;
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
	main_buff.tail += main_buff.capacity - 1;
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
		//std::cerr << "Ошибка! Выход за границы буфера!\n";
		throw "IndexOutOfRangeException";
	}
	return main_buff.buffer[i];
}

const value_type& CircularBuffer::at(int i) const
{
	if (i < 0 || i >= main_buff.capacity)
	{
		//std::cerr << "Ошибка! Выход за границы буфера!\n";
		throw "IndexOutOfRangeException";
	}
	return main_buff.buffer[i];
}

value_type& CircularBuffer::front()
{
	std::cout << "Index of front = " << main_buff.head << '\n';
	return main_buff.buffer[main_buff.head];
}

value_type& CircularBuffer::back()
{
	std::cout << "Index of back = " << main_buff.tail << '\n';
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
				for (int i = 0; i < main_buff.capacity-1; i++)
				{
					main_buff.buffer[i] = main_buff.buffer[i + 1];
				}
				main_buff.buffer[main_buff.capacity - 1] = temp;
				main_buff.head--;
				main_buff.tail--;
				if (main_buff.tail < 0) main_buff.tail = main_buff.capacity - 1;
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
				main_buff.head++;
				main_buff.tail++;
				if (main_buff.tail > main_buff.capacity - 1) main_buff.tail = 0;
				if (main_buff.head > main_buff.capacity - 1) main_buff.head = 0;
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
				main_buff.head--;
				main_buff.tail--;
				if (main_buff.tail < 0) main_buff.tail = main_buff.capacity - 1;
				if (main_buff.head < 0) main_buff.head = main_buff.capacity - 1;
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
				main_buff.head++;
				main_buff.tail++;
				if (main_buff.tail > main_buff.capacity - 1) main_buff.tail = 0;
				if (main_buff.head > main_buff.capacity - 1) main_buff.head = 0;
				begin++;
				if (begin > main_buff.capacity - 1) begin = 0;
			}
		}
	}
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
		value_type *temp = new value_type[new_capacity];
		int old_iter = 0;
		for (int i = 0; i < main_buff.capacity; i++)
		{
			old_iter = i + main_buff.head;
			if (old_iter >= main_buff.capacity) old_iter -= main_buff.capacity;
			temp[i] = main_buff.buffer[old_iter];
		}
		main_buff.head = 0;
		main_buff.tail = main_buff.capacity - 1;
		main_buff.buffer = temp;
		main_buff.capacity = new_capacity;
	}
	else if (new_capacity < main_buff.capacity)
	{
		assert(!(new_capacity < main_buff.size));// Loss data!!!
		value_type* temp = new value_type[new_capacity];
		int old_iter = 0;
		for (int i = 0; i < main_buff.size; i++)
		{
			old_iter = i + main_buff.head;
			if (old_iter >= main_buff.capacity) old_iter -= main_buff.capacity;
			temp[i] = main_buff.buffer[old_iter];
		}
		main_buff.head = 0;
		main_buff.tail = main_buff.size - 1;
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

void CircularBuffer::push_back(const value_type& item)
{
	if (this->empty())
	{
		main_buff.buffer[main_buff.tail] = item;
		main_buff.size++;
		if (main_buff.size > main_buff.capacity) main_buff.size = main_buff.capacity;
	}
	else
	{
		main_buff.tail++;
		if (main_buff.tail >= main_buff.capacity) main_buff.tail = 0;
		main_buff.buffer[main_buff.tail] = item;
		main_buff.size++;
		if (main_buff.size > main_buff.capacity) main_buff.size = main_buff.capacity;
	}
}

void CircularBuffer::push_front(const value_type& item)
{
	if (this->empty())
	{
		main_buff.buffer[main_buff.tail] = item;
		main_buff.size++;
		if (main_buff.size > main_buff.capacity) main_buff.size = main_buff.capacity;
	}
	else
	{
		main_buff.head--;
		if (main_buff.head < 0) main_buff.head = main_buff.capacity - 1;
		main_buff.buffer[main_buff.head] = item;
		main_buff.size++;
		if (main_buff.size > main_buff.capacity) main_buff.size = main_buff.capacity;
	}
}

void CircularBuffer::pop_back()
{
	if (!(this->empty()))
	{
		main_buff.tail--;
		if (main_buff.tail < 0) main_buff.tail = main_buff.capacity - 1;
		main_buff.size--;
	}
}

void CircularBuffer::pop_front()
{
	if (!(this->empty()))
	{
		main_buff.head++;
		if (main_buff.head >= main_buff.capacity) main_buff.head = 0;
		main_buff.size--;
	}
}

void CircularBuffer::insert(int pos, const value_type& item) ///BAGGED!!
{
	int loc_pos = pos;
	
}

void CircularBuffer::erase(int first, int last) ///BAGGED!!
{

}

void CircularBuffer::clear()
{
	main_buff.size = 0;
	main_buff.head = 0;
	main_buff.tail = 0;
}

bool operator==(const CircularBuffer& a, const CircularBuffer& b)
{

}

void CircularBuffer::render()
{
	std::cout << "\nBUFFER : ";
	for (int i = 0; i < main_buff.capacity-1; i++)
	{
		std::cout << main_buff.buffer[i] << " -> ";
	}
	std::cout << main_buff.buffer[main_buff.capacity - 1] << "\n\n";
}