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
int*& arr1 = new int[10];
// ��������� �� ������ �����: 
string* s_arr = new string[];
// ��������� �� ��������� �� ������: 
char** c3 = &c1;
// ����� ���������: 
const int c4 = 10;
// ��������� �� ����� ���������: 
const int* c5 = &c4;
// ����������� ��������� �� �����: 
int const* c6 = &c4;


// TASK 2
// ����������� ���� �++ � ����������� �� �� �������.
// char <= short <= int <= long <= long long 


int main() {

	return 0;
}