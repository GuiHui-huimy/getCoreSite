#include "header.h"

void IndexPage(string& workPath) {
	cout << "Welcome to AOTM Core Site Project!" << endl;
	cout << "This project is used to calculate  core site based on pdb file data." << endl;
	setWorkPath(workPath);
	return;
	
}
void setWorkPath(string& workPath) {

Reset:
	cout << "-------------------------------------" << endl;
	cout << "Please set workpath to AOTM Core Site project." << endl;
	cout << "WorkPath dir : ";
	cin >> workPath;
	if (!workPath.empty()) {
		return;
	}
	else {
		cout << "None workpath dir !\n";
		goto Reset;
	}

}
void chosePdbAnalysis(string& workPath ,string& fullPdbPath) {
	string pdbFileName = "";
	fullPdbPath = "";
	cout << "-------------------------------------" << endl;
	cout << "Chose PDB file analysis from workPath: " << workPath << endl;
	Reinput_pdbname:
	cout << "Please input you .pdb file name. Just like : model_1.pdb " << endl;
	cout << "File name : ";
	cin >> pdbFileName;
	if (!pdbFileName.empty()) {
		fullPdbPath = workPath + "\\" + pdbFileName;
		return ;
	}
	else {
		cout << "None pdb file name !\n";
		goto Reinput_pdbname;
	}

}
void choseList(string& workPath) {
	string fullPdbPath = "";
	int choice = 0;
	Reinput_choice:
	cout << "-------------------------------------" << endl;
	cout << "Reading PDB file workpath: " << workPath << endl;
	cout << "Please chose Action you want to do.\n" << endl;
	cout << "**********************************" << endl;
	cout << "1.Reset workPath" << endl;
	cout << "2.Analysis pdb file from workPath" << endl;
	cout << "**********************************\n" << endl;
	cout << "Enter choice:";
	cin >> choice;
	if (choice == 1 || choice == 2) {
		switch (choice) {
		case 1:
			setWorkPath(workPath);
			break;
		case 2:
			chosePdbAnalysis(workPath,fullPdbPath);
			readLinesFromPdb(fullPdbPath);
			break;
		}
		return;
	}
	else {
		cout << "Invalid choice ! Please chose again.\n";
		goto Reinput_choice;
	}
}