#include <iostream>
using namespace std;

//Изначальный класс - A
class A1
{
protected:
    int a1;
public:
    A1()
    {
        a1 = 0;
        cout << "Constructor A1 1\n";
    }
    A1(int a)
    {
        a1 = a;
        cout << "Constructor A1 2\n";
    }
    virtual void print() const
    {
        cout << "\nClass A\n";
    }
    virtual void show() const
    {
        cout << "a1 = " << a1 << endl;
    }
};

//Дочерние классы:
//от A
class B1 : virtual public A1
{
protected:
    int b1;
public:
    B1() : A1()
    {
        b1 = 0;
        cout << "Constructor B1 1\n";
    }
    B1(int b) : A1()
    {
        b1 = b;
        cout << "Constructor B1 2\n";
    }
    B1(int a, int b)
    {
        a1 = a;
        b1 = b;
        cout << "Constructor B1 3\n";
    }
    void print() const override
    {
        cout << "\nClass B1\n";
    }
    void show() const override
    {
        cout << "a1 = " << a1 << endl;
        cout << "b1 = " << b1 << endl;
    }
};
class B2 : virtual public A1
{
protected:
    int b2;
public:
    B2() : A1()
    {
        b2 = 0;
        cout << "Constructor B2 1\n";
    }
    B2(int b) : A1()
    {
        b2 = b;
        cout << "Constructor B2 2\n";
    }
    B2(int a, int b)
    {
        a1 = a;
        b2 = b;
        cout << "Constructor B2 3\n";
    }
    void print() const override
    {
        cout << "\nClass B2\n";
    }
    void show() const override
    {
        cout << "a1 = " << a1 << endl;
        cout << "b2 = " << b2 << endl;
    }
};

//от B1 и B2
class C1 : public B1, public B2
{
protected:
    int c1;
public:
    C1() : B1(), B2()
    {
        c1 = 0;
        cout << "Constructor C1 1\n";
    }
    C1(int c) : B1(), B2()
    {
        c1 = c;
        cout << "Constructor C1 2\n";
    }
    C1(int a, int b10, int b20, int c) : B1(a, b10), B2(a, b20)
    {
        c1 = c;
        cout << "Constructor C1 3\n";
    }
    void print() const override
    {
        cout << "\nClass C1\n";
    }
    void show() const override
    {
        cout << "a1 = " << a1 << endl;
        cout << "b1 = " << b1 << endl;
        cout << "b2 = " << b2 << endl;
        cout << "c1 = " << c1 << endl;
    }
};

//от C1
class D1 : public C1
{
protected:
    int d1;
public:
    D1() : C1()
    {
        d1 = 0;
        cout << "Constructor D1 1\n";
    }
    D1(int d) : C1()
    {
        d1 = d;
        cout << "Constructor D1 2\n";
    }
    D1(int a, int b10, int b20, int c, int d) : C1(a, b10, b20, c)
    {
        d1 = d;
        cout << "Constructor D1 3\n";
    }
    void print() const override
    {
        cout << "\nClass D1\n";
    }
    void show() const override
    {
        cout << "a1 = " << a1 << endl;
        cout << "b1 = " << b1 << endl;
        cout << "b2 = " << b2 << endl;
        cout << "c1 = " << c1 << endl;
        cout << "d1 = " << d1 << endl;
    }
};
class D2 : public C1
{
protected:
    int d2;
public:
    D2() : C1()
    {
        d2 = 0;
        cout << "Constructor D2 1\n";
    }
    D2(int d) : C1()
    {
        d2 = d;
        cout << "Constructor D2 2\n";
    }
    D2(int a, int b10, int b20, int c, int d) : C1(a, b10, b20, c)
    {
        d2 = d; 
        cout << "Constructor D2 3\n";
    }
    void print() const override
    {
        cout << "\nClass D2\n";
    }
    void show() const override
    {
        cout << "a1 = " << a1 << endl;
        cout << "b1 = " << b1 << endl;
        cout << "b2 = " << b2 << endl;
        cout << "c1 = " << c1 << endl;
        cout << "d2 = " << d2 << endl;
    }
};

int main()
{
    D1 test = D1(10, 5, 3, 4, 5);
    //D1 test = D1();
    test.print();
    test.show();
}
