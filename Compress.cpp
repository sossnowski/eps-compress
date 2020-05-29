#include "Compress.h"
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

/**
 * Main program feature - compress algorithm
 *
 * @param dataToCompress
 */
void Compress::compressData(string* dataToCompress) {
    float x,y;
    string c;
    istringstream f(*dataToCompress);
    while (f >> x >> y >> c) {
        if (c != this->previousC && this->flag) {
            this->coordinates.push_back({ x, y, this->numberOfCurrentLine++});
            this->flag = false;
        } else {
            this->flag = true;
            x += this->previousX;
            y += this->previousY;
            this->coordinates.push_back({ x, y, this->numberOfCurrentLine++});
        }
        this->previousC = c;
        this->previousX = x;
        this->previousY = y;
    }
}

/**
 * Function finding covered coordinates
 */
void Compress::computeCoordinates() {
    this->sortVectorByX(&this->coordinates);

    sort( this->coordinates.begin( ), this->coordinates.end( ), [ ]( const auto& lhs, const auto& rhs ){
        return lhs.y < rhs.y;
    });

    this->generateCoveringXCoords();
    this->generateCoveringYCoords();

    cout << this->coordinates.size() <<endl;
    this->findCommonIndexes();

    cout << this->commonIndexes.size() <<endl;

    // cut common coordinates from coordinates vector
    for (int i = 0; i < this->commonIndexes.size() ; ++i) {
        this->coordinates.erase(this->coordinates.begin() + this->commonIndexes[i] - i);
    }

    cout << this->coordinates.size() <<endl;
}

/**
 * Function sorting vector of Coords struct by key x
 * @param v
 */
void Compress::sortVectorByX(vector<Coords>*(v)) {
    sort( v->begin( ), v->end( ), [ ]( const auto& lhs, const auto& rhs ){
        return lhs.x < rhs.x;
    });
}

/**
 * Function sorting vector of Coords struct by key y
 * @param v
 */
void Compress::sortVectorByY(vector<Coords>*(v)) {
    sort( v->begin( ), v->end( ), [ ]( const auto& lhs, const auto& rhs ){
        return lhs.y < rhs.y;
    });
}

/**
 * Functions generate vector of Coords struct which contains covered x axis points
 */
void Compress::generateCoveringXCoords() {
    float distanceBetweenPoints = 1;
    float tmpCoord = this->coordinates[0].x;
    for (int i = 1; i < this->coordinates.size() ; ++i) {
        if (abs( this->coordinates[i].x - tmpCoord ) < distanceBetweenPoints) {
            this->coverXCoordinates.push_back(i);
        } else {
            tmpCoord = this->coordinates[i].x;
        }
    }
}

/**
 * Functions generate vector of Coords struct which contains covered y axis points
 */
void Compress::generateCoveringYCoords() {
    float distanceBetweenPoints = 1;
    float tmpCoord = this->coordinates[0].y;
    for (int i = 1; i < this->coordinates.size() ; ++i) {
        if (abs( this->coordinates[i].y - tmpCoord ) < distanceBetweenPoints) {
            this->coverYCoordinates.push_back(i);
        } else {
            tmpCoord = this->coordinates[i].y;
        }
    }
}

/**
 * Function finding points which have x and y axis covered
 */
void Compress::findCommonIndexes() {
    for (int i = 0; i < this->coverYCoordinates.size() ; ++i) {
        if (find(this->coverXCoordinates.begin(), this->coverXCoordinates.end(), this->coverYCoordinates[i]) != this->coverXCoordinates.end()) {
            this->commonIndexes.push_back(this->coverYCoordinates[i]);
        }
    }
}

vector<Coords>* Compress::getCoordinates() {
    return &this->coordinates;
}


