// Practic1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
class Vector
{
private:
	//координаты вектора
	double x;
	double y;
public:
	//конструкторы
	Vector()
	{
		x = 0; y = 0; 
	}
	Vector(double X)
	{
		x = X; y = 0;
	}
	Vector(double X, double Y)
	{
		x = X; y = Y;
	}
	Vector(const Vector& V)
	{
		x = V.x; y = V.y;
	}
	 double operator & (const Vector& V) const
	{	
		Vector R;

		double a1 = x;
		double a2 = y;
		double b1 = V.x;
		double b2 = V.y;

		double result = (a1 * b1 + a2 * b2) / (sqrt(b1 * b1 + b2 * b2));

		//R.x = result * b1 / sqrt(b1 * b1 + b2 * b2);
		//R.y = result * b2 / sqrt(b1 * b1 + b2 * b2);

		return result;
	}

	friend Vector operator / (double n, const Vector& V);

	void print() const
	{
		cout<< "x: " << x << endl << "y: " << y << endl << endl;
	}
	void printx() const
	{
		cout << "Projection Vector 1 on x:\n";
		cout << x << endl;
	}
	void printy() const
	{
		cout << "Projection Vector 1 on y:\n";
		cout << y << endl;
	}
};

Vector operator / (double n, const Vector& V)
{
	Vector Res;
	Res.x = n / V.x;
	Res.y = n / V.y;
	return Res;

}

int main()
{
	Vector V1(12, 5);
	Vector V2(4, 1);
	double n = 2;

	cout << "Vector 1:\n";
	V1.print();
	cout << "Vector 2:\n";
	V2.print();
	V1.printx();
	V1.printy();

	double projection = V1 & V2;
	cout << "Projection Vector 1 on Vector 2:\n";
	cout << projection << endl;


	Vector V4 = operator / (n, V1);
	cout << "\nn:\n" << n << endl << "n/Vector 1:\n";
	V4.print();


	char c; std::cin >> c;
	return 0;
}









// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
