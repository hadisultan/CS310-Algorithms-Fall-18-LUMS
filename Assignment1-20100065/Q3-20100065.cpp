#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <climits>

using namespace std;

// I have used Dijkstra's shortest path algorithm to find the shortest paths for my
// nodes. Since, I have used an Adjacency Matrix to keep track of the nodes and 
// edges, the space and time complexity of my program is going to be O(V^2).
// The other data structures that I have used include sets and queues. The 
// functions using the queues have a time complexity of O(V*log(V)). The functions
// using the sets have a time complexity of O(1). 

int n;
set<int> visited;
const int inf = INT_MAX;
queue<int>* paths;

void makedistinf(int* dist){
	for(int i=0; i<n; i++)
		dist[i] = inf;
}

void dijkstrasetup(int** link, int start, int dest, int* dist){
	dist[start] = 0;
	while(visited.find(dest)==visited.end()){
		int u;
		int min = inf;
		for(int v=0; v<n; v++){
			if(dist[v] <= min){
				if(visited.find(v) == visited.end()){
					u = v;
					min = dist[v];
				}
			}
		}
		visited.insert(u);
		for(int v = 0; v<n; v++){
			if(visited.find(v) == visited.end() && link[u][v] != 0 && dist[u] != inf && dist[u]+link[u][v] < dist[v]){
				dist[v] = dist[u] + link[u][v];
				paths[v] = paths[u];
				paths[v].push(u);

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
		for(int j = breaker; j<linelen;)
		{
			if(line[j] == 'C'){
				int rellen = 0;
				int k = j+1;
				while(true){
					if(line[k] == ';'){
						break;
					}
					k++;
				} 
				int rel = stoi(line.substr(j+1, k-j));
				int l = k+1;
				while(true){
					if(line[l] == ',' || l == linelen){
						break;
					}
					l++;
				}
				int weight = stoi(line.substr(k+1, l-k));
				j= l+1;
				link[node][rel] = weight;
			}
			else
				j++;
			if(j == linelen-1){
				break;
			}
		}
	}
	int* dist = new int[n];
	makedistinf(dist);
	paths = new queue<int>[n];
	int start, end, detour;
	cout << "Enter the starting node: ";
	cin >> start;
	cout << "Enter the ending node: ";
	cin >> end;
	cout << "Enter the detour node: ";
	cin >> detour;
	dijkstrasetup(link, start, end, dist);
	int distWithoutDetour = dist[end];
	if(distWithoutDetour == inf)
		cout << "The ending node is unreachable from the starting node." << endl;
	else{
		cout << "The distance without the detour is: " << distWithoutDetour << endl;
		cout << "The path is: " << paths[end].front();
		paths[end].pop();
		while(!paths[end].empty()){
			cout << " -> " << paths[end].front();
			paths[end].pop();
		}
		cout << " -> " << end << endl; 
		queue<int> emptyqueue;
		for(int i = 0; i<n; i++){
			paths[i] = emptyqueue;
		}
		queue<int> dqueue;
		makedistinf(dist);
		set<int> newset;
		visited = newset;
		dijkstrasetup(link, start, detour, dist);
		while(!paths[detour].empty()){
			dqueue.push(paths[detour].front());
			paths[detour].pop();
		}
		for(int i = 0; i<n; i++){
			paths[i] = emptyqueue;
		}
		int distToDetour = dist[detour];
		if(distToDetour == INT_MAX){
			cout << "The detour is not reachable." << endl;
		}
		else{
			makedistinf(dist);
			visited = newset;
			dijkstrasetup(link, detour, end, dist);
			int distFromDetour = dist[end];
			if(distFromDetour == INT_MAX)
				cout << "Ending node not reachable via detour. " << endl;
			else{ 
				while(!paths[end].empty()){
					dqueue.push(paths[end].front());
					paths[end].pop();
				}
				int distUsingDetour = distToDetour + distFromDetour;
				cout << "The distance with the detour is: " << distUsingDetour << endl;
				cout << "The path using the detour is: " ;
				while(!dqueue.empty()){
					cout << dqueue.front() << " -> ";
					dqueue.pop();
				}
				cout<< end << endl;
				if(distUsingDetour <= distWithoutDetour*1.2)
					cout << "You should use the detour." << endl;
				else
					cout << "Don't use the detour!" << endl;
			}
		}
 	}
	return 0;
}