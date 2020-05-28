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
        this->numberOfCurrentLine++;
        if (c != this->previousC && this->flag) {
            this->oldCoordinates.push_back({ x, y, this->numberOfCurrentLine});
            this->flag = false;
        } else {
            this->flag = true;
            x += this->previousX;
            y += this->previousY;
            this->oldCoordinates.push_back({ x, y, this->numberOfCurrentLine});
        }
        this->previousC = c;
        this->previousX = x;
        this->previousY = y;
    }
}


void Compress::computeCoordinates() {
    cout << "siema" <<endl;
    sort( this->oldCoordinates.begin( ), this->oldCoordinates.end( ), [ ]( const auto& lhs, const auto& rhs ){
        return lhs.x < rhs.x;
    });

    for (int i = 0; i < this->oldCoordinates.size() ; ++i) {
        cout << this->oldCoordinates[i].x <<endl;
    }

    float tmpCoord = this->oldCoordinates[0].x;
    for (int i = 1; i < this->oldCoordinates.size() - 1 ; ++i) {
        if (abs( this->oldCoordinates[i].x - tmpCoord ) < 1) {
            this->coverXCoordinates.push_back(this->oldCoordinates[i + 1].position);
        } else {
            tmpCoord = this->oldCoordinates[i].x;
        }
    }

    sort( this->oldCoordinates.begin( ), this->oldCoordinates.end( ), [ ]( const auto& lhs, const auto& rhs ){
        return lhs.y < rhs.y;
    });

    tmpCoord = this->oldCoordinates[0].y;
    for (int i = 1; i < this->oldCoordinates.size() - 1 ; ++i) {
        if (abs(this->oldCoordinates[i].y - tmpCoord ) < 1) {
            this->coverYCoordinates.push_back(this->oldCoordinates[i + 1].position);
        } else {
            tmpCoord = this->oldCoordinates[i].y;
        }
    }
    //wspolr`edne wyluczajac te nachodzace na siebie
    long int commonCoverCoordinatesLength = this->coverXCoordinates.size() > this->coverYCoordinates.size() ?
            this->coverYCoordinates.size() : this->coverXCoordinates.size();
    for (int i = 0; i < commonCoverCoordinatesLength ; ++i) {
        if ( std::find(this->coverYCoordinates.begin(), this->coverYCoordinates.end(), this->coverYCoordinates[i]) != this->coverYCoordinates.end()) {
            this->oldCoordinates.erase(this->oldCoordinates.begin() + this->coverYCoordinates[i] - 1);
        }
    }
}


