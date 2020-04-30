#include "UserInterface.h"
#include <SFML/Graphics.hpp>
#include "File.h"


/**
 * Handle file and start compress
 * @param filePath
 */
void UserInterface::handleFile(string filePath) {
    File f = File(filePath);
    f.processData();
}

/**
 * User interface class
 */
void UserInterface::displayInterface() {
    sf::RenderWindow window(sf::VideoMode(640,480,32),"EPS Compress");



    sf::Font font;

    font.loadFromFile("../font.ttf");



    sf::Text text("Compress your EPS file", font,11);

    text.setCharacterSize(32);

    text.setPosition(window.getSize().x/2 - text.getGlobalBounds().width/2,

                     window.getSize().y/2 - text.getGlobalBounds().height/2);





    while(window.isOpen()){



        sf::Event event;

        while(window.pollEvent(event)) {

            if(event.type == sf::Event::Closed){

                window.close();

            }



            window.clear(sf::Color::Black);

            window.draw(text);

            window.display();

        }

    }
}
