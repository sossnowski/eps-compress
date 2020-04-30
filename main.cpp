#include <iostream>
#include <fstream>

using namespace std;

int main() {

    ifstream bigFile("../tmp.txt");
    constexpr size_t bufferSize = 10;
    unique_ptr<char[]> buffer(new char[bufferSize]);
    while (bigFile)
    {
        bigFile.read(buffer.get(), bufferSize);
        cout << buffer << endl;
    }



    cout << "111" << endl;
    return 0;
}
