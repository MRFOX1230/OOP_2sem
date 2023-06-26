#include <iostream>
using namespace std;
class MyArrayParent
{
protected:
	//сколько памяти выделено?
	int capacity;
	//количество элементов - сколько памяти используем
	int count;
	//массив
	double* ptr;
public:
	//Конструкторы
	//По умолчанию (имея только память выделенную под массив)
	MyArrayParent(int Dimension=100)
	{
		if (Dimension <= 0)
			throw "Length isn't correct!";
		else
		{
			cout << "\nMyArray constructor";
			ptr = new double[Dimension];
			if (ptr == NULL)
				throw "Empty massive!";
			capacity = Dimension;
			count = 0;
		}
	}
	//Существующий массив
	MyArrayParent(const double* arr, int len)
	{
		cout << "\nMyArray constructor";
		if (ptr != nullptr)
		{
			delete[] ptr;
		}
		if (arr == NULL or len <= 0)
		{
			throw "Massive or length isn't correct!";
		}
		else
		{
			ptr = new double[len];
			if (ptr == NULL)
				throw "Empty massive!";
			int k = 0;
			for (int i = 0; i < len; i++)
			{
				ptr[i] = arr[i];
				k += 1;
			}
			capacity = len + 10;
			count = len;
		}

	}
	//Существющий массив с запасом выделенной памяти
	MyArrayParent(const double* arr, int count0, int capacity0)
	{
		if (capacity0 >= count0 and count0 > 0 and arr != NULL)
		{
			cout << "\nMyArray constructor";
			if (ptr != nullptr)
			{
				delete[] ptr;
			}
			ptr = new double[capacity0];
			if (ptr == NULL)
				throw "No memory for massive";
			int k = 0;
			for (int i = 0; i < count0; i++)
			{
				ptr[i] = arr[i];
				k += 1;
			}
			capacity = capacity0;
			count = count0;
		}
		else
			throw "Not correct value";

	}
	//Деструктор
	~MyArrayParent()
	{
		cout << "\nMyArray destructor";
		if (ptr != NULL)
		{
			delete[] ptr;
			ptr = NULL;
		}
	}


	//Обращение к полям
	int Capacity() const
	{ return capacity; }
	int Size() const
	{ return count; }
	double GetComponent(int index) const
	{
		if (index >= 0 and index < count)
			return ptr[index];
		//Исключение
		else
			throw "Out of massive";
	}
	void SetComponent(int index, double value)
	{
		if (index >= 0 and index < count)
			ptr[index] = value;
		//Исключение
		else
			throw "Out of massive";
	}


	//Добавление в конец нового значения
	void push(double value)
	{
		if (count < capacity)
		{
			ptr[count] = value;
			count++;
		}
		else
		{
			throw "Out of memory!";
		}
	}

	//Удаление элемента с конца
	void RemoveLastValue()
	{
		if (count > 0)
			count--;
		else
			throw "Empty massive";
	}
	//Перегрузка оператора []
	double &operator[](int index)
	{
		if (count > 0 and 0 <= index < count)
		{
			return ptr[index];
		}
		else
			throw "Index isn't correct";
	}
	MyArrayParent operator=(const MyArrayParent& V)
	{
		cout << "\noperator = ";
		//оператор =
		//arr1 = arr2 = arr3; где arr_i - объекты нашего класса
		if (this == &V)
		{
			return V;
		}
		else
		{
			this->capacity = V.capacity;
			this->count = V.count;
			if (this->ptr != nullptr)
			{
				delete[] this->ptr;
				this->ptr = NULL;
			}
			this->ptr = new double[V.capacity];
			if (this->ptr == NULL)
				throw "No memory for massive";
			for (int i = 0; i < V.count; i++)
			{
				this->ptr[i] = V.ptr[i];
			}

			return *this;
		}
	}


	//Создание копии объекта - в основном, при возвращении результата из функции / передаче параметров в функцию
	MyArrayParent(const MyArrayParent& V)
	{
		cout << "\nCopy constructor";
		this->capacity = V.capacity;
		this->count = V.count;
		this->ptr = new double[V.capacity];
		if (this->ptr == NULL)
			throw "No memory for massive";
		for (int i = 0; i < V.count; i++)
		{
			this->ptr[i] = V.ptr[i];
		}
	}

	//Вывод
	void print() const
	{
		cout << "\nMyArr, size: " << count << ", values: {";
		int i = 0;
		for (i = 0; i < count; i++)
		{
			cout << ptr[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "}";
	}

	//Поиск элемента в массиве (значений, встречающихся больше 2 раз)
	int* IndexOf() const
	{
		if (count > 2)
		{
			double* searchindex = new double[count];
			int* timemas = new int[count];
			if (searchindex == NULL or timemas == NULL)
				throw "No memory for massive";
			else
			{
				for (int _ = 0; _ < count; _++)
				{
					searchindex[_] = 0;
				}


				for (int i = 0; i < count; i++)
				{
					for (int _ = 0; _ < count; _++)
					{
						timemas[_] = 0;
					}
					int k = 1; //счетчик кол-ва числа в массиве
					timemas[i] = 1;
					for (int j = (i + 1); j < count; j++)
					{
						if (ptr[j] == ptr[i])
						{
							timemas[j] = 1;
							k += 1;
						}
					}
					if (k > 2)
					{
						for (int s = 0; s < count; s++)
						{
							if (timemas[s] == 1)
							{
								searchindex[s] = 1;
							}
						}
					}
				}


				int t = 0;
				for (int _ = 0; _ < count; _++)
				{
					if (searchindex[_] == 1)
					{
						t += 1;
					}
				}
				int* index = new int[t];
				if (index == NULL)
					throw "No memory for massive";
				else
				{
					int l = 0;
					for (int m = 0; m < count; m++)
					{
						if (searchindex[m] == 1)
						{
							index[l] = m;
							l += 1;
						}
					}
				}
				delete[] searchindex;
				delete[] timemas;
				searchindex = NULL;
				timemas = NULL;
				return index;
			}
		}
		else
			throw "Lenth of massive is less 3";
	}
	
	//Поиск индекса элемента по первому попавшемуся значению
	int Search(double num) const
	{
		if (count < 1)
			throw "Empty massive";
		for (int i = 0; i < count; i++)
		{
			if (ptr[i] == num)
				return i;
		}
	}
};
class MyArrayChild : public MyArrayParent
{
public:
	//Используем конструктор родителя.
	MyArrayChild(int Dimension=100) : MyArrayParent(Dimension)
	{
		cout << "\nMyArrayChild constructor";
	}
	MyArrayChild(const double* arr, int len) : MyArrayParent(arr, len)
	{
		cout << "\nMyArrayChild constructor";
	}
	MyArrayChild(const double* arr, int count0, int capacity0) : MyArrayParent(arr, count0, capacity0)
	{
		cout << "\nMyArrayChild constructor";
	}
	~MyArrayChild() { cout << "\nMyArrayChild destructor\n"; }
	
	//Удаление элемента по индексу
	void RemoveAt(int index)
	{
		if (count > 0 and 0 <= index < count)
		{
			double* timemas = new double[capacity];
			if(timemas == NULL)
				throw "No memory";
			else
			{
				for (int i = 0; i < index; i++)
				{
					timemas[i] = ptr[i];
				}
				for (int j = index + 1; j < count; j++)
				{
					timemas[j - 1] = ptr[j];
				}
				count--;
				delete[] ptr;
				ptr = NULL;
				ptr = timemas;
			}
		}
		else
			throw "Index isn't correct";
	}
	
	//Поиск
	virtual int* IndexOf() const
	{
		if (count > 0)
		{
			double* searchindex = new double[count];
			int* timemas = new int[count];
			if (searchindex == NULL or timemas == NULL)
				throw "No memory for massive";
			else
			{
				for (int _ = 0; _ < count; _++)
					searchindex[_] = 0;

				for (int i = 0; i < count; i++)
				{
					for (int _ = 0; _ < count; _++)
					{
						timemas[_] = 0;
					}
					int k = 1; //счетчик кол-ва числа в массиве
					timemas[i] = 1;
					for (int j = (i + 1); j < count; j++)
					{
						if (ptr[j] == ptr[i])
						{
							timemas[j] = 1;
							k += 1;
						}
					}
					if (k > 2)
					{
						for (int s = 0; s < count; s++)
						{
							if (timemas[s] == 1)
							{
								searchindex[s] = 1;
							}
						}
					}
					delete[] timemas;
					timemas = NULL;
					timemas = new int[count];
					if (timemas == NULL)
						throw "No memory for massive";
				}


				int t = 0;
				for (int _ = 0; _ < count; _++)
				{
					if (searchindex[_] == 1)
					{
						t += 1;
					}
				}
				int* index = new int[t];
				if (index == NULL)
					throw "No memory for massive";
				int l = 0;
				for (int m = 0; m < count; m++)
				{
					if (searchindex[m] == 1)
					{
						index[l] = m;
						l += 1;
					}
				}

				delete[] searchindex;
				searchindex = NULL;
				delete[] timemas;
				timemas = NULL;
				return index;
			}
		}
		else
			throw "Empty massive";
	}
	
	//Вставка элемента
	void InsertAt(double value, int index)
	{
		if (count > 0 and 0 <= index < count)
		{
			ptr[index] = value;
		}
		else
			throw "Index isn't correct";
	}
	
};
class MyArraySorted : public MyArrayChild
{
public:
	//предполагается, что массив отсортирован
	//Используем конструктор наследника
	MyArraySorted(int Dimension=100) : MyArrayChild(Dimension)
	{
		cout << "\nMyArraySorted constructor";
	}
	MyArraySorted(const double* arr, int len) : MyArrayChild(arr, len)
	{
		cout << "\nMyArraySorted constructor";
	}
	MyArraySorted(const double* arr, int count0, int capacity0) : MyArrayChild(arr, count0, capacity0)
	{
		cout << "\nMyArraySorted constructor";
	}
	~MyArraySorted() { cout << "\nMyArraySorted destructor\n"; }
	
	//Поиск при отсортированном массиве
	int* IndexOf() const
	{
		if (count > 0)
		{
			int* index = new int[count]; //список с найденными индексами
			if (index == NULL)
				throw "No memory for massive";
			int n = 0; //кол-во элементов в конечном списке индексов
			double x = 0; //число
			int k = 1; //счетчик числа
			int* timemas = new int[count]; //временный массив индексов числа
			if (timemas == NULL)
				throw "No memory for massive";
			for (int i = 0; i < count; i++)
			{
				if (ptr[i] != x)
				{
					if (k > 2)
					{
						for (int j = 0; j < k; j++)
						{
							index[n] = timemas[j];
							n++;
						}
					}
					x = ptr[i];
					k = 1;
					delete[] timemas;
					timemas = NULL;
					timemas = new int[count];
					if (timemas == NULL)
						throw "No memory for massive";
					timemas[k - 1] = i;
				}
				else
				{
					k += 1;
					timemas[k - 1] = i;
				}
			}
			delete[] timemas;
			timemas = NULL;
			return index;
		}
		else
			throw "Empty massive";
	}
	
	//Вставка с учетом сохранения отсортированности массива
	void push(double value)
	{
		if (count == 0 and capacity > count)
		{
			ptr[count] = value;
			count++;
		}
		else if (count > 0 and capacity > count)
		{
			int b = count;
			for (int i = 0; i < count; i++)
			{
				if (value < ptr[i])
				{
					b = i - 1;
					break;
				}
			}
			count++;
			if (b != count + 1)
			{
				for (int j = (count - 1); j > (b - 1); j--)
				{
					ptr[j + 1] = ptr[j];
				}
				ptr[b] = value;
			}
			else
				ptr[b] = value;
		}
		else
			throw "Empty or full massive";
	}
};
int main()
{
	try
	{
		if (true)
		{
			MyArrayParent arr;
			int i = 0;
			for (i = 0; i < 10; i++)
			{
				arr.push(i);
			}
			MyArrayParent p1;
			p1 = arr;
			p1.print();
			p1[1] = 2;
			p1 = p1;
			p1.print();
			cout << "\n";
		}

		////Для проверки
		//double* mas = new double[10] {1, 2, 3, 3, 3, 4, 5, 6, 7, 8};
		//MyArraySorted test = MyArraySorted(mas, 10);
		//test.print();
		//test.push(3);
		//test.print();
		////


		char c; cin >> c;
		return 0;
	}
	catch (const char* error)
	{
		cout << error;
	}
}



