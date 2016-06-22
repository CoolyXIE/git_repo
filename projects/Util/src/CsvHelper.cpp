#include <CsvHelper.h>

CsvHelper::CsvHelper(const char *filePath){
    assert(loadCSV(filePath));
}

CsvHelper::~CsvHelper(){
}

map<u32, map<u32, string>>& CsvHelper::getCSVMap(){
    return m_stringMap;
}

//用于分割字符串，将CSV表格中的一行按照规则解析成一组字符串，存储在一个vector中
int CsvHelper::parseLineToVec(string str, vector<string> &stringVec){
    char delim = ',';
    char *token = strtok(const_cast<char *>(str.c_str()), &delim);
    while (token)
    {
        string strTemp = token;
        stringVec.push_back(strTemp);
        token = strtok(NULL, &delim);
    }

    return stringVec.size();
}

bool CsvHelper::loadCSV(const char *path){
    FILE *pFile = fopen(path, "r");
    if (pFile)
    {
        fseek(pFile, 0, SEEK_END);
        u32 uSize = ftell(pFile);
        rewind(pFile);

        char *fileBuffer = new char[uSize];
        fread(fileBuffer, 1, uSize, pFile);

        map<u32, string> stringMap;
        u32 uiIndex = 1;
        char *pBegin = fileBuffer;
        char *pEnd = strchr(pBegin, '\n');


        pBegin = pEnd + 1;
        pEnd = strchr(pBegin, '\n');

        while (pEnd)
        {
            string strTemp;
            strTemp.insert(0, pBegin, pEnd-pBegin);
            assert(!strTemp.empty());
            stringMap[uiIndex++] = strTemp;
            pBegin = pEnd + 1;
            pEnd = strchr(pBegin, '\n');
        }
        delete []fileBuffer;
        fileBuffer = NULL;
        pBegin = NULL;
        pEnd = NULL;

        map<u32, string>::iterator iter = stringMap.begin();
        for (; iter != stringMap.end(); ++iter)
        {
            vector<string> stringVec;
            map<u32, string> stringMapTemp;
            assert(parseLineToVec(iter->second, stringVec) > 0);

            vector<string>::size_type idx = 0;
            for (; idx != stringVec.size(); ++idx)
            {
                stringMapTemp[idx + 1] = stringVec[idx];
            }

            m_stringMap[iter->first] = stringMapTemp;
        }

        fclose(pFile);
        m_CSVName = path;
        return true;
    }
    else
    {
        return false;
    }
}

string* CsvHelper::getStringValue(u32 uiRow, u32 uiCol){
    map<u32, map<u32, string>>::iterator iter = m_stringMap.find(uiRow);
    if (iter != m_stringMap.end())
    {
        map<u32, string> &rStrMap = iter->second;
        map<u32, string>::iterator it = rStrMap.find(uiCol);
        if (it != rStrMap.end())
        {
            return &(it->second);
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

void CsvHelper::getVecFromLine(int lineNum, vector<string>& stringVec){
    map<u32, string> lineMap = m_stringMap[lineNum];
    map<u32, string>::iterator it;
    for(it = lineMap.begin(); it != lineMap.end(); ++it)
        stringVec.push_back(it->second);
}

