#include "UserInterface.h"
#include <SFML/Graphics.hpp>
#include "File.h"
#include "TextBox.h"


/**
 * Handle file and start compress
 * @param filePath
 */
void UserInterface::handleFile(string filePath, int width) {
    File f = File(filePath);
    f.processData(width);
}

/**
 * User interface class
 */
void UserInterface::displayInterface() {
    sf::RenderWindow window;

    sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);

    window.create(sf::VideoMode(900, 900), "EPS Compress", sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(centerWindow);

    window.setKeyRepeatEnabled(true);

    sf::Font font;
    if (!font.loadFromFile("../font.ttf"))
        std::cout << "Font not found!\n";

    Textbox text1(20, sf::Color::White, true);
    text1.setPosition({ 100, 100 });
    text1.setLimit(true, 300);
    text1.setFont(font);


    //Main Loop:
    while (window.isOpen()) {

        sf::Event Event;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            //text1.setSelected(true);
            if (text1.getText().length() > 0) {
                this->filePathTyped = true;
                Textbox text1(20, sf::Color::White, true);
                text1.setPosition({ 100, 300 });
                text1.setLimit(true, 300);
                text1.setFont(font);
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            text1.setSelected(false);
        }

        //Event Loop:
        while (window.pollEvent(Event)) {
            switch (Event.type) {

                case sf::Event::Closed:
                    window.close();
                case sf::Event::TextEntered:
                    text1.typedOn(Event);
            }
        }
        window.clear();
        text1.drawTo(window);
        window.display();
    }
}

