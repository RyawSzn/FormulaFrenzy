#include <bits/stdc++.h>
using namespace std;

unordered_map<string, vector<string>> formulasWithVariables;

// Initializes the formulas and their corresponding variables
void initializeFormulas() {
    formulasWithVariables = {
        // Kinematics
        {"s = ½(u + v)t", {"s", "u", "v", "t"}},
        {"v = u + at", {"v", "u", "a", "t"}},
        {"s = ut + ½at²", {"s", "u", "a", "t"}},
        {"v² = u² + 2as", {"v", "u", "a", "s"}},

        // Mechanics
        {"F = ma", {"F", "m", "a"}},
        {"F = G(m₁m₂) / r²", {"F", "G", "m", "r"}},
        {"F = q₁q₂ / (4πε₀)r²", {"F", "q", "ε", "r", "π"}},
        {"F = qE", {"F", "q", "E"}},
        {"F = BIL", {"F", "B", "I", "L"}},
        {"F = qvB", {"F", "q", "v", "B"}},
        {"F = kx", {"F", "k", "x"}},
        {"F = mv² / r", {"F", "m", "v", "r"}},
        {"F = mrω²", {"F", "m", "r", "ω"}},
        {"F = Δp / t", {"F", "p", "t"}},
        {"τ = F x d", {"τ", "F", "d"}},

        // Work, Energy, and Power
        {"W = Fs", {"W", "F", "s"}},
        {"KE = ½mv²", {"KE", "m", "v"}},
        {"PE = mgh", {"PE", "m", "g", "h"}},
        {"P = VI", {"P", "V", "I"}},
        {"P = I²R", {"P", "I", "R"}},
        {"P = V²/R", {"P", "V", "R"}},
        {"P = Fv", {"P", "F", "v"}},
        {"E = Pt", {"E", "P", "t"}},

        // Thermal Physics
        {"Q = mcΔT", {"Q", "m", "c", "T"}},
        {"Q = mL", {"Q", "m", "L"}},

        // Waves and Optics
        {"v = fλ", {"v", "f", "λ"}},
        {"f = 1 / T", {"f", "T"}},
        {"n₁sinθ₁ = n₂sinθ₂", {"n", "θ"}},
        {"1/f = 1/u + 1/v", {"f", "u", "v"}},

        // Electricity and Magnetism
        {"V = IR", {"V", "I", "R"}},
        {"V = W / Q", {"V", "W", "Q"}},
        {"ε = V + Ir", {"ε", "V", "I", "r"}},
        {"C = Q / V", {"C", "Q", "V"}},
        {"E = V / d", {"E", "V", "d"}},
        {"B = μ₀NIL", {"B", "μ", "N", "I", "L"}},
        {"B = μ₀I / (2πr)", {"B", "μ", "I", "r", "π"}},
        {"Φ = BA", {"Φ", "B", "A"}},
        {"ε = -N(ΔΦ/Δt)", {"ε", "N", "Φ", "t"}},
        {"I = nAve", {"I", "n", "A", "v", "e"}},
        {"Q = It", {"Q", "I", "t"}},
        {"V = Ed", {"V", "E", "d"}},

        // Modern Physics
        {"E = hf", {"E", "h", "f"}},
        {"E = mc²", {"E", "m", "c"}},
        {"N = N₀e^(-kt)", {"N", "e", "k", "t"}},
        {"A = kN", {"A", "k", "N"}},
        {"KEₘₐₓ = eVₛ", {"KE", "e", "V"}},
        {"φ = hf₀", {"φ", "h", "f"}},

        // Circular Motion
        {"a = v² / r", {"a", "v", "r"}},
        {"v = rω", {"v", "r", "ω"}},
        {"a = rω²", {"a", "r", "ω"}},
        {"T = 2πr / v", {"T", "π", "r", "v"}},
        {"T = 2π / ω", {"T", "π", "ω"}},
    };
}

// Checks if the selected symbols match exactly with the required variables of a formula
bool checkExactFormulaMatch(const string& formula, const unordered_set<string>& clickedVariables) {
    auto it = formulasWithVariables.find(formula);
    if (it == formulasWithVariables.end()) return false;
    
    const vector<string>& requiredVariables = it->second;
    if (requiredVariables.size() != clickedVariables.size()) return false;
    
    unordered_set<string> requiredSet(requiredVariables.begin(), requiredVariables.end());
    return clickedVariables == requiredSet;
}