#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;

// Converts a standard string to an SFML string
sf::String toSFMLString(const string& input) {
    return sf::String::fromUtf8(input.begin(), input.end());
}

// Joins a vector of strings into a single string with a delimiter
string join(const vector<string>& vec, const string& delimiter) {
    if (vec.empty()) return "";
    string result = vec[0];
    for (size_t i = 1; i < vec.size(); ++i) {
        result += delimiter + vec[i];
    }
    return result;
}