#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <set>

using namespace std;

/*
The data structures used were arrays and vectors.

I used the Gale Shapely algorithm but whenever, I was about to match a
plane with an airport, I checked to see whether or not the pair was in
X or not. If it wasn't then that meant that the pair was legal and could
be made.

The run-time and space complexity of the algorithm was O(n^2).
The run-time was O(n^2) because in the worst case a total of n^2 proposals
had to be made. I improved the run time by make the preference lookup 
faster by using the method I described in PA1 Q5.
The space-tinme was O(n^2) as a few 2-D arrays of size n were made.
*/

int n;
int **tablep;
int **tableposp;
int **tablea;
int **tableposa;
int **engaged;
vector<int> a;
vector<int> p;

void takeinput(){
	string fname;
	cout << "Enter filename: ";	
	getline(cin, fname);
	ifstream inFile;
	inFile.open(fname.c_str());
	string line;
	getline(inFile, line);
	int linelen = line.length();
	n = stoi(line.substr(2, linelen-2));
	tablep = new int*[n];
	tableposp = new int*[n];
	tablea = new int*[n];
	tableposa = new int*[n];
	// cout << "hello1" << endl;
	for(int i=0; i<n; i++){
		tablep[i] = new int[n];
		tableposp[i] = new int[n];
		tablea[i] = new int[n];
		tableposa[i] = new int[n];
	}
	int start = 0;
	int end = 0;
	int os;
	for(int k=0; k<n; k++){
		os = 0;
		getline(inFile, line);
		linelen = line.length();
		for(int i=0; i<linelen; i++){
			if(line[i] == ':'){
				start = i+3;
				break;
			}
		}
		for(int i=start; i<linelen; i++){
			if((line[i] == ',') || (i == linelen-1)){
				if(line[i] == ',')
					end = i;
				else
					end = i+1;
				int temp = stoi(line.substr(start, end-start));
				tablep[k][os] = --temp;
				os++;
				if(i == linelen-1){
					break;
				}
				for(int j=i; j<linelen; j++){
					if(line[j] == 'A'){
						start = j+1;
						break;
					}
				}
			}
		}
	}
	for(int k=0; k<n; k++){
		os = 0;
		getline(inFile, line);
		linelen = line.length();
		for(int i=0; i<linelen; i++){
			if(line[i] == ':'){
				start = i+3;
				break;
			}
		}
		for(int i=start; i<linelen; i++){
			if((line[i] == ',') || (i == linelen-1)){
				if(line[i] == ',')
					end = i;
				else
					end = i+1;
				int temp = stoi(line.substr(start, end-start));
				tablea[k][os] = --temp;
				os++;
				if(i == linelen-1){
					break;
				}
				for(int j=i; j<linelen; j++){
					if(line[j] == 'P'){
						start = j+1;
						break;
					}
				}
			}
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			int temp = tablep[i][j];
			tableposp[i][temp] = j;
			temp = tablea[i][j];
			tableposa[i][temp] = j;
		}
	}
	engaged = new int*[n];
	for(int i=0; i<n; i++){
		engaged[i] = new int[n];
		for(int j=0; j<n; j++){
			engaged[i][j] = 0;
		}
	}
	getline(inFile, line);
	linelen = line.length();
	for(int i = 0; i<linelen; i++){
		if(line[i] == 'P'){
			start = i+1;
			for(int j = i; j<linelen; j++){
				if(line[j] == ' '){
					end = j;
					break;
				}
			}
			p.push_back(stoi(line.substr(start, end-start))-1);
			start = end+2;
			for(int j = start+1; j<linelen; j++){
				if(line[j] == ','){
					end = j;
					break;
				}
				else if(j == linelen-1){
					end = j;
					break;
				}
			}
			a.push_back(stoi(line.substr(start, end-start))-1);
		}
	}

}

void galeShapley(){
	int counter[n];
	int men[n];
	int women[n];
	for(int i=0; i<n; i++){
		counter[i] = 0;
		men[i] = -1;
		women[i] = -1;
	}
	int prop = 0;
	int i = 0;
	while(prop < n*n){
		prop++;
		int breaker = 0;
		if(men[i]!=-1){
			i = (i+1)%n;
			continue;
		}
		else{
			int potentialw = tablep[i][counter[i]];
			counter[i] = counter[i]+1;
			if(women[potentialw] == -1){
				for(int k = 0; k < p.size(); k++){
					if(a[k] == potentialw && p[k] == i){
						breaker = 1;
						break;
					}
				}
				if(breaker != 1){
					engaged[i][potentialw] = 1;
					men[i] = potentialw;
					women[potentialw] = i;
				}
			}
			else{
				for(int k = 0; k < p.size(); k++){
					if(a[k] == potentialw && p[k] == i){
						breaker = 1;
						break;
					}
				}
				if(breaker!= 1){
					if(tableposa[potentialw][i] < tableposa[potentialw][women[potentialw]] ){
						engaged[i][potentialw] = 1;
						engaged[women[potentialw]][potentialw] = 0;
						men[women[potentialw]] = -1;
						women[potentialw] = i;
						men[i] = potentialw;
					}
				}
			}
		}
		i = (i+1)%n;
	}
}

void printoutput(){
	cout << "Stable Matching: ";
	int no = 0;
	int is = -1;
	int js;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(engaged[i][j] == 1){
				if(no == n-1){
					is = i;
					js = j;
					break;
				}
				else{
					cout << "A" << j+1 << " " << "P" << i+1 << ", ";
					no++;
				}				
			}
		}
		if(is != -1)
			break;
	}
	cout << "A" << js+1 << " " << "P" << is+1 << endl;

}

int main(int argc, char const *argv[])
{
	takeinput();
	galeShapley();
	printoutput();


	return 0;
}