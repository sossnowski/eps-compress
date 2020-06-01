#include <string>
#include <fstream>
#include "Compress.h"

#ifndef EPSCOMPRESS_FILE_H
#define EPSCOMPRESS_FILE_H

using namespace std;


class File {
private:
    string inFileName;
    string outFileName;
    string filePath;
    string beginningOfFile;
    string endOfFile;
    bool beginningSaved;
    bool saveFlag;
    int linesSavedBeforeCompute;

public:
    File() : linesSavedBeforeCompute(0), beginningSaved(false), saveFlag(true) {};
    File(string filePath);
    ~File() {};
    void processData(int width);
    string getFileNameFromPath(string filePath);
    string getInFileName();
    string getOutFileName();
    void saveToOutputFile(string* line);
    void findEssentialLines(Compress* c, string filePath);
};


#endif //EPSCOMPRESS_FILE_H
