/* 
* Author: Dean Fletcher
* Purpose: This is a Snake game with 2 different play modes. The coices are to play as a Viper
*          or a Mamba. The Viper is an arcade like mode whereas the Mamba is a challenge mode. 
*          In challenge mode you can traverse through walls and there wll be new obstacles 
*          to avoid.
* Compile: g++ -std=c++11 main.cpp Snake.cpp Mamba.cpp Food.cpp Board.cpp FileIO.cpp -lcurses
*/

#include <curses.h>
#include <iomanip>
#include <limits>
#include "Board.h"
#include "Snake.h"
#include "Mamba.h"
#include "Viper.h"
#include "Food.h"
#include "FileIO.h"

using namespace std;

#define EXIT 26 // Exit command 

Board board;

void Render(Food&, Snake&, vector<Player>&, bool);
void Input(Snake&);
void Logic(Food&, Snake&, bool);
void scoreboard(vector<Player>&);
void checkPlayerScore (FileIO&, vector<Player>&, string);
void validatePos(Food&, Snake&);
void prompts(string);
string validateInput(string);
void drawEdge();
void utilSetup();
void clearScreen();

int main()
{
    string type, name;
    bool rock = false;

    FileIO file;
    vector<Player> highScores = file.read(); // Players & high scores from file
    
    Mamba mamba; // Initialize objects
    Viper viper;
    Snake& snake1 = mamba; 
    Snake& snake2 = viper;

    clearScreen();
    prompts("Snake Game"); // ASCII Snake Game prompt
    prompts("Rules");      // Game rules prompt

    cout << "\t\tWould you like to play as a \"Viper\" or \"Mamba\"?  ";
    cin >> type; 

    if (type != "Viper" && type != "Mamba") // Input validation 
        type = validateInput(type);

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear stream
    cout << "\n\t\tEnter your preferred player name:  ";
    getline(cin, name);

    if (type == "Mamba") {
        board.setArea(snake1.getArea()); // Setup board from snake type
        rock = true;
    } else board.setArea(snake2.getArea());  
    
    Food food(board.getArea());          // Setup for random food 

    while (!board.currentStatus())       // Game Loop
    {  
        // Mamba //
        if (type == "Mamba") {
            Render(food, snake1, highScores, rock); // Output game
            Input(snake1);                          // Keyboard input
            Logic(food, snake1, rock);              // Game rules
        } 
        // Viper // 
        else {                                  
            Render(food, snake2, highScores, rock);  
            Input(snake2);          
            Logic(food, snake2, rock);    
        }
        napms(1); // Take a nap (1ms)
    }
    checkPlayerScore (file, highScores, name);  // Checks players score for new High Score

    clearScreen();
    prompts("Game Over");   // Game Over prompt
    scoreboard(highScores); // Outputs scoreboard

    return EXIT_SUCCESS;
}
// Function to output the board, snake, and food //
void Render(Food& food, Snake& snake, vector<Player>& highScores, bool rock)
{
    clearScreen();
    prompts("Snake Game"); // ASCII art
    drawEdge();            // Top edge
                
    for (int y = 0; y < board.getArea(); y++)    // L/R Edges
    {
        cout << "\t\t* ";                         // Left edge
        for (int x = 0; x < board.getArea(); x++) // Playing area 
        {   
            if (rock && (x == 5 && y == 4 || x == 15 && y == 14 || x == 3 && y == 16)) // Rock pacement
                 cout << "##";
            else if (x == snake.headX() && y == snake.headY()) // Place snake head
                cout << "O "; 
            else if (snake.bodyPosition(x, y))                 // Place snake body
                cout << "o ";
            else if (y == food.foodY() && x == food.foodX())   // Place food
                cout << "x ";
            else
                cout << "  ";
        }
        cout << "* " << endl; // Right edge
    } 
    drawEdge();               // Bottom edge
    outputScore(board);       // Friend func current players score
    cout << "\n\t\tHigh Score: " << highScores[0].playerScore() << endl;
}
// Function to get keyboard input using curses library //
void Input(Snake& snake)
{
    utilSetup();               // setup for curses mode
    timeout(snake.getSpeed()); // controls snake speed
    int key = getch();
    switch (key)
    {
        case KEY_UP: snake.setDirection('y', -1); break;   // change directon    
        case KEY_DOWN: snake.setDirection('y', 1); break;  
        case KEY_LEFT: snake.setDirection('x', -1); break;  
        case KEY_RIGHT: snake.setDirection('x', 1); break; 
        case EXIT: board.changeStatus(); break;            // escape sequence
        default: break;
    }
    keypad(stdscr, FALSE); // turn on function keys
    snake.move();          // moves snake even if no keypress
    endwin();              // free memory and end curses mode
}
// Function to test the game rules for eating and collisions //
void Logic(Food& food, Snake& snake, bool rock)
{
    if (snake.headX()==food.foodX() && snake.headY()==food.foodY()) { // Eats food get new food
        food.newFood();      

        if (rock) {             // Rocks present in Mamba.. avoid
            validatePos(food, snake);
        } else {
            while (snake.bodyPosition(food.foodX(), food.foodY()))
                food.newFood();
        }

        snake.grow();           // Increase length
        board.increaseScore();  // Increase score
    }
    else if (snake.collision()) { // Hit wall/self/rock 
        board.changeStatus();     // Game over status
        napms(1000);              // 1 sec nap
    }
}
// Function for console output using ASCII art //
void prompts(string choice)
{
    if (choice == "Snake Game") {
        cout 
             << "\t\t   ____          __         _____              " << endl
             << "\t\t  / __/__  ___ _/ /_____   / ___/__ ___ _  ___     " << endl
             << "\t\t _\\ \\/ _ \\/ _ `/  '_/ -_) / (_ / _ `/  ' \\/ -_)" << endl
             << "\t\t/___/_//_/\\_,_/_/\\_\\\\__/  \\___/\\_,_/_/_/_/\\__/" << endl << endl;
    }
    else if (choice == "Game Over") {
        cout 
             << "\t\t  _____                 ____                " << endl
             << "\t\t / ___/__  __ _  ___   / __ \\_  _____ ____ " << endl
             << "\t\t/ (_ / _ `/  ' \\/ -_) / /_/ / |/ / -_) __/ " << endl
             << "\t\t\\___/\\_,_/_/_/_/\\__/  \\____/|___/\\__/_/" << endl 
             << endl;
    }
    else if (choice == "Rules") {
        cout << "\t\t  Viper\t\t\t\t\t     Mamba\n"
            << "* * * * * * * * * * * * * * * * * * * * *   * * * * * * * * * * * * * * * * * * * * *\n"
            << "* Type Viper for this choice...         *   * Type Mamba for this choice...         *\n"
            << "*                                       *   *                                       *\n"
            << "* Follows Standard Rules:               *   * Follows Custom Rules:                 *\n"
            << "*  > Wall or Self collision ends game   *   *  > Self or Rock collision ends game   *\n"
            << "*  > Viper moves at normal speed        *   *  > Mamba is twice as fast as Viper    *\n"
            << "*  > Cannot pass through walls          *   *  > Ability to go through walls!       *\n"
            << "*  > Food objects are an 'x'            *   *  > Food objects are an 'x'            *\n"
            << "*                                       *   *  > Rocks appear as an '##'            *\n"
            << "* * * * * * * * * * * * * * * * * * * * *   * * * * * * * * * * * * * * * * * * * * *\n"
            << endl;
    }
}
// Function for checking the players score against current high scores //
void checkPlayerScore (FileIO& file, vector<Player>& highScores, string name)
{
    for (int i=0; i < highScores.size(); i++) {
        if (highScores[i].playerScore() < board.getScore() ) {
            Player player(name, board.getScore()); // creates player object
            vector<Player>::iterator it;
            it = highScores.begin()+i;      // position to be added
            highScores.insert(it, player);  // insert new high score
            file.write(highScores);         // update file
            break;
        }
    }
}
// Function for scoreboared output //
void scoreboard(vector<Player>& highScores)
{
    cout << "\t\t\t *---------------------*" << endl;
    cout << left << setw(15) << "\t\t\t |     High Scores     |" << endl;
    cout << "\t\t\t *---------------------*" << endl;
    for(int i=0; i < highScores.size(); i++) {
        cout << "\t\t\t  " << left << setw(17) << highScores[i].playerName(); 
        cout << "  " << highScores[i].playerScore() <<  endl;
    }
    cout << endl << endl;
}
// Helper function for Render() //
void drawEdge() // util draw funciton
{
    cout << "\t\t";
    for (int i = 0; i < board.getArea()+2; i++)
        cout << "* ";
    cout << endl;
}
// Helper funciton for ncurses setup used in Input() //
void utilSetup()
{
    initscr();       // initialize curses mode 
    raw();           // line buffering
    curs_set(FALSE); // set cursor
    flushinp();      // flushes stream
    keypad(stdscr, TRUE); // turn on function keys
    noecho();        // turn off echo for getch()
}
// Function for input validation //
string validateInput(string type) {
    while (type != "Viper" && type != "Mamba") {
        clearScreen();
        prompts("Snake Game"); // ASCII Snake Game prompt
        prompts("Rules");      // Game rules prompt
        cout << "\t\tTry agian, would you like to play as a \"Viper\" or \"Mamba\"?  ";
        cin >> type;
    }
    return type;
}
// Function for checking food position on Mamba board //
void validatePos(Food& food, Snake& snake) 
{   
    while (food.foodX() == 5 && food.foodY() == 4   // rock positions 
         ||food.foodX() == 15 && food.foodY()== 14 
         ||food.foodX() == 3 && food.foodY() == 16)
    {
        food.newFood(); 
        if ((snake.bodyPosition(food.foodX(), food.foodY()))) // snakes position
            validatePos(food, snake); // recursively call 
    }
}
// Cross platform system clear //
void clearScreen()
{
#ifdef WINDOWS
    std::system("cls");
#else
    std::system ("clear");
#endif
}