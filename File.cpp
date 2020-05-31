#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "File.h"
#include "Compress.h"

using namespace std;

/**
 * Contructor
 * @param filePath
 */
File::File(string filePath){
    this->filePath = filePath;
    string fileName = this->getFileNameFromPath(filePath);
    this->inFileName = fileName;
    this->outFileName = fileName + "out.eps";
}


/**
 * Read data from file and save compressed to new file
 */
void File::processData() {
    const int numberOfCoordsForFunctionComputing = 100;
    const float compressionRate = 0.1;
    ifstream inputFile(this->filePath);
    float x, y;
    string line, c;
    int lineCounter = 0;
    Compress co = Compress();
    string dataFromFile;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        // Check if coordinates are on the beginning of line
        if ((!(iss >> x >> y >> c) || line[0] == ' ') && !this->beginningSaved) {
            this->beginningOfFile += line + "\n";
            this->linesSavedBeforeCompute++;
            continue;
        }

        this->beginningSaved = true;
        iss.clear();
        iss.str("");
        iss.str(line);

        if(!(iss >> x >> y >> c) && this->beginningSaved) {
            this->endOfFile += line + "\n";
            continue;
        }

        dataFromFile += line += "\n";
        lineCounter++;

        if (lineCounter == numberOfCoordsForFunctionComputing) {
            co.getCoordinatesFromFileData(&dataFromFile);
            dataFromFile = "";
            lineCounter = 0;
        }
    }

    this->saveToOutputFile(&this->beginningOfFile);
    co.getCoordinatesFromFileData(&dataFromFile);
    co.findCoverCoordinates();
    this->findEssentialLines(&co, this->filePath);
    this->saveToOutputFile(&this->endOfFile);

}

/**
 * Function getting file name from file path after get file
 * @param filePath
 * @return
 */
string File::getFileNameFromPath(string filePath) {
    string fileName;

    return fileName;
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
    vector<Coords>* v = c->getNewCoordinates();
    std::vector<string> tokens;
    string line, buff, newLine, previousStringPartOfLine;
    long int lineCounter = 0, coordinatesIndexCounter = 0;
    ostringstream floatToString;
    this->saveFlag = true;

    while (getline(file, line)) {
        if (v->size() == coordinatesIndexCounter) break;
        // Beggining of file was saved earlier so skip this lines
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
