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
    this->outFileName = fileName + "out";
}


/**
 * Read data from file and save compressed to new file
 */
void File::processData() {
    const int numberOfCoordsForFunctionComputing = 3;
    const float compressionRate = 0.1;
    ifstream inputFile(this->filePath);
    float x, y;
    string line, c;
    int lineCounter = 0;
    Compress co = Compress();
    string dataFromFile;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        if (!(iss >> x >> y >> c)) {
            this->saveToOutputFile(&line);
            continue;
        }
        line += "\n";
        dataFromFile += line;
        lineCounter++;

        if (lineCounter == numberOfCoordsForFunctionComputing) {
            co.compressData(&dataFromFile);
            //this->saveToOutputFile(&dataFromFile);
            dataFromFile = "";
            lineCounter = 0;
        }
    }
    co.compressData(&dataFromFile);

    co.computeCoordinates();

    //process data - get chunks of data from input file and compress it

    //c.compressData()
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

void File::saveToOutputFile(string* line) {
    ofstream outputFile(this->outFileName, ios_base::app | ios_base::out);
    *line += "\n";
    outputFile << *line;
}
