#include <iostream>
#include <string>

using namespace std;

// TASK 1
// ��������� �� ������: 
char c2 = 'g';
char* c1 = &c2; // �����
// ������ �� 10  �����: 
int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
// ������ �� ������ �� 10 �����: 
//int*& arr1 = new int[10];
// ��������� �� ������ �����: 
string* s_arr = new string[10];
// ��������� �� ��������� �� ������: 
char** c3 = &c1;
// ����� ���������: 
const int c4 = 10;
// ��������� �� ����� ���������: 
const int* c5 = &c4;
// ����������� ��������� �� �����: 
int* const c6 = nullptr;


// TASK 2
// ����������� ���� �++ � ����������� �� �� �������.
// char <= short <= int <= long <= long long 


// TASK 3
// 
// 

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
// �������� ���, ��������������� ������ ����������� ������� � ������� �� ��������� �� ������������� �������.

// ��������� � virtual � ��� ���� ����������
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

// ��� ��� �����:
//Child chld;
//Parent& par = chld;
//cout << par.doSth() << endl;


// TASK 6


// TASK 7
//�������������� ���� A
//����������� A
//�������������� ���� B
//����������� B
//�������������� ���� C
//����������� C

// ����������� � �������� �������


// TASK 8
//int n = 1;
//int* p1 = new int; // ���� ���
// delete p1;
//myType* t1 = new myType(args); // ������ ����� ����, � ����������� ������������ 
// delete t1;
//int* p2 = new int[n]; // ������ �����
// delete[] p2;
//
//int* p3 = (int*)malloc(sizeof(int)*n);
//if(p3 == NULL) { ... };


// TASK 9 

#include <iterator>
class DynamicArr {
private:
	size_t size;
	size_t* data;
public:

	void setSize(const size_t &newSize);
	size_t getSize();
	size_t& operator[](const size_t& idx);
	void push_back(const size_t& item);
	/*iterator begin();
	iterator end();*/

};




int main() {

	


	return 0;
}