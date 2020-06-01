#include "File.h"

using namespace std;

int main(int argc, char *argv[]) {

    //Trigger action button and get user file path
    string filePath = "../epsFiles/przyklad.eps";
    int width = 1000;
    File f = File(filePath);
    f.processData(width);




    return 0;
}
