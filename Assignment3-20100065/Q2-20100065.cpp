#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <set>

using namespace std;

/*
The data structures used were arrays, vectors and sets.

My code looked at the final locations for each team and assigned the final
location to the team that asked for their final location first. It then put
both the team and the locations in sets and went on to focus on the teams
and locations that weren't in these sets. This algorithm was derived from
the Gale Shapely algorithm but instead of the second array, I assigned the
location preferences based on the team that asked for the location earlier.

The space and running time for this algorithm is O(T*D) where T is the 
number of teams and D is the number of days. Since there is a 2-D TxD vector
in my code, the space complexity is O(T*D) and because the worst case 
involves traversing the entire vector, the running time complexity of my
algorithm is also O(T*D).  
*/

int n;
vector<vector<int>> schedule;
int* final;
set<int> finalized;
set<int> finalizedLoc;

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
	for(int i = 0; i<n; i++){
		vector<int> temp;
		schedule.push_back(temp);
	}
	for(int i = 0; i<n; i++){
		getline(inFile, line);
		linelen = line.length();
		int start = 0;
		int end = 0;
		int flag = 0;
		for(int j = 0; j < linelen; j++){
			if(flag == 0){
				if(line[j] == ':'){
					flag = 1;
				}
			}
			else{
				if(line[j+1] == '-'){
					schedule[i].push_back(-1);
					j++;
				}
				else{
					for(int k = j+1; k<=linelen; k++){
						if(line[k] == ',' || k == linelen){
							end = k-1;
							break;
						}
					}
					schedule[i].push_back(stoi(line.substr(j+2, end-j))-1);
					j = end;					
				}
			}
		}
	}

}

void findfinal(int finaldest[], int finalweek[]){
	for(int i=0; i<schedule.size(); i++){
		int counter = 0;
		if(finalizedLoc.find(i) != finalizedLoc.end()){
			continue;
		}
		for(int j=0; j<schedule[i].size(); j++){
			counter++;
			if((finalized.find(schedule[i][j]) == finalized.end()) && (schedule[i][j]!=-1)){
				finaldest[i] = schedule[i][j];
				finalweek[i] = counter;
			}
		}
	}
}

void solver(){
	int finaldest[n];
	int finalweek[n];
	final = new int[n];
	for(int i=0; i<n; i++){
		final[i] = -1;
	}
	while(finalized.size() != n){
		findfinal(finaldest, finalweek);
		int temp[n]	;
		for(int i = 0; i<n; i++){
			temp[i] = -1;
		}
		for(int i = 0; i<n; i++){
			int t2 = finaldest[i];
			if(final[t2] == -1){
				final[t2] = i;
			}
			else if((finalweek[final[t2]] > finalweek[i])){
				final[t2] = i;
			}
		}
		for(int i=0; i<n; i++){
			if(final[i]!=-1){
				finalized.insert(i);
				finalizedLoc.insert(final[i]);
			}
		}
		findfinal(finaldest, finalweek);
	}
	cout << "Final Destinations: ";
	for(int i=0; i<n-1; i++){
		cout << "L" << i+1 << " T" << final[i]+1 << ", ";
	}
	cout << "L" << n << " T" << final[n-1]+1 << endl;
	
}

int main(){
	takeinput();
	solver();

	return 0;
}