#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;

extern void initializeFormulas();
extern void playGameGUI(sf::RenderWindow& window);

int main() {
    cout << "Program started" << endl;
    
    initializeFormulas();
    cout << "Formulas initialized" << endl;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Formula Frenzy");
    window.setFramerateLimit(60);

    playGameGUI(window);

    cout << "Program ended" << endl;
    return 0;
}