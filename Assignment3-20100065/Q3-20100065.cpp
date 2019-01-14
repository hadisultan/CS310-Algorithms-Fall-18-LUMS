#include <iostream>
#include <fstream>

using namespace std;

/*
My algorithm involved breaking the 2-D array into 4 grids, each of size half
of the previous grid and assigning the edges of these grids a char. This
went on until the size of the grids being recursively passed to my function
were 2x2, where the base case was hit.

The space complexity is O(n^2) as there is an nxn char array being used.
The run-time complexity, being proved in Q3-recurrence.jpeg, is O(n^2). 
*/

int n;
int r;
int c;
char** grid;
char alpha = 'a';

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
	cout << "n is: " << n << endl;
	getline(inFile, line);
	linelen = line.length();
	r = stoi(line.substr(2, linelen-2));
	cout << "r is: " << r << endl;
	getline(inFile, line);
	linelen = line.length();
	c = stoi(line.substr(2, linelen-2));
	cout << "c is: " << c << endl;
	grid = new char*[n];
	for(int i=0; i<n; i++){
		grid[i] = new char[n];
	}
	grid[r][c] = '\0';

}

void solve(int startr, int midr, int startc, int midc, int row, int col){
	int quadrant;
	if(row>=midr){
		if(col>=midc){
			quadrant = 4;
		}
		else{
			quadrant = 3;
		}
	}
	else{
		if(col>=midc){
			quadrant = 2;
		}
		else{
			quadrant = 1;
		}
	}
	if(quadrant == 1){
		grid[midr-1][midc] = alpha;
		grid[midr][midc-1] = alpha;
		grid[midr][midc] = alpha;
		alpha++;
		if(alpha>'z')
			alpha = 'a';
		if(midr-startr > 1){
			solve(startr, (startr+midr)/2, startc, (startc+ midc)/2, row, col);
			solve(startr, (startr+midr)/2, midc, (midc-startc)/2+midc, midr-1, midc);
			solve(midr, (midr-startr)/2+midr, startc, (startc+ midc)/2, midr, midc-1);
			solve(midr, (midr-startr)/2+midr, midc, (midc-startc)/2+midc, midr, midc);
		}
	}
	else if(quadrant == 2){
		grid[midr-1][midc-1] = alpha;
		grid[midr][midc-1] = alpha;
		grid[midr][midc] = alpha;
		alpha++;
		if(alpha>'z')
			alpha = 'a';
		if(midr-startr > 1){
			solve(startr, (startr+midr)/2, startc, (startc+ midc)/2, midr-1, midc-1);
			solve(startr, (startr+midr)/2, midc, (midc-startc)/2+midc, row, col);
			solve(midr, (midr-startr)/2+midr, startc, (startc+ midc)/2, midr, midc-1);
			solve(midr, (midr-startr)/2+midr, midc, (midc-startc)/2+midc, midr, midc);
		}
	}
	else if(quadrant == 3){
		grid[midr-1][midc-1] = alpha;
		grid[midr-1][midc] = alpha;
		grid[midr][midc] = alpha;
		alpha++;
		if(alpha>'z')
			alpha = 'a';
		if(midr-startr > 1){
			solve(startr, (startr+midr)/2, startc,(startc+ midc)/2, midr-1, midc-1);
			solve(startr, (startr+midr)/2, midc, (midc-startc)/2+midc, midr-1, midc);
			solve(midr, (midr-startr)/2+midr, startc, (startc+midc)/2, row, col);
			solve(midr, (midr-startr)/2+midr, midc, (midc-startc)/2+midc, midr, midc);
		}
	}
	else if(quadrant == 4){
		grid[midr-1][midc-1] = alpha;
		grid[midr-1][midc] = alpha;
		grid[midr][midc-1] = alpha;
		alpha++;
		if(alpha>'z')
			alpha = 'a';
		if(midr-startr > 1){
			solve(startr, (startr+midr)/2, startc, (startc+ midc)/2, midr-1, midc-1);
			solve(startr, (startr+midr)/2, midc, (midc-startc)/2+midc, midr-1, midc);
			solve(midr, (midr-startr)/2+midr, startc, (startc+ midc)/2, midr, midc-1);
			solve(midr, (midr-startr)/2+midr, midc, (midc-startc)/2+midc, row, col);
		}
	}


	return;
	
}

void printoutput(){
	for(int i = 0; i<n; i++){
		for(int j = 0; j<n; j++){
			if(grid[i][j] == '\0'){
				cout << ' ' << '|';
			}
			else
				cout << grid[i][j] << '|';
		}
		cout << endl;
	}
}

int main(){
	takeinput();
	solve(0, n/2, 0, n/2, r, c);
	printoutput();

	return 0;
}