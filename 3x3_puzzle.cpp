/*
cpp code for solving the 3 x 3 puzzle

-------------          	-------------
| 2 | 6 | 8 |           | 0 | 1	| 2 |               
-------------           -------------
| 4 | 0 | 1 | ------->  | 3 | 4	| 5 | 
-------------           -------------    
| 3 | 5	| 7 |        	| 6 | 7 | 8 |
-------------           -------------                                  

*/

#include<bits/stdc++.h>
using namespace std;
const int mx = 1e6;

map<string, int> state_to_int; //mapping every state to unique value
map<int, string> int_to_state; //getting the state for every int value
string d; // destination state
int ind = 0; // a variable for representing every state to int
vector<int> adj[mx + 1]; // adjacent matrix
vector<int> par(mx + 1, -1); // parent array
int dx[4] = {1, -1, 0, 0}; // direction array for x axis
int dy[4] = {0, 0, 1, -1}; // direction array for y axis
int vis[mx + 1]; // visited array

void bfs(int strt) {
	// declaring queue for bfs
	queue<int> q;
	q.push(strt);
	while(!q.empty()) {
		int fr = q.front();
		q.pop();
		vis[fr] = 1;

		string str = int_to_state[fr];
		if (str == d) {
            return; // if str is our destination
		}

		int x, y, sx, sy;

		// finding the position of blank square(0)
		for (int i = 0; i < 9; i++) {
			if (str[i] == '0') {
				x = i / 3; // row num
				y = i % 3; // col num
				break;
			}
		}

		for (int i = 0; i < 4; i++) {
			sx = x + dx[i];
			sy = y + dy[i];
			if (sx >= 0  and sx < 3 and sy >= 0  and sy < 3) {
				string tem = str;
				swap(tem[x * 3 + y], tem[sx * 3 + sy]);

				// if the state is new one
				if (state_to_int.find(tem) == state_to_int.end()) {
					state_to_int[tem] = ind;
					int_to_state[ind] = tem;
					ind++;
					adj[fr].push_back(state_to_int[tem]);
					par[state_to_int[tem]] = fr;
				}
			}
		}
		for (int i = 0; i < adj[fr].size(); i++) {
			if (!vis[adj[fr][i]]) {
				q.push(adj[fr][i]);
				vis[adj[fr][i]] = 1;
			}
		}
	}
}

int32_t main() {

	// define destination state
	d = "012345678";
	// taking input the source state
	string s = "";
	char c;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> c;
			s += c;
		}
	}

	//converting the source state to unique integer value
	state_to_int[s] = ind;
	int_to_state[ind] = s;
	ind++;

	// intializing the visited array by 0
	memset(vis, 0, sizeof(vis));

	// calling the bfs function with source value
	bfs(state_to_int[s]);

	// reversing the path using stack
	stack<int> st;
	int node = state_to_int[d];
	while(node != -1) {
		st.push(node);
		node = par[node];
	}

	// printing the path
	string str;
	int cnt = 0;
	while(!st.empty()) {
		str = int_to_state[st.top()];
		st.pop();
		if (cnt == 0) cout << "Given :\n";
		else cout << "move no : " << cnt << "\n";
		for (int i = 0; i < 9; i++) {
			if (i % 3 == 0) cout << "-------------\n";
			cout << "| " <<  str[i] << " ";
			if (i % 3 == 2) cout << "|\n";
		}
		cout << "-------------\n\n";
		cnt++; 
	}

	return 0;
}
