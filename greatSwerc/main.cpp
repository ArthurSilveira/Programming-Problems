#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <time.h>

using namespace std;

//---
void getPermutations( unordered_set<string> &permutations, int &max_perm_size);
void getUniqueChars(string &unique_chars, string &in_word);
//---

//driver function
int main(int argc, char const *argv[])
{	

	// for timekeeping
	clock_t t1,t2;
	

	unordered_set<string> permutations;
	// vector<string> words;
	string in_word;
	string unique_chars;
	
	// the ammount of words
	int n;
	// max number of unique characters
	int max_perm_size;

	cin >>n;
	cin.ignore(100,'\n');

	// getting the words from user and storing them.
	for (int i=0; i<n; ++i)	{
		
		getline(cin, in_word);
		getUniqueChars(unique_chars, in_word);
		// words.push_back(in_word);
	
	}

	// c.time tracks the time for this block to execute-----------------------
	t1 = clock();

	max_perm_size = unique_chars.size();

	getPermutations(permutations, max_perm_size);
	//------------------------------------------------------------------------
	
	t2 = clock();
	float t_elapsed ((float)t2 - (float)t1);
	cout << "\nDone generating permutations\n";
	cout << "Time elapsed : " << t_elapsed/CLOCKS_PER_SEC << " seconds"<< endl;
	cout << "With a max_perm_size of: " << max_perm_size << endl;
	// for (string const& perm : permutations){
	// 	cout << perm << endl;
	// }

	return 0;
}

// Generates every permutation of "0123456789"
// stores all but duplicates (acording to max_perm_size)
void getPermutations(unordered_set<string> &permutations, int &max_perm_size)
{
	string digits = "0123456789";

	do{

		permutations.insert(digits.substr(0, max_perm_size));
		
	} while (next_permutation(digits.begin(), digits.end()));
	
}

// get unique characters from the word.
void getUniqueChars(string &unique_chars, string &in_word){

	unique_chars += in_word;
	sort(unique_chars.begin(), unique_chars.end());
	unique_chars.erase(unique(unique_chars.begin(), unique_chars.end()), unique_chars.end());
	
}