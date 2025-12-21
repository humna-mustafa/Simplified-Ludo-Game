// Simplified Ludo Game Project
//2 players Game
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;
//this structure stores all information about the player
struct Player{
    string name;  // player name
    int pos;  // Position of Player,-1 means player is still in base,and 0-45 means Player is on the track
    bool started,finished;  // started means Player has entered in the board, finished means Player has won the game.
    int moves;  // it shows number of moves by player
};
//this structure is used for saving each dice roll so we can show history later
struct DiceRoll{
    int rollNum;   //Number of Dice Rolled
    string player;  // name of player who rolled
    int dice;    //dice number(1-6)
    int position;  //position after dice moves
};
//this structure combines all game related data.
struct Game{
    Player p1, p2;  //two players
    DiceRoll history[100]; //array to store all dice rolls,max 100
    int rollCount;    //total number of dice rolls
    string winner;  //winner of game
};
//these are the safe positions where Player can not get captured by opponent
int safeSpots[] = {8, 13,21,26, 34, 39};
//these arrays are for shortcuts. if Player land on shortcut dice moves directly to shortcutTo
int shortcutFrom[] = {5, 23, 36};
int shortcutTo[] = {15, 33, 43};
//All Functions Declaration
void showMenu();
void showRules();
void getPlayerName(Player &p, int num);
int rollDice();
bool isSafe(int pos);
int getShortcut(int pos);
void movePlayer(Player &current, Player &other,int dice, Game &g);
void showBoard(Player &p1, Player &p2);
void playGame(Game &g);
void saveToFile(Game &g);
void showHistory();
void showWinners();

int main() {
    srand(time(0));//srand is used to ensure different dice value on each program execution.
    Game g; //this game object stores all data related to gameplay
    g.rollCount = 0;
    g.winner = "";
    // both players start in base with no moves
    g.p1.pos = -1; g.p1.started = false; g.p1.finished = false; g.p1.moves = 0;
    g.p2.pos = -1; g.p2.started = false; g.p2.finished = false; g.p2.moves = 0;
    int choice;
    bool running = true;
    cout << "\n\t======================================\n";
    cout << "\t        SIMPLIFIED LUDO GAME         \n";
    cout << "\t           2 Players Game                \n";
    cout << "\t    Programming Fundamentals Project \n";
    cout << "\t======================================\n";
    // main menu  it dialpays until player exits
    while(running) {
        showMenu();
        cin >> choice;
        //this checks what player picked from menu
        if(choice == 1) {
            getPlayerName(g.p1, 1); //get first player name
            getPlayerName(g.p2, 2); //get second player name
            playGame(g); // this starts the game
        }
    else if(choice == 2)
            showRules();  //this function  shows the rules of game
    else if(choice == 3)
        showHistory();    // this function shows dice history from file
    else if(choice == 4)
        showWinners();    // this function shows winner from the file
    else if(choice == 0) {
        cout << "\n\t+=====================================+";
        cout << "\n\t|     Goodbye! Thanks for playing     |\n";
        cout << "\t+=====================================+\n";
        running = false;  // this stops the while loop
        }
        else
            cout << "\n\tInvalid choice!\n";}
    return 0;
    }

// this function displays Menu
void showMenu() {
    cout << "\n\t----- MENU -----\n";
    cout << "\t1. Play Game\n";
    cout << "\t2. Rules\n";
    cout << "\t3. Dice History\n";
    cout << "\t4. Winners\n";
    cout << "\t0. Exit\n";
    cout << "\tChoice: ";
}
// this function asks player for their name and sets up their starting values
void getPlayerName(Player &p, int num) {
    cout << "\n\tEnter Player " << num << " name: ";
    cin >> p.name;
    p.pos = -1;   // start in base
    p.started = false;  // not on board yet
    p.finished = false; // didnt win yet
    p.moves = 0;   // no moves made
    cout << "\tWelcome " << p.name << "!\n";
}
// this function prints all the game rules
void showRules() {
    cout << "\n\t----- GAME RULES -----\n";
    cout << "\t1. Each player has only 1 token\n";
    cout << "\t2. Roll 6 to start\n";
    cout << "\t3. Roll 6 gives an extra turn\n";
    cout << "\t4. If player Land on opponent the opponent is sent back to base \n";
    cout << "\t5. Safe spots: 8,13,21,26,34,39\n";
    cout << "\t6. Shortcuts: 5->15, 23->33, 36->43\n";
    cout << "\t7. Reach position 45 (HOME) to win\n";
}
// this function generates random dice number between 1 and 6
int rollDice() {
    return (rand()%6)+1;  // rand  function gives big number, mod 6 gives 0-5,+1 gives 1-6
}
// this function checks if a position is a safe spot
bool isSafe(int pos) {
    for(int i = 0;i < 6;i++) { // loop through all 6 safe spots
        if(safeSpots[i] == pos) return true;
    return false;  // not in the list so not safe
}}
// this function checks if position has a shortcut and returns where to jump
int getShortcut(int pos) {
    for(int i = 0;i < 3; i++) { // this loop checks all 3 shortcuts
        if(shortcutFrom[i] == pos) return shortcutTo[i];  // if found shortcut then it return destination
    }
    return pos;  // no shortcut found,so it stay at same position
}
// this is the main function that handles to  move player Token on the board
void movePlayer(Player &current, Player &other,int dice,Game &g) {
    if(!current.started) {
        if(dice == 6) {
            current.started = true;
            current.pos = 0;
            cout << "\t" << current.name << " entered the board!\n";
        } else {
            cout << "\t" << current.name << " needs 6 to start\n";
            return;
        }
    } else {
        // player is already on board so this move them forward
        int newPos = current.pos + dice;
        // check if token went past home
        if(newPos > 45) {
            int need = 45 - current.pos;
            cout << "\tNeed exactly " << need << " to reach HOME!\n";
            return;
        }
        if(newPos == 45) {
            current.pos = 45;
            current.finished = true;
            cout << "\t*** " << current.name << " reached HOME! ***\n";
            return;
        }
        current.pos = newPos;
        cout << "\t" << current.name << " moved to " << current.pos << "\n";
        // now check if there is a shortcut at this position
        int shortcut = getShortcut(current.pos);
        if(shortcut != current.pos) {
            cout << "\t SHORTCUT! " << current.pos << " -> " << shortcut << "\n";
            current.pos = shortcut;  // jump to shortcut destination
        }
        // check if player landed on opponent
        if(other.started && !other.finished && current.pos == other.pos) {
            if(isSafe(current.pos)) {
                cout << "\tSafe spot - no capture\n";
            } else {
                cout << "\t" << current.name << " captured " << other.name << "!\n";
                other.pos = -1;
                other.started = false;
            }
        }
        if(isSafe(current.pos)) cout << "\t* Safe spot *\n";
    }
    current.moves++;  // count this move
}
// this function draws the ludo board and shows where players are
void showBoard(Player &p1, Player &p2) {
    // get first letter of each player name to show on board
    char t1 = toupper(p1.name[0]);
    char t2 = toupper(p2.name[0]);
    if(t1 == t2) { t1 = '1'; t2 = '2'; }  // if same letter use numbers instead
    // Position mapping for CLOCKWISE movement on 11x11 cross
    // Each position has {row, col} - tokens move around the table in clockwise
    // this array stores coordinates for each position 0-45 on board
    int road[46][2] = {
// --- MAIN TRACK (0–51) ---
//Left arm to right:
    {4,0}, {4,1}, {4,2}, {4,3}, {4,4},
//Turn up
    {4,4},{3,4}, {2,4}, {1,4}, {0,4},
//Top arm to right:
    {0,5}, {0,6},
//Go down:
    {1,6}, {2,6}, {3,6}, {4,6},
//Right arm to right:
   {4,6},{4,7}, {4,8}, {4,9}, {4,10},
//Turn down:
    {6,10}, {6,9}, {6,8}, {6,7}, {6,6},
//Bottom arm to left
    {10,6}, {9,6}, {8,6}, {7,6},
//Turn left
    {10,5}, {10,4},
//Go up
    {9,4}, {8,4}, {7,4}, {6,4},
//Left arm bottom to left
    {6,3}, {6,2}, {6,1}, {6,0},
//Turn up
    {5,0}, {5,1}, {5,2}, {5,3}, {5,4},
//home
        {5,5}
    };
    // Build 11 x 11 board
    char board[11][11];  // 2D array to store board characters
    // Initialize board with spaces
    for(int r = 0; r < 11; r++) {
        for(int c = 0; c < 11; c++) {
            board[r][c] = ' ';
        }
    }
    // Mark cross shape cells with dots
    // dots show the playable track area on board
    for(int r = 0; r < 11; r++) {
        for(int c = 0; c < 11; c++) {
            bool vert = (c >= 4 && c <= 6);  // vertical part of cross
            bool horz = (r >= 4 && r <= 6);  // horizontal part of cross
            if(vert || horz) board[r][c] = '.';  // mark track with dot
        }
    }
    //this 2d array marks HOME in center
    board[5][5] = 'H';
    // Mark safe spots with * so players know where they cant be captured
    for(int i = 0; i < 6; i++) {
        int p = safeSpots[i];
        if(p >= 0 && p < 46) {
            int r = road[p][0];
            int c = road[p][1];
            board[r][c] = '*';
        }
    }
    // Mark shortcut positions with > so players know they can jump ahead
    for(int i = 0; i < 3; i++) {
        int p = shortcutFrom[i];
        if(p >= 0 && p < 46) {
            int r = road[p][0];
            int c = road[p][1];
            board[r][c] = '>';
        }
    }
    // Place player 1 token on board if player is playing
    if(p1.started && !p1.finished && p1.pos >= 0 && p1.pos < 46) {
        int r = road[p1.pos][0];  // get row from road array
        int c = road[p1.pos][1];  // get column from road array
        board[r][c] = t1;  // place player letter on board
    }
    // Place player 2 token on board if player is playing
    if(p2.started && !p2.finished && p2.pos >= 0 && p2.pos < 46) {
        int r = road[p2.pos][0];  // get row from road array
        int c = road[p2.pos][1];  // get column from road array
        if(board[r][c] == t1) board[r][c] = 'X';  // Both on same spot show X
        else board[r][c] = t2;  // place player 2 letter
    }
    // Print the board with decorative box around it
    cout << "\n\t+=====================================+\n";
    cout << "\t|         L U D O   B O A R D         |\n";
    cout << "\t+=====================================+\n";
    // loop through each row and print board cells
    for(int r = 0; r < 11; r++) {
        cout << "\t|  ";
        for(int c = 0; c < 11; c++) {
            bool vert = (c >= 4 && c <= 6);
            bool horz = (r >= 4 && r <= 6);
            if(vert || horz) {
                cout << "[" << board[r][c] << "]";  // print cell in brackets
            } else {
                cout << "   ";  // empty space outside track
            }
        }
        cout << "  |\n";
    }
    cout << "\t+=====================================+\n";
    cout << "\t|         PLAYER STATUS               |\n";
    cout << "\t+-------------------------------------+\n";
    // Player 1 status box - shows name and current position or status
    cout << "\t| " << t1 << " = " << p1.name;
    for(int i = p1.name.length(); i < 8; i++) cout << " ";
    cout << "   | ";
    if(!p1.started) cout << "In BASE       ";
    else if(p1.finished) cout << "WINNER!       ";
    else {
        cout << "Position: " << p1.pos;
        if(p1.pos < 10) cout << "   ";
        else cout << "  ";
    }
    cout << "     |\n";
    // Player 2 status box - shows name and current position or status
    cout << "\t| " << t2 << " = " << p2.name;
    for(int i = p2.name.length(); i < 8; i++) cout << " ";  // add spaces for alignment
    cout << "   | ";
    if(!p2.started) cout << "In BASE       ";  // player hasnt started yet
    else if(p2.finished) cout << "WINNER!       ";
    else {
        cout << "Position: " << p2.pos;
        if(p2.pos < 10) cout << "   ";
        else cout << "  ";
    }
    cout << "     |\n";
    cout << "\t+-------------------------------------+\n";
    // print legend so players know what symbols mean
    cout << "\t|[H]=HOME [X]=Both [*]=Safe [>]=Short |\n";
    cout << "\t+=====================================+\n";
}
// this function runs the main game loop where players take turns
void playGame(Game &g) {
    int turn = 1;  //1 means player1 turn, 2 means player2 turn
    int dice, choice;  // dice stores roll value, choice stores menu selection
    bool gameOn = true;  // controls the game loop
    cout << "\n\t\t*** " << g.p1.name << " vs " << g.p2.name << " ***\n";
    showBoard(g.p1, g.p2);
    while(gameOn) {
        Player *current, *other;
        // set pointers to current player and opponent
        if(turn == 1) { current = &g.p1; other = &g.p2; }
        else { current = &g.p2; other = &g.p1; }
        cout << "\n\t--- " << current->name << "'s turn ---\n";
        cout << "\t1.Roll  0.Quit : ";
        cin >> choice;  // get player choice
        // if player wants to quit
        if(choice == 0) {
            cout << "\tGame ended\n";
            break;
        }
        dice = rollDice();  // roll the dice
        cout << "\n\tDice: " << dice << "\n";  // show dice value
        // Save dice roll to history array for record keeping
        if(g.rollCount < 100) {  // max 100 rolls can be saved
            g.history[g.rollCount].rollNum = g.rollCount + 1;  // roll number
            g.history[g.rollCount].player = current->name;  // who rolled
            g.history[g.rollCount].dice = dice;  // what they rolled
            g.history[g.rollCount].position = current->pos + dice;  // new position
            g.rollCount++;  // increase roll counter
        }
        movePlayer(*current, *other, dice, g);
        showBoard(g.p1, g.p2);
        // check if current player won
        if(current->finished) {
            g.winner = current->name;  // save winner name
            // display winning message
            cout << "\n\t********************************************\n\n";
            cout << "\t  Congratulations! "<< g.winner << ", You WINS the Game!!   \n\n";
            cout << "\t********************************************\n";
            saveToFile(g);  // save game results to file
            gameOn = false;
        }
        else if(dice == 6) {
            cout << "\tRolled 6 - go again!\n";  // rolling 6 gives extra turn
}
        else {
            turn = (turn == 1) ? 2 : 1;  // switch to other player
        }}}
// this function saves game data to files
void saveToFile(Game &g) {
    // Save winner to winners.txt file
    ofstream wfile("winners.txt", ios::app);  // ios::app means append mode so old data not deleted
    if(wfile.is_open()) {  // check if file opened successfully
        time_t now = time(0);  // get current time for timestamp
        // write winner info with date and move counts
        wfile << "Winner: " << g.winner << " | " << ctime(&now);
        wfile << "Moves - " << g.p1.name << ": " << g.p1.moves;
        wfile << ", " << g.p2.name << ": " << g.p2.moves << "\n";
        wfile << "------------------------\n";
        wfile.close();  // close file after writing
        cout << "\tSaved to winners.txt\n";
    }
    // Save dice history to dice_history.txt file
    ofstream hfile("dice_history.txt", ios::app);  //this opens file in append mode
    if(hfile.is_open()) {  // check if file opened
        time_t now = time(0);  // get current time
        // write game header info
        hfile << "\n=== GAME ===\n";
        hfile << "Date: " << ctime(&now);
        hfile << g.p1.name << " vs " << g.p2.name << "\n";
        hfile << "Winner: " << g.winner << "\n";
        // write all dice rolls from history array using loop
        for(int i = 0; i < g.rollCount; i++) {  // loop through all rolls
            hfile << "#" << g.history[i].rollNum;  // roll number
            hfile << " " << g.history[i].player;  // player name
            hfile << " dice:" << g.history[i].dice;  // dice value
            hfile << " pos:" << g.history[i].position << "\n";  // position after move
        }
        hfile.close();  // close file after writing
        cout << "\tSaved to dice_history.txt\n";
    }
}
// this function reads and displays dice history from file
void showHistory() {
    ifstream file("dice_history.txt");  // open file for reading
    string line;  // variable to store each line
    cout << "\n\t----- DICE HISTORY -----\n";
    if(file.is_open()) {  // check if file exists and opened
        while(getline(file, line)) {  // read file line by line
            cout << "\t" << line << "\n";  // print each line
        }
        file.close();
    } else {
        cout << "\tNo history yet\n";
    }
}
// this function reads and displays winners from file
void showWinners() {
    ifstream file("winners.txt");  // open file for reading
    string line;  // variable to store each line
    cout << "\n\t----- WINNERS -----\n";
    if(file.is_open()) {  // check if file exists and opened
        while(getline(file, line)) {  // read file line by line
            cout << "\t" << line << "\n";  // print each line
        }
        file.close();  // close file after reading
    } else {
        cout << "\tNo winners yet\n";  // file doesnt exist
    }
}
