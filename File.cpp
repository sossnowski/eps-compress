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
    fstream inputFile, outputFile;
    inputFile.open( this->inFileName , ios::in);

    //process data - get chunks of data from input file and compress it
    Compress c = Compress();
    //c.compressData()

    //save final file
    outputFile.open( this->inFileName , ios::out);
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
