// The code is part of a project that deals with atomic structures and calculations related to atomic sites.
// header.h
#ifndef HEADER_H
#define HEADER_H
#define ERROR 0
#define SUCCESS 1
//Include files
#include <iostream> 
#include <vector>
#include <regex>
#include <map>
#include <sstream>
#include <string>
#include <set>
#include <iomanip> 
#include <fstream>
using namespace std;

// Structure to hold atom information
struct AtomInfo {
	string recordName;
	string moleculeName;
	int moleculeSerial;
	string atomName; // 原子名称（如CA、N、O）
	string type;     // 原子类型（如C、O、N）
	double x, y, z; // 坐标
	
	AtomInfo() : recordName(""), moleculeName(""), moleculeSerial(0),
		atomName(""), type(""), x(0.0), y(0.0), z(0.0) {
	}
};

// Function declarations
bool initArrayDect(int atomNum, std::vector<string> atomType, std::vector<double> x, std::vector<double> y, std::vector<double> z);
double getAtomicRadius(string atomType);
bool extractSingleLine(const string& line, struct AtomInfo& info);
std::vector<double> rWeightedSiteCalc(int atomNum, std::vector<string> atomType, std::vector<double> x, std::vector<double> y, std::vector<double> z);
string extractElementFromAtomName(const string& atomName);
string smartElementExtraction(const string& atomName);
vector<string> getLinesfromMutiString(const string& pdbData);
void readLinesFromPdb(string fileDir);
void readLineOnly(void);
int getPdbData(string fileDir, vector<string>& pdbLines);
bool isNeedMol(string ligandName, int ligandSer, AtomInfo infos);

void IndexPage(string &workPath);
void setWorkPath(string& workPath);
void chosePdbAnalysis(string& workPath, string& fullPdbPath);
void choseList(string& workPath);
void recogLigand(int lineNum, vector<string> Lines, vector <string>& recLigands, vector<int>& recLigandseries);
//Define constants
const set<string> VALID_ELEMENTS = {
	"H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne",
	"Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar", "K", "Ca",
	"Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn",
	"Ga", "Ge", "As", "Se", "Br", "Kr", "I", "Pt", "Au", "Ag"
};
//Map we need special end set !!
const map<string,string> KNOW_NOMEAN_R = {
	{"MIX","NOMEAN"}
};
static const map<string, double>	RADUIS_TABLE = {
	{"H", 1.20}, {"C", 1.70}, {"N", 1.55}, {"O", 1.52},
	{"F", 1.47}, {"S", 1.80}, {"Cl", 1.75}, {"P", 1.80},
	{"Br", 1.85}, {"I", 1.98}, {"Fe", 1.40}, {"Zn", 1.39},
	{"Cu", 1.40}, {"Mg", 1.73}, {"Ca", 2.31}, {"Na", 2.27},
	{"K", 2.75},{"NOMEAN",1.00}
	};




#endif // HEADER_H