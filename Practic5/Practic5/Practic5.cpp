#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Классы исключений
class Exception : public exception
{
protected:
    //сообщение об ошибке
    char* str;
public:
    Exception(const char* s)
    {
        str = new char[strlen(s) + 1];
        if (str == NULL)
            throw "Empty massive!";
        strcpy_s(str, strlen(s) + 1, s);
    }
    Exception(const Exception& e)
    {
        str = new char[strlen(e.str) + 1];
        if (str == NULL)
            throw "Empty massive!";
        strcpy_s(str, strlen(e.str) + 1, e.str);
    }
    ~Exception()
    {
        delete[] str;
    }
    //функцию вывода можно будет переопределить в производных классах, когда будет ясна конкретика
    virtual void print() const
    {
        cout << "Exception: " << str << endl;
    }
};
class IndexOutOfBounds : public Exception
{
public:
    IndexOutOfBounds(const char* s) : Exception(s) {}
    IndexOutOfBounds(const Exception& e) : Exception(e) {}
    ~IndexOutOfBounds() {}
};
class WrongDimensionsException : public Exception
{
public:
    WrongDimensionsException(const char* s) : Exception(s) {}
    WrongDimensionsException(const Exception& e) : Exception(e) {}
    ~WrongDimensionsException() {}
};
class WrongSizeException : public WrongDimensionsException
{
public:
    WrongSizeException(const char* s) : WrongDimensionsException(s) {}
    WrongSizeException(const Exception& e) : WrongDimensionsException(e) {}
    ~WrongSizeException() {}
};

template <class T>
class BasicClass
{
protected:
    int sizex; //размер по первому входу
    int sizey; //размер по второму
    T** mas; //двумерный массив
public:
    //Конструкторы базового класса
    BasicClass() {}
    BasicClass(int x, int y)
    {
        if (x <= 0 or y <= 0)
            throw WrongSizeException("Wrong matrix dimensions!");
        sizex = x;
        sizey = y;
        mas = new T* [x];
        if (mas == NULL)
            throw "No memory for massive";
        for (int i = 0; i < x; i++)
        {
            mas[i] = new T[y];
            if (mas[i] == NULL)
                throw "No memory for massive";
        }
        cout << "BasicClass constructor\n";
    }
    ~BasicClass()
    {
        if (mas != NULL)
        {
            for (int i = 0; i < sizex; i++)
            {
                delete[] mas[i];
                mas[i] = NULL;
            }
            delete[] mas;
            mas = NULL;
            cout << "BasicClass destructor\n";
        }
    }
};
class ChildClass : public BasicClass<double>
{
public:
    //Конструкторы дочернего класса
    ChildClass(int x, int y) : BasicClass(x, y) { cout << "ChildClass constructor\n\n"; }
    //Запись матрицы из файла
    ChildClass(string filename)
    {
        ifstream file;
        file.open(filename);
        if (!file.is_open())
            throw "Error of opening of the file";
        else
        {
            while (!file.eof())
            {
                char time;
                file >> time;
                if (!isdigit(time))
                  throw "Matrix isn't correct";
            }

            file.close();
            file.open(filename);
            sizex = 0;
            sizey = 1;
            int size = 0;
            bool piecenum = false;
            char ch;
            while (file.get(ch))
            {
                if (ch != ' ' and ch != '\n' and !piecenum)
                {
                    size++;
                    piecenum = true;
                }
                else if (ch == ' ' or ch == '\n')
                    piecenum = false;


                if (sizey == 1)
                    sizex = size;
                if (ch == '\n')
                {
                    if (size % sizex != 0)
                        throw "Matrix isn't correct";
                    sizey++;
                }

            }
            if (size % sizex != 0)
                throw "Matrix isn't correct";
            if (sizex == 0)
                throw "Empty matrix";
            sizey = size / sizex;



            mas = new double* [sizex];
            if (mas == NULL)
                throw "No memory for massive";
            for (int i = 0; i < sizex; i++)
            {
                mas[i] = new double[sizey];
                if (mas[i] == NULL)
                    throw "No memory for massive";
            }

            if (sizex > 0 and sizey > 0)
            {
                file.close();
                file.open(filename);
                int x = 0;
                int y = -1;
                while (!file.eof() and (x+1)*(y+1) < (sizex*sizey+1))
                {
                    x %= sizex;

                    if (x == 0)
                    {
                        y++;
                    }
                    double n;
                    file >> n;
                    mas[x][y] = n;
                    x++;
                }
            }
            else
                throw "Matrix isn't correct";
        }
        file.close();
    }
    ~ChildClass() { cout << "ChildClass destructor\n"; }
    

    //Заполнение массива случайными числами
    void FillingMas(int num)
    {
        for (int x = 0; x < sizex; x++)
        {
            for (int y = 0; y < sizey; y++)
            {
                mas[x][y] = rand() % num;
            }
        }
    }
    //Вывод массива
    void print() const
    {
        cout << "Matrix:" << endl;
        for (int y = 0; y < sizey; y++)
        {
            for (int x = 0; x < sizex; x++)
            {
                cout << mas[x][y] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }
    //Функция из варианта 18
    void Function(double bord) const
    {
        double border = bord; //значение из варианта для сравнения
        int* delx = new int[sizex]; //столбцы, которые нужно убрать
        if (delx == NULL)
            throw "No memory for massive";
        int cdelx = 0; //кол-во удаленных столбцов
        int* dely = new int[sizey]; //строки, которые нужно убрать
        if (dely == NULL)
            throw "No memory for massive";
        int cdely = 0; //кол-во удаленных строк

        //проход по столбцам
        for (int x = 0; x < sizex; x++)
        {
            double avgx = 0;//среднее арифметическое столбца
            for (int y = 0; y < sizey; y++)
            {
                avgx += mas[x][y];
            }
            avgx /= sizey;
            if (avgx > border)
            {
                delx[cdelx] = x;
                cdelx++;
            }
        }
        //проход по строкам
        for (int y = 0; y < sizey; y++)
        {
            double avgy = 0;//среднее арифметическое строки
            for (int x = 0; x < sizex; x++)
            {
                avgy += mas[x][y];
            }
            avgy /= sizex;
            if (avgy > border)
            {
                dely[cdely] = y;
                cdely++;
            }
        }
    
        //Массив с учетом удаленных строк и столбцов
        double** newmas = new double* [sizex-cdelx];
        if (newmas == NULL)
            throw "No memory for massive";
        for (int i = 0; i < (sizex-cdelx); i++)
        {
            newmas[i] = new double[sizey-cdely];
            if (newmas[i] == NULL)
                throw "No memory for massive";
        }

        int tx = 0;//сколько столбцов уже оказались удаленными
        for (int x1 = 0; x1 < sizex; x1++)
        {
            bool isxdel = false; //является ли текущий столбец в списке удаленных
            for (int x2 = 0; x2 < cdelx; x2++)
            {
                if (x1 == delx[x2])
                {
                    isxdel = true;
                    tx++;
                    break;
                }
            }

            if (!isxdel)
            {
                int ty = 0;//сколько строк уже оказались удаленными
                for (int y1 = 0; y1 < sizey; y1++)
                {
                    bool isydel = false; //является ли текущая строка в списке удаленных
                    for (int y2 = 0; y2 < cdely; y2++)
                    {
                        if (y1 == dely[y2])
                        {
                            isydel = true;
                            ty++;
                            break;
                        }
                    }
                    if (!isydel)
                    {
                        newmas[x1-tx][y1-ty] = mas[x1][y1];
                    }
                }
            }
        }

        //Вывод
        int newsizex = sizex - cdelx;
        int newsizey = sizey - cdely;
        cout << "\nMatrix after Function:" << endl;
        for (int y = 0; y < newsizey; y++)
        {
            for (int x = 0; x < newsizex; x++)
            {
                cout << newmas[x][y] << "\t";
            }
            cout << endl;
        }
        cout << endl;
        //


        //Очистка массивов
        for (int i = 0; i < newsizex; i++)
        {
            delete[] newmas[i];
            newmas[i] = NULL;
        }
        delete [] newmas;
        newmas = NULL;
        delete[] delx;
        delx = NULL;
        delete[] dely;
        dely = NULL;
    }

    //Участок кода для возможности генерации исключения при сумме массивов (по заданию)
    ChildClass operator+(const ChildClass& M) const
    {
        if (this->sizex != M.sizex or this->sizey != M.sizey)
            throw WrongDimensionsException("Matrix sizes don't match!");
        ChildClass t(this->sizex, this->sizey);
        for (int x = 0; x < this->sizex; x++)
        {
            for (int y = 0; y < this->sizey; y++)
            {
                t.mas[x][y] = this->mas[x][y] + M.mas[x][y];
            }
        }
        return t;
    }
    //
 
    //Участок кода для возможности генерации исключения при неправильном индексе массива (по заданию)
    double Index(int indexx, int indexy) const
    {
        if (0 <= indexx < sizex and 0 <= indexy < sizey)
        {
            return mas[indexx][indexy];
        }
        else
            throw IndexOutOfBounds("Index is out of matrix (massive)");
    }
    //

    //Гетеры
    int getsizex() const { return sizex; }
    int getsizey() const { return sizey; }
    double** getmas() const
    {
        double** copymas = new double* [sizex];
        if (copymas == NULL)
            throw "No memory for massive";
        for (int i = 0; i < sizex; i++)
        {
            copymas[i] = new double[sizey];
            if (copymas[i] == NULL)
                throw "No memory for massive";
        }
        for (int x = 0; x < sizex; x++)
        {
            for (int y = 0; y < sizey; y++)
            {
                copymas[x][y] = mas[x][y];
            }
        }
        return copymas;
    }


    //Запись матрицы в файл
    void writematrix(string filename) const
    {
        ofstream file;
        file.open(filename);
        if (!file.is_open())
            throw "Error of opening of the file";
        else
        {
            for (int y = 0; y < sizey; y++)
            {
                for (int x = 0; x < sizex; x++)
                {
                    file << mas[x][y] << " ";
                }
                file << endl;
            }
        }
        file.close();
    }
};


//Чтение файла
void readmatrix(string filename)
{
    ifstream file;
    file.open(filename);
    if (!file.is_open())
        throw "Error of opening of the file";
    else
    {
        cout << "File matrix:\n";
        char ch;
        while (file.get(ch))
        {
            cout << ch;
        }

    }
    file.close();
}

int main()
{
    try
    {
        ChildClass m(4, 4);// массив размером x*y
        m.FillingMas(50);//рандом в пределах от 0 до указанного значения
        //ChildClass n(5, 5);
        //n.FillingMas(50);//рандом в пределах от 0 до указанного значения
        m.print();
        //n.print();
        //ChildClass res = m + n;
        //res.print();
        m.Function(25);// внутри число, с которым должно происходить сравнение (border)
        ChildClass t("myfile.txt");
        t.print();
    }
    catch (WrongSizeException e)
    {
        e.print();
    }
    catch (WrongDimensionsException e)
    {
        e.print();
    }
    catch (IndexOutOfBounds e)
    {
        e.print();
    }
    catch (const char* error)
    {
        cout << error << endl;
    }
}

