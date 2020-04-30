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

    while(window.isOpen()){



        sf::Event event;

        while(window.pollEvent(event)) {

            if(event.type == sf::Event::Closed){

                window.close();

            }



            window.clear(sf::Color::Black);

            window.display();

        }

    }
}
