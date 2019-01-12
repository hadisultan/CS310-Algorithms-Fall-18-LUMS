#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;


// I have used vectors to store the stations and their delays and distances. The space complexity of these vectors is O(N).
// The running time complexity of my algorithm is O(N) as I just traverse all the vectors once and computes if it needs to refill
// its tank or not.

double maximum;
double currentfuel;
double fillrate;
double travrate;
int n;
double total;
vector<double> stops;
vector<double> totaldists;
vector<double> delay;
vector<double> locations;

void takeinput(){
	string fname;
	cout << "Enter filename: ";
	getline(cin, fname);
	ifstream inFile;
	inFile.open(fname.c_str());
	string line;
	getline(inFile, line);
	int linelen = line.length();
	maximum = stoi(line.substr(2, linelen-2));
	currentfuel = maximum;
	getline(inFile, line);
	linelen = line.length();
	travrate = stoi(line.substr(2, linelen-2));
	getline(inFile, line);
	linelen = line.length();
	fillrate = stoi(line.substr(2, linelen-2));
	getline(inFile, line);
	linelen = line.length();
	double totaldist = 0;
	n = stoi(line.substr(2, linelen-2));
	for(int i = 0; i<n; i++){
		getline(inFile, line);
		linelen = line.length();
		for(int j = 0; j<linelen; j++){
			if(line[j] == ' '){
				if(i == 0){
					locations.push_back(stoi(line.substr(j+1, linelen-j+1)));
					totaldist = stoi(line.substr(j+1, linelen-j+1));
				}
				else{
					locations.push_back(stoi(line.substr(j+1, linelen-j+1))-totaldist);
					totaldist = stoi(line.substr(j+1, linelen-j+1));
				}
				totaldists.push_back(stoi(line.substr(j+1, linelen-j+1)));
				break;
			}			
		}
	}
	getline(inFile, line);
	linelen = line.length();
	total = stoi(line.substr(2, linelen-2));
	locations.push_back(total-totaldist);
}

void takestep(int currentpos){
	if(currentpos > n)
		return;
	if(currentfuel/travrate >= locations[currentpos]){
		currentfuel -= locations[currentpos]*travrate;
		// cout << "Travelled " << locations[currentpos] << "km to pos " << currentpos << " without filling the tank." << endl;
		// cout << "Current fuel is now " << currentfuel << endl;
		takestep(currentpos+1);
	}
	else{
		double journeyahead = 0;
		// for(int i = currentpos; i<=n; i++)
		// 	journeyahead += locations[i];
		journeyahead = locations[currentpos];
		double filling = min(maximum, journeyahead*travrate);
		stops.push_back(currentpos);
		double fuel = filling-currentfuel;
		double timedelay = (fuel)/fillrate;
		delay.push_back(timedelay);
		currentfuel = filling;
		currentfuel -= locations[currentpos]*travrate;
		// cout << "Travelled " << locations[currentpos] << "km to pos " << currentpos << ". Filled " << fuel << " litres in the tank, had to wait " << timedelay << "mins." << endl;
		// cout << "Current fuel is now " << currentfuel << endl;
		takestep(currentpos+1);

	}
}

void printoutput(){
	if(stops.size() == 0){
		cout << "Total time: " << 0 << endl;
	}
	else if(stops.size() == 1){
		cout << "L" << stops[0] << " " << delay[0] << endl;
		cout << "Total time: " << delay[0] << endl;	
	}
	else{
		double totaltime = 0;
		for(int i=0; i<stops.size()-1; i++){
			cout << "L" << stops[i] << " " << delay[i] << ", ";
			totaltime += delay[i];
		}
		cout << "L" << stops[stops.size()-1] << " " << delay[stops.size()-1] << endl;
		totaltime += delay[stops.size()-1];
		cout << "Total time: " << totaltime << endl;		

	}
}

int main(){
	takeinput();
	takestep(0);
	printoutput();

	return 0;
}