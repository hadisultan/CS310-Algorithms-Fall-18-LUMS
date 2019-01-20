#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <cstdlib>
#include <ctime>

using namespace std;

// Reccurrence relatiion:
// sumMemo[0][0] = arr[0]][0]
// sumMemo[0][j] = arr[0][j]+sumMemo[0][j-1]
// sumMemo[i][0] = arr[i][0]+sumMemo[i-1][0]
// sumMemo[i][j] = arr[i][j]+sumMemo[i-1][j]+sumMemo[i][j-1]-sumMemo[i-1][j-1]

// Time complexity: O(n^3), O(n^2) time to find the max for a single width w, since w can range from 1<=w<=n, which is O(n), the total time complexity is O(n^3)

int n;
int** sumMemo;
int** arr;
int w, lowi, lowj;
int maxi = INT_MIN;

void findMaxSum(){
	for(int i=1;i<n; i++){
		for(int j=i-1; j<n; j++){
			for(int k=i-1; k<n; k++){
				int sum = 0;
				if(j-i>=0){
					sum = sum - sumMemo[j-i][k];
				}
				if(k-i>=0){
					sum = sum - sumMemo[j][k-i];
				}
				if(k-i>=0 && j-i>=0){
					sum += sumMemo[j-i][k-i];
				}
				sum += sumMemo[j][k];
				if(maxi < sum){
					maxi = sum;
					w = i;
					lowi = j;
					lowj = k;
				}
			}
		}
	}
}

void makeSumMemo(){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(i==0 && j==0){
				sumMemo[i][j] = arr[i][j];
			}
			else if(i==0){
				sumMemo[i][j] = arr[i][j]+sumMemo[i][j-1];
			}
			else if(j==0){
				sumMemo[i][j] = arr[i][j]+sumMemo[i-1][j];
			}
			else{
				sumMemo[i][j] = arr[i][j]+sumMemo[i-1][j]+sumMemo[i][j-1]-sumMemo[i-1][j-1];
			}
		}
	}

}

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
	sumMemo = new int*[n];
	arr = new int*[n];
	for(int i=0; i<n; i++){
		sumMemo[i] = new int[n];
		arr[i] = new int[n];
	}
	for(int i=0; i< n; i++){
		int start = 0, end = start;
		int counter = 0;
		getline(inFile, line);
		linelen = line.length();
		if(i==0){
			start = 2;
		}
		else
			start = 0;
		for(int k = start; k < linelen; k++){
			for(int j=start; j<linelen; j++){
				if(j==linelen-1 || line[j] == ','){
					end = j;
					break;
				}
			}
			arr[i][counter] = stoi(line.substr(start, end-start));
			// cout << "Inserted " << arr[i][counter] << " into arr " << i << counter << endl;
			counter++;
			start = end+2;
			k = start;
		}
	}

}

void makeRandom(){
	int l = -90;
	int h = 100;
	n = rand()%12+4;
	cout << "n is: " << n << endl;
	sumMemo = new int*[n];
	arr = new int*[n];
	for(int i=0; i<n; i++){
		sumMemo[i] = new int[n];
		arr[i] = new int[n];
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			arr[i][j] = rand()%(h-l+1)+l;
		}
	}
}

int main(){
	// n = 8;
	srand(time(NULL));
	string dec;
	cout << "Enter 1 for file input, 2 for random array: ";
	getline(cin, dec);
	if(dec == "1"){ 
		takeinput();
	}
	else{
		makeRandom();
	}
	// int temparr[n][n] = { {25, 31, 1, 8, 33, -1, 20, -25},
	// 		{14, 13, -10, 2, 23, -7, 27, 21},
	// 		{31, 45, 11, -27, 8, 6, 7, 32},
	// 		{12, -19, -25, 4, -67, 4, 4, 13},
	// 		{14, -12, 10, 3, 11, 5, 4, 5},
	// 		{4, 4, -25, 4, -67, 13, 12, -19},
	// 		{22, -29, -15, 14, -37, -141, 14, 13},
	// 		{11, -29, -15, 14, 17, 6, 4, 13} };
	// for(int i=0; i<n; i++)
	// 	for(int j=0; j<n; j++)
	// 		arr[i][j] = temparr[i][j];
	cout << "The array is: " << endl;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	makeSumMemo();
	cout << endl << endl;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cout << sumMemo[i][j] << " ";
		}
		cout << endl;
	}
	findMaxSum();
	
	cout << endl << "width = " << w << endl << endl;
	cout << "top left = (" << lowi-w+1 << "," << lowj-w+1 << ")" << endl;
	cout << "bottom right = (" << lowi << "," << lowj << ")" << endl << endl;
	cout << "Sum is " << maxi << endl;
	// cout << "max: " << maxi << ", w: " << w << ", lowi: " << lowi << ", lowj: " << lowj << endl;


	return 0;
}