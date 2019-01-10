#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <set>
#include <queue>
#include <stack>

using namespace std;

//My algorithm uses the Depth First Search (DFS) method to check if the graph 
// can be divided into two or not (bipartite). The time complexity of the algorithm
// will be O(V+E).
// To store my data, I have decided to use an Adjacency Matrix, which means the that
// the space complexity of the algorithm will be O(V^2) but this gives me faster and
// more efficient lookups.
// The other data structures that I have used include sets, stacks and queues. The 
// functions using the sets have a time complexity of O(V*log(V)). The functions
// using the sets and queses have a time complexity of O(1). 

set<int> visited;
queue<int> order;
bool status = 0;
int n;
int check = 0;
stack<int> errlist;
set<int> errset;
int**link3;

int dfs(int** link, int starter){
	link = link3;
	if(starter == -1){
		for(int i=0; i<n; i++){
			for(int j=0; j<n;j++){
				if(link[i][j] == 1){
					starter = i;
					if(dfs(link, starter)==1)
						return 1;
				}
			}
		}
	}
	if(errset.find(starter) == errset.end()){
		errset.insert(starter);
		errlist.push(starter);
		for(int i=0; i<n; i++){
			if(link[starter][i] == 1){
				link[starter][i] = 0;
				if(dfs(link, i) == 1){
					return 1;
				}
			}
		}
		errlist.pop();
		return 0;
	}
	else{
		errlist.push(starter);
		return 1; 
	}
}

void topoSort(int** link, int* indegrees){
	int zerodeg = -1;
	for(int i=0; i<n; i++)
	{
		if(indegrees[i] == 0 && (visited.find(i) == visited.end())){
			zerodeg = i;
			check++;
			break;
		}
		if(check == n){
			return;
		}
	}
	if(zerodeg == -1){
		status = 1;
		dfs(link, -1);
		return;
	}
	order.push(zerodeg);
	visited.insert(zerodeg);
	for(int i=0; i<n; i++){
		if(link[zerodeg][i] == 1){
			link[zerodeg][i] = 0;
			indegrees[i]--;
		}
	}
	topoSort(link, indegrees);
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
	int *indegrees = new int[n];
	for(int i=0; i<n; i++){
		int degree = 0;
		for(int j=0; j<n; j++){
			if(link[j][i] == 1){
				degree++;
			}
		}
		indegrees[i] = degree;
	}
	int** link2 = new int*[n];
	for(int i=0; i<n; i++){
		link2[i] = new int[n];
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			link2[i][j]=link[i][j];
		}
	}
	link3 = link;
	topoSort(link2, indegrees);
	if(status == 0){
		cout<<"Yes"<<endl;
		cout<<"L"<<order.front();
		order.pop();
		while(!order.empty()){
			cout<<", L"<<order.front();
			order.pop();
		}
		cout<<endl;
	}
	else {
		stack<int> ans;
		while(!errlist.empty()){
			ans.push(errlist.top());
			errlist.pop();
		}
		cout<<"No"<<endl;
		cout<<"L"<<ans.top();
		ans.pop();
		while(!ans.empty()){
			cout<<"->L"<<ans.top();
			ans.pop();
		}
		cout<<endl;
	}


	return 0;
}