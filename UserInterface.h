#include <string>
#ifndef EPSCOMPRESS_USERINTERFACE_H
#define EPSCOMPRESS_USERINTERFACE_H

using namespace std;


class UserInterface {
public:
    UserInterface() {};
    ~UserInterface() {};
    void displayInterface();
    void handleFile(string filePath, int width);
};


#endif //EPSCOMPRESS_USERINTERFACE_H
