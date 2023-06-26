//Написать функцию, которая читает массив из файла,
//сортирует его указанным методом,
//записывает отсортированный массив в новый файл.
//Функция, выполняющая сортировку, должна быть выполнена в виде шаблона функции.
//Сортировки, которые нужно реализовать:
//1. Сортировка пузырьком.
//2. Поразрядная сортировка.

#include <iostream>
#include <fstream>
using namespace std;

class Mas
{
private:
	int* mas;
	int len;
public:
	Mas(const int* m, int l)
	{
		if (l < 1)
			throw "The length of massive isn't correct";
		len = l;
		mas = new int[l];
		if (mas == NULL)
			throw "Not memory for massive";
		for (int i = 0; i < l; i++)
		{
			mas[i] = m[i];
		}
	}
	Mas(string filename)
	{
		ifstream file;
		file.open(filename);
		if (!file.is_open())
			throw "Cannot read the file";
		len = 0;
		while (!file.eof())
		{
			int time;
			file >> time;
			len++;
		}
		mas = new int[len];
		if(mas == NULL)
			throw "Not memory for massive";

		file.close();
		file.open(filename);
		int k = 0;//счетчик
		while (!file.eof())
		{
			int num;
			file >> num;
			mas[k] = num;
			k++;
		}

		file.close();
	}

	void writemas(string filename) const
	{
		ofstream file;
		file.open(filename);
		if (!file.is_open())
			throw "Error of opening of the file";

		for (int x = 0; x < len; x++)
		{
			file << mas[x] << " ";
		}
		file.close();
	}
	void print() const
	{
		for (int i = 0; i < len; i++)
		{
			cout << mas[i] << " ";
		}
		cout << endl << len << endl;
	}
	int* getmas() const
	{
		int* timemas = new int[len];
		if (timemas == NULL)
			throw "Not memory for massive";
		for (int i = 0; i < len; i++)
		{
			timemas[i] = mas[i];
		}
		return timemas;
	}
	int getlen() const
	{
		return len;
	}
};

//Сортировка пузырьком
template <typename T>
void bubblesort(T* m, int l)
{
	if (m == NULL)
		throw "Massive is empty";
	if (l < 1)
		throw "Length isn't correct";
	int i = 0;
	while (i < l - 1)
	{
		int j = i + 1;
		while (j < l)
		{
			if (m[i] > m[j])
			{
				T timen = m[i];
				m[i] = m[j];
				m[j] = timen;
			}
			j += 1;
		}
		i += 1;
	}

}

//Поразрядная сортировка
template <typename T>
void radixsort(T* array, int size)
{
	if (array == NULL)
		throw "Empty massive";
	if (size < 1)
		throw "Length isn't correct";
	//Получение максимального элемента
	T max = array[0];
	for (int i = 1; i < size; i++)
		if (array[i] > max)
			max = array[i];

	//[32, 11, 15]
	const int maxn = 10;
	for (int place = 1; max / place > 0; place *= 10)
	{
		T* output = new T[size];
		if (output == NULL)
			throw "Not memory for massive";
		T* count = new T[maxn];
		if (count == NULL)
			throw "Not memory for massive";

		for (int i = 0; i < maxn; i++)
			count[i] = 0;

		for (int i = 0; i < size; i++)
			count[(array[i] / place) % 10]++;

		for (int i = 1; i < maxn; i++)
			count[i] += count[i - 1];

		for (int i = size - 1; i >= 0; i--)
		{
			output[count[(array[i] / place) % 10] - 1] = array[i];
			count[(array[i] / place) % 10]--;
		}

		for (int i = 0; i < size; i++)
			array[i] = output[i];

		delete[] count;
		delete[] output;
		count = NULL;
		output = NULL;
	}
}


int main()
{
	try
	{
		Mas test("myfile.txt");
		test.print();
		int* massive = test.getmas();
		int length = test.getlen();
		radixsort<int>(massive, length);
		Mas newmas(massive, length);
		newmas.writemas("forwrite.txt");
		newmas.print();
	}
	catch (const char* error)
	{
		cout << error;
	}
}

