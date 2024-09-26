#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;

extern unordered_map<string, vector<string>> formulasWithVariables;
extern pair<vector<vector<string>>, vector<string>> generateGridAndFormulas(int gridSize);
extern int chooseDifficulty(sf::RenderWindow& window, const sf::Font& font);
extern void showWinningMessage(sf::RenderWindow& window, const sf::Font& font);

extern void drawGrid(sf::RenderWindow& window, const vector<vector<string>>& grid, const sf::Font& font, 
                     const vector<pair<size_t, size_t>>& highlightedCells, const vector<pair<size_t, size_t>>& matchedCells);
extern void drawSelectedFormula(sf::RenderWindow& window, const string& selectedFormula, const sf::Font& font);
extern void drawFormulaHistory(sf::RenderWindow& window, const vector<string>& formulaHistory, const sf::Font& font);
extern void drawButton(sf::RenderWindow& window, const sf::RectangleShape& button, const sf::Text& text);
extern void drawSubmittedHistory(sf::RenderWindow& window, const vector<string>& submittedHistory, const sf::Font& font);

extern void handleMouseClick(const sf::Event& event, const vector<vector<string>>& grid, vector<string>& clickedVariables, 
                             vector<pair<size_t, size_t>>& highlightedCells, const vector<pair<size_t, size_t>>& matchedCells, 
                             sf::Text& selectedVariablesText);

extern void handleSubmitButtonClick(unordered_map<string, int>& formulaCount, sf::Text& messageText, sf::Clock& messageClock,
                                    vector<pair<size_t, size_t>>& highlightedCells, vector<pair<size_t, size_t>>& matchedCells,
                                    vector<string>& clickedVariables, sf::Text& selectedVariablesText, 
                                    vector<string>& formulaHistory);

extern void drawMessageBox(sf::RenderWindow& window, const sf::Text& messageText);

extern string join(const vector<string>& vec, const string& delimiter);
extern sf::String toSFMLString(const string& input);

// Main game loop for the GUI version of the game
void playGameGUI(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/DejaVuSans.ttf")) {
        cerr << "Failed to load font" << endl;
        return;
    }

    sf::Text selectedSymbolsText("Selected symbols (up to 5): ", font, 32); 
    selectedSymbolsText.setFillColor(sf::Color(100, 100, 100));
    selectedSymbolsText.setPosition(35.0f, window.getSize().y - 150.0f);

    vector<string> clickedSymbols;

    while (window.isOpen()) {
        int gridSize = chooseDifficulty(window, font);
        if (gridSize == -1) return;

        bool backToDifficultySelection = false;

        while (!backToDifficultySelection && window.isOpen()) {
            vector<vector<string>> grid;
            vector<string> currentFormulas;
            try {
                tie(grid, currentFormulas) = generateGridAndFormulas(gridSize);
            } catch (const exception& e) {
                cerr << "Error generating grid: " << e.what() << endl;
                break;
            }

            vector<string> clickedSymbols;
            vector<pair<size_t, size_t>> highlightedCells;
            vector<pair<size_t, size_t>> matchedCells;
            vector<string> formulaHistory;
            unordered_map<string, int> formulaCount;

            for (const auto& formula : currentFormulas) {
                formulaCount[formula]++;
            }

            vector<string> initialClickedSymbols = clickedSymbols;
            vector<pair<size_t, size_t>> initialHighlightedCells = highlightedCells;
            vector<pair<size_t, size_t>> initialMatchedCells = matchedCells;
            vector<string> initialFormulaHistory = formulaHistory;
            unordered_map<string, int> initialFormulaCount = formulaCount;

            sf::Text messageText("", font, 24);
            messageText.setFillColor(sf::Color::Black);

            vector<pair<sf::RectangleShape, sf::Text>> buttons;
            vector<string> buttonLabels = {"Submit", "Restart", "Back", "Random"};
            vector<sf::Color> buttonColors = {
                sf::Color(76, 175, 80),  // Submit - Green
                sf::Color(255, 152, 0),  // Restart - Orange
                sf::Color(244, 67, 54),  // Back - Red
                sf::Color(33, 150, 243)  // Random - Blue
            };
            float buttonWidth = 150.0f;
            float buttonHeight = 55.0f;
            float buttonY = window.getSize().y - 75.0f;

            for (size_t i = 0; i < buttonLabels.size(); ++i) {
                sf::RectangleShape button(sf::Vector2f(buttonWidth, buttonHeight));
                button.setPosition(25.0f + i * (buttonWidth + 20), buttonY);
                button.setFillColor(buttonColors[i]);

                sf::Text buttonText(buttonLabels[i], font, 24);
                buttonText.setFillColor(sf::Color::White);
                
                buttons.push_back(make_pair(button, buttonText));
            }

            selectedSymbolsText.setFillColor(sf::Color(128, 128, 128));
            selectedSymbolsText.setPosition(30.0f, window.getSize().y - 130.0f);

            sf::Clock messageClock;

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                    } else if (event.type == sf::Event::MouseButtonPressed) {
                        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                        for (size_t i = 0; i < buttons.size(); ++i) {
                            if (buttons[i].first.getGlobalBounds().contains(mousePos)) {
                                switch (i) {
                                    case 0: // Submit
                                        handleSubmitButtonClick(formulaCount, messageText, messageClock,
                                                                highlightedCells, matchedCells, clickedSymbols, selectedSymbolsText, 
                                                                formulaHistory);
                                        break;
                                    case 1: // Restart
                                        clickedSymbols = initialClickedSymbols;
                                        highlightedCells = initialHighlightedCells;
                                        matchedCells = initialMatchedCells;
                                        formulaHistory = initialFormulaHistory;
                                        formulaCount = initialFormulaCount;
                                        messageText.setString("Game restarted!");
                                        messageClock.restart();
                                        break;
                                    case 2: // Back
                                        backToDifficultySelection = true;
                                        break;
                                    case 3: // Random
                                        tie(grid, currentFormulas) = generateGridAndFormulas(gridSize);
                                        clickedSymbols.clear();
                                        highlightedCells.clear();
                                        matchedCells.clear();
                                        formulaHistory.clear();
                                        formulaCount.clear();
                                        for (const auto& formula : currentFormulas) {
                                            formulaCount[formula]++;
                                        }
                                        messageText.setString("New grid generated!");
                                        messageClock.restart();

                                        initialClickedSymbols = clickedSymbols;
                                        initialHighlightedCells = highlightedCells;
                                        initialMatchedCells = matchedCells;
                                        initialFormulaHistory = formulaHistory;
                                        initialFormulaCount = formulaCount;
                                        break;
                                }
                                break;
                            }
                        }
                        if (!backToDifficultySelection) {
                            handleMouseClick(event, grid, clickedSymbols, highlightedCells, matchedCells, selectedSymbolsText);
                        }
                    }
                }

                if (backToDifficultySelection) break;

                string selectedFormula;
                for (const auto& [formula, symbols] : formulasWithVariables) {
                    if (unordered_set<string>(clickedSymbols.begin(), clickedSymbols.end()) == unordered_set<string>(symbols.begin(), symbols.end())) {
                        selectedFormula = formula;
                        break;
                    }
                }

                window.clear(sf::Color::White);

                drawGrid(window, grid, font, highlightedCells, matchedCells);
                drawFormulaHistory(window, formulaHistory, font);
                drawMessageBox(window, messageText);

                string selectedSymbolsString = "Selected symbols (up to 5): " + join(clickedSymbols, " ");
                selectedSymbolsText.setString(toSFMLString(selectedSymbolsString));

                window.draw(selectedSymbolsText);
                
                for (const auto& [button, text] : buttons) {
                    drawButton(window, button, text);
                }

                if (messageClock.getElapsedTime().asSeconds() > 3.0f) {
                    messageText.setString("");
                }

                window.display();

                if (all_of(formulaCount.begin(), formulaCount.end(), [](const auto& pair) { return pair.second == 0; })) {
                    showWinningMessage(window, font);
                    break;
                }
            }
        }
    }
}