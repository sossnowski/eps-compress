#ifndef EPSCOMPRESS_TEXTBOX_H
#define EPSCOMPRESS_TEXTBOX_H


#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

using namespace std;

// Define keys:
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox {
private:
    sf::Text textbox;

    ostringstream text;
    bool isSelected = false;
    bool hasLimit = false;
    int limit = 0;

    void deleteLastChar();
    void inputLogic(int charTyped);


public:
    Textbox(int size, sf::Color color, bool sel);

    // Make sure font is passed by reference:
    void setFont(sf::Font &fonts);

    void setPosition(sf::Vector2f point);

    // Set char limits:
    void setLimit(bool ToF);

    void setLimit(bool ToF, int lim);

    // Change selected state:
    void setSelected(bool sel);

    string getText();

    void drawTo(sf::RenderWindow &window);

    // Function for event loop:
    void typedOn(sf::Event input);
};


#endif //EPSCOMPRESS_TEXTBOX_H
