/*	Implement a function void reverse(char *str) in C or C++ 
*	which reverses a null-terminated string.
*/

#include <iostream>
#include <cstring>


using namespace std;

void reverseInPlace(char *str){

	int length = strlen(str);

	for (int i =0; i < length/2; i++)
		swap(str[i], str[length-i-1]);

}



int main(int argc, const char** argv){
	
	char test[256];

	cin >> test;

	reverseInPlace(test);

	cout << test;

	return 0;
}

