#ifndef CSVHELPER_H
#define CSVHELPER_H
#include <assert.h>
#include <map>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;
typedef unsigned long  u32;

class CsvHelper{
private:
	map<u32, map<u32, string>> stringMap;
	string m_CSVName;
public:
    //constructor
	CsvHelper(){};
	CsvHelper(const char *filePath);
	~CsvHelper(){};

	bool loadCSV(const char *filePath);//to-do
	bool saveCSV(const char *filePath = NULL); //to-do

	//get
	map<u32, map<u32, string>>& getCSVMap();

    //unit
    string* getStringValue(u32 row, u32 col);

	int parseLineToVec(string line, vector<string> &stringVec, char delim = ',');
    void getVecAtLine(int lineNum, vector<string>& stringVec);

//	int getParamFromString(string str, vector<string> &stringVec, char delim  = ',');
//	void getSkillRecordMapTable(map<int, SkillRecord> &sSkillMapTable);
};
#endif // CSVHELPER_H
