#include "File.h"
#include "UserInterface.h"

using namespace std;

int main(int argc, char *argv[]) {

    UserInterface u = UserInterface();
    u.displayInterface();
    //Trigger action button and get user file path
    string filePath;
    u.handleFile(filePath);




    return 0;
}
