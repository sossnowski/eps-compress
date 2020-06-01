#include "Compress.h"
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

/**
 * Function get coordinates from input file data
 *
 * @param dataToCompress
 */
void Compress::getCoordinatesFromFileData(string* dataToCompress) {
    float x,y;
    string line, c;
    istringstream f(*dataToCompress);
    while (getline(f, line)) {
        istringstream iss(line);
        iss >> x >> y >> c;
        this->oldCoordinates.push_back({ x, y, this->numberOfCurrentLine});

        // Check if coordinates are given as relative or absolute and add to vector
        if (c != this->previousC && this->flag) {
            this->coordinates.push_back({ x, y, this->numberOfCurrentLine++});
            this->flag = false;
        } else if (c == this->previousC && !this->flag) {
            this->coordinates.push_back({ x, y, this->numberOfCurrentLine++});
            this->absoluteCoordinates = true;
        } else {
            this->flag = true;
            x += this->previousX;
            y += this->previousY;
            this->coordinates.push_back({ x, y, this->numberOfCurrentLine++});
            this->absoluteCoordinates = false;
        }
        this->previousC = c;
        this->previousX = x;
        this->previousY = y;
    }
}

/**
 * Function find covered coordinates
 */
void Compress::findCoverCoordinates() {

    this->sortVectorByX(&this->coordinates);

    // Resize coordinates to output image size
    if (this->width) this->scaleImage();

    this->generateCoveringCoords();

    cout << "Usunięto " << this->coverCoordinates.size() << " z " << this->coordinates.size() << " punktów" <<endl;

    this->sortVectorByPosition(&this->coverCoordinates);
    this->sortVectorByPosition(&this->coordinates);

    // Cut common coordinates from coordinates vector
    for (int i = 0; i < this->coverCoordinates.size() ; ++i) {
        this->coordinates.erase(this->coordinates.begin() + this->coverCoordinates[i].position - i);
    }

    // If coordinates were relative extract it from absolute
    if (!this->absoluteCoordinates) {
        this->setFinalCoordinates();
    } else {
        this->newCoordinates = this->coordinates;
    }
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
 * Function sorting vector of Coords struct by key y
 * @param v
 */
void Compress::sortVectorByPosition(vector<Coords>*(v)) {
    sort( v->begin( ), v->end( ), [ ]( const auto& lhs, const auto& rhs ){
        return lhs.position < rhs.position;
    });
}

/**
 * Functions generate vector of Coords struct which contains covered x axis points
 */
void Compress::generateCoveringCoords() {
    Coords tmpCoords;
    vector<Coords>x, v;
    int j = 0;
    for (int i = 0; i < this->coordinates.size() - 1 ; ++i) {
        // Check if this coordinate was not added to cover array before
        if (find(this->coverCoordinates.begin(), this->coverCoordinates.end(), this->coordinates[i]) != this->coverCoordinates.end()) continue;
        tmpCoords = this->coordinates[i];
        // Get all coordinates which are not further than this->distanceBetweenPoints(default 1) from reference coords in this iteration
        while (this->coordinates[i + 1 + j].x - tmpCoords.x <= this->distanceBetweenPoints) {
            if (i + 1 + j >= this->coordinates.size()) break;
            x.push_back(this->coordinates[i + 1 + j]);
            j++;
        }
        if (x.size()) {
            v = this->findCoverYCoordinates(x, tmpCoords);
            this->coverCoordinates.insert(this->coverCoordinates.end(), v.begin(), v.end());
            x.clear();
        }
        j = 0;
    }

}

/**
 * Get new coordinates
 *
 * @return this->newCoordinates
 */
vector<Coords>* Compress::getNewCoordinates() {
    return &this->newCoordinates;
}

/**
 * Get absolute coordinates flag
 *
 * @return this->absoluteCoordinates
 */
bool Compress::getAbsoluteCoordinatesFlag() {
    return this->absoluteCoordinates;
}

/**
 * Set coords as relative again
 */
void Compress::setFinalCoordinates() {
    this->newCoordinates.push_back(this->coordinates[0]);
    for (int i = 1; i < this->coordinates.size(); ++i) {
        this->newCoordinates.push_back({
           this->roundToTwoDecimal(this->coordinates[i].x - this->coordinates[i - 1].x),
           this->roundToTwoDecimal(this->coordinates[i].y - this->coordinates[i - 1].y),
           this->coordinates[i].position
        });
    }
}

/**
 * Function round float to two decimal places
 *
 * @param val
 * @return
 */
float Compress::roundToTwoDecimal(float val) {
    return nearbyint(val * 100) / 100;
}

/**
 * Function compute absolute value of point when index given
 *
 * @param index
 * @return
 */
Coords Compress::getAbsoluteCoords(long int index) {
    Coords c;
    c.x = 0, c.y = 0;
    for (int i = 0; i <= index; ++i) {
        c.x += this->newCoordinates[i].x;
        c.y += this->newCoordinates[i].y;
    }
    return c;
}

vector<Coords> Compress::findCoverYCoordinates(vector<Coords> v, Coords refPoint) {
    vector<Coords>coords;
    this->sortVectorByY(&v);
    for (int i = 0; i < v.size() ; ++i) {
        // If y distance is also less than 1 from reference axis add this point to cover array
        if (abs(v[i].y - refPoint.y) <= this->distanceBetweenPoints) {
            if (find(this->coverCoordinates.begin(), this->coverCoordinates.end(), v[i]) != this->coverCoordinates.end() != true) coords.push_back(v[i]);
        }
    }
    return coords;
}

/**
 * Comparison operator for Coords structure
 *
 * @param rhs
 * @param lhs
 * @return
 */
bool operator==(const Coords& rhs, const Coords& lhs) {
    return rhs.position == lhs.position;
}

/*
 * Set image width
 */
void Compress::setImageDimension(int width) {
    this->width = width;
}

/**
 * Scale all coordinates of image
 */
void Compress::scaleImage() {
    for (int i = 0; i < this->coordinates.size() ; ++i) {
        this->coordinates[i].x *= this->width / this->originalWidth;
        this->coordinates[i].y *= this->width / this->originalWidth;
    }
}

/**
 * Set original image width
 * @param width
 */
void Compress::setOriginalImageWidth(int width) {
    this->originalWidth = width;
}

/**
 * Get scale to resize
 * @return scale
 */
float Compress::getScale() {
    return this->width / this->originalWidth;
}


