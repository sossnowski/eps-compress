#include <string>
#include <fstream>

#ifndef EPSCOMPRESS_FILE_H
#define EPSCOMPRESS_FILE_H

using namespace std;


class File {
private:
    string inFileName;
    string outFileName;
    fstream inputFile;
    fstream outputFile;

public:
    File();
    ~File();
    void openInputFile();
    void createOutputFile();
    void processData();
};


#endif //EPSCOMPRESS_FILE_H
