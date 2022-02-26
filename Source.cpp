#include<iostream>
#include<string>
#include<fstream>
using namespace std;



int getSize(string fileNamePar) {
	std::ifstream inputFile(fileNamePar);
	string fileSize;

	getline(inputFile, fileSize);

	return stoi(fileSize);
}

int main(int argc, char* argv[]) {

	string fileName;
	string sppArgument;

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

	const int systemSize = getSize(fileName);

	int systemVariables[systemSize][systemSize] = ;
	

	return 0;
}