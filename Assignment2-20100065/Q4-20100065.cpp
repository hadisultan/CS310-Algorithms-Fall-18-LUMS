#include <iostream>
#include <queue>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

// I have sorted the racks in order of their probability per unit length (p/L) using a priiority queue. This insertion takes O(nlogn) time and O(n) space.
// I have then outputted the priority queue by popping it, so the time complexity of my program remains O(nlogn) and the space complexity remains O(n).

struct rack{
	double len;
	double prob;
	int id;

	bool operator<(const rack& rhs) const
    {
        return prob/len < rhs.prob/rhs.len;
    }
};

priority_queue<rack> r; 
int n;
vector<double> length;
vector<double> probability;
vector<int> order;


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
			startpos = 2;
		else
			startpos = endpos+2;
		for(int j = startpos; j<=linelen; j++){
			if(line[j] == ',' || j== linelen){
				endpos = j;
				// cout << "Pushed back " << (line.substr(startpos, endpos-startpos)) << " into len." << endl;
				length.push_back(stod(line.substr(startpos, endpos-startpos)));
				break;
			}
		}
	}
	getline(inFile, line);
	linelen = line.length();
	for(int i=0; i<n; i++){
		if(i == 0)
			startpos = 2;
		else
			startpos = endpos+2;
		for(int j = startpos; j<=linelen; j++){
			if(line[j] == ',' || j== linelen){
				endpos = j;
				// cout << "Pushing " << line.substr(startpos, endpos-startpos) << " into probability." << endl;
				probability.push_back(stod(line.substr(startpos, endpos-startpos)));
				// cout << "Pushed back " << probability[probability.size()-1] << " into probability." << endl;
				
				break;
			}
		}
	}
	
}

void createqueue(){
	for(int i=0; i<n; i++){
		rack rcks;
		rcks.len = length[i];
		rcks.prob = probability[i];
		rcks.id = i;
		r.push(rcks);
	}
	// priority_queue<rack> t;
	// for(int i=0; i<n; i++){
	// 	rack test = r.top();
	// 	cout << "Number " << test.id+1 << " has length " << test.len << ", prob " << test.prob << " and product " << test.prob*test.len << endl;
	// 	r.pop();
	// 	t.push(test);
	// }
	// r=t;
}

void extractqueue(){
	int totallen = 0;
	double expected = 0;
	for(int i=0; i<n-1; i++){
		rack temp = r.top();
		totallen += temp.len;
		expected += temp.prob*totallen;
		cout << "rack" << temp.id+1 << ", ";
		r.pop();
	}
	rack temp = r.top();
	totallen += temp.len;
	expected += temp.prob*totallen;
	cout << "rack" << temp.id+1 << endl;
	r.pop();
	cout << "Expected time: " << expected << endl;

}



int main(int argc, char const *argv[])
{
	takeinput();
	createqueue();
	extractqueue();


	return 0;
}