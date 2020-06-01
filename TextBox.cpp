#include "TextBox.h"


using namespace std;

// Delete the last character of the text:
void Textbox::deleteLastChar() {
    string t = text.str();
    string newT = "";
    for (int i = 0; i < t.length() - 1; i++) {
        newT += t[i];
    }
    this->text.str("");
    this->text << newT;
    this->textbox.setString(text.str() + "_");
}

// Get user input:
void Textbox::inputLogic(int charTyped) {
    // If the key pressed isn't delete, or the two selection keys, then append the text with the char:
    if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
        this->text << static_cast<char>(charTyped);
    }
        // If the key is delete, then delete the char:
    else if (charTyped == DELETE_KEY) {
        if (this->text.str().length() > 0) {
            this->deleteLastChar();
        }
    }
    // Set the textbox text:
    this->textbox.setString(this->text.str() + "_");
}

Textbox::Textbox(int size, sf::Color color, bool sel) {
    this->textbox.setCharacterSize(size);
    this->textbox.setColor(color);
    this->isSelected = sel;

    // Check if the textbox is selected upon creation and display it accordingly:
    if(this->isSelected)
        this->textbox.setString("_");
    else
        this->textbox.setString("");
}

// Make sure font is passed by reference:
void Textbox::setFont(sf::Font &fonts) {
    this->textbox.setFont(fonts);
}

void Textbox::setPosition(sf::Vector2f point) {
    this->textbox.setPosition(point);
}

void Textbox::setLimit(bool ToF) {
    this->hasLimit = ToF;
}

void Textbox::setLimit(bool ToF, int lim) {
    this->hasLimit = ToF;
    this->limit = lim - 1;
}

void Textbox::setSelected(bool sel) {
    this->isSelected = sel;

    // If not selected, remove the '_' at the end:
    if (!sel) {
        string t = this->text.str();
        string newT = "";
        for (int i = 0; i < t.length(); i++) {
            newT += t[i];
        }
        this->textbox.setString(newT);
    }
}

string Textbox::getText() {
    return this->text.str();
}

void Textbox::drawTo(sf::RenderWindow &window) {
    window.draw(this->textbox);
}

void Textbox::typedOn(sf::Event input) {
    if (this->isSelected) {
        int charTyped = input.text.unicode;

        // Only allow normal inputs:
        if (charTyped < 128) {
            if (this->hasLimit) {
                // If there's a limit, don't go over it:
                if (this->text.str().length() <= this->limit) {
                    this->inputLogic(charTyped);
                }
                    // But allow for char deletions:
                else if (this->text.str().length() > limit && charTyped == DELETE_KEY) {
                    this->deleteLastChar();
                }
            }
                // If no limit exists, just run the function:
            else {
                this->inputLogic(charTyped);
            }
        }
    }
}
