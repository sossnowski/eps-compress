#include "Compress.h"
#include <sstream>
#include <algorithm>
#include <cmath>

// trzeba przepisyac wszystkie spolrzedne na bezwzgledne wtedy trzeba wziac tylko te odpowiednio od siebie oddalone, a nastepnie przerobic je na wzgldne.
// bo jak wezme oryginalne na indeksach z wartosci bezwzglednych to po prostu biore tylko 200 z 2000 a wiec finalnie rysunek jest znacznie krotszy mimo ze te wartosci
// sa bardzo male, trzeva z bezwzglednych wydzielic wzgledne na zasadzie ze oblicze po prostu aktulna - poprzednia i mam wartosc bezwzgledna jaka trzeba dodac.
// pozostaje rozkminic tylko jak radzic sibie z tym ze niektopre sa bezwzgledne a wiec napis sie rozni ||||chyba juz

// zaokraghlic cyfry w pliku

using namespace std;

/**
 * Function get coordinates from input file data
 *
 * @param dataToCompress
 */
void Compress::getCoordinatesFromFileData(string* dataToCompress) {
    float x,y;
    string c;
    istringstream f(*dataToCompress);
    while (f >> x >> y >> c) {
        this->oldCoordinates.push_back({ x, y, this->numberOfCurrentLine});
        // Check if coordinates are given as relative or absolute and add to vector
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
 * Function find covered coordinates
 */
void Compress::findCoverCoordinates() {
    // Sort and choose cover x coordinates
    this->sortVectorByX(&this->coordinates);
    this->generateCoveringXCoords();

    // Sort and choose cover y coordinates
    this->sortVectorByY(&this->coordinates);
    this->generateCoveringYCoords();

    this->findCommonIndexes();

    // Cut common coordinates from coordinates vector
    for (int i = 0; i < this->commonIndexes.size() ; ++i) {
        this->coordinates.erase(this->coordinates.begin() + this->commonIndexes[i] - i);
    }

    this->setFinalCoordinates();
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
    float tmpCoord = this->coordinates[0].x;
    for (int i = 1; i < this->coordinates.size() ; ++i) {
        if (abs( this->coordinates[i].x - tmpCoord ) < this->distanceBetweenPoints) {
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
    float tmpCoord = this->coordinates[0].y;
    for (int i = 1; i < this->coordinates.size() ; ++i) {
        if (abs( this->coordinates[i].y - tmpCoord ) < this->distanceBetweenPoints) {
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

/**
 * Get new coordinates
 *
 * @return this->newCoordinates
 */
vector<Coords>* Compress::getNewCoordinates() {
    return &this->newCoordinates;
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


