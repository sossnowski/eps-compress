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
    int linesSavedBeforeCompute;

public:
    File() : linesSavedBeforeCompute(0), beginningSaved(false) {};
    File(string filePath);
    ~File() {};
    void processData();
    string getFileNameFromPath(string filePath);
    string getInFileName();
    string getOutFileName();
    void saveToOutputFile(string* line);
    void findEssentialLines(Compress* c, string filePath);
    fstream& gotoLine(fstream& file, long int num);
};


#endif //EPSCOMPRESS_FILE_H
