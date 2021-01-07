#include <iostream>
#include <string>

using namespace std;

// TASK 1
// указатель на символ: 
char c2 = 'g';
char* c1 = &c2; // ответ
// массив из 10  целых: 
int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
// ссылка на массив из 10 целых: 
//int*& arr1 = new int[10];
// указатель на массив строк: 
string* s_arr = new string[10];
// указатель на указатель на символ: 
char** c3 = &c1;
// целая константа: 
const int c4 = 10;
// указатель на целую константу: 
const int* c5 = &c4;
// константный указатель на целое: 
int* const c6 = nullptr;


// TASK 2
// Примитивные типы С++ и ограничения на их размеры.
// char <= short <= int <= long <= long long 
// float <= double
// signed или unsigned на размер не влияет


// TASK 3
// состояние (значения полей), поведение (методы), идентичность/детефикатор (имя объекта)


// TASK 4
void swap(int* first, int* second) {
	int tmp = *first;
	*first = *second;
	*second = tmp;
}

void swap(int& first, int& second) {
	int tmp = first;
	first = second;
	second = tmp;
}

// TASK 5
// Напишите код, демонстрирующий работу виртуальной функции и отличие ее поведения от невиртуальных функций.

// поведение с virtual и без него отличается
class Parent
{
public:
	string doSth() { return "P"; }
	// virtual string doSth() { return "P"; }
};

class Child : public Parent
{
public:
	 string doSth() { return "C"; }
	 // virtual string doSth() { return "C"; }
};

// код для мэйна:
//Child chld;
//Parent& par = chld;
//cout << par.doSth() << endl;



// TASK 6
class A {
public:
	//virtual size_t getIdx() { return myIdx; }
	A() {
		info = "A - " + to_string(exceptionsCnt++);
	}
	size_t getInstance(){
		return exceptionsCnt++;
	}
	virtual string getInfo(){ return info; }
private:
	static size_t exceptionsCnt;
	string info;
};
size_t A::exceptionsCnt = 0;

class B : public A {
public:
	B() {
		info = "B - " + to_string(getInstance());
	}
	virtual string getInfo() { return info; }
private:
	string info;
};

class C : public B {
public:
	C() {
		info = "C - " + to_string(getInstance());
	}
	virtual string getInfo() { return info; }
private:
	string info;
};

void testSixTask() {
	try {
		throw B();
	}
	catch (C ex) {
		cout << "C: " + ex.getInfo() << endl;
	}
	catch (B ex) {
		cout << "B: " + ex.getInfo() << endl;
	}
	catch (A ex) {
		cout << "A: " + ex.getInfo() << endl;
	}
}

// TASK 7
//Конструируются поля A
//Конструктор A
//Конструируются поля B
//Конструктор B
//Конструируются поля C
//Конструктор C

// деструкторы в обратном порядке


// TASK 8
//int n = 1;
//int* p1 = new int; // один инт
// delete p1;
//myType* t1 = new myType(args); // объект моего типа, с аргументами конструктора 
// delete t1;
//int* p2 = new int[n]; // массив интов
// delete[] p2;
//
//int* p3 = (int*)malloc(sizeof(int)*n);
//if(p3 == NULL) { ... };
//if it is class obj, call constructor


// TASK 9 

class Iterator {
public:
	Iterator(size_t* arr, size_t& idx);
	virtual ~Iterator();

	Iterator& operator++ ();
	bool operator== (const Iterator& other);
	bool operator!= (const Iterator& other);
	size_t& operator* ();
	size_t* operator-> ();
};

#include <iterator>
class DynamicArr {
private:
	size_t size;
	size_t* data; // arr itself
	size_t capacity;
public:
	DynamicArr();
	virtual ~DynamicArr();
	void setSize(const size_t &newSize);
	size_t getSize();
	size_t& operator[](const size_t& idx);
	DynamicArr& operator=(const DynamicArr& other);
	void push_back(const size_t& item);
	void erase(const size_t& idx);
	Iterator begin();
	Iterator end();
};




// TASK 10
// Напишите аналог shared_ptr. Для счетчика используйте разделяемый между указателями объект. 

class Count {
private:
	size_t cnt = 0;
public:
	void increase() { ++cnt; }
	void decrease() { --cnt; }
	size_t getCnt() { return cnt; }
};

template<typename _Ty>
class mySharedPtr {
private:
	Count* cnt = nullptr;
	_Ty* ptr = nullptr;
public:
	mySharedPtr(_Ty* ptr) {
		cnt = new Count;
		cnt->increase();
		this->ptr = ptr;
	}
	mySharedPtr(const mySharedPtr& other) {
		cnt = other.cnt;
		cnt->increase();
		this->ptr = other.ptr;
	}
	~mySharedPtr() {
		cnt->decrease();
		if (cnt.getCnt() == 0) {
			delete[] ptr;
			delete cnt;
		}
	}
	mySharedPtr& operator= (const mySharedPtr& other) {
		this->cnt->decrease();
		if (cnt.getCnt() == 0) {
			delete[] ptr;
			delete cnt;
		}

		this->cnt = other.cnt;
		this->ptr = other.ptr;
	}
};


int main() {
	int* ptr1, *ptr2;
	mySharedPtr<int> a(ptr1);
	mySharedPtr<int> aa(a);

	mySharedPtr<int> b(ptr2);
	a = b;


	//testSixTask();


	return 0;
}