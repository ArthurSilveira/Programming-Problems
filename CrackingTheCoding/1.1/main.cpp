/* Implement an algorithm to determine if a 
*  string has all unique characters. What if 
*  you cannot use additional data structures?
*/

#include <iostream>
#include <string>
#include <cstring> //for memset.

using namespace std;

//------------------------------------------------------------
// very naive approach! o(n^2)
// bool allUnique(string &in_string){
	
// 	if (in_string.length() > 256) return false;

// 	for (int i = 0; i < in_string.length()-1; i++){
// 		for (int j = i+1; j< in_string.length(); j++){
// 			if (in_string[i]== in_string[j])
// 				return false;
// 		}
// 	}

// 	return true;
// }
//-----------------------------------------------------------

//	Much better approach utilizing an array of booleans to false
//	and setting them true, when we have a character corresponding to it's
//  Location.
bool allUnique(string &in_string)
{
	
	if (in_string.length() > 256) return false;

	bool char_set[256];
	memset(char_set, 0, sizeof(char_set));

	for (int i=0; i <= in_string.length(); i++){

		if (char_set[(int)in_string[i]])
			return false;
		else
			char_set[(int)in_string[i]] = true;
	}

	return true;
}

int main()
{
	
	string test;

	
	for(;;){
		cin >> test;

		cout << test;
		if (allUnique(test))
			cout << " is unique" << endl;
		else
			cout << " is NOT unique" << endl;

	}

	return 0;
}