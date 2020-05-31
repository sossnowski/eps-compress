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
    bool absoluteCoordinates;
    float distanceBetweenPoints;
public:
    Compress() : numberOfCurrentLine(0), previousX(0), previousY(0), previousC(""), flag(true), distanceBetweenPoints(1), absoluteCoordinates(false) {};
    ~Compress() {};
    vector<Coords>* getNewCoordinates();
    bool getAbsoluteCoordinatesFlag();
    void getCoordinatesFromFileData(string* dataToCompress);
    void findCoverCoordinates();
    void sortVectorByX(vector<Coords>*v);
    void sortVectorByY(vector<Coords>*v);
    void sortVectorByPosition(vector<Coords>*v);
    void generateCoveringXCoords();
    void generateCoveringYCoords();
    void findCommonIndexes();
    void setFinalCoordinates();
    float roundToTwoDecimal(float val);
    Coords getAbsoluteCoords(long int index);
    float distance(int x1, int y1, int x2, int y2);
};


#endif //EPSCOMPRESS_COMPRESS_H
