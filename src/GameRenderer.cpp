#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;

extern sf::String toSFMLString(const string& input);

// Draws the game grid with highlighted and matched cells
void drawGrid(sf::RenderWindow& window, const vector<vector<string>>& grid, const sf::Font& font, 
              const vector<pair<size_t, size_t>>& highlightedCells, const vector<pair<size_t, size_t>>& matchedCells) {
    const float maxGridWidth = 1000.0f;
    const float maxGridHeight = 720.0f;
    const float minCellSize = 55.0f;
    const float topPadding = 20.0f; 

    float leftHalfWidth = window.getSize().x / 2;

    float cellSize = min({
        maxGridWidth / grid[0].size(),
        maxGridHeight / grid.size(),
        90.0f
    });

    cellSize = max(cellSize, minCellSize);

    float gridWidth = cellSize * grid[0].size();
    float gridHeight = cellSize * grid.size();

    float leftPadding = (leftHalfWidth - gridWidth) / 2;

    float bottomPadding = 155.0f;
    float availableHeight = window.getSize().y - bottomPadding - topPadding;

    if (gridHeight > availableHeight) {
        cellSize = availableHeight / grid.size();
        gridWidth = cellSize * grid[0].size();
        gridHeight = cellSize * grid.size();
        leftPadding = (leftHalfWidth - gridWidth) / 2;
    }

    float startY = topPadding + (availableHeight - gridHeight) / 2;
    float startX = leftPadding;

    sf::RectangleShape gridBackground(sf::Vector2f(gridWidth + 20, gridHeight + 20));
    gridBackground.setPosition(startX - 10, startY - 10);
    gridBackground.setFillColor(sf::Color(240, 240, 245));
    gridBackground.setOutlineThickness(2);
    gridBackground.setOutlineColor(sf::Color(180, 180, 200));
    window.draw(gridBackground);

    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[i].size(); ++j) {
            sf::RectangleShape cell(sf::Vector2f(cellSize - 4, cellSize - 4));
            cell.setPosition(startX + j * cellSize + 2, startY + i * cellSize + 2);
            cell.setFillColor(sf::Color(250, 250, 255));
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color(200, 200, 220));
            
            if (find(highlightedCells.begin(), highlightedCells.end(), make_pair(i, j)) != highlightedCells.end()) {
                cell.setFillColor(sf::Color(255, 255, 200));
            } else if (find(matchedCells.begin(), matchedCells.end(), make_pair(i, j)) != matchedCells.end()) {
                cell.setFillColor(sf::Color(200, 255, 200));
            }
            
            // Draw shadow first
            sf::RectangleShape shadow = cell;
            shadow.setFillColor(sf::Color(0, 0, 0, 20));
            shadow.move(2, 2);
            window.draw(shadow);

            // Draw cell
            window.draw(cell);

            sf::Text text(toSFMLString(grid[i][j]), font, min(32.0f, cellSize * 0.5f));
            
            if (find(highlightedCells.begin(), highlightedCells.end(), make_pair(i, j)) != highlightedCells.end()) {
                text.setFillColor(sf::Color(0, 0, 128));
            } else if (find(matchedCells.begin(), matchedCells.end(), make_pair(i, j)) != matchedCells.end()) {
                text.setFillColor(sf::Color(0, 100, 0));
            } else {
                text.setFillColor(sf::Color(50, 50, 80));
            }
            
            text.setPosition(
                startX + j * cellSize + (cellSize - text.getLocalBounds().width) / 2,
                startY + i * cellSize + (cellSize - text.getLocalBounds().height) / 2 - text.getLocalBounds().top
            );
            window.draw(text);
        }
    }
}

// Draws the selected formula at the bottom of the window
void drawSelectedFormula(sf::RenderWindow& window, const string& selectedFormula, const sf::Font& font) {
    sf::Text formulaText(toSFMLString(selectedFormula), font, 30);
    formulaText.setFillColor(sf::Color(50, 50, 80));
    formulaText.setPosition(50.0f, window.getSize().y - 50.0f);
    window.draw(formulaText);
}

// Draws the history of matched formulas
void drawFormulaHistory(sf::RenderWindow& window, const vector<string>& formulaHistory, const sf::Font& font) {
    float startX = window.getSize().x - 550.0f;
    float startY = 30.0f;
    float lineHeight = 40.0f;
    float historyHeight = 600.0f;

    sf::RectangleShape historyBackground(sf::Vector2f(520, historyHeight));
    historyBackground.setPosition(startX - 10, startY - 10);
    historyBackground.setFillColor(sf::Color(245, 245, 250));
    historyBackground.setOutlineThickness(2);
    historyBackground.setOutlineColor(sf::Color(180, 180, 200));
    window.draw(historyBackground);

    sf::Text titleText("Formula History:", font, 32);
    titleText.setFillColor(sf::Color(50, 50, 80));
    titleText.setPosition(startX, startY);
    window.draw(titleText);

    startY += 60.0f;

    for (size_t i = 0; i < formulaHistory.size(); ++i) {
        sf::Text formulaText(toSFMLString(formulaHistory[formulaHistory.size() - 1 - i]), font, 24);
        formulaText.setFillColor(sf::Color(80, 80, 100));
        formulaText.setPosition(startX, startY + i * lineHeight);
        window.draw(formulaText);
    }
}

// Draws a message box at the bottom of the window
void drawMessageBox(sf::RenderWindow& window, const sf::Text& messageText) {
    float boxWidth = 520.0f;
    float boxHeight = 60.0f;
    float boxX = window.getSize().x - 550.0f - 10;
    float boxY = window.getSize().y - 80.0f;

    sf::RectangleShape messageBox(sf::Vector2f(boxWidth, boxHeight));
    messageBox.setPosition(boxX, boxY);
    messageBox.setFillColor(sf::Color(240, 240, 245));
    messageBox.setOutlineThickness(2);
    messageBox.setOutlineColor(sf::Color(180, 180, 200));

    window.draw(messageBox);

    sf::Text centeredText = messageText;
    centeredText.setPosition(
        boxX + (boxWidth - centeredText.getLocalBounds().width) / 2,
        boxY + (boxHeight - centeredText.getLocalBounds().height) / 2 - centeredText.getLocalBounds().top
    );
    window.draw(centeredText);
}

// Draws a message box at the bottom of the window
void drawButton(sf::RenderWindow& window, const sf::RectangleShape& button, const sf::Text& text) {
    sf::RectangleShape shadowButton = button;
    shadowButton.setFillColor(sf::Color(0, 0, 0, 50));
    shadowButton.move(3, 3);
    window.draw(shadowButton);

    window.draw(button);

    sf::Text buttonText = text;
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    buttonText.setPosition(
        button.getPosition().x + button.getSize().x / 2.0f,
        button.getPosition().y + button.getSize().y / 2.0f
    );
    window.draw(buttonText);
}