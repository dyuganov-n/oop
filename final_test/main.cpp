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
int*& arr1 = new int[10];
// указатель на массив строк: 
string* s_arr = new string[];
// указатель на указатель на символ: 
char** c3 = &c1;
// целая константа: 
const int c4 = 10;
// указатель на целую константу: 
const int* c5 = &c4;
// константный указатель на целое: 
int const* c6 = &c4;


// TASK 2
// Примитивные типы С++ и ограничения на их размеры.
// char <= short <= int <= long <= long long 


int main() {

	return 0;
}