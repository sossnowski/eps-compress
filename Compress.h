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
    vector<Coords>coverCoordinates;
    long int numberOfCurrentLine;
    float previousX;
    float previousY;
    string previousC;
    bool flag;
    bool absoluteCoordinates;
    float distanceBetweenPoints;
    float width;
    float originalWidth;
    float scale;
public:
    Compress() : numberOfCurrentLine(0), previousX(0), previousY(0), previousC(""), flag(true),
                distanceBetweenPoints(1), absoluteCoordinates(false), width(0) {};
    ~Compress() {};
    vector<Coords>* getNewCoordinates();
    bool getAbsoluteCoordinatesFlag();
    void setImageDimension(int width);
    void setOriginalImageWidth(int width);
    void setScale();
    void getCoordinatesFromFileData(string* dataToCompress);
    float getScale();
    void findCoverCoordinates();
    void sortVectorByX(vector<Coords>*v);
    void sortVectorByY(vector<Coords>*v);
    void sortVectorByPosition(vector<Coords>*v);
    void generateCoveringCoords();
    vector<Coords> findCoverYCoordinates(vector<Coords> v, Coords referencePoint);
    void setFinalCoordinates();
    float roundToTwoDecimal(float val);
    Coords getAbsoluteCoords(long int index);
    void scaleImage();
};


#endif //EPSCOMPRESS_COMPRESS_H
