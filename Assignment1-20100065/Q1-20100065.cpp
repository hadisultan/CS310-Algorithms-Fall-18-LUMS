#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <set>
#include <queue>
#include <stack>

using namespace std;

//My algorithm uses the Breadth First Search (BFS) method to check if the graph 
// can be divided into two or not (bipartite). The time complexity of the algorithm
// will be O(V+E).
// To store my data, I have decided to use an Adjacency Matrix, which means the that
// the space complexity of the algorithm will be O(V^2) but this gives me faster and
// more efficient lookups.
// When the division of the data into two boxes is not possible, I use the Depth 
// First Search (DFS) to find a cycle of odd length on the node which gives the 
// problem in the inital BFS. The time complexity for this is also O(V+E).
// The other data structures that I have used include sets and stacks. The 
// functions using the sets have a time complexity of O(V*log(V)). The functions
// using the sets have a time complexity of O(1). 

//3 sets declared as global variables, 'visited' will contain all the visited nodes. 'red' and 'green' are colors for bipartite graphs. 
set<int> visited;
set<int> red;
set<int> green;
//errlist and errset are used when the graph is not bipartite.
stack<int> errlist;
set<int> errset;
int n;
bool status = 0;

int error(int** link, int start, int no, int prob){
	errlist.push(start);
	errset.insert(start);
	for(int i=0; i<n; i++){
		if(link[start][i] == 1){
			if(i == prob){
				if(no%2 == 1){
					errlist.push(prob);
					return 1;
				}
			}
			else if(errset.find(i) == errset.end()){
				if(error(link, i, no+1, prob) == 1){
					return 1;
				}
			}
		}
	}
	errlist.pop();
	errset.erase(start);
	return 0;
}

void checker(int** link){
	queue<int> q;
	queue<int> q2;
	q.push(0);
	char color = 'r';
	while(!q.empty()){
		int v = q.front();
		q.pop();
		if(color == 'r'){
			if(green.find(v) != green.end()){
				status = 1;
				error(link, v, 1, v);
				return;
			}
		}
		else{
			if(red.find(v) != red.end()){
				status = 1;
				error(link, v, 1, v);
				return;
			}
		}
		if(visited.find(v) == visited.end()){
			visited.insert(v);
			if(color == 'r'){
				red.insert(v);
			}
			else{
				green.insert(v);
			}
		}
		for(int i = 0; i<n; i++){
			if(link[v][i] == 1){
				if(visited.find(i) == visited.end()){
					q2.push(i);
				}
			}
		}
		if(q.empty()){
			while(!q2.empty()){
				q.push(q2.front());
				q2.pop();
			}
			if(color == 'r'){
				color = 'g';
			}
			else{
				color = 'r';
			}							
		}
	}
}

int main(int argc, char const *argv[])
{
	string fname;
	cout << "Enter filename: ";
	getline(cin, fname);
	ifstream inFile;
	inFile.open(fname.c_str());
	string line;
	getline(inFile, line);
	int linelen = line.length();
	//Reads the first line to find the number of chemicals:
	for(int i=0; i<linelen; i++){
		if(line[i] == 'n')
		{
			n = stoi(line.substr(i+1, linelen-i-1));
		}
	}
	//Create a n x n matrix and set the values to zero:
	int **link = new int*[n];
	for(int i = 0; i < n; i++){
		link[i] = new int[n];
		for(int j = 0; j < n; j++){
			link[i][j] = 0;
		}
	}
	//Parse the file to fill the matrix.	
	for(int i=0; i<n; i++){
		getline(inFile, line);
		linelen = line.length();
		int breaker;
		int node;
		for(int j=0; j<linelen; j++){
			if(line[j] == ':'){
				node =  stoi(line.substr(1, j-1));
				breaker = j+1;
				break;
			}
		}
		while(breaker < linelen-1){
			for(int j = breaker; j<linelen; j++)
			{
				if(line[j] == ','){
					int rel = stoi(line.substr(breaker+2, j-(breaker+2)));
					breaker = j+1;
					link[node][rel] = 1;
				}
				if(j == linelen-1){
					int rel = stoi(line.substr(breaker+2, j-(breaker+1)));
					breaker = j;	
					link[node][rel] = 1;
				}
			}
		}		
	}
	checker(link);
	if(status == 0){
		cout << "Yes" << endl;
		set<int>::iterator iter;
		iter = red.begin();
		cout <<"C"<< *iter ;
		iter++;
		for(; iter!=red.end(); iter++)
		{
			cout << ", C" << *iter;
		}
		cout << endl;
		iter = green.begin();
		cout <<"C"<< *iter ;
		iter++;
		for(; iter!=green.end(); iter++)
		{
			cout << ", C" << *iter;
		}
		cout << endl;
		 
	}
	else{
		cout << "No" << endl;
		cout<<"C"<<errlist.top();
		errlist.pop();
		while(!errlist.empty()){
			cout<<"->"<<"C"<<errlist.top();
			errlist.pop();
		}
		cout<<endl;
	}
	inFile.close();

	return 0;
}