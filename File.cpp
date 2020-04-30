#include "File.h"

using namespace std;

/**
 * Otwieranie pliku wejsciowego
 */
void File::openInputFile() {
    this->inputFile.open( this->inFileName , ios::in);
}

/**
 * Tworzenie pliku wyjsciowego
 */
void File::createOutputFile() {
    this->outputFile.open( this->outFileName , ios::out);
}

/**
 * Odczytywanie danych z pliku wejciowego i zapisanie rezultatu kompresji do pliku wyjsciowego
 */
void File::processData() {

}
