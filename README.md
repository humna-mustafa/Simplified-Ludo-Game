# 🎲 Simplified Ludo Game

Welcome to the **Simplified Ludo Game**! This is a C++ console project for two players, created as a Programming Fundamentals project. Enjoy a classic board game experience with a modern, easy-to-understand codebase.

---

## 📋 Features
- 2 Player Ludo gameplay
- Roll dice, move tokens, and race to HOME
- Safe spots, shortcuts, and captures
- Dice roll and winner history saved to files
- Visual board display in the console

---

## 🕹️ How to Play
1. **Start the game** and enter player names.
2. **Roll a 6** to enter the board.
3. **Move your token** according to the dice roll.
4. **Land on your opponent** (not on a safe spot) to send them back to base.
5. **Use shortcuts** to jump ahead!
6. **Reach position 45 (HOME)** to win.

---

## 📝 Game Rules
- Each player has only 1 token.
- Roll a 6 to start and get an extra turn.
- Safe spots: 8, 13, 21, 26, 34, 39 (cannot be captured here).
- Shortcuts: 5→15, 23→33, 36→43.
- First to reach HOME (45) wins!

---

## 📂 Files
- `Simplified Ludo Game.cpp` — Main game source code
- `dice_history.txt` — Dice roll history
- `winners.txt` — Game winners log

---

## 🚀 How to Run
1. **Compile the code** (using g++ or any C++ compiler):
   ```sh
   g++ "Simplified Ludo Game.cpp" -o ludo
   ```
2. **Run the game:**
   ```sh
   ./ludo
   ```

---

## 👨‍💻 Authors
- Humna Mustafa

---

## ⭐ Enjoy the Game!
If you like this project, feel free to star the repo and share with friends! 🥳
