#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;

/*
My algorithm involved creating a random n sized array and then breaking it 
into ~equal pieces and then passing these pieces recursively into the 
function. Once the base case of size 1 was hit, it returned the only value
in the grid. The call above this recursive call then compared the value
with its sibling value and looked at which of the values was repeated more.
This comparison was an O(n) comparison and since there were an O(log(n))
recursive steps, the run-time complexity of my algorithm was O(n*logn).
Proved in q5-recurrence.jpeg.

The space complexity of my algorithm was O(n) as an array of size n was used.
*/

int m;
int n;
int *grid;

bool decode(int a, int b){
	if(a == b)
		return true;
	return false;
}

int solve(int start, int end){
	if(start == end-1)
		return grid[start];
	int mid = (start+end)/2;
	int t1 = solve(start, mid);
	int t2 = solve(mid, end);
	int counter1 = 0;
	int counter2 = 0;
	for(int i=start; i<end; i++){
		if(decode(grid[i], t1))
			counter1++;
		if(decode(grid[i], t2))
			counter2++;
	}
	if(counter1>counter2)
		return t1;
	else
		return t2;
}

int main(){
	srand(time(NULL));
	cout << "Enter n: ";
	cin >> n;
	cout << "Enter m: ";
	cin >> m;
	grid = new int[n];
	for(int i = 0; i< n; i++)
		grid[i] = rand()%m+1;
	cout << "The array is: ";
	for(int i = 0; i< n; i++)
		cout << grid[i] << " ";
	cout << endl;
	int r = solve(0, n);
	cout << "Max is: " << r << endl;
	int counter = 0;
	for(int i=0; i<n; i++){
		if(decode(grid[i], r))
			counter++;
	}
	if(counter*1.0 > (n*1.0)/2.0){
		cout << "success" << endl;
	}
	else
		cout << "failure" << endl;

	return 0;
}