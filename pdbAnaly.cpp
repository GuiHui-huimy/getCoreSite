#include "header.h"
/*
bool extractSingleLine(const string& line, AtomInfo& info) {
	regex pattern(R"(^HETATM\s+\d+\s+([A-Za-z0-9]+)\s+\w+\s+\d+\s+(\S+)\s+(\S+)\s+(\S+).*$)");
	smatch matchResult;
	if (!regex_match(line, matchResult, pattern)) {
		return false; // 格式不匹配
	}
	try {
		info.type = matchResult[1].str()[0];  // 原子类型（首字符）
		info.x = stod(matchResult[2].str());  // x坐标
		info.y = stod(matchResult[3].str());  // y坐标
		info.z = stod(matchResult[4].str());  // z坐标
		return true;
	}
	catch (const exception&) {
		return false;
	}
}
*/
int getPdbData(string fileDir, vector<string>& pdbLines) {
    std::ifstream pdbFile(fileDir);
    if (pdbFile.is_open()) {
        string line;
        while (std::getline(pdbFile, line))
        {
            pdbLines.push_back(line);
        }
        return SUCCESS;
    }
    else {
        return ERROR;

    }

}
vector<string> getLinesfromMutiString(const string& pdbData) {
    vector<string> lines;
    string line;
    istringstream stream(pdbData);
    int i = 1;
    while (getline(stream,line)) {
        lines[i] = line;
        i++;
    }
    cout << "-------------------------------------" << endl;
    cout << "Read " << lines.size() << " lines from string data." << endl;
    return lines;
}



bool extractSingleLine(const string& line, AtomInfo& info) {
    //Detect line lenth
    if (line.length() < 54) {
        cerr << "Line too short: " << line << endl;
        return false;
    }

    try {
        // Get infomation from pdb line with standerd pdb form
        string recordName = line.substr(0, 6);
        string atomSerial = line.substr(6, 5);
        string atomName = line.substr(12, 4);  // 原子名称
        string resName = line.substr(17, 3);   // 残基名称
        string chainId = line.substr(21, 1);   // 链ID
        string resSeq = line.substr(22, 4);    // 残基序号
        string xStr = line.substr(30, 8);      // X坐标
        string yStr = line.substr(38, 8);      // Y坐标
        string zStr = line.substr(46, 8);      // Z坐标

        // Delet "" NONE
        auto trim = [](string str) {
            str.erase(0, str.find_first_not_of(" \t"));
            str.erase(str.find_last_not_of(" \t") + 1);
            return str;
            };

        recordName = trim(recordName);
        atomName = trim(atomName);
        xStr = trim(xStr);
        yStr = trim(yStr);
        zStr = trim(zStr);
        resName = trim(resName);
        // Dect record name
        if (recordName != "HETATM" && recordName != "ATOM") {
            return false;
        }
        //Get recordName
		info.recordName = recordName;
        //Get moleculeInfo
        info.moleculeName = resName;
        info.moleculeSerial = std::stoi(resSeq);
        
        // Get atomType
        info.atomName = atomName;
        auto it = KNOW_NOMEAN_R.find(resName);
        if (it != KNOW_NOMEAN_R.end())
        {
            info.type = it->second;
        }
        else
        {
            info.type = extractElementFromAtomName(atomName);
        }
        // Get x,y,z
        info.x = stod(xStr);
        info.y = stod(yStr);
        info.z = stod(zStr);
        return true;
    }
    catch (const exception& e) {
        cerr << "Error parsing line: " << e.what() << endl;
        return false;
    }
}

string extractElementFromAtomName(const string& atomName) {
    if (atomName.empty()) return "C"; // 默认值

    // 方法1: 直接取前两个字符检查是否为已知元素
    if (atomName.length() >= 2) {
        string twoChar = atomName.substr(0, 2);
        // 标准化：首字母大写，第二个字母小写
        twoChar[0] = toupper(twoChar[0]);
        if (twoChar.length() > 1) {
            twoChar[1] = tolower(twoChar[1]);
        }

        if (VALID_ELEMENTS.find(twoChar) != VALID_ELEMENTS.end()) {
            return twoChar;
        }
    }

    // 方法2: 取第一个字符
    string oneChar = string(1, toupper(atomName[0]));
    if (VALID_ELEMENTS.find(oneChar) != VALID_ELEMENTS.end()) {
        return oneChar;
    }

    // 方法3: 智能提取 - 处理特殊情况
    return smartElementExtraction(atomName);
}

string smartElementExtraction(const string& atomName) {
    // 处理常见的特殊情况
    string name = atomName;

    // 去除数字
    name.erase(remove_if(name.begin(), name.end(), ::isdigit), name.end());

    if (name.empty()) return "C";

    // 检查是否为双字母元素
    if (name.length() >= 2) {
        string candidate = name.substr(0, 2);
        candidate[0] = toupper(candidate[0]);
        candidate[1] = tolower(candidate[1]);

        if (VALID_ELEMENTS.find(candidate) != VALID_ELEMENTS.end()) {
            return candidate;
        }
    }

    // 检查单字母元素
    char firstChar = toupper(name[0]);
    string singleChar(1, firstChar);

    if (VALID_ELEMENTS.find(singleChar) != VALID_ELEMENTS.end()) {
        return singleChar;
    }

    // 基于常见命名模式推断
    if (name.find("CL") == 0 || name.find("Cl") == 0 || name.find("cl") == 0) {
        return "Cl";
    }
    if (name.find("BR") == 0 || name.find("Br") == 0 || name.find("br") == 0) {
        return "Br";
    }
    if (name.find("FE") == 0 || name.find("Fe") == 0 || name.find("fe") == 0) {
        return "Fe";
    }

    // 默认返回碳
    return "C";
}


double getAtomicRadius(string atomType) {

	auto it = RADUIS_TABLE.find( atomType);
	if (it != RADUIS_TABLE.end()) {
		return it->second;
	}
	else {
		return 1.50; // 默认值
	}

}