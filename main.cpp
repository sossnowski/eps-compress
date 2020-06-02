#include "File.h"

using namespace std;

int main(int argc, char *argv[]) {

    //Trigger action button and get user file path
    try{
        cout << "Podaj sciężkę do pliku do kompresji"<<endl;
        string filePath;
        cin >> filePath;
        if (cin.fail()) throw "Podaj poprawną scieżke do pliku";
        int width;
        cout << "Podaj docelową szerokość pliku w pikselach"<<endl;
        cin >> width;
        if (cin.fail()) throw logic_error( "Podaj szerokość jako liczbę całkowitą" );

        File f = File(filePath);
        f.processData(width);
        cout << "Proces optymalizacji zakończony. Ścieżka do pliku wynikowego: " << f.getOutFileName() <<endl;
    } catch (const logic_error & e) {
        cout << e.what() <<endl;
    } catch (const ios_base::failure& e) {
        cout << e.what()<<endl;
    }





    return 0;
}
