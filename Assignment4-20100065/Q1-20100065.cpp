#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;

// Recurrence relation: 
// solver(-2) = 0
// solver(-1) = 0
// solver(m) = max(rh[m]+solver(m-2), rl[m]+solver(m-1))
// the solver function conputes the maximum revenue for a
// particular week 'm'. We pass the value of the last 
// week (n-1) to compute this.

// Time Complexity: O(n), there are O(n) sub-problems which take 0(1) time thanks to memoization.



vector<int> rh;
vector<int> rl;
int n;
int* arr;
char* dest;

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
	getline(inFile, line);
	linelen = line.length();
	int startpos, endpos;
	for(int i=0; i<n; i++){
		if(i == 0)
			startpos = 3;
		else
			startpos = endpos+1;
		for(int j = startpos; j<=linelen; j++){
			if(line[j] == ' ' || j== linelen){
				endpos = j;
				rh.push_back(stoi(line.substr(startpos, endpos-startpos)));
				break;
			}
		}
	}
	getline(inFile, line);
	linelen = line.length();
	for(int i=0; i<n; i++){
		if(i == 0)
			startpos = 3;
		else
			startpos = endpos+1;
		for(int j = startpos; j<=linelen; j++){
			if(line[j] == ' ' || j== linelen){
				endpos = j;
				rl.push_back(stoi(line.substr(startpos, endpos-startpos)));
				break;
			}
		}
	}
	
}

void initializeArr(){
	arr = new int[n];
	dest = new char[n];
	for(int i=0; i<n; i++){
		arr[i] = -1;
	}
	if(rh[0] > rl[0]){
		arr[0] = rh[0];
		dest[0] = 'h'; 
	}
	else{
		arr[0] = rl[0];
		dest[0] = 'l'; 
	}
}

int solver(int q){
	if(arr[q] != -1){
		return arr[q];
	}
	else{
		int rhstep;
		if(q > 1)
			rhstep = rh[q]+solver(q-2);
		else
			rhstep = rh[q];
		int rlstep = rl[q]+solver(q-1);
		if(rhstep > rlstep){
			arr[q] = rhstep;
			dest[q] = 'h';
		}
		else{
			arr[q] = rlstep;
			dest[q] = 'l';
		}
		return arr[q];
	}
}

void makeSchedule(){
	int sum = 0;
	for(int i=n-1; i>=0; i--){
		if(dest[i] == 'h'){
			dest[i-1] = 'p';
			i--;
		}
	}
}

int main(){
	takeinput();
	initializeArr();
	int total = solver(n-1);
	makeSchedule();
	// cout << "Ans: " << endl;
	for(int i = 0; i < n; i++){
		cout << "Week " << i+1 << ": ";
		if(dest[i] == 'h'){
			cout << "High " << rh[i] << endl;
		}
		else if(dest[i] == 'l'){
			cout << "Low " << rl[i] << endl;
		}
		else{
			cout << "Priming" << endl;
		}
	}
	cout << "Total Revenue: " << total << endl;

	return 0;
}