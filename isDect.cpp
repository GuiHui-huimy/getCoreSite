#include "header.h"
//Is array size equal to atomNum
bool initArrayDect(int atomNum, std::vector<string> atomType, std::vector<double> x, std::vector<double> y, std::vector<double> z) {
	size_t xArraySize = x.size();
	size_t yArraySize = y.size();
	size_t zArraySize = z.size();
	size_t atomTypeSize = atomType.size();
	int atomNumReal = atomNum + 1;
	if (atomNumReal == xArraySize && atomNumReal == yArraySize && atomNumReal == zArraySize  && atomNumReal == atomTypeSize) {
		return true;
	}
	else {
		return false;
	}
}
bool isNeedMol(string ligandName,int ligandSer,AtomInfo infos) {
	if (infos.moleculeSerial == ligandSer && infos.moleculeName == ligandName) {
		return true;
	}
	else {
		return false;
	}
}