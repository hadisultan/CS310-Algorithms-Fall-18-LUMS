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
queue<int> row;
int rows = 0;

void topoSort(int** link, int* indegrees){
	int zerodeg = -1;
	order.push(-1);
	int hello = 0;
	for(int i=0; i<n; i++)
	{
		if(check == n && hello == 0){
			return;
		}
		if(indegrees[i] == 0 && (visited.find(i) == visited.end())){
			row.push(i);
			check++;
			hello = 1;
		}
	}
	if(row.empty()){
		status = 1;
		return;
	}
	while(!row.empty()){
		zerodeg = row.front();
		row.pop();
		order.push(zerodeg);
		visited.insert(zerodeg);
		for(int i=0; i<n; i++){
			if(link[zerodeg][i] == 1){
				link[zerodeg][i] = 0;
				indegrees[i]--;
			}
		}
	}
	rows++;
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
	topoSort(link2, indegrees);
	if(status == 0){
		cout<<"Yes"<<endl;
		cout<<rows<<endl;
		order.pop();
		int temp2;
		temp2 = order.front();
		order.pop();
		if(order.front() == -1){
			cout<<"L"<<temp2;
		}
		else{
			cout<<"L"<<temp2<<", ";
		}
		while(!order.empty()){
			if(order.front() == -1){
				cout<<endl;
				order.pop();
			}
			if(order.empty()){
				break;
			}
			int temp = order.front();
			order.pop();
			if(order.front()==-1){
				cout<<"L"<<temp;
			}
			else{
				cout<<"L"<<temp<<", ";
			}
		}
	}
	else {
		cout<<"No"<<endl;
	}


	return 0;
}