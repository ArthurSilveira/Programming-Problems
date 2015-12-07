/*** 
**	Solution to Arrow problem for CS315
** 	by Arthur Silveira
** 
** 	This is based on Ethan Toney's framework but modified.
** 	It creates a graph of game states and utilizes hashtables to quickly access 
** 	properties of the graph.
** 	
**	tested against 'hike.in' file:
**			produced good solution for all test cases with following time
**
**			real		0m0.549s
**			user	0m0.549s
**			sys		0m0.003s
**
**	-- Compile with -std=c++11 flag
**	-- run with command 
**		'./a.out < hike.in'
**	-- or
**		'time ./a.out < hike.in' to get the time.
**	
******************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <queue>				
#include <unordered_map>	// hash_tables
#include <algorithm>			// for sort()

using namespace std;

	/* The state of the game, is a "node" in the graph we will create.
	*
	* The key for a state in the hashtable will pre represented as 
	* x:y:z where x, y and z represent the positions of players.
	* because state 1:2:3 is the same as 3:2:1 for this purpose
	* we keep the players sorted and don't store repeated states.
	**/
class State{
	
	private:
			// the distance from root of tree.
		int distance = 0;

	public:
			// stores the position of players in this state of the game.
		vector<int> player_positions;
			
		State(int p1_pos, int p2_pos, int p3_pos){

			player_positions.push_back(p1_pos);
			player_positions.push_back(p2_pos);
			player_positions.push_back(p3_pos);

			sort(player_positions.begin(), player_positions.end());
		}

		int getDistance(){
			return distance;
		}
		void setDistance(int new_dist){
			distance = new_dist;
			return;
		}

			//returns key to lookup in hashtable(to see this state is already been visited)
		string getStateKey(){
			
			string key;
			for( int i = 0; i< player_positions.size(); i++){
				key+= to_string(player_positions[i]);
				if (i != (player_positions.size() -1) )
					key+= ':';
			}
			return key;
		}

			// takes a player and returns the valid color it can move on.
		string getColorKey(int &player){
			
				//opponents position index
			int op1_index, op2_index;

			getOpponentsPos(player, op1_index, op2_index);

			string key;
			key+= to_string(player_positions[op1_index]);
			key+=':';
			key+= to_string(player_positions[op2_index]);


			return key;
		}

			// takes 2 adjacent nodes and returns the key to color between them.
		string getColorKey(int &part1, int &part2){
			if (part1 > part2)
				return (to_string(part2)+':'+to_string(part1));
			else
				return (to_string(part1)+':'+to_string(part2));
			
		}

			//This just decides the index of the oponents 
		void getOpponentsPos(int &player, int &op1_index, int &op2_index){
			
			if (player == 0){
				op1_index = 1;
				op2_index = 2;
			}
			else if (player ==1){
				op1_index=0; 
				op2_index=2;
			}
			else {
				op1_index = 0; 
				op2_index = 1;
			}

			return;
		}
};

//--------------------------------Function prototypes ---------------------------------------------------------
bool getInput(int &total_nodes, int &p1_pos, int &p2_pos, int &p3_pos, 
				unordered_map<string, char> &edge_colors);

int playGame(queue<State*> &state_q,
				int &total_nodes,
				unordered_map<string, char> &edge_colors, 
				unordered_map<string, bool> &visited);

string genrateStateKey(int &p1_pos, int &p2_pos, int &p3_pos);
//------------------------------------------------------------------------------------------------------------------------

int main(int argc, const char** argv){
	
		// create the queue (builds graph)
	queue<State*> state_q;

		// hash table for storing the color of edges between nodes on board.
	unordered_map<string, char> edge_colors;

		// hash table for storing already visited game states.
	unordered_map<string, bool> visited;

	int total_nodes, p1_pos, p2_pos, p3_pos;

	while ( cin >> total_nodes ){

			// reached end of input, terminate program
		if (total_nodes == 0)
			return 0;

		if ( (getInput(total_nodes, p1_pos, p2_pos, p3_pos, edge_colors) ) ){
			cout << "0\n";
		}

		else {
				// create first state and add to Queue
			State initial_state(p1_pos, p2_pos, p3_pos);
			state_q.push(&initial_state);
				// add to table of visited states.
			visited[initial_state.getStateKey()] = true;

				//play the game and find optimal solution.
			int result = playGame(state_q, total_nodes, edge_colors, visited);

				// -1 means no solutions were found.
			if (result == -1){
				cout << "impossible\n";
			}
			else
				cout << result << endl;
		}

		// clear containers before starting new test case.
		edge_colors.clear();
		visited.clear();
		while(!state_q.empty())
			state_q.pop();
	}

	return 0;
}

// get input for game setup. Returns true if trivial case.
bool getInput(int &total_nodes, int &p1_pos, int &p2_pos, int &p3_pos, 
				unordered_map<string, char> &edge_colors){

	bool trivial_case = false;
	
	cin >> p1_pos >> p2_pos >> p3_pos;
	
	//if all players start in same position(trivial case)
	if ( (p1_pos == p2_pos) && (p1_pos == p3_pos) )
		trivial_case = true;

	char color;
	string color_key;

	//creates color_key for each edge and stores them in a hashtable.
	//we only need to take in the bottom left half of matrix since it's symetrical
	for (int i =1; i<=total_nodes; ++i){
		for (int j =1; j<= i; ++j){
			
			cin >> color;
			color_key = to_string(j) + ':' + to_string(i);

			edge_colors[color_key] = color;
		}
		cin.ignore(500, '\n');
	}
	return trivial_case;
}

// play the game finding optimal solution
int playGame(queue<State*> &state_q,
				int &total_nodes, 
				unordered_map<string, char> &edge_colors, 
				unordered_map<string, bool> &visited){

	int result = -1;

	// Traverse states of game in Queue (BFS)
	while( !state_q.empty() ){

			//creates pointer to next element in queue, then pop queue.
		State* current_state = state_q.front();
		state_q.pop();

			//the color a player can move on
		char valid_color;

			// for each player in the state
		for(int i = 0; i<3; i++){
			
			string color_key = current_state->getColorKey(i);
			valid_color = edge_colors[color_key];
			
				//get index of opponents positions (i in this loop is the index of current player)
			int p2_index, p3_index;
			current_state->getOpponentsPos(i, p2_index, p3_index);

				// get current player positions
			int p1_pos = current_state->player_positions[i];
			int p2_pos = current_state->player_positions[p2_index];
			int p3_pos = current_state->player_positions[p3_index];

				// for each edge in the graph (from current position to all other nodes)
			for(int  j = 1; j <= total_nodes; j++){
				string current_edge_key = current_state->getColorKey(p1_pos, j);

					// if it's a valid edge to move on
				if( edge_colors[current_edge_key] == valid_color){
			
						//move player there
					int new_p1_pos = j;
				
						//create key for this state and check if it would be a new state.
					string state_key = genrateStateKey(new_p1_pos, p2_pos, p3_pos);
					if ( !( visited[state_key] ) ){

							//create new state and set visited to true in hashtable
						State* new_state = new State(new_p1_pos, p2_pos, p3_pos);
						visited[state_key] = true;

							//set the distance of this state to previous state+1.
						new_state->setDistance(current_state->getDistance()+1);
						
							//if new_state is the answer (all players in same place)
							// the distance from the root is the shortest path to the answer.
						if ( new_p1_pos == p2_pos && new_p1_pos == p3_pos){
							return new_state->getDistance();
						}	
						else	//push new state on queue
							state_q.push(new_state);
					}
					
				}

			}

		}
		
	}

	return result;
}

// helper function to generate state string keys without object.
string genrateStateKey(int &p1_pos, int &p2_pos, int &p3_pos){
	vector<int> player_positions;

	player_positions.push_back(p1_pos);
	player_positions.push_back(p2_pos);
	player_positions.push_back(p3_pos);

	sort( player_positions.begin(), player_positions.end() );

	string key;
	
		for( int i = 0; i< player_positions.size(); i++){

			key+= to_string(player_positions[i]);
			if (i != (player_positions.size() -1) )
				key+= ':';
		}

	return key;
}