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
    sort( this->oldCoordinates.begin( ), this->oldCoordinates.end( ), [ ]( const auto& lhs, const auto& rhs ){
        return lhs.x < rhs.x;
    });

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
    cout << this->oldCoordinates.size() <<endl;
    vector<long int>commonIndexes;
    if (this->coverXCoordinates.size() > this->coverYCoordinates.size()) {
        for (int i = 0; i < this->coverYCoordinates.size() ; ++i) {
            if (find(this->coverXCoordinates.begin(), this->coverXCoordinates.end(), this->coverYCoordinates[i]) != this->coverXCoordinates.end()) {
                commonIndexes.push_back(this->coverYCoordinates[i]);
            }
        }
    } else {
        for (int i = 0; i < this->coverXCoordinates.size() ; ++i) {
            if (find(this->coverYCoordinates.begin(), this->coverYCoordinates.end(), this->coverXCoordinates[i]) != this->coverYCoordinates.end()) {
                commonIndexes.push_back(this->coverXCoordinates[i]);
            }
        }
    }
    //wspolr`edne wyluczajac te nachodzace na siebie
    //mam indexy tablicy do usuniecia ale jak usune jeden z nich to juz tablica sie przesuwa i indexy sie zmieniaja - rozkmin
    cout << commonIndexes.size() <<endl;
    for (int i = 0; i < commonIndexes.size() ; ++i) {
        this->oldCoordinates.erase(this->oldCoordinates.begin() + commonIndexes[i] - 1 - i);
    }

    cout << this->oldCoordinates.size() <<endl;
}


