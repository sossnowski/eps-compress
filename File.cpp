#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "File.h"
#include "Compress.h"

using namespace std;

/**
 * Constructor
 * @param filePath
 */
File::File(string filePath){
    this->filePath = filePath;
    this->outFileName = this->getFileNameFromPath(filePath);
    this->linesSavedBeforeCompute = 0;
}


/**
 * Read data from file and save compressed to new file
 */
void File::processData(int width = 0) {
    const int numberOfCoordsForFunctionComputing = 100;
    ifstream inputFile(this->filePath);
    if (inputFile.fail()) throw ios_base::failure("Nie udało się otworzyć pliku podaj poprawną scieżkę.");
    float x, y;
    int originalImageWidth, originalImageHeight;
    string line, c, buff, newLine, w1, w2;
    int lineCounter = 0;
    Compress co = Compress();
    co.setImageDimension(width);
    string dataFromFile;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        // Check if coordinates are on the beginning of line if not it is a header
        if ((!(iss >> x >> y >> c) || line[0] == ' ') && !this->beginningSaved) {
            iss.clear();
            iss.str(line);
            iss >> c >> w1 >> w2 >> originalImageWidth >> originalImageHeight;
            // Get original file dimensions and scale them
            if (c == "%%BoundingBox:") {
                co.setOriginalImageWidth(originalImageWidth);
                originalImageWidth = originalImageWidth * co.getScale();
                originalImageHeight = originalImageHeight * co.getScale();
                ostringstream intToString;
                intToString << originalImageWidth;
                newLine = c + " " + w1 + " " + w2 + " " + intToString.str() + " ";
                intToString.str("");
                intToString << originalImageHeight;
                newLine += intToString.str();
                line = newLine;
            }
            this->beginningOfFile += line + "\n";
            this->linesSavedBeforeCompute++;
            continue;
        }

        this->beginningSaved = true;
        iss.clear();
        iss.str("");
        iss.str(line);

        // Check if footer of file did not start, if so get this line
        if(!(iss >> x >> y >> c) && this->beginningSaved) {
            this->endOfFile += line + "\n";
            continue;
        }

        dataFromFile += line += "\n";
        lineCounter++;

        // Get chunk of input file data and save coordinates from it
        if (lineCounter == numberOfCoordsForFunctionComputing) {
            co.getCoordinatesFromFileData(&dataFromFile);
            dataFromFile = "";
            lineCounter = 0;
        }
    }

    this->saveToOutputFile(&this->beginningOfFile);
    cout << "Przetworzono nagłówki pliku." <<endl;
    cout << "Rozpoczynam analizę i kompresję pliku..."<<endl;
    co.getCoordinatesFromFileData(&dataFromFile);
    co.findCoverCoordinates();
    cout << "Kompresja zakończona. Zapisuję..."<<endl;
    this->findEssentialLines(&co, this->filePath);
    this->saveToOutputFile(&this->endOfFile);

}

/**
 * Function getting file name from file path after get file
 * @param filePath
 * @return
 */
string File::getFileNameFromPath(string filePath) {
    for (int i = 0; i < 4 ; ++i) {
        filePath.erase(filePath.end() - 1);
    }
    filePath += "_out.eps";
    return filePath;
}

/**
 * Get input file name
 * @return
 */
string File::getInFileName() {
    return this->inFileName;
}

/**
 * Get output file name
 * @return
 */
string File::getOutFileName() {
    return this->outFileName;
}

/*
 * Function saves line to output file
 */
void File::saveToOutputFile(string* line) {
    ofstream outputFile(this->outFileName, ios_base::app | ios_base::out);
    if (outputFile.fail()) throw ios_base::failure("Nie udało się otworzyć pliku wynikowego");
    *line += "\n";
    outputFile << *line;
}

/**
 * Function prepare final lines with coordinates to save to output file
 * @param c
 * @param filePath
 */
void File::findEssentialLines(Compress *c, string filePath) {
    ifstream file(filePath);
    if (file.fail()) throw ios_base::failure("Nie udało się otworzyć pliku podaj poprawną scieżkę.");
    vector<Coords>* v = c->getNewCoordinates();
    std::vector<string> tokens;
    string line, buff, newLine, previousStringPartOfLine;
    long int lineCounter = 0, coordinatesIndexCounter = 0;
    ostringstream floatToString;
    this->saveFlag = true;

    while (getline(file, line)) {
        if (v->size() == coordinatesIndexCounter) break;

        // Beginning of file was saved earlier so skip this lines
        if (lineCounter - this->linesSavedBeforeCompute == v->at(coordinatesIndexCounter).position) {
            istringstream ss(line);
            while (ss >> buff)
                tokens.push_back(buff);

            // To check if coordinates in this line inside old file were relative or absolute
            if (previousStringPartOfLine != tokens[2] && !c->getAbsoluteCoordinatesFlag() && this->saveFlag) {
                Coords tmp = c->getAbsoluteCoords(coordinatesIndexCounter);
                floatToString << tmp.x;
                tokens[0] = floatToString.str();
                floatToString.str("");
                floatToString << tmp.y;
                tokens[1] = floatToString.str();
                floatToString.str("");
                this->saveFlag = false;
            } else {
                this->saveFlag = true;
                floatToString << v->at(coordinatesIndexCounter).x;
                tokens[0] = floatToString.str();
                floatToString.str("");
                floatToString << v->at(coordinatesIndexCounter).y;
                tokens[1] = floatToString.str();
                floatToString.str("");
            }
            newLine = tokens[0];
            for (int i = 1; i < tokens.size(); ++i) {
                newLine += " " + tokens[i];
            }
            this->saveToOutputFile(&newLine);
            previousStringPartOfLine = tokens[2];
            coordinatesIndexCounter++;
            newLine = "";
            tokens.clear();
        }
        lineCounter++;
    }

}
