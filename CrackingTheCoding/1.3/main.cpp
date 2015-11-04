/*	Given two strings, write a method to decide if 
*	one is a permutation of the other
*/ 

#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

bool isPermutation(string &string1, string &string2){
	if (string1.length() != string2.length()) return false;

	sort(string1.begin(), string1.end());
	sort(string2.begin(), string2.end());

	for (int i = 0; i<string1.length(); i++){
		if (string1[i] != string2[i]) return false;
	}

	return true;

}

int main(int argc, const char **argv){
	
	string first_string;
	string second_string;

	while(1){

		getline(cin, first_string);
		getline(cin, second_string);

		if (isPermutation(first_string, second_string))
			cout << "is a permutation" << endl;
		else 
			cout << "is NOT a permutation" << endl;

	}


	return 0;
}