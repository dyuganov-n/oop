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






int main() {

	


	return 0;
}