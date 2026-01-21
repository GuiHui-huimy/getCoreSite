#include "header.h"
void readLinesFromPdb(string fileDir) {
	//initialize variables
	int i;
	std::vector<double> x(0);
	std::vector<double> y(0);
	std::vector<double> z(0);
	std::vector<string> atomType;
	int atomNum = 1;
	std::vector<double> coreSite(4);
	string inputLines;
	vector<string> Lines;
	bool isHaveThisMol = false;
	vector <string> recLigands;
	vector <int> recLigandseries;
	//input pdb HETATM lines
	/*cout << "Please input lines pdb HETATM lines";*/
	//while (getline(cin, inputLines)) {
	//	if (inputLines.empty()) break; 
	//	Lines.push_back(inputLines);
	//}

	/*cout << "Please input pdb file directory:\n";
	string fileDir;
	cin >> fileDir;*/
	int stut = getPdbData(fileDir, Lines);
	rsize_t lineNum = Lines.size();
	if (stut == SUCCESS) {
		cout << "-------------------------------------" << endl;
		cout << "Read " << Lines.size() << "lines form pdb file" << fileDir << endl;
		// Resize vectors to hold atom information
		x.resize(lineNum + 1);
		y.resize(lineNum + 1);
		z.resize(lineNum + 1);
		atomType.resize(lineNum + 1);
		recogLigand(lineNum, Lines, recLigands,recLigandseries);
		if (!recLigands.empty()&&!recLigandseries.empty()) {
			if (recLigands.size() == recLigandseries.size()) {
				cout << "**********************************" << endl;
				cout << "Recognized Ligand Molecules in PDB file:" << endl;
				for (size_t i = 0; i < recLigands.size(); i++)
				{
					cout << "Ligand Name   Serial Number"<<"\n" << endl;
					cout << recLigands[i] << "           " << recLigandseries[i] <<"\n" << endl;
					cout << "**********************************" << endl;
				}
			
			}
			else
			{
				 cerr<< "Fail recognizing Ligand Molecules in PDB file." << endl;
			}
		
		}
		else {
			cout << "No Ligand Molecules recognized in PDB file." << endl;
		}
	}
	else
	{
		cout << "Unable to open pdb file from " << fileDir << endl;
		return ;
	}
	
	cout << "Please input ligand molecule name:";
	string ligandName;
	cin >> ligandName;
	if (ligandName.empty()) {
		cout << "Ligand name can't empty\n";
		return;
	}
	cout << "Please input ligand molecule  serial Number:";
	int serialNum = 0;
	cin >> serialNum;
	if (serialNum == 0) {
		cout << "Ligand name can't empty\n";
		return;
	}

	// Loop to get atom information
	for (i = 1; i <= lineNum; i++) {
		cout << "Read line - " << i << "Info " << endl;
		AtomInfo atomInfos;
		if (Lines[i - 1] == "END") { 
		cout << "END\n"; break;
		}
		if (Lines[i - 1] == "TER") {
			cout << "TER:Chain End Symbol\n"; break;
		}
		if (extractSingleLine(Lines[i-1], atomInfos)) {
			if (isNeedMol(ligandName, serialNum, atomInfos)==true) {
				
				cout << "Ligand Atom Type: " << atomInfos.type << ", Coordinates: (" << atomInfos.x << ", " << atomInfos.y << ", " << atomInfos.z << ")" << endl;
				x[atomNum] = atomInfos.x;
				y[atomNum] = atomInfos.y;
				z[atomNum] = atomInfos.z;
				atomType[atomNum] = atomInfos.type;
				isHaveThisMol = true;
				atomNum++;
			}
		}
		else {
			cerr << "Error: Invalid atom information format." <<"Error in line " << i<< "\n" << endl;
		}

	}
	if (isHaveThisMol == false) {
		cerr << "Can't find this ligand Molecule:" << ligandName << "\n" << endl;
		return;
	}
	// Calculate core site
	atomType.resize(atomNum + 1);
	x.resize(atomNum + 1);
	y.resize(atomNum + 1);
	z.resize(atomNum + 1);
	coreSite = rWeightedSiteCalc(atomNum, atomType, x, y, z);
	cout << "Core Site Coordinates: (" << coreSite[0] << ", " << coreSite[1] << ", " << coreSite[2] << "," << coreSite[3] << ")" << endl;
	cout << fixed << setprecision(3) << "HETATM   33  COR MIX     1       " << coreSite[1] << "   " << coreSite[2] << "  " << coreSite[3] << " - TestPdbLine" << endl;
	cout << "Welcome to the AOTM Core Site Next!" << endl;
	//D:\Users\sgh18\Desktop\model_1.pdb
}

void recogLigand(int lineNum, vector<string> Lines, vector <string>& recLigands ,vector<int>& recLigandseries) {
	int i = 1;
	
	for (i = 1; i <= lineNum; i++) {
		AtomInfo atomInfos;
		if (Lines[i - 1] == "END") {
			break;
		}
		if (Lines[i - 1] == "TER") {
			break;
		}
		if (extractSingleLine(Lines[i - 1], atomInfos)) {
			if (atomInfos.recordName == "HETATM") {
				if (std::find(recLigands.begin(), recLigands.end(), atomInfos.moleculeName) != recLigands.end()) {
					break;
				}
				else {
					recLigands.push_back(atomInfos.moleculeName);
					recLigandseries.push_back(atomInfos.moleculeSerial);

				}
			}
		}
		else {
			cerr << "Error: Invalid atom information format." << "Error in line " << i << "\n" << endl;
		}

	}
	return ;
}
