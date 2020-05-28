#include <iostream>
#include <vector>
#include "Coords.h"
#ifndef EPSCOMPRESS_COMPRESS_H
#define EPSCOMPRESS_COMPRESS_H

using namespace std;


class Compress {
private:
    vector<Coords>oldCoordinates;
    vector<long int>coverXCoordinates;
    vector<long int>coverYCoordinates;
    long int numberOfCurrentLine;
    float previousX;
    float previousY;
    string previousC;
    bool flag;
public:
    Compress() : numberOfCurrentLine(0), previousX(0), previousY(0), previousC(""), flag(true) {};
    ~Compress() {};
    void compressData(string* dataToCompress);
    void computeCoordinates();
};


#endif //EPSCOMPRESS_COMPRESS_H
