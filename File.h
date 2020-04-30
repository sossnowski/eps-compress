#include <string>
#include <fstream>

#ifndef EPSCOMPRESS_FILE_H
#define EPSCOMPRESS_FILE_H

using namespace std;


class File {
private:
    string inFileName;
    string outFileName;
    string filePath;

public:
    File() {};
    File(string filePath);
    ~File() {};
    void processData();
    string getFileNameFromPath(string filePath);
    string getInFileName();
    string getOutFileName();
};


#endif //EPSCOMPRESS_FILE_H
