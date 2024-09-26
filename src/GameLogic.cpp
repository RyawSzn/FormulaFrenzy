#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;

extern bool checkExactFormulaMatch(const string& formula, const unordered_set<string>& clickedVariables);
extern unordered_map<string, vector<string>> formulasWithVariables;

// Handles mouse click events to select or deselect symbols on the grid
void handleMouseClick(const sf::Event& event, const vector<vector<string>>& grid, vector<string>& clickedSymbols, 
                      vector<pair<size_t, size_t>>& highlightedCells, const vector<pair<size_t, size_t>>& matchedCells, 
                      sf::Text& selectedSymbolsText) {
    const float maxGridWidth = 1000.0f;
    const float maxGridHeight = 720.0f;
    const float minCellSize = 55.0f;
    const float topPadding = 20.0f;

    float leftHalfWidth = 1280.0f / 2;

    float cellSize = min({
        maxGridWidth / grid[0].size(),
        maxGridHeight / grid.size(),
        90.0f
    });

    cellSize = max(cellSize, minCellSize);

    float gridWidth = cellSize * grid[0].size();
    float leftPadding = (leftHalfWidth - gridWidth) / 2;
    float gridHeight = cellSize * grid.size();
    float bottomPadding = 170.0f;
    float availableHeight = 720.0f - bottomPadding - topPadding;

    if (gridHeight > availableHeight) {
        cellSize = availableHeight / grid.size();
        gridWidth = cellSize * grid[0].size();
        gridHeight = cellSize * grid.size();
        leftPadding = (leftHalfWidth - gridWidth) / 2;
    }

    float startY = topPadding + (availableHeight - gridHeight) / 2;
    float startX = leftPadding;

    int row = static_cast<int>((event.mouseButton.y - startY) / cellSize);
    int col = static_cast<int>((event.mouseButton.x - startX) / cellSize);
    
    if (row >= 0 && row < static_cast<int>(grid.size()) && col >= 0 && col < static_cast<int>(grid[0].size())) {
        pair<size_t, size_t> currentCell = make_pair(static_cast<size_t>(row), static_cast<size_t>(col));
        if (find(matchedCells.begin(), matchedCells.end(), currentCell) == matchedCells.end()) {
            string clickedSymbol = grid[row][col];
            auto cellIt = find(highlightedCells.begin(), highlightedCells.end(), currentCell);
            
            if (cellIt == highlightedCells.end()) {
                if (clickedSymbols.size() < 5 && find(clickedSymbols.begin(), clickedSymbols.end(), clickedSymbol) == clickedSymbols.end()) {
                    highlightedCells.push_back(currentCell);
                    clickedSymbols.push_back(clickedSymbol);
                }
            } else {
                highlightedCells.erase(cellIt);
                auto varIt = find(clickedSymbols.begin(), clickedSymbols.end(), clickedSymbol);
                if (varIt != clickedSymbols.end()) {
                    clickedSymbols.erase(varIt);
                }
            }
            
            string selectedSyms = "Selected symbols (up to 5): ";
            for (size_t i = 0; i < clickedSymbols.size(); ++i) {
                selectedSyms += clickedSymbols[i];
                if (i < clickedSymbols.size() - 1) {
                    selectedSyms += ", ";
                }
            }
            selectedSymbolsText.setString(sf::String::fromUtf8(selectedSyms.begin(), selectedSyms.end()));
        }
    }
}

// Handles the submit button click to check if the selected symbols form a valid formula
void handleSubmitButtonClick(unordered_map<string, int>& formulaCount, sf::Text& messageText, sf::Clock& messageClock,
                             vector<pair<size_t, size_t>>& highlightedCells, vector<pair<size_t, size_t>>& matchedCells,
                             vector<string>& clickedSymbols, sf::Text& selectedSymbolsText, 
                             vector<string>& formulaHistory) {
    bool formulaMatched = false;
    string matchedFormula;

    for (const auto& [formula, symbols] : formulasWithVariables) {
        if (checkExactFormulaMatch(formula, unordered_set<string>(clickedSymbols.begin(), clickedSymbols.end()))) {
            formulaCount[formula]--;
            matchedFormula = formula;
            
            matchedCells.insert(matchedCells.end(), highlightedCells.begin(), highlightedCells.end());
            
            formulaMatched = true;
            formulaHistory.push_back(formula);
            break;
        }
    }
    
    if (formulaMatched) {
        string utf8Formula = "Formula matched: " + matchedFormula;
        messageText.setString(sf::String::fromUtf8(utf8Formula.begin(), utf8Formula.end()));
        messageText.setFillColor(sf::Color(0, 128, 0));
    } else {
        messageText.setString("Invalid formula. Try again.");
        messageText.setFillColor(sf::Color(178, 34, 34));
        messageText.setCharacterSize(32);
    }
    
    messageClock.restart();
    
    clickedSymbols.clear();
    highlightedCells.clear();
    selectedSymbolsText.setString("Selected symbols (up to 5): ");
}