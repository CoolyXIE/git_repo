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
	map<u32, map<u32, string>> m_stringMap;
	string m_CSVName;
public:

	CsvHelper();
	CsvHelper(const char *filePath);
	~CsvHelper();

	bool loadCSV(const char *filePath);
	bool saveCSV(const char *filePath = NULL);

    string* getStringValue(u32 uiRow, u32 uiCol);
	map<u32, map<u32, string>>& getCSVMap();

	int parseLineToVec(string str, vector<string> &stringVec);

    void getVecFromLine(int lineNum, vector<string>& stringVec);



//	bool getIntValue(U32 uiRow, U32 uiCol, int &riValue);
//	bool getFloatValue(U32 uiRow, U32 uiCol, float &rfValue);



//	int getParamFromString(string str, vector<string> &stringVec, char delim  = ',');

//	void getSkillRecordMapTable(map<int, SkillRecord> &sSkillMapTable);
};

#endif // CSVHELPER_H
