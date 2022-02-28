#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;



int getSize(string fileNamePar) {
	ifstream inputFile;
	string fileSize;

	inputFile.open(fileNamePar);

	inputFile >> fileSize;

	inputFile.close;

	return stoi(fileSize);
}

vector <vector <int>> createMatrix(int arraySizePar, string fileNamePar) {
	ifstream inputFile;
	vector <vector <int>> returnMatrix;

	inputFile.open(fileNamePar);
	
	for (int i = 0; i < arraySizePar; i++) {
		if (i == 0) {

		}
		else {
			for (int j = 0; j < arraySizePar; j++) {
				inputFile >> ;
			}

		}

	}

}

int main(int argc, char* argv[]) {

	string fileName;
	string sppArgument;

	vector <vector <int>> userMatrix;

	bool sppFlag = false;

	if (argc == 3) {
		if (argv[1] == "--spp") {
			sppFlag = true;

			fileName = argv[2];
		}
		else {
			cout << "Invalid Input";
		}
	}

	if (argc == 2) {
		fileName = argv[1];
	}

	if (argc < 2) {
		cout << "Invalid input. Missing a file name.";
	}

	if (argc > 3) {
		cout << "Invalid input. Too many arguments.";
	}

	int systemSize = getSize(fileName);

	userMatrix = createMatrix(systemSize, fileName);
	

	return 0;
}
