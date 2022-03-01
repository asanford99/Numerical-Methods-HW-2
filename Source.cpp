#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;



int getSize(string fileNamePar) {
	ifstream inputFile;
	int fileSize = 0;

	inputFile.open(fileNamePar);

	if (!inputFile.is_open()) {
		cout << "File cannot be opened.";
	}

	inputFile >> fileSize;

	inputFile.close();

	return fileSize;
}

vector<double> getLastLine(int vectorSizePar, string fileNamePar) {
	double dump; ;
	ifstream inputFile;
	vector<double> returnVector;

	returnVector.resize(vectorSizePar);

	inputFile.open(fileNamePar);

	for (int i = 0; i <= (vectorSizePar * vectorSizePar); i++) {
		inputFile >> dump;
	}

	for (int i = 0; i < vectorSizePar; i++) {
		inputFile >> returnVector[i];
	}

	inputFile.close();

	return returnVector;
}

vector <vector <double>> createMatrix(int arraySizePar, string fileNamePar) {
	ifstream inputFile;
	vector <vector <double>> returnMatrix;
	double dump;

	//constructs vector size
	returnMatrix.resize(arraySizePar);

	for (int i = 0; i < arraySizePar; i++) {
		returnMatrix[i].resize(arraySizePar);
	}

	inputFile.open(fileNamePar);

	for (int i = 0; i <= arraySizePar; i++) {
		if (i == 0) {
			inputFile >> dump;
		}
		else {
			for (int j = 0; j < arraySizePar; j++) {
				inputFile >> returnMatrix[i - 1][j];
			}

		}

	}

	inputFile.close();

	return returnMatrix;

}

 vector<double> backSub(int systemSizePar, vector<vector<double>> systemVariablesPar, vector<double> systemAnswersPar) {
	vector<double> returnVector;
	double sum;

	returnVector.resize(systemSizePar);

	returnVector[systemSizePar -1] = systemAnswersPar[systemSizePar -1] / systemVariablesPar[systemSizePar -1][systemSizePar -1];

	for (int i = (systemSizePar - 2); i >= 0; i--) {

		sum = systemAnswersPar[i];

		for (int j = (i + 1); j < systemSizePar; j++) {

			sum = sum - (systemVariablesPar[i][j] * returnVector[j]);

		}

		returnVector[i] = sum / systemVariablesPar[i][i];
	}

	for (int i = 0; i < systemSizePar; i++) {
		if (returnVector[i] == -0) {

			returnVector[i] = 0;

		}
	}

	return returnVector;
}

vector<double> forwardElim(int systemSizePar, vector <vector<double>> systemVariablesPar, vector<double> systemAnswersPar) {
	 vector<double> returnVector;

	 returnVector.resize(systemSizePar);

	 for (int k = 0; k < (systemSizePar - 1); k++) {

		 for (int i = (k + 1); i < systemSizePar; i++) {

			 double mult = systemVariablesPar[i][k] / systemVariablesPar[k][k];

			 for (int j = k; j < systemSizePar; j++) {

				 systemVariablesPar[i][j] = systemVariablesPar[i][j] - (mult * systemVariablesPar[k][j]);

			 }

			 systemAnswersPar[i] = systemAnswersPar[i] - (mult * systemAnswersPar[k]);
		 }
	 }

	 returnVector = backSub(systemSizePar, systemVariablesPar, systemAnswersPar);

	 return returnVector;

}

vector<double> sppBackSub(int systemSizePar, vector <vector<double>> systemVariablesPar, vector<double> systeamAnswersPar, vector<int> ind) {
	vector<double> returnVector;
	double sum;

	returnVector.resize(systemSizePar);

	returnVector[systemSizePar - 1] = systeamAnswersPar[ind[systemSizePar - 1]] / systemVariablesPar[ind[systemSizePar - 1]][systemSizePar - 1];

	for (int i = (systemSizePar - 2); i >= 0; i--){

		sum = systeamAnswersPar[ind[i]];

		for (int j = (i + 1); j < systemSizePar; j++) {

			sum = sum - (systemVariablesPar[ind[i]][j] * returnVector[j]);

		}

		returnVector[i] = sum / systemVariablesPar[ind[i]][i];
	}

	return returnVector;

}

vector<double> sppForwardElim(int systemSizePar, vector <vector<double>> systemVariablesPar, vector<double> systeamAnswersPar, vector<int> ind) {
	vector<double> scaling;
	vector<double> returnVector;

	scaling.resize(systemSizePar);
	returnVector.resize(systemSizePar);

	for (int i = 0; i < systemSizePar; i++) {

		double smax = 0;

		for (int j = 0; j < systemSizePar; j++) {
			smax = max(smax, abs(systemVariablesPar[i][j]));
		}

		scaling[i] = smax;
	}

	for (int k = 0; k < (systemSizePar - 1); k++) {

		double rmax = 0;
		int maxInd = k;

		for (int i = k; i < systemSizePar; i++) {

			double r = abs(systemVariablesPar[ind[i]][k]/scaling[ind[i]]);

			if (r > rmax) {

				rmax = r;
				maxInd = i;
			}
		}

		swap(ind[maxInd], ind[k]);

		for (int i = (k + 1); i < systemSizePar; i++) {

			double mult = systemVariablesPar[ind[i]][k] / systemVariablesPar[ind[k]][k];

			for (int j = k; j < systemSizePar; j++) {

				systemVariablesPar[ind[i]][j] = systemVariablesPar[ind[i]][j] - (mult * systemVariablesPar[ind[k]][j]);

			}

			systeamAnswersPar[ind[i]] = systeamAnswersPar[ind[i]] - (mult * systeamAnswersPar[ind[k]]);
		}

	}

	returnVector = sppBackSub(systemSizePar, systemVariablesPar, systeamAnswersPar, ind);

	return returnVector;
}


int main(int argc, char* argv[]) {

	string fileName;
	string sppArgument;
	string sppTag = "--spp";
	string fileTitle = "";
	string fileType = "";

	vector<double> matrixAnswers;
	vector <vector <double>> userMatrix;

	bool sppFlag = false;
	bool hasDot = false;

	if (argc == 3) {

		sppArgument = argv[1];

		if (sppArgument == "--spp") {
			sppFlag = true;

			fileName = argv[2];

			for (int i = 0; i < fileName.length(); i++) {

				if (hasDot == false) {

					fileTitle += fileName[i];
				}

				if (hasDot == true) {

					fileType += fileName[i];

				}

				if (fileName[i] == '.') {

					hasDot = true;

				}

			}

			if (fileType != "lin") {

				cout << "Invalid file type. Must be of type lin." << endl;

				exit;

			}
		}
		else {
			cout << "Invalid Input";
		}
	}

	if (argc == 2) {

		fileName = argv[1];

		for (int i = 0; i < fileName.length(); i++) {

			if (hasDot == false) {

				fileTitle += fileName[i];
			}

			if (hasDot == true) {

				fileType += fileName[i];

			}

			if (fileName[i] == '.') {

				hasDot = true;

			}

		}

		if (fileType != "lin") {

			cout << "Invalid file type. Must be of type lin." << endl;

			exit;

		}
	}

	if (argc < 2) {
		cout << "Invalid input. Missing a file name.";
	}

	if (argc > 3) {
		cout << "Invalid input. Too many arguments.";
	}
	

	//gets input from user and stores into systemSize
	int systemSize = getSize(fileName);

	//gets input from file and stores into userMatrix
	userMatrix = createMatrix(systemSize, fileName);

	//gets input from file and stores into matrixAnswers
	matrixAnswers = getLastLine(systemSize, fileName);

	//calls appropriate function depending on the status of sppFlag
	if (sppFlag == false) {

		matrixAnswers = forwardElim(systemSize, userMatrix, matrixAnswers);

	}
	else {

		vector<int> ind;
		ind.resize(systemSize);

		for (int i = 0; i < systemSize; i++) {

			ind[i] = i;
		}

		matrixAnswers = sppForwardElim(systemSize, userMatrix, matrixAnswers, ind);

	}
	
	//creates a file and store output info in it
	ofstream outputFile;

	outputFile.open(fileTitle + "sol");

	for (int i = 0; i < systemSize; i++) {

		outputFile << matrixAnswers[i] << " ";
	}
	
	return 0;
}
