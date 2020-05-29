#include <iostream>
#include <vector>
#include "Coords.h"
#ifndef EPSCOMPRESS_COMPRESS_H
#define EPSCOMPRESS_COMPRESS_H

using namespace std;


class Compress {
private:
    vector<Coords>coordinates;
    vector<Coords>newCoordinates;
    vector<Coords>oldCoordinates;
    vector<long int>coverXCoordinates;
    vector<long int>coverYCoordinates;
    vector<long int>commonIndexes;
    long int numberOfCurrentLine;
    float previousX;
    float previousY;
    string previousC;
    bool flag;
public:
    Compress() : numberOfCurrentLine(0), previousX(0), previousY(0), previousC(""), flag(true) {};
    ~Compress() {};
    vector<Coords>* getNewCoordinates();
    void compressData(string* dataToCompress);
    void computeCoordinates();
    void sortVectorByX(vector<Coords>*v);
    void sortVectorByY(vector<Coords>*(v));
    void generateCoveringXCoords();
    void generateCoveringYCoords();
    void findCommonIndexes();
    void setFinalCoordinates();
    float roundToTwoDecimal(float val);
};


#endif //EPSCOMPRESS_COMPRESS_H
