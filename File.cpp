#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "File.h"
#include "Compress.h"
#include <limits>

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
        if (!(iss >> x >> y >> c)) {
            this->saveToOutputFile(&line);
            this->linesSavedBeforeCompute++;
            continue;
        }
        line += "\n";
        dataFromFile += line;
        lineCounter++;

        if (lineCounter == numberOfCoordsForFunctionComputing) {
            co.compressData(&dataFromFile);
            dataFromFile = "";
            lineCounter = 0;
        }
    }
    co.compressData(&dataFromFile);
    co.computeCoordinates();
    this->findEssentialLines(&co, this->filePath);

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

void File::findEssentialLines(Compress *c, string filePath) {
    ifstream file(filePath);
    vector<Coords>* v = c->getCoordinates();
    std::vector<string> tokens;
    string line, buff, newLine;
    long int lineCounter = 0, coordinatesIndexCounter = 0;
    ostringstream floatToString;
    while (getline(file, line)) {
        if (lineCounter - this->linesSavedBeforeCompute == v->at(coordinatesIndexCounter).position) {
            istringstream ss(line);
            while (ss >> buff)
                tokens.push_back(buff);
            floatToString << v->at(coordinatesIndexCounter).x;
            tokens[0] = floatToString.str();
            floatToString.str("");
            floatToString << v->at(coordinatesIndexCounter).y;
            tokens[1] = floatToString.str();
            newLine = tokens[0];
            for (int i = 1; i < tokens.size(); ++i) {
                newLine += " " + tokens[i];
            }
            newLine += "\n";
            cout << line << "a"<<endl;
            cout << newLine <<endl;
        }

//        this->saveToOutputFile(&line);
//        continue;


        lineCounter++;
    }

}

fstream& gotoLine(fstream& file, long int num){
    file.seekg(ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    return file;
}
