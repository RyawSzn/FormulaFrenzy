#include <bits/stdc++.h>
using namespace std;

extern unordered_map<string, vector<string>> formulasWithVariables;

// Generates a grid and a list of formulas based on the grid size
pair<vector<vector<string>>, vector<string>> generateGridAndFormulas(int gridSize) {
    cout << "Starting grid generation..." << endl;
    auto start = chrono::high_resolution_clock::now();

    int totalCells = gridSize * gridSize;
    vector<vector<string>> grid(gridSize, vector<string>(gridSize, " "));
    vector<string> formulas;
    map<string, int> variableCount;

    random_device rd;
    mt19937 g(rd());

    vector<pair<string, vector<string>>> formulaVector(formulasWithVariables.begin(), formulasWithVariables.end());
    shuffle(formulaVector.begin(), formulaVector.end(), g);

    int totalVariables = 0;

    for (const auto& [formula, variables] : formulaVector) {
        if (totalVariables + static_cast<int>(variables.size()) <= totalCells) {
            formulas.push_back(formula);
            for (const auto& var : variables) {
                variableCount[var]++;
                totalVariables++;
            }
            if (totalVariables == totalCells) {
                break;
            }
        }
    }

    if (totalVariables < totalCells) {
        return generateGridAndFormulas(gridSize);
    }

    vector<string> allVariables;
    for (const auto& [var, count] : variableCount) {
        for (int i = 0; i < count; i++) {
            allVariables.push_back(var);
        }
    }
    shuffle(allVariables.begin(), allVariables.end(), g);

    int index = 0;
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            grid[i][j] = allVariables[index++];
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    cout << "Grid generation completed in " << diff.count() << " seconds." << endl;
    cout << "Generated " << formulas.size() << " formulas." << endl;

    return {grid, formulas};
}