/************************************************************
** Arthur Silveira
** Solution for Touchscreen Keyboard problem
** from https://open.kattis.com/problems/touchscreenkeyboard
**
** requires C++11
*************************************************************/

#include <iostream>
#include <unordered_map>
#include <vector> 
#include <cmath> // for std::abs()
#include <algorithm> // for std::sort()

using namespace std;

// for filling keyboard
void fillKeyboard(unordered_map< char, vector<int> > &keyboard);

//computer string distance
int findDistance(unordered_map< char, vector<int> > &keyboard, 
					string &ori_string, string &new_string);

//struc for new words, will make sorting very easy.
struct Word
{
	int w_distance;  //distance from original word
	string w_string; //new_word string

	Word(int w_d, string & w_s) : w_distance(w_d), w_string(w_s) {}

	// for sorting words by distance from original,
	// if same distance, sort alphabetically.
	bool operator < (const Word & str) const{
		if (w_distance == str.w_distance)
			return (w_string < str.w_string);
		else
			return (w_distance < str.w_distance);
	}
};

//----------driver function-----------------------------------------------------
int main(){
	
	unordered_map< char, vector<int> > keyboard;
	fillKeyboard(keyboard);

	int t_cases;	

	cin >> t_cases;
	cin.ignore(100, '\n');

	for (int i = 0; i < t_cases; i++){
		vector<Word> words_vec;
		string ori_string, new_string;
		int entries;
		int total_distance = 0;
		cin >> ori_string >> entries;

		for(int j = 0; j< entries; j++){
			cin >> new_string;
			total_distance = findDistance(keyboard, ori_string, new_string);
			words_vec.push_back(Word(total_distance, new_string));
			sort(words_vec.begin(), words_vec.end());
		}
		for (int i = 0; i<words_vec.size(); i++){
			cout << words_vec[i].w_string << " " 
				 << words_vec[i].w_distance << endl;;
		}
	}

	// debugging --
	// for(auto& x: keyboard)
	// 	cout << x.first << " " << x.second[0] << "," << x.second[1] << endl;

	return 0;
}
//------------------------------------------------------------------------------

//computes distance between words based on keyboard.
int findDistance(unordered_map< char, vector<int> > &keyboard, 
					string &ori_string, string &new_string){

	int total_distance = 0;

	for (int i = 0; i < ori_string.length(); i++){

		int distance = 
			abs(keyboard[ori_string[i]][0]-keyboard[new_string[i]][0]) +
			abs(keyboard[ori_string[i]][1]-keyboard[new_string[i]][1]);
				
		total_distance += distance;
	}

	return total_distance;
}

//helper function to prefill keyboard grid.
void fillKeyboard(unordered_map< char, vector<int> > &keyboard){

	string line1 = "qwertyuiop";
	string line2 = "asdfghjkl";
	string line3 = "zxcvbnm";

	for (int i = 0; i< line1.length(); i++ ){
		vector<int> position;
		position.push_back(0);
		position.push_back(i);
		keyboard.insert(make_pair(line1[i], position));
	}
	for (int i = 0; i< line2.length(); i++ ){
		vector<int> position;
		position.push_back(1);
		position.push_back(i);
		keyboard.insert(make_pair(line2[i], position));
	}
	for (int i = 0; i< line3.length(); i++ ){
		vector<int> position;
		position.push_back(2);
		position.push_back(i);
		keyboard.insert(make_pair(line3[i], position));
	}

	return;
}

