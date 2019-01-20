#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <string>
#include <tuple>
#include <unordered_map>

using namespace std;

// Recurrence Relation:
// func(len, {}) = 0;
// func(len, {x}) = len;
// func(len, {x:xs}) = min(len+func(n, {y} for all y<n)+func(len-n, {(y)-n} for all y>n)) for all n in {x:xs}
// len is the length of the specific rod being passed to the function while the second argument is the vector 
// containing all the cuts present on that specific rod. 

// Time-complexity = O(mlog(m)), there are mlog(m) subproblems which take O(1) thanks to memoization.

typedef tuple<string,int> info;

struct key_hash : public unary_function<info, size_t>
{
   size_t operator()(const info& k) const
   {
      return get<0>(k)[0] ^ get<1>(k);
   }
};

struct key_equal : public binary_function<info, info, bool>
{
   bool operator()(const info& v0, const info& v1) const
   {
      return (
               get<0>(v0) == get<0>(v1) &&
               get<1>(v0) == get<1>(v1) 
             );
   }
};

typedef unordered_map<info,vector<int>,key_hash,key_equal> map_t;

map_t arr;

int n;
vector<int> m;

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
	for(int i=0; i<linelen; i++){
		if(line[i] == ' '){
			for(int j=i+1; j<linelen; j++){
				if(line[j+1] == ' ' || j == linelen-1){
					m.push_back(stoi(line.substr(i+1, j-i)));
					i = j;
					break;
				}
			}
		}
	}
}

vector<int> func(int len, vector<int> cuts){
	vector<int> tot;
	if(cuts.size() == 0){
		tot.push_back(0);
		return tot;
	}
	if(cuts.size() == 1){
		string v = to_string(len);		
		v += to_string(cuts[0]);
		tuple<string, int> temp1(v, cuts[0]);
		auto itr = arr.find(temp1);
		if(itr != arr.end()){
			// cout << "In memo." << endl;
			return arr[temp1];
		}
		else{
			vector<int> v;
			v.push_back(len);
			v.push_back(cuts[0]);
			arr[temp1] = v;
			return v;
		}
	}
	int min = INT_MAX;
	int cost;
	for(int i=0; i<cuts.size(); i++){
		int temp = cuts[i];
		string v = to_string(len);		
		for(int j=0; j<cuts.size(); j++){
			v += to_string(cuts[j]);
		}
		tuple<string, int> temp1(v, temp);
		auto itr = arr.find(temp1);
		if(itr != arr.end()){
			// cout << "In memo2." << endl;
			tot = arr[temp1];
		}
		
		vector<int> before;
		vector<int> after;
		for(int j=0; j<cuts.size(); j++){
			if(j != i){
				if(cuts[j] < temp){
					before.push_back(cuts[j]);
				}
				else{
					after.push_back(cuts[j]-temp);
				}
			}
		}
		vector <int> left = func(temp, before);
		vector <int> right = func(len-temp, after);
		cost = len + left[0] + right[0];
		if(cost < min){
			min = cost;
			vector <int> tempvec;
			tempvec.push_back(cost);
			tempvec.push_back(temp);
			for(int k=1; k<left.size(); k++){
				tempvec.push_back(left[k]);
			}
			for(int k=1; k<right.size(); k++){
				tempvec.push_back(right[k]+temp);
			}
			tot = tempvec;
		}
		arr[temp1] = tot;
	}
	return tot;
}

int main(){
	takeinput();
	vector <int> lol = func(n,m);
	for(int i=0; i<lol.size(); i++){
		cout << lol[i] << " ";
	}
	cout << endl;
	return 0;
}