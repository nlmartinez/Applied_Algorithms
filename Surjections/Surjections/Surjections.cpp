#include<iostream>
#include<fstream>

using std::cout;
using std::ifstream;
using std::ofstream;

int getFactorial(int m){
	int result = 1;
	while(m > 1){
		result = result*m;
		m = m - 1;
	}

	return result;
}

int getCombinations(int n, int i){
	if(i == 0 || n==0 || i==n){
		return 1;
	}
	if(0 < i < n){
		return (getCombinations((n-1),(i-1)) + getCombinations((n-1), i));
	}
}

int getSurjection(int m, int n){

	if(n == 1){
		return 1;
	}
	if(m < n){
		return 0;
	}
	if(m == n){
		return getFactorial(m);
	}
	if(n > 1 && m > n){
		return (n^m - (getCombinations(n, (n-1))*getSurjection(m, (n-1))));
	}
}

//I'm sorry this is a few minutes late; I'm at a Honors retreat with spotty internet connection
//Nathan Martinez

int main(){
	ifstream inFile;
	ofstream outFile;
	int m; int n; char space;

	inFile.open("surjections.in");
	if(inFile){
		outFile.open("surjections.out");

		while(!inFile.eof()){
			inFile >> m >> space >> n;
			if(m != 0 && n != 0){
				outFile << getSurjection(m, n) << "\n";
			}
		}
		inFile.close();
		outFile.close();
	}
	else
		cout << "File not found.\n";
	return 0;
}