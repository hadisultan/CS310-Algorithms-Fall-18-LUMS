#include <iostream>
#include <fstream>
#include <cstring>
#include <set>
#include <cmath>
#include <climits>
#include <queue>
#include <vector>
#include <ctime>

using namespace std;

// I have used an adjacency list using a 2D vector and only pushes back an edge if it exists, this improves the space complexity to O(V+E). I have 
// also used the Prim's algorithm to find the MST first. I have defined edges using structs that not the two nodes and the weight of the edge.
// I have also used a priority queue to keep track of the minimum nodes, the insertion in priority_queues is O(logE). The sets that I have used also
// have a running time complexity of O(logE). The overall time complexity of my algorithm is O(ElogV) and the space time complexity is O(V+E).

struct edge{
	int from;
	int to;
	int weight;
	bool operator<(const edge& rhs) const
    {
    	if((rhs.from == from && rhs.to == to) || (rhs.to == from && rhs.from == to)){
    		//equal
    		return weight > rhs.weight;
    	}
    	else if(rhs.weight == weight){
    		if(rhs.from != from){
    			return from > rhs.from;
    		}
    		else
    			return to > rhs.to;
    	}
        return weight > rhs.weight;
    }
};

int mste = 0;
set<int> tree1;
set<int> tree2;
vector<int> tree1vec;
vector<int> tree2vec;
vector<vector<edge>> mst1;
set<int> visited;
vector<edge> ms1edges;
int e = 0;
int n;
const int inf = INT_MAX;
priority_queue<edge> p; 
vector<vector<edge>> v;

void takeinput(){
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
	for(int i=0; i<n; i++){
		vector<edge> temp1;
		v.push_back(temp1);
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
				edge temp;
				temp.from = node;
				temp.to = rel;
				temp.weight = weight;
				v[i].push_back(temp);
				p.push(temp);
			}
			else
				j++;
			if(j == linelen-1){
				break;
			}
		}
	}
}

void printvec(){
	for(int i=0; i<mst1.size(); i++){
		for(int j=0; j<mst1[i].size(); j++){
			// cout << "From: " << mst1[i][j].from << ", to: " << mst1[i][j].to << ", weight: " << v[i][j].weight << endl ;
			cout << "(" << mst1[i][j].from << "," << mst1[i][j].to << ")";
			ms1edges.push_back(mst1[i][j]);
			// if(v[i][j].from &&
			// v[i][j].to &&
			// v[i][j].weight);
		}
	}
		cout << endl;
}

int getMinKey(int k[]){
	int mk;
	int min = inf;
	for(int i=0; i<n; i++){
		if(visited.find(i) == visited.end() && k[i] < min){
			min = k[i];
			mk = i;
			// cout << "min changed to: " << min << endl;
			// cout << "mk changed to: " << mk << " " << i <<  endl;
		}
	}
	// cout << "RETURN" << endl;
	return mk;
}

int findweight(int i, int j){
	for(int k = 0; k<v[i].size(); k++){
		if(v[i][k].to == j){
			return v[i][k].weight;
		}
	}
	return -1;
}

void getMST(){
	int parent[n];
	for(int i = 0 ; i<n; i++)
		parent[n] = 0;
	int k[n];

	for(int i=0; i<n; i++){
		k[i] = inf;
	}
	k[0] = 0;
	parent[0] = -1;
	for(int i = 0; i<n-1; i++){
		int m = getMinKey(k);
		// cout << "Visited " << m << endl;
		visited.insert(m);
		for(int j = 0; j<v[m].size(); j++){
			// cout << "lol" << m << endl;
			// if(m==0 and j == 1){
			// 	cout << "Weight " << v[m][j].weight;
			// 	cout << "Kvalue " << k[v[m][j].to];	
			// }
			if(v[m][j].weight < k[v[m][j].to] && visited.find(v[m][j].to) == visited.end()){
				parent[v[m][j].to] = m;
				k[v[m][j].to] = v[m][j].weight; 
				// cout << "k[" << v[m][j].to << "] set to " << v[m][j].weight << ", Parent is: " << m << endl;
			}
		}
	}
	for(int i=0; i<n; i++){
		vector<edge> t;
    	mst1.push_back(t);

	}
	// printf("Edge \tWeight\n"); 
	for (int i = 1; i < n; i++) {
		vector<edge> t;
    	mst1.push_back(t);

    	// printf("%d - %d \t%d \n", parent[i], i, findweight(i, parent[i])); 
    	edge temp;
    	temp.to = i;
    	temp.from = parent[i];
    	temp.weight = findweight(i, parent[i]);
    	mst1[temp.from].push_back(temp);
    	mste++;
	}
}

void separatetree(set<int> &tree, vector<int> &vec, int inc, int notinc){
	for(int i=0; i<ms1edges.size(); i++){
		if(ms1edges[i].from == inc){
			if(ms1edges[i].to != notinc){
				if(tree.find(ms1edges[i].to) == tree.end()){
					vec.push_back(ms1edges[i].to);
					tree.insert(ms1edges[i].to);
					separatetree(tree, vec, ms1edges[i].to, notinc);
				}
			}
		}
		if(ms1edges[i].to == inc){
			if(ms1edges[i].from != notinc){
				if(tree.find(ms1edges[i].from) == tree.end()){
					vec.push_back(ms1edges[i].from);
					tree.insert(ms1edges[i].from);
					separatetree(tree, vec, ms1edges[i].from, notinc);
				}
			}
		}
	}
}

void removedge(int i, int j){
	for(int k = 0; k < mst1[i].size(); k++){
		if(mst1[i][k].to == j)
		{
			mst1[i].erase(mst1[i].begin()+k);
			// cout << "hello" << endl;
			// printvec();
		}
	}
	priority_queue<edge> p2;
	while(!p.empty()){
		if((p.top().from == i && p.top().to == j) || (p.top().to == i && p.top().from == j) ){
			p.pop();
		}
		else{
			p2.push(p.top());
			p.pop();
		}
	}
	while(!p2.empty()){
		p.push(p2.top());
		p2.pop();	
	} 


}

int findnewnode(){
	while(!p.empty()){	
		edge temp = p.top();
		p.pop();
		if((tree1.find(temp.from)!=tree1.end() && tree2.find(temp.to)!=tree2.end()) || (tree2.find(temp.from)!=tree2.end() && tree1.find(temp.to)!=tree1.end()) ){
			mst1[temp.from].push_back(temp);
			return 0;
		}
	}
	return 1;
}

int main(){
	srand(time(NULL));
	takeinput();
	getMST();
	cout << "MST1: ";
	printvec();
	int random = rand()%ms1edges.size();
	cout << "Edge removed: (" << ms1edges[random].from << "," << ms1edges[random].to << ")" << endl;
	removedge(ms1edges[random].from, ms1edges[random].to);
	tree1.insert(ms1edges[random].from);
	tree1vec.push_back(ms1edges[random].from);
	tree2.insert(ms1edges[random].to);
	tree2vec.push_back(ms1edges[random].to);
	separatetree(tree1, tree1vec, ms1edges[random].from, ms1edges[random].to);
	separatetree(tree2, tree2vec, ms1edges[random].to, ms1edges[random].from);
	// cout << "TREE 1 : ";
	// for(int i=0; i<tree1vec.size(); i++){
	// 	cout << tree1vec[i] << " ";
	// }
	// cout << endl;
	// cout << "TREE 2 : ";
	// for(int i=0; i<tree2vec.size(); i++){
	// 	cout << tree2vec[i] << " ";
	// }
	// cout << endl;
	// while(!p.empty()){
	// 	cout << p.top().from << " " << p.top().to << " " << p.top().weight << endl;
	// 	p.pop();
	// }
	if(!findnewnode()){
		cout << "MST2: ";
		printvec();
	}
	else{
		cout << "MST2 not possible. " << endl;
	}


	return 0;
} 


