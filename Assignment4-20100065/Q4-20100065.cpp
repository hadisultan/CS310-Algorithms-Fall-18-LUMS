#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

// Recurrence relation:
// solve({}, {}, s3, concat) = (concat == s3)
// solve({x:xs}, {y:ys}, s3, concat) = (solve({xs},{y:ys},s3,concat+x))||(solve({x:xs},{ys}, s3, concat+y)) 
// The first argument is S1, the second is S2 and the third is S3. We initialize the function by calling func( s1, s2, s3, {})

// Time-complexity = O(len(S1)+len(S2))^2, there are O(len(S1)+len(S2))^2 which take O(1) time.

string s1, s2, s3;
string fin = "";
unordered_map<string, bool> memo;

void takeinput(){
	string fname;
	cout << "Enter filename: ";
	getline(cin, fname);
	ifstream inFile;
	inFile.open(fname.c_str());
	string line;
	getline(inFile, s1);
	getline(inFile, s2);
	getline(inFile, s3);
}

int recur = 0;

bool solve(string one, string two, string three, string concat){
	string val = "";
	val = one + " " + two + " " + concat;
	auto itr = memo.find(val);
	// if(itr != memo.end()){
	// 	// cout << "found" << endl;
	// 	return itr->second;
	// }
	++recur;
	if(one.length() == 0 && two.length() == 0){
		if(concat == three){
			memo[val] = 1;
			return true;
		}
		memo[val] = 0;
		return false;
	}
	if(one.length() == 0){
		concat += two[0];
		two = two.substr(1);
		if(solve(one, two, three, concat)){
			fin = "2" + fin;
			memo[val] = 1;
			return true;
		}
		memo[val] = 0;
		return false;
	}
	if(two.length() == 0){
		concat += one[0];
		one = one.substr(1);
		if(solve(one, two, three, concat)){
			fin = "1" + fin;
			memo[val] = 1;
			return true;
		}
		memo[val] = 0;
		return false;
	}
	string tempconcat1 = concat;
	string tempconcat2 = concat;
	string temp1 = one;
	string temp2 = two;
	tempconcat1 += temp1[0];
	temp1 = temp1.substr(1); 
	tempconcat2 += temp2[0];
	temp2 = temp2.substr(1);
	bool sol1 = solve(temp1, two, three, tempconcat1); 
	if(sol1){
		fin = "1" + fin;	
		memo[val] = 1;
		return true;
	}
	bool sol2 = solve(one, temp2, three, tempconcat2);
	if(sol2){
		fin = "2" + fin;
		memo[val] = 1;
		return true;
	}
	memo[val] = 0;
	return false;
	// return (sol1 || sol2); 

}

int main(){
	takeinput();
	bool ans = solve(s1, s2, s3, "");
	if(ans){
		cout << "VALID" << endl;
		int counter1 = 0;
		int counter2 = 0;
		char current = fin[0];
		cout << "S" << current;
		if(current == '1'){
			cout << s1[counter1];
			counter1++;
		}
		else{
			cout << s2[counter2];
			counter2++;
		}

		for(int i=1; i<s3.length(); i++){
			if(current != fin[i]){
				cout<<" S" << fin[i];
				current = fin[i];
			}
			if(current == '1'){
				cout << s1[counter1];
				counter1++;
			}
			else{
				cout << s2[counter2];
				counter2++;
			}
		}
		cout << endl;
	}
	else{
		cout << "INVALID" << endl;
	}
	// cout << "recursions: " << recur << endl;

	return 0;
}