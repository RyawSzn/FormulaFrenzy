# C++ Game Programming - Formula Frenzy
Remember the Physics formulas game C++ using SFML as graphics library

## How to Play the Game?
The goal of Formula Frenzy is to match all the given physics formulas by selecting the correct symbols from a grid. This game tests your knowledge of various physics formulas and your ability to recognize and match them quickly.

### Features
- **Interactive Grid Interface**
- **Difficulty Levels**
- **Real-Time Feedback**
- **Formula History**
- **Multiple Control Options**
- **Educational Content**
- **Engaging Visuals**

## Instructions and Rules

### Setup
1. **Choose Grid Size:** 
   - At the start of the game, you will be prompted to choose the difficulty level by selecting the grid size. The grid size determines the number of cells in the grid, with larger grids being more challenging.

2. **Grid Generation:** 
   - Once the grid size is selected, the game generates a grid filled with symbols and a list of formulas (without repetition) that need to be matched.

### Gameplay
1. **Grid Display:** 
   - The grid is displayed on the screen, with each cell containing a symbol. The symbols are randomly distributed across the grid.

2. **Selecting Symbols:** 
   - You can select symbols by clicking on the cells in the grid. Up to 5 symbols can be selected at a time.
   - Subscripts and superscripts are simply regarded as the symbol itself. (n₁ → n; v² → v)

3. **Highlighted Cells:** 
   - Selected cells are highlighted in yellow to indicate they are part of the current selection.

4. **Matching Formulas:** 
   - The selected symbols are checked against the list of formulas. If the selected symbols match the required symbols of a formula, the formula is considered matched.

5. **Matched Cells:** 
   - Cells that are part of a matched formula are highlighted in green to indicate they have been successfully matched.

### Controls
- **Mouse Click:** 
  - Use the mouse to click on cells to select or deselect symbols.

- **Submit Button:** 
  - Click the "Submit" button to check if the selected symbols form a valid formula.

- **Restart Button:** 
  - Click the "Restart" button to reset the grid and start over with the same grid size.

- **Back Button:** 
  - Click the "Back" button to return to the difficulty selection screen.

- **Random Button:** 
  - Click the "Random" button to generate a new grid with the same grid size.

### Winning the Game
1. **Matching All Formulas:** 
   - The game is won when all the formulas in the list have been matched. A congratulatory message is displayed to indicate the successful completion of the game.

2. **Winning Message:** 
   - The winning message includes a "Continue" button to acknowledge the victory and return to the main menu or difficulty selection screen.

## List of Formulas (according to the HKDSE Physics Syllabus)

- ### Kinematics
- - s = ½(u + v)t, {"s", "u", "v", "t"},
- - v = u + at, {"v", "u", "a", "t"},
- - s = ut + ½at², {"s", "u", "a", "t"},
- - s = ½(u + v)t, {"s", "u", "v", "t"},
- - v = u + at, {"v", "u", "a", "t"},
- - s = ut + ½at², {"s", "u", "a", "t"},
- - v² = u² + 2as, {"v", "u", "a", "s"},
- - p = mv, {"p", "m", "v"},

- ### Gas
- - pV = nRT, {"p", "V", "n", "R", "T"},
- - pV = ⅓Nmc², {"p", "V", "N", "m", "c"},
- - KE = 3RT / (2NA), {"KE", "R", "T", "NA"},

- ### Mechanics
- - F = ma, {"F", "m", "a"},
- - F = G(m₁m₂) / r², {"F", "G", "m", "r"},
- - F = Q₁Q₂ / (4πε₀)r², {"F", "Q", "ε", "r", "π"},
- - F = qE, {"F", "q", "E"},
- - F = BIL, {"F", "B", "I", "L"},
- - F = qvB, {"F", "q", "v", "B"},
- - F = mv² / r, {"F", "m", "v", "r"},
- - F = mrω², {"F", "m", "r", "ω"},
- - F = Δp / t, {"F", "p", "t"},
- - τ = F x d, {"τ", "F", "d"},

- ### Work, Energy, and Power
- - W = Fs, {"W", "F", "s"},
- - KE = ½mv², {"KE", "m", "v"},
- - PE = mgh, {"PE", "m", "g", "h"},
- - P = VI, {"P", "V", "I"},
- - P = I²R, {"P", "I", "R"},
- - P = V²/R, {"P", "V", "R"},
- - P = Fv, {"P", "F", "v"},
- - E = Pt, {"E", "P", "t"},

- ### Thermal Physics
- - Q = mcΔT, {"Q", "m", "c", "T"},
- - Q = mL, {"Q", "m", "L"},

- ### Waves and Optics
- - Δy = λD / a, {"y", "λ", "D", "a"},
- - dsinθ = nλ, {"d", "θ", "n", "λ"},
- - v = fλ, {"v", "f", "λ"},
- - f = 1 / T, {"f", "T"},
- - n₁sinθ₁ = n₂sinθ₂, {"n", "θ"},
- - 1/f = 1/u + 1/v, {"f", "u", "v"},

- ### Electricity and Magnetism
- - V = IR, {"V", "I", "R"},
- - ε = V + Ir, {"ε", "V", "I", "r"},
- - E = V / d, {"E", "V", "d"},
- - E = Q / (4πε₀r²), {"E", "Q", "ε", "r", "π"},
- - B = μ₀NIL, {"B", "μ", "N", "I", "L"},
- - B = μ₀I / (2πr), {"B", "μ", "I", "r", "π"},
- - Φ = BA, {"Φ", "B", "A"},
- - ε = -N(ΔΦ/Δt), {"ε", "N", "Φ", "t"},
- - R = ρl/A, {"R", "ρ", "l", "A"},
- - V = Ed, {"V", "E", "d"},
- - V₁ / V₂ ≈ N₁ / N₂, {"V", "N"},

- ### Modern Physics
- - ΔE = Δmc², {"E", "m", "c"},
- - N = N₀e^(-kt), {"N", "e", "k", "t"},
- - t½ = ln2 / k, {"t", "k"},
- - A = kN, {"A", "k", "N"},

- ### Circular Motion
- - a = v² / r, {"a", "v", "r"},
- - v = rω, {"v", "r", "ω"},
- - a = rω², {"a", "r", "ω"},
- - T = 2πr / v, {"T", "π", "r", "v"},
- - T = 2π / ω, {"T", "π", "ω"},

- ### Atomic World
- - KEₘₐₓ = eVₛ, {"KE", "e", "V"},
- - E = hf, {"E", "h", "f"},
- - φ = hf₀, {"φ", "h", "f"},
- - ½mₑvₘₐₓ² = hf - φ, {"m", "v", "h", "f", "φ"},
- - λ = h / (mv), {"λ", "h", "m", "v"},
- - λ = h / p, {"λ", "h", "p"},
- - θ ≈ 1.22λ / d, {"θ", "λ", "d"},
- - S = θr, {"S", "θ", "r"},

- ### Energy and Use of Energy
- - E = Φ / A, {"E", "Φ", "A"},
- - Q / t = UAΔT, {"Q", "t", "U", "T", "d"},
- - U = κ / d, {"U", "κ", "d"},
- - P = ½ρAv³, {"P", "ρ", "A", "v"}