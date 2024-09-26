#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;

extern void drawButton(sf::RenderWindow& window, const sf::RectangleShape& button, const sf::Text& text);

// Allows the user to choose the difficulty level by selecting the grid size
int chooseDifficulty(sf::RenderWindow& window, const sf::Font& font) {
    sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setFillColor(sf::Color(240, 240, 245));

    sf::Text titleText("Formula Frenzy", font, 60);
    titleText.setStyle(sf::Text::Bold);
    titleText.setFillColor(sf::Color(50, 50, 100));
    titleText.setPosition(window.getSize().x / 2 - titleText.getGlobalBounds().width / 2, 50);

    sf::Text instructionText("Choose Grid Size", font, 36);
    instructionText.setFillColor(sf::Color(100, 100, 150));
    instructionText.setPosition(window.getSize().x / 2 - instructionText.getGlobalBounds().width / 2, 140);

    sf::RectangleShape sliderTrack(sf::Vector2f(400, 6));
    sliderTrack.setFillColor(sf::Color(200, 200, 220));
    sliderTrack.setPosition(window.getSize().x / 2 - 200, 250);

    sf::Texture sliderTexture;
    if (!sliderTexture.loadFromFile("assets/icons/SliderHandleIcon.png")) {
        cerr << "Failed to load slider texture" << endl;
        return -1;
    }

    sf::CircleShape sliderHandle(22);
    sliderHandle.setTexture(&sliderTexture);
    sliderHandle.setOrigin(22, 22);
    sliderHandle.setFillColor(sf::Color(220, 220, 240, 200));

    sf::Text gridSizeText("", font, 30);
    gridSizeText.setFillColor(sf::Color(50, 50, 100));

    sf::RectangleShape previewArea(sf::Vector2f(300, 300));
    previewArea.setFillColor(sf::Color(250, 250, 255));
    previewArea.setOutlineColor(sf::Color(150, 150, 200));
    previewArea.setOutlineThickness(2);
    previewArea.setPosition(window.getSize().x / 2 - 150, 320);

    sf::RectangleShape startButton(sf::Vector2f(200, 60));
    startButton.setFillColor(sf::Color(100, 150, 250));
    startButton.setPosition(window.getSize().x / 2 - 100, 640);

    sf::Text startButtonText("Start Game", font, 30);
    startButtonText.setFillColor(sf::Color::White);
    startButtonText.setStyle(sf::Text::Bold);

    int gridSize = 2;
    float sliderValue = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1;
            } else if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseMoved) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (mousePos.x >= sliderTrack.getPosition().x && mousePos.x <= sliderTrack.getPosition().x + sliderTrack.getSize().x &&
                        mousePos.y >= sliderTrack.getPosition().y - 10 && mousePos.y <= sliderTrack.getPosition().y + 16) {
                        sliderValue = (mousePos.x - sliderTrack.getPosition().x) / sliderTrack.getSize().x;
                        sliderValue = std::max(0.0f, std::min(1.0f, sliderValue));
                        gridSize = 2 + static_cast<int>(sliderValue * 12);
                    }
                }
            } else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (startButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        return gridSize;
                    }
                }
            }
        }

        sliderHandle.setPosition(sliderTrack.getPosition().x + sliderValue * sliderTrack.getSize().x, sliderTrack.getPosition().y + 3);

        gridSizeText.setString(to_string(gridSize) + "x" + to_string(gridSize));
        gridSizeText.setPosition(window.getSize().x / 2 - gridSizeText.getGlobalBounds().width / 2, 270);

        startButtonText.setPosition(startButton.getPosition().x + 100 - startButtonText.getGlobalBounds().width / 2,
                                    startButton.getPosition().y + 30 - startButtonText.getGlobalBounds().height / 2);

        window.clear(sf::Color::White);
        window.draw(background);
        window.draw(titleText);
        window.draw(instructionText);
        window.draw(sliderTrack);
        window.draw(sliderHandle);
        window.draw(gridSizeText);
        window.draw(previewArea);
        drawButton(window, startButton, startButtonText);

        float cellSize = 300.0f / gridSize;
        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                sf::RectangleShape cell(sf::Vector2f(cellSize - 2, cellSize - 2));
                cell.setPosition(previewArea.getPosition().x + j * cellSize + 1, previewArea.getPosition().y + i * cellSize + 1);
                cell.setFillColor(sf::Color(220, 220, 240));
                cell.setOutlineColor(sf::Color(200, 200, 220));
                cell.setOutlineThickness(1);
                window.draw(cell);
            }
        }

        window.display();
    }

    return -1;
}

// Displays a winning message when the player matches all formulas
void showWinningMessage(sf::RenderWindow& window, const sf::Font& font) {
    sf::Text congratsText("Congratulations!", font, 60);
    congratsText.setFillColor(sf::Color::Green);
    congratsText.setPosition(window.getSize().x / 2 - congratsText.getGlobalBounds().width / 2, 200);

    sf::Text messageText("You've matched all the formulas!", font, 30);
    messageText.setFillColor(sf::Color::Black);
    messageText.setPosition(window.getSize().x / 2 - messageText.getGlobalBounds().width / 2, 300);

    sf::RectangleShape continueButton(sf::Vector2f(200, 60));
    continueButton.setPosition(window.getSize().x / 2 - 100, 400);
    continueButton.setFillColor(sf::Color(100, 200, 100));

    sf::Text continueText("Continue", font, 30);
    continueText.setFillColor(sf::Color::White);
    continueText.setPosition(continueButton.getPosition().x + 100 - continueText.getGlobalBounds().width / 2,
                             continueButton.getPosition().y + 30 - continueText.getGlobalBounds().height / 2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (continueButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        return;
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(congratsText);
        window.draw(messageText);
        drawButton(window, continueButton, continueText);
        window.display();
    }
}