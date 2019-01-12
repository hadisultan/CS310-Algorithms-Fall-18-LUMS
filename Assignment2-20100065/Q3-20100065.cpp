#include <iostream>
#include <fstream>
#include <queue>
#include <cstring>
#include <vector>

using namespace std;

// I have defined a struct for each piece and used vectors to store them. The space complexity of my algorithm is O(P+n), where P is the number of pieces
// and n is the number of rows. The running time complexity of my algorithm is O(Pn), as for each column, it have to insert 0<x<P pieces in the rows. 

struct piece{
	int row;
	int col;
};

struct roworder{
	int row;
	int tot;
	bool operator<(const roworder& rhs) const
    {
        return tot < rhs.tot;
    }
};

priority_queue<roworder> r; 
vector<roworder> fin;
vector<piece> p;
vector<int> rows;
vector<int> columns;
int n;

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
			startpos = 4;
		else
			startpos = endpos+1;
		for(int j = startpos; j<=linelen; j++){
			if(line[j] == ' ' || j== linelen){
				endpos = j;
				rows.push_back(stoi(line.substr(startpos, endpos-startpos)));
				break;
			}
		}
	}
	getline(inFile, line);
	linelen = line.length();
	for(int i=0; i<n; i++){
		if(i == 0)
			startpos = 4;
		else
			startpos = endpos+1;
		for(int j = startpos; j<=linelen; j++){
			if(line[j] == ' ' || j== linelen){
				endpos = j;
				columns.push_back(stoi(line.substr(startpos, endpos-startpos)));
				break;
			}
		}
	}
	
}

void assignrows(){
	for(int i = 0; i < n; i++){
		int rownum = rows[i];
		roworder a;
		a.row = i+1;
		a.tot = 0;
		fin.push_back(a);
		for(int j = 0; j < rownum; j++){
			piece pcs;
			pcs.row = i+1;
			pcs.col = -1;
			fin[i].tot++;
			p.push_back(pcs);
		}
		r.push(fin[i]);
	}
	// for(int i = 0; i<n; i++){
	// 	fin[i] = (r.top());
	// 	cout << "Vector " << i << ", row: " << fin[i].row << ", tot: " << fin[i].tot << endl;
	// 	r.pop();
	// }
}

void printq(){
	while(!r.empty()){
		cout << " ID row: " << r.top().row << " tot: " << r.top().tot << endl;
		r.pop();
	}
}

int assigncols(){
	int finval = 0;
	int rowval;
	for(int i = 0; i < n; i++){
		vector<roworder> used ;
		// cout << endl << "COLUMN " << i << endl << endl;
		// finval = 0;
		// rowval = fin[finval].row;
		rowval = (r.top().row);
		// cout << "Outside loop, row val changed to: " << rowval << endl;
		// cout << "Outside loop, row tot: " << r.top().tot << endl;

		int colnum = columns[i];
		int pcsfixed = 0;
		int j = 0;
		roworder temp = r.top();
		temp.tot--;
		r.pop();
		used.push_back(temp);
		int erj = 0;
		while(pcsfixed < colnum){
			if(p[j].row == rowval && p[j].col == -1){
				p[j].col = i+1;
				pcsfixed++;
				// cout << "Piece row: " << p[j].row << ", col: " << p[j].col << endl;
				if(pcsfixed == colnum){
					break;
				}				
				rowval = (r.top().row);
				// cout << "Row val changed to: " << rowval << endl;
				// cout << "Row tot: " << r.top().tot << endl;
				// while(r.top().tot == 0){
				// 	used.push_back(r.top());
				// 	r.pop()	;			
				// 	rowval = (r.top().row);
				// 	cout << "Row val changed to: " << rowval << endl;
				// 	cout << "Row tot: " << r.top().tot << endl;
				// }
				temp = r.top();
				temp.tot--;
				r.pop();
				used.push_back(temp);
			}
			j++;
			erj++;
			if(erj >= 100000){
				// cout << r.size() << endl;
				return 1;
			}
			if(j >= p.size()){
				// finval = (finval+1)%4;
				// rowval = fin[finval].row;
				j = 0;
			}
		}
		for(int k = 0; k<used.size(); k++){
			r.push(used[k]);
		}
	}
	// for(int i=0; i<p.size(); i++){
	// 	cout << "Piece " << i+1 <<" Row: " << p[i].row << " Col: " << p[i].col << endl;
	// }
	return 0;
}

void printoutput(){
	int rownum = 1;
	for(int i = 0; i < p.size(); i++){
		if(p[i].row != rownum){
			cout << endl;
			rownum = p[i].row;
		}
		cout << "(" << p[i].row << "," << p[i].col << ")";
	}
	cout << endl;
}

int main(){
	takeinput();
	assignrows();
	if(assigncols()){
		cout << "IMPOSSIBLE" << endl;
		return 0;
	}
	printoutput();

	return 0;
}