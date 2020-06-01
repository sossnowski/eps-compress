#include "File.h"
#include "UserInterface.h"

using namespace std;

int main(int argc, char *argv[]) {

    UserInterface u = UserInterface();
    u.displayInterface();
    //Trigger action button and get user file path
    string filePath = "../epsFiles/przyklad.eps";
    int width = 1000;
    //u.handleFile(filePath);
    File f = File(filePath);
    f.processData(width);




    return 0;
}
