#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

// Recurrence relation:
// allPossible(s1, s2, {}) = true if |s1-s2| = k, else false
// allPossible(s1, s2, {x:xs}) = (allPossible(s1+x, s2, {xs}))||(allPossible(s1, s2+x, {xs}))
// S1 and S2 is the sum of both sets at a particular points while the third argument is the remaining elements in the array.

//Time complexity: O(m^2), there are O(m^2) subproblems which take O(1) time thanks to memoization.

int k;
int n;
vector<int> tot;
vector<vector <int>>** memo;

void takeinput(){
	n = 0;
	string fname;
	cout << "Enter filename: ";
	getline(cin, fname);
	ifstream inFile;
	inFile.open(fname.c_str());
	string line;
	getline(inFile, line);
	int linelen = line.length();
	k = stoi(line.substr(2, linelen-2));
	getline(inFile, line);
	linelen = line.length();
	for(int i=0; i<linelen; i++){
		if(line[i] == ' '){
			for(int j=i+1; j<linelen; j++){
				if(line[j+1] == ' ' || j == linelen-1){
					tot.push_back(stoi(line.substr(i+1, j-i)));
					n++;
					i = j;
					break;
				}
			}
		}
	}
}

int recur = 0;
int worecur = 0;

vector<vector <int>> allPossible(int s1, int s2, vector<int> t){
	// cout << ++recur << endl;
	// recur++;
	if(memo[s1][s2].size() != 0){
		// cout << "CASE 1" << endl;
		return memo[s1][s2];
	}
	if(memo[s2][s1].size() != 0){
		// cout << "CASE 2 " << memo[s2][s1].size()<< endl;
		vector<vector <int>> ret;
		ret.push_back(memo[s2][s1][0]);
		ret.push_back(memo[s2][s1][2]);
		ret.push_back(memo[s2][s1][1]);
		return ret;
	}
	worecur++;
	if(t.size() == 0){
		// cout << "CASE 3" << endl;
		vector<vector<int>> temp;
		vector<int> base;
		for(int i=0; i<3; i++){
			temp.push_back(base);
		}
		if(s1-s2 == k){
			// cout << "CASE 4" << endl;
			temp[0].push_back(1);
			memo[s1][s2] = temp;
			return temp;
		}
		if(s2-s1 == k){
			// cout << "CASE 5" << endl;
			temp[0].push_back(1);
			memo[s1][s2] = temp;
			return temp;
		}
		// cout << "CASE 6" << endl;
		temp[0].push_back(0);
		memo[s1][s2] = temp;
		return temp;
	}
	int ele = t[0];
	t.erase(t.begin());
	vector<vector<int>> anss1 = allPossible(s1+ele, s2, t);
	vector<vector<int>> anss2 = allPossible(s1, s2+ele, t);
	if(anss1[0][0]){
		// cout << "CASE 7" << endl;
		anss1[1].push_back(ele);
		memo[s1][s2] = anss1;
		return anss1;
	}
	else if(anss2[0][0]){
		// cout << "CASE 8" << endl;
		anss2[2].push_back(ele);
		memo[s1][s2] = anss2;
		return anss2;
	}
	else{
		// cout << "CASE 9" << endl;		
		memo[s1][s2] = anss1;
		return anss1;
	}
}


int main(int argc, char const *argv[])
{
	takeinput();
	int sum = 0;
	for(int i=0; i<tot.size(); i++)
		sum += tot[i];
	memo = new vector<vector <int>>*[sum+1];
	for(int i=0; i<sum+1; i++)
		memo[i] = new vector<vector <int>>[sum+1];
	// for(int i=0; i<sum+1; i++){
	// 	for(int j=0; j<sum+1; j++){
	// 		memo[i][j] = new vector<vector <int>>;
	// 	}
	// }
	vector<int> temp = tot;
	vector<vector<int>> answer = allPossible(0, 0, temp);
	if( answer[0][0]){
		cout << "POSSIBLE" << endl;
		int sum1 = 0, sum2 = 0;
		cout << "S1: ";
		for(int i=0; i<answer[1].size(); i++){
			cout << answer[1][i] << " ";
			sum1 += answer[1][i];
		}
		cout << " sum = " << sum1 << endl;	
		cout << "S2: ";
		for(int i=0; i<answer[2].size(); i++){
			cout << answer[2][i] << " ";
			sum2 += answer[2][i];
		}
		cout << " sum = " << sum2 << endl;
		cout << "Difference: " << sum1 << "-" << sum2 << " = " << sum1-sum2 << endl;	
	}
	else
		cout << "IMPOSSIBLE" << endl;
	// cout << "Number of accesses: " << worecur << endl;
 
	return 0;
}