#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

//Вариант 18
//Структура «Человек».
//Минимальный набор полей : фамилия, имя, пол, рост, вес, дата
//рождения, телефон, адрес.
//Добавление : в начало
//Удаление : с конца
//Поиск по фамилии, фильтр по адресу.

//Структура из варианта
class Human {
public:
	string surname;
	string name;
	string sex;
	int height;
	int weight;
	string birthday;
	string phone;
	string address;

	Human(const string& sn = "", const string& nm = "", const string& s = "", int h = 0,
		  int w = 0, const string& b = "", const string& p = "", const string& add = "") {
		surname = sn;
		name = nm;
		sex = s;
		height = h;
		weight = w;
		birthday = b;
		phone = p;
		address = add;
	}
};

//Элементы в связном списке LinkedList
template<class T>
class Element
{
public:
	Element* next;
	Element* prev;
	T info;
public:
	//конструкторы
	Element(const T& data)
	{
		next = prev = NULL;
		info = data;
	}
	Element(const Element* Next, const Element* Prev, const T& data)
	{
		next = Next;
		prev = Prev;
		info = data;
	}
	Element(const Element& el)
	{
		next = el.next;
		prev = el.prev;
		info = el.info;
	}
};

//Связный список, состоящий из Element, в которых находятся структуры типа T (Human) 
template<class T>
class LinkedList
{
protected:
	Element<T>* head;
	Element<T>* tail;
	int count;
public:
	LinkedList()
	{
		head = tail = NULL;
		count = 0;
	}
	virtual Element<T>* pop() = 0;

	virtual Element<T>* push(const T& value) = 0;

	Element<T>& operator[](int index)
	{
		Element<T>* current = head;
		for (int i = 0;
			current != NULL && i < index;
			current = current->next, i++);
		return *current;
	}

	virtual bool isEmpty() {
		return (LinkedList<T>::count == 0);
	}

	virtual ~LinkedList()
	{
		cout << "\nLinkedList class destructor";
		Element<T>* nextelement = head;
		while (nextelement != NULL) {
			Element<T>* trash = nextelement;
			nextelement = nextelement->next;
			delete trash;
			trash = NULL;
		}
	}
};


//класс очередь для обработки связного списка
template<class T>
class Queue : public LinkedList<T>
{
public:
	Queue<T>() : LinkedList<T>() {}
	Queue<T>(const LinkedList<T>& t) {
		LinkedList<T>::head = t->head;
		LinkedList<T>::tail = t->tail;
		LinkedList<T>::count = t.count;
	}
	Queue<T>(const T* arr, int len) : LinkedList<T>(arr, len) {}
	
	//добавление нового элемента в конец списка
	Element<T>* push(const T& value) override
	{
		if (LinkedList<T>::head == NULL) //if(count==0)
		{
			//пустой список
			LinkedList<T>::head = new Element<T>(value);
			if (LinkedList<T>::head == NULL)
				throw "No memory";
			LinkedList<T>::tail = LinkedList<T>::head;
		}
		else
		{
			//элементы уже есть
			LinkedList<T>::tail->next = new Element<T>(value);
			if (LinkedList<T>::tail->next == NULL)
				throw "No memory";
			LinkedList<T>::tail->next->prev = LinkedList<T>::tail;
			LinkedList<T>::tail = LinkedList<T>::tail->next;
		}
		LinkedList<T>::count++;
		//return LinkedList<T>::tail;
	}
	//добавление нового элемента в начало списка
	Element<T>* pushs(const T& value)
	{
		if (LinkedList<T>::head == NULL) //if(count==0)
		{
			//пустой список
			LinkedList<T>::head = new Element<T>(value);
			if (LinkedList<T>::head == NULL)
				throw "No memory";
			LinkedList<T>::tail = LinkedList<T>::head;
		}
		else
		{
			//элементы уже есть
			LinkedList<T>::head->prev = new Element<T>(value);
			if (LinkedList<T>::head->prev == NULL)
				throw "No memory";
			LinkedList<T>::head->prev->next = LinkedList<T>::head;
			LinkedList<T>::head = LinkedList<T>::head->prev;
		}
		LinkedList<T>::count++;
		//return LinkedList<T>::tail;
	}
	//Извлечение 1-ого элемента из списка
	Element<T>* pop() override
	{
		if (LinkedList<T>::head == NULL)
			return NULL;
		Element<T>* res = LinkedList<T>::head;
		if (LinkedList<T>::head == LinkedList<T>::tail)
			LinkedList<T>::head = LinkedList<T>::tail = NULL;
		else
			LinkedList<T>::head = LinkedList<T>::head->next;
		LinkedList<T>::count--;
		return res;
	}
	//Извлечение последнего элемента из списка
	Element<T>* pops()
	{
		if (LinkedList<T>::tail == NULL)
			return NULL;
		Element<T>* res = LinkedList<T>::tail;
		if (LinkedList<T>::tail == LinkedList<T>::head)
			LinkedList<T>::head = LinkedList<T>::tail = NULL;
		else
			LinkedList<T>::tail = LinkedList<T>::tail->prev;
		LinkedList<T>::count--;
		return res;
	}

	//добавление элемента в произвольное место списка
	void insert(const T& human, int index) {
		if (index > LinkedList<T>::count or index < 0)
			throw "Index isn't correct";

		Element<T>* newelement = new Element<T>(human);
		if(newelement == NULL)
			throw "No memory";
		if (index == 0) {
			Element<T>* indexelement = LinkedList<T>::head;
			newelement->prev = NULL;
			newelement->next = indexelement;
			indexelement->prev = newelement;
			LinkedList<T>::head = newelement;
		}
		else if (index == LinkedList<T>::count) {
			Element<T>* indexelement = LinkedList<T>::tail;
			newelement->prev = indexelement;
			newelement->next = NULL;
			indexelement->next = newelement;
			LinkedList<T>::tail = newelement;
		}
		else {
			Element<T>* indexelement = LinkedList<T>::head;
			for (int i = 0; i < index; i++) {
				indexelement = indexelement->next;
			}
			newelement->prev = indexelement->prev;
			newelement->next = indexelement;
			indexelement->prev->next = newelement;
			indexelement->prev = newelement;
		}
		LinkedList<T>::count++;
	}

	//удалание элемента из произвольного места списка
	Element<T>* remove(int index) {
		if (index >= LinkedList<T>::count or index < 0)
			throw "Index isn't correct";
		Element<T>* indexelement = LinkedList<T>::head;
		if (index == 0) {
			if (LinkedList<T>::count == 1) {
				LinkedList<T>::head = LinkedList<T>::tail = NULL;
			}
			else {
				LinkedList<T>::head = LinkedList<T>::head->next;
				LinkedList<T>::head->prev = NULL;
			}
		}
		if (index == (LinkedList<T>::count)-1) {
			LinkedList<T>::tail = LinkedList<T>::tail->prev;
			LinkedList<T>::tail->next = NULL;
		}
		else {
			for (int i = 0; i < index; i++) {
				indexelement = indexelement->next;
			}
			indexelement->prev->next = indexelement->next;
			indexelement->next->prev = indexelement->prev;
		}
		delete indexelement;
		indexelement = NULL;
		LinkedList<T>::count--;
	}
	void clear() {
		while (!this->isEmpty())
		{
			Element<T>* ptr = this->pop();
			if (ptr != NULL)
				delete ptr;
		}
	}



	//фильтр по адресу
	Queue<T> filter(const string& add) {
		Queue<T> result;
		Element<T>* indexelement = LinkedList<T>::head;
		for (int i = 0; i < LinkedList<T>::count; i++) {
			if (indexelement->info.address == add)
				result.push(indexelement->info);
			indexelement = indexelement->next;
		}
		//Queue<T> res(result)
		return result;
	}
	//фильтр по адресу (рекурсивно)
	void recfunc(Queue<T>& r, Element<T>* i, string& a)
	{
		if (i != NULL) {
			if (i->info.address == a)
				r.push(i->info);
			i = i->next;
			return recfunc(r, i, a);
		}
	}
	Queue<T> filter_recursive(const string& add) {
		Queue<T> result;
		Element<T>* indexelement = LinkedList<T>::head;
		recfunc(result, indexelement, add);
		return result;
	}

	//универсальный фильтр по произвольному полю в элементе списка
	template <class type>
	Queue<T> filtertype(bool (*condition)(const T&, const type&), const type& value) {
		Queue<T> result;
		Element<T>* indexelement = LinkedList<T>::head;
		for (int i = 0; i < LinkedList<T>::count; i++) {
			if (condition(indexelement->info, value))
				result.push(indexelement->info);
			indexelement = indexelement->next;
		}
		return result;
	}

	//поиск по фамилии
	Queue<T> find(const string& sname)
	{
		Queue<T> result;
		Element<T>* indexelement = LinkedList<T>::head;
		for (int i = 0; i < LinkedList<T>::count; i++) {
			if (indexelement->info.surname == sname) {
				result.push(indexelement->info);
				return result;
			}
			indexelement = indexelement->next;
		}
		return result;
	}
	//поиск по фамилии (рекурсивно)
	void recfuncfind(Queue<T>& r, Element<T>* i, const string& s, bool bl)
	{
		if (bl == 0 and i != NULL) {
			if (i->info.surname == s) {r.push(i->info); bl = 1;}
			i = i->next;
			return recfuncfind(r, i, s, bl);
		}
	}
	Queue<T> find_recursive(const string& snm) {
		Queue<T> result;
		Element<T>* indexelement = LinkedList<T>::head;
		bool b = 0;
		recfuncfind(result, indexelement, snm, b);
		return result;
	}


	//сохранение списка в файл
	void save(const string& filename) const {
		ofstream file;
		file.open(filename);
		if (!file.is_open())
			throw "Error of opening of the file";

		Element<T>* indexelement = LinkedList<T>::head;
		for (int i = 0; i < (LinkedList<T>::count); i++) {
			file << indexelement->info.surname << endl;
			file << indexelement->info.name << endl;
			file << indexelement->info.sex << endl;
			file << indexelement->info.height << endl;
			file << indexelement->info.weight << endl;
			file << indexelement->info.birthday << endl;
			file << indexelement->info.phone << endl;
			file << indexelement->info.address << endl << endl;
			indexelement = indexelement->next;
		}
		file.close();
	}

	//чтение списка из файла
	void load(const string& filename, Queue<T>& fu) {
		ifstream file;
		file.open(filename);
		if (!file.is_open())
			throw "Error of opening of the file";
		if (LinkedList<T>::count != 0)
			this->clear();
		int k = 0; //счетчик
		Human el;
		while (!file.eof()) {
			k++;
			string x1 = "";
			int x2 = 0;

			switch (k) {
				case 1:
					file >> x1;
					el.surname = x1;
					break;
				case 2:
					file >> x1;
					el.name = x1;
					break;
				case 3:
					file >> x1;
					el.sex = x1;
					break;
				case 4:
					file >> x2;
					el.height = x2;
					break;
				case 5:
					file >> x2;
					el.weight = x2;
					break;
				case 6:
					file >> x1;
					el.birthday = x1;
					break;
				case 7:
					file >> x1;
					el.phone = x1;
					break;
				case 8:
					file >> x1;
					el.address = x1;
					break;
				case 9:
					file >> x1;
					fu.push(el);
					k = 1;
					el.surname = x1;
					break;
			}
		}
		file.close();
	}

	void print() const {
		Element<T>* indexelement = LinkedList<T>::head;
		cout << "List" << endl;
		for (int i = 0; i < (LinkedList<T>::count); i++) {
			cout << "Element " << (i + 1) << endl;
			cout << "surname: " << indexelement->info.surname << endl;
			cout << "name: " << indexelement->info.name << endl;
			cout << "sex: " << indexelement->info.sex << endl;
			cout << "height: " << indexelement->info.height << endl;
			cout << "weight: " << indexelement->info.weight << endl;
			cout << "birthday: " << indexelement->info.birthday << endl;
			cout << "phone: " << indexelement->info.phone << endl;
			cout << "address: " << indexelement->info.address << endl << endl;
			indexelement = indexelement->next;
		}
		cout << "------------------------------------------------" << endl << endl;
	}

	virtual ~Queue() { cout << "\nQueue class destructor"; }
};

//Пример функции для универсального фильтра (фильтр по фамилии)
template <class T>
bool filtersurname(const T& a, const string& surn) {
	if (a.surname == surn)
		return 1;
	return 0;
}



int main()
{
	try {
		Queue<Human> testlist;
		Human x1;
		Human x2;
		Human x3("Testovich", "Test", "Male", 120, 40, "10.10.2002", "8923874239", "Russia");
		//testlist.push(x1);
		//testlist.push(x2);
		//testlist.push(x3);
		//testlist.insert(x3, 3);
		//testlist.print();
		////Queue<Human> y1 = testlist.filter_recursive("Russia");
		////y1.print();
		//Queue<Human> y2 = testlist.find_recursive("Penkin");
		//y2.print();
		//testlist.save("myfile");


		Queue<Human> y3;
		y3.push(x3);
		y3.load("myfile", y3);
		y3.print();

		//string sn = "Penkin";
		//Queue<Human> newy3 = y3.filtertype(filtersurname, sn);
		//newy3.print();


		//testlist.save("myfile");
		//testlist.load("myfile");

		
		LinkedList<Human>* ptr_cast = new Queue<Human>;
		Queue<Human>* casted = dynamic_cast<Queue<Human>*>(ptr_cast);
		if (casted) {
			Queue<Human> cast = *casted;
			cout << "Dynamic_cast is succesfull";
		}
		else
			throw "Invalid type cast";

		return 0;
	}
	catch (const string& error) {
		cout << error;
	}
}

