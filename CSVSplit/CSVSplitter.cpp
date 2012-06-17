#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <istream>
#include <pthread.h>
#include <cctype>
#include <cstdlib>

using namespace std;

bool IsInt(const string Input) {
	for(int i = 0; i < Input.length(); i++){
		if(!isdigit(Input[i])){
			return false;
		}
	}
	return true;
}

bool LinesValidation(int& NumInput) {
	string Input;
	cout << "Enter in the number of lines per subset: " << endl;
	cin >> Input;
	cout << "Input was: " << Input << endl;
	if (IsInt(Input)) {
		char* Offset;
		NumInput = strtol(Input.c_str(), &Offset, 10);
		return true;
	} else {
		cout << "Wrong Value Type!!!  Please enter in a positive integer." << endl;
		return LinesValidation(NumInput);
	}
	return false;
}

bool FileExists(string& FilePath, ifstream& InputFile) {
	cout << "Enter in the path of the main file: " << endl;
	cin >> FilePath;

	InputFile.open(FilePath.c_str());
	if (InputFile) {
		return true;
	} else {
		cout << "The filepath you entered does not exist.  Please try again." << endl;
		return FileExists(FilePath, InputFile);
	}
	return false;
}

int main() {
	/*	 ofstream myfile;
	 ifstream myinfile;
	 myfile.open("example.txt");
	 myfile << "Writing this to a file.\n";
	 myfile.close();

	 myfile.open("example1.txt");
	 myfile << "Writing to another file.\n";
	 myfile.close();*/
//string buffer[25];
	int lineNumbers;
	if (LinesValidation(lineNumbers)) {
		string filepath;
		ifstream myinfile;
		if (FileExists(filepath, myinfile)) {
			//myinfile.open("Horace_Rec_Descriptor.csv");

			int i = 0;
			int fileNum = 0;
			string filename;
			string str;
			string headerstr;
			stringstream basename;
			ofstream outfile;
			basename << filepath << fileNum << ".csv";
			filename = basename.str();

			getline(myinfile, headerstr);
			outfile.open(filename.c_str(), ofstream::binary);
			while (myinfile.good()) {
				if (i == 0) {
					outfile << headerstr << endl;
					i++;
					cout << "We're on file: " << filename.c_str() << endl;
					//cout << "Inserting header row...";
				} else if (i <= lineNumbers) {
					getline(myinfile, str);
					outfile << str << endl;
					i++;
					//cout << "We're on this number i: " << i << endl;
				} else if (i > lineNumbers || myinfile.eof()) {
					outfile.close();
					basename.str("");
					fileNum++;
					i = 0;
					basename << filepath << fileNum << ".csv";
					filename = basename.str();
					outfile.open(filename.c_str(), ofstream::binary);
				}
			}
			outfile.close();
			myinfile.close();

			int c;
			cout << "Press ENTER to exit... ";
			cin >> c;
			do
				c = getchar();
			while (c != EOF);
		}
	}

	return 0;
}

