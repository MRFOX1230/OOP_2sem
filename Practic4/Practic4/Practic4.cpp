#include <iostream>
#include <string>
using namespace std;

class Line
{
protected:
    string str = "";
public:
    Line()
    {
        str = "";
    }
    Line(string strx)
    {
        str = strx;
    }
    Line(const Line& Linex)
    {
        this->str = Linex.str;
    }
    ~Line()
    {

    }

    Line operator=(const Line& Linex)
    {
        this->str = Linex.str;
        return* this;
    }
};

class MyClass : public Line
{
protected:
    string mystr;
public:
    MyClass()
    {
        str = "";
    }
    MyClass(string mystrx)
    {
        mystr = mystrx;
    }
    MyClass(const MyClass& MyClassx)
    {
        this->str = MyClassx.str;
    }
    ~MyClass()
    {

    }

    MyClass operator=(const MyClass& MyClassx)
    {
        this->str = MyClassx.str;
        return* this;
    }
    void Function() const
    {
        int count = mystr.size();
        if (count < 5)
        {
            throw "The line must have at least 5 letters\n";
        }
        else
        {
            int k = 0;//счетчик гласных букв в паре
            int n = 0; //кол-во пар
            double average = 0; //среднее кол-во гласных в каждой паре
            int letters = 5; //кол-во слов в одной паре
            char vowels[12] {'A', 'a', 'E', 'e', 'I', 'i', 'O', 'o', 'U', 'u', 'Y', 'y'}; //гласные буквы
            int* time = new int[count]; //временный массив с кол-вом гласных в каждой паре
            if (time == NULL)
                throw "No memory for massive";
            for (int i = 0; i < count; i++)
            {
                if ((i + 1) % letters == 0)
                {
                    time[n] = k;
                    average += k;
                    n++;
                    k = 0;
                }
                for (int j = 0; j < 12; j++)
                {
                    if (mystr[i] == vowels[j])
                    {
                        k++;
                        break;
                    }
                }
            }

            average = average / n;
            int result = 0; //кол-во пар, в которых кол-во гласных больше среднего кол-ва гласных в каждой паре
            for (int s = 0; s < n; s++)
            {
                if (time[s] > average)
                {
                    result += 1;
                }
            }

            cout << "Result of Function: " << result << endl;
            delete[] time;
            time = NULL;
        }
    }
};
int main()
{
    MyClass test("-1232aaaaaa222aa22aaaa");
    test.Function();
}

