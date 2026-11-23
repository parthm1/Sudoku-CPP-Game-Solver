//Title: Sudoku
//Description: Sudoku is a logic-based, combinatorial number-placement puzzle. The objective is to fill a 9 × 9 grid with digits so that each column, each row, and each of the nine 3 × 3 subgrids that compose the grid contain all of the digits from 1 to 9.
//Date created: 1 september, 2022
//Date last modified: 1 November, 2022
//Author: Parth Madan
//Known limitations: please choose/enter alphabets from the bracket or the game might crash


#include <iostream>
using namespace std;

// declared 12 multidimensional arrays, 2 arrays for each grid in which one of them I output to the user to fill in and the other one with answer key to check user's placements. there are two grids for all modes(easy,ameteur,hard). There are two grids for each level

// amateur level first puzzle gird
int Gridamateurans[9][9] = { {7,9,1,5,2,3,8,6,4},            // answer key
                        {4,2,5,6,8,7,1,3,9},
                        {8,6,3,9,1,4,2,7,5},
                        {2,3,4,1,5,9,7,8,6},
                        {9,1,7,8,4,6,5,2,3},
                        {6,5,8,7,3,2,4,9,1},
                        {1,4,6,2,9,8,3,5,7},
                        {3,7,2,4,6,5,9,1,8},
                        {5,8,9,3,7,1,6,4,2} };

int Gridamateur [9][9] = { {0,0,0,0,0,3,0,0,4},            // grid to fill in
                    {4,0,5,0,0,0,1,0,0},
                    {0,0,0,9,1,0,0,7,0},
                    {2,3,0,0,5,0,7,0,0},
                    {0,1,0,8,0,6,0,2,0},
                    {0,0,8,0,3,0,0,9,1},
                    {0,4,0,0,9,8,0,0,0},
                    {0,0,2,0,0,0,9,0,8},
                    {5,0,0,3,0,0,0,0,0} };

// amateur level second puzzle grid
int Gridamateur2ans[9][9] = { {2,1,7,4,5,6,3,8,9},
                     {8,6,5,7,3,9,1,2,4},
                     {3,4,9,8,1,2,7,6,5},
                     {5,9,6,3,4,8,2,1,7},
                     {7,2,3,6,9,1,4,5,8},
                     {1,8,4,5,2,7,6,9,3},
                     {6,7,2,9,8,4,5,3,1},
                     {9,5,1,2,7,3,8,4,6},
                     {4,3,8,1,6,5,9,7,2} };

int Gridamateur2[9][9] = { {0,1,0,0,0,6,0,0,9},
                    {8,0,0,7,3,0,0,0,0},
                    {3,4,0,0,0,0,0,0,5},
                    {0,9,0,0,4,0,0,1,0},
                    {0,2,0,6,0,1,0,5,0},
                    {0,8,0,0,2,0,0,9,0},
                    {6,0,0,0,0,0,0,3,1},
                    {0,0,0,0,7,3,0,0,6},
                    {4,0,0,1,0,0,0,7,0} };

// easy level first puzzle grid
int Grideasyans[9][9] = { {8,2,5,6,4,7,9,1,3},
                        {6,9,3,1,5,2,7,8,4},
                        {4,7,1,3,9,8,6,5,2},
                        {3,1,7,8,6,4,2,9,5},
                        {9,5,8,2,1,3,4,7,6},
                        {2,6,4,9,7,5,1,3,8},
                        {1,4,9,5,3,6,8,2,7},
                        {5,8,6,7,2,1,3,4,9},
                        {7,3,2,4,8,9,5,6,1} };

int Grideasy[9][9] = { {0,0,5,0,4,0,9,0,3},
                    {6,9,0,1,0,2,7,0,0},
                    {0,0,1,3,9,0,6,0,0},
                    {3,0,0,0,6,0,0,0,5},
                    {0,0,0,0,0,0,0,0,0},
                    {2,0,0,0,7,0,0,0,8},
                    {0,0,9,0,3,6,8,0,0},
                    {0,0,6,7,0,1,0,4,9},
                    {7,0,2,0,8,0,5,0,0} };

// easy level second puzzle grid
int Grideasy2ans[9][9] = { {7,6,3,5,8,1,4,2,9},
                     {4,1,5,2,6,9,3,7,8},
                     {9,2,8,4,7,3,5,6,1},
                     {1,5,7,6,9,4,8,3,2},
                     {3,9,6,8,1,2,7,4,5},
                     {2,8,4,3,5,7,1,9,6},
                     {8,3,1,9,4,6,2,5,7},
                     {6,7,2,1,3,5,9,8,4},
                     {5,4,9,7,2,8,6,1,3} };

int Grideasy2[9][9] = { {0,6,0,0,8,0,4,2,0},
                    {0,1,5,0,6,0,3,7,8},
                    {0,0,0,4,0,0,0,6,0},
                    {1,0,0,6,0,4,8,3,0},
                    {3,0,6,8,1,0,7,0,5},
                    {0,8,0,3,5,0,0,0,0},
                    {8,3,0,9,4,0,0,0,0},
                    {0,7,2,1,3,0,9,0,0},
                    {0,0,9,0,2,0,6,1,0} };

// hard level first puzzle grid
int Gridhardans[9][9] = { {8,6,1,4,9,2,7,5,3},
                        {7,9,4,5,3,6,8,1,2},
                        {5,3,2,8,7,1,4,9,6},
                        {6,1,7,9,2,8,3,4,5},
                        {9,4,8,3,6,5,1,2,7},
                        {3,2,5,1,4,7,9,6,8},
                        {1,5,6,7,8,4,2,3,9},
                        {2,8,3,6,1,9,5,7,4},
                        {4,7,9,2,5,3,6,8,1} };

int Gridhard[9][9] = { {0,6,0,0,0,0,7,5,0},
                    {0,0,0,0,3,6,8,0,0},
                    {0,0,2,8,0,0,4,0,0},
                    {0,0,0,0,2,0,0,0,5},
                    {9,0,8,0,0,0,1,0,7},
                    {3,0,0,0,4,0,0,0,0},
                    {0,0,6,0,0,4,2,0,0},
                    {0,0,3,6,1,0,0,0,0},
                    {0,7,9,0,0,0,0,8,0} };
    
// hard level second grid
int Gridhard2ans[9][9] = { {7,3,9,6,4,5,2,8,1},
                        {8,5,2,1,7,3,4,9,6},
                        {1,4,6,8,9,2,3,5,7},
                        {9,1,5,3,8,4,6,7,2},
                        {6,8,3,2,1,7,9,4,5},
                        {4,2,7,5,6,9,1,3,8},
                        {2,9,4,7,5,6,8,1,3},
                        {5,6,1,4,3,8,7,2,9},
                        {3,7,8,9,2,1,5,6,4} };

int Gridhard2[9][9] = { {0,0,9,6,0,0,2,0,1},
                    {0,0,0,0,0,3,0,9,0},
                    {0,0,0,8,0,2,0,0,0},
                    {0,1,0,0,0,4,6,7,2},
                    {0,0,0,0,0,0,0,0,0},
                    {4,2,7,5,0,0,0,3,0},
                    {0,0,0,7,0,6,0,0,0},
                    {0,6,0,4,0,0,0,0,0},
                    {3,0,8,0,0,1,5,0,0} };

// these two multidimensional arrays are to basically get copied by the arrays with grids from the level of grid which the user wants to play
int Grid[9][9];

int Gridans[9][9];

// declared variables to use them in the future
int column;
int row;
int placenum;
char mode = 'E';
int correct;
string Continue;
int hintnum;
int num = 1;
int usergrid;
int incgrid;
int mistakes;
char hint = 'h';
bool hintstop = false;
bool hintnone = false;
char reset = 'y';
bool gameover = false;
int findgrid;

// declared this full meal deal function
int placemark(int a, int b, int c) {       // this function takes in the column, row, and the placing number from the use with help of parameters and place the number. it also helps to determine if it is correct or not
    usergrid = Grid[a - 1][b - 1] = c;            // placing number
    
    if (Grid[a - 1][b - 1] == Gridans[a - 1][b - 1]){              // if the user's number matches to the answer key array then it is correct
        cout << "           correct! \n";
        num += 1;
    }
    else if (Grid[a - 1][b - 1] != Gridans[a - 1][b - 1]){           // if the user's number doesnt match to the answer key array then it is incorrect
        cout << "           incorrect \n";
        mistakes -= 1;
        incgrid = Grid[a - 1][b - 1] = 0;
    }
    else {                             // if none, then error
        cout << "           Error";
    }
    return 0;
}


void gridoutput() {             // this function outputs the sudoku grid that changes as the user enters number.
    cout << "                  Mistakes: " << mistakes << "                        Hints "<< hintnum << " \n";     // it also outputs mistakes and hints user can have and make and decreases as the user uses them
    cout << "           *************************************************************** \n";
    cout << "           *   " << Grid[0][0] << "  |  " << Grid[0][1] << "  |  " << Grid[0][2] << "   ||   " << Grid[0][3] << "  |  " << Grid[0][4] << "  |  " << Grid[0][5] << "   ||   " << Grid[0][6] << "  |  " << Grid[0][7] << "  |  " << Grid[0][8] << "   *\n";
    cout << "           *   " << Grid[1][0] << "  |  " << Grid[1][1] << "  |  " << Grid[1][2] << "   ||   " << Grid[1][3] << "  |  " << Grid[1][4] << "  |  " << Grid[1][5] << "   ||   " << Grid[1][6] << "  |  " << Grid[1][7] << "  |  " << Grid[1][8] << "   *\n";
    cout << "           *   " << Grid[2][0] << "  |  " << Grid[2][1] << "  |  " << Grid[2][2] << "   ||   " << Grid[2][3] << "  |  " << Grid[2][4] << "  |  " << Grid[2][5] << "   ||   " << Grid[2][6] << "  |  " << Grid[2][7] << "  |  " << Grid[2][8] << "   *\n";
    cout << "           *   " << Grid[3][0] << "  |  " << Grid[3][1] << "  |  " << Grid[3][2] << "   ||   " << Grid[3][3] << "  |  " << Grid[3][4] << "  |  " << Grid[3][5] << "   ||   " << Grid[3][6] << "  |  " << Grid[3][7] << "  |  " << Grid[3][8] << "   *\n";
    cout << "           *   " << Grid[4][0] << "  |  " << Grid[4][1] << "  |  " << Grid[4][2] << "   ||   " << Grid[4][3] << "  |  " << Grid[4][4] << "  |  " << Grid[4][5] << "   ||   " << Grid[4][6] << "  |  " << Grid[4][7] << "  |  " << Grid[4][8] << "   *\n";
    cout << "           *   " << Grid[5][0] << "  |  " << Grid[5][1] << "  |  " << Grid[5][2] << "   ||   " << Grid[5][3] << "  |  " << Grid[5][4] << "  |  " << Grid[5][5] << "   ||   " << Grid[5][6] << "  |  " << Grid[5][7] << "  |  " << Grid[5][8] << "   *\n";
    cout << "           *   " << Grid[6][0] << "  |  " << Grid[6][1] << "  |  " << Grid[6][2] << "   ||   " << Grid[6][3] << "  |  " << Grid[6][4] << "  |  " << Grid[6][5] << "   ||   " << Grid[6][6] << "  |  " << Grid[6][7] << "  |  " << Grid[6][8] << "   *\n";
    cout << "           *   " << Grid[7][0] << "  |  " << Grid[7][1] << "  |  " << Grid[7][2] << "   ||   " << Grid[7][3] << "  |  " << Grid[7][4] << "  |  " << Grid[7][5] << "   ||   " << Grid[7][6] << "  |  " << Grid[7][7] << "  |  " << Grid[7][8] << "   *\n";
    cout << "           *   " << Grid[8][0] << "  |  " << Grid[8][1] << "  |  " << Grid[8][2] << "   ||   " << Grid[8][3] << "  |  " << Grid[8][4] << "  |  " << Grid[8][5] << "   ||   " << Grid[8][6] << "  |  " << Grid[8][7] << "  |  " << Grid[8][8] << "   *\n";
    cout << "           *************************************************************** \n";
}

class allgrids {       // this class is used for all grids.
    public:         // making the variables public
        int numistakes;            // helps to store number of mistakes user can make based on the level of puzzle
        int question;              // helps to store number of zero's or amount of grids user have to fill in each grid
        int hints;                  // helps to store number of hints user has based on the level of puzzle
};


int main()
{
    // displays the title of the game
    cout << "         _______. __    __   _______   ______    __  ___  __    __        \n";
    cout << "         /       ||  |  |  | |       \\ /  __  \\  |  |/  / |  |  |  |          \n";
    cout << "        |   (----`|  |  |  | |  .--.  |  |  |  | |  '  /  |  |  |  |         \n";
    cout << "         \\   \\    |  |  |  | |  |  |  |  |  |  | |    <   |  |  |  |         \n";
    cout << "     .----)   |   |  `--'  | |  '--'  |  `--'  | |  .  \\  |  `--'  |      \n";
    cout << "     |_______/     \\______/  |_______/ \\______/  |__|\\__\\  \\______/           \n\n";

    // displays basic rules of the game to the user, after reading they are supposed to press a key to continue
    cout << "                                   Rules: \n\n";
    cout << "           1) Each row must contain the numbers from 1 to 9, without repetitions \n";
    cout << "           2) Each column must contain the numbers from 1 to 9, without repetition \n";
    cout << "           3) Choose/enter options from the brackets \n";
    cout << "           4) Press any key to continue ... ";
    cin >> Continue;
    
    // I wrote a bunch of random letters in this if statement to start the game if they dont enter this word which the user probably wont
    if (Continue != "ttttthththththththththhtthhtthhffhfuhfuhfuhuffuhfuh"){      // if the dont enter this word, then start the game
        
        // displaying all the modes in this game
        cout << "\n\n";
        cout << "                                  EASY MODE(E) \n";
        cout << "                                 AMATEUR MODE(A) \n";
        cout << "                                  HARD MODE(H) \n";
        cout << "\n\n";
        
        // assigning objects to the classes
        allgrids easy;       // created an object of the class for first puzzle of easy mode
        // accessing attributes and set values
        easy.numistakes = 5;     // number of mistakes in the puzzle
        easy.question = 49;       // number of grids to fill in the puzzle
        easy.hints = 3;         // number of hints the user has in the puzzles
        
        allgrids easy2;
        easy2.numistakes = 5;
        easy2.question = 42;
        easy2.hints = 3;
        
        allgrids amateur;
        amateur.numistakes = 4;
        amateur.question = 53;
        amateur.hints = 2;
        
        allgrids amateur2;
        amateur2.numistakes = 4;
        amateur2.question = 53;
        amateur2.hints = 2;
        
        allgrids hard;
        hard.numistakes = 3;
        hard.question = 55;
        hard.hints = 1;
        
        allgrids hard2;
        hard2.numistakes = 3;
        hard2.question = 55;
        hard2.hints = 1;
        
        // asking user what mode the user wants to play (easy, amateur, hard)
        cout << "           What mode would you like to play (E/A/H)? ";
        cin >> mode;
        // this while loops keeps asking the user to enter mode until they enter incorrect option for mode
        while (mode != 'e' && mode != 'E' && mode != 'a' && mode != 'A' && mode != 'h' && mode != 'H'){
            cout << "           Invalid option, try again \n";
            cout << "           What mode would you like to play (E/A/H)? ";
            cin >> mode;
        }
        cout << "\n\n";
        
        if(mode == 'e'|| mode == 'E'){        // if user chooses easy mode then ...
            srand (time(NULL));
            findgrid = (rand() % 2) + 1;             // this random function generates a number between 1 and 2 to help me choose a puzzle between 2 puzzles in easy level
        
            if(findgrid == 1) {        // if the random gets 1, means first puzzle in the easy grid
                correct = easy.question;        // saving classes in a common variable
                hintnum = easy.hints;
                mistakes = easy.numistakes;
                
                for (int i = 0; i <= 8; i++){        // this for loops helps to save the array with numbers to a common array
                    Grid[i][0] = Grideasy[i][0];
                    Grid[i][1] = Grideasy[i][1];
                    Grid[i][2] = Grideasy[i][2];
                    Grid[i][3] = Grideasy[i][3];
                    Grid[i][4] = Grideasy[i][4];
                    Grid[i][5] = Grideasy[i][5];
                    Grid[i][6] = Grideasy[i][6];
                    Grid[i][7] = Grideasy[i][7];
                    Grid[i][8] = Grideasy[i][8];
                    
                    Gridans[i][0] = Grideasyans[i][0];
                    Gridans[i][1] = Grideasyans[i][1];
                    Gridans[i][2] = Grideasyans[i][2];
                    Gridans[i][3] = Grideasyans[i][3];
                    Gridans[i][4] = Grideasyans[i][4];
                    Gridans[i][5] = Grideasyans[i][5];
                    Gridans[i][6] = Grideasyans[i][6];
                    Gridans[i][7] = Grideasyans[i][7];
                    Gridans[i][8] = Grideasyans[i][8];
                }
                cout << "           You can make upto " << easy.numistakes << " mistakes \n";        // outputting the number of mistakes and hints user has based on their level
                cout << "           You can get upto " << easy.hints << " hints \n";
            }
            else if(findgrid == 2) {        // if the random gets 2, means second puzzle in the easy grid
                correct = easy2.question;
                hintnum = easy2.hints;
                mistakes = easy2.numistakes;
                
                for (int j = 0; j <= 8; j++){
                    Grid[j][0] = Grideasy2[j][0];
                    Grid[j][1] = Grideasy2[j][1];
                    Grid[j][2] = Grideasy2[j][2];
                    Grid[j][3] = Grideasy2[j][3];
                    Grid[j][4] = Grideasy2[j][4];
                    Grid[j][5] = Grideasy2[j][5];
                    Grid[j][6] = Grideasy2[j][6];
                    Grid[j][7] = Grideasy2[j][7];
                    Grid[j][8] = Grideasy2[j][8];
                    
                    Gridans[j][0] = Grideasy2ans[j][0];
                    Gridans[j][1] = Grideasy2ans[j][1];
                    Gridans[j][2] = Grideasy2ans[j][2];
                    Gridans[j][3] = Grideasy2ans[j][3];
                    Gridans[j][4] = Grideasy2ans[j][4];
                    Gridans[j][5] = Grideasy2ans[j][5];
                    Gridans[j][6] = Grideasy2ans[j][6];
                    Gridans[j][7] = Grideasy2ans[j][7];
                    Gridans[j][8] = Grideasy2ans[j][8];
                }
                cout << "           You can make upto " << easy2.numistakes << " mistakes \n";
                cout << "           You can get upto " << easy2.hints << " hints \n";
            }
        }
        else if (mode == 'a'|| mode == 'A'){      // if the user chooses amateur mode then ...
            srand (time(NULL));
            int findgrid = rand() %(4-3 +1)+3;                 // this random function generates a number between 3 and 4 to help me choose a puzzle between 2 puzzles in amateur level
            
            if(findgrid == 3) {              // if the random gets 3, means first puzzle in the amateur grid
                correct = amateur.question;
                hintnum = amateur.hints;
                mistakes = amateur.numistakes;
                
                for (int i = 0; i <= 8; i++){
                    Grid[i][0] = Gridamateur[i][0];
                    Grid[i][1] = Gridamateur[i][1];
                    Grid[i][2] = Gridamateur[i][2];
                    Grid[i][3] = Gridamateur[i][3];
                    Grid[i][4] = Gridamateur[i][4];
                    Grid[i][5] = Gridamateur[i][5];
                    Grid[i][6] = Gridamateur[i][6];
                    Grid[i][7] = Gridamateur[i][7];
                    Grid[i][8] = Gridamateur[i][8];
                    
                    Gridans[i][0] = Gridamateurans[i][0];
                    Gridans[i][1] = Gridamateurans[i][1];
                    Gridans[i][2] = Gridamateurans[i][2];
                    Gridans[i][3] = Gridamateurans[i][3];
                    Gridans[i][4] = Gridamateurans[i][4];
                    Gridans[i][5] = Gridamateurans[i][5];
                    Gridans[i][6] = Gridamateurans[i][6];
                    Gridans[i][7] = Gridamateurans[i][7];
                    Gridans[i][8] = Gridamateurans[i][8];
                }
                cout << "           You can make upto " << amateur.numistakes << " mistakes \n";
                cout << "           You can get upto " << amateur.hints << " hints \n";
            }
            else if(findgrid == 4) {            // if the random gets 4, means second puzzle in the amateur grid
                correct = amateur2.question;
                hintnum = amateur2.hints;
                mistakes = amateur2.numistakes;
                
                for (int i = 0; i <= 8; i++){
                    Grid[i][0] = Gridamateur2[i][0];
                    Grid[i][1] = Gridamateur2[i][1];
                    Grid[i][2] = Gridamateur2[i][2];
                    Grid[i][3] = Gridamateur2[i][3];
                    Grid[i][4] = Gridamateur2[i][4];
                    Grid[i][5] = Gridamateur2[i][5];
                    Grid[i][6] = Gridamateur2[i][6];
                    Grid[i][7] = Gridamateur2[i][7];
                    Grid[i][8] = Gridamateur2[i][8];
                    
                    Gridans[i][0] = Gridamateur2ans[i][0];
                    Gridans[i][1] = Gridamateur2ans[i][1];
                    Gridans[i][2] = Gridamateur2ans[i][2];
                    Gridans[i][3] = Gridamateur2ans[i][3];
                    Gridans[i][4] = Gridamateur2ans[i][4];
                    Gridans[i][5] = Gridamateur2ans[i][5];
                    Gridans[i][6] = Gridamateur2ans[i][6];
                    Gridans[i][7] = Gridamateur2ans[i][7];
                    Gridans[i][8] = Gridamateur2ans[i][8];
                }
                cout << "           You can make upto " << amateur2.numistakes << " mistakes \n";
                cout << "           You can get upto " << amateur2.hints << " hints \n";
            }
            
        }
        else if (mode == 'h'|| mode == 'H'){              // if the user chooses hard mode then ...
            srand (time(NULL));
            int findgrid = rand() %(6-5 +1)+5;          // this random function generates a number between 5 and 6 to help me choose a puzzle between 2 puzzles in hard level
            
            if(findgrid == 5) {                 // if the random gets 5, means first puzzle in the hard grid
                correct = hard.question;
                hintnum = hard.hints;
                mistakes = hard.numistakes;
                
                for (int k = 0; k <= 8; k++){
                    Grid[k][0] = Gridhard[k][0];
                    Grid[k][1] = Gridhard[k][1];
                    Grid[k][2] = Gridhard[k][2];
                    Grid[k][3] = Gridhard[k][3];
                    Grid[k][4] = Gridhard[k][4];
                    Grid[k][5] = Gridhard[k][5];
                    Grid[k][6] = Gridhard[k][6];
                    Grid[k][7] = Gridhard[k][7];
                    Grid[k][8] = Gridhard[k][8];
                    
                    Gridans[k][0] = Gridhardans[k][0];
                    Gridans[k][1] = Gridhardans[k][1];
                    Gridans[k][2] = Gridhardans[k][2];
                    Gridans[k][3] = Gridhardans[k][3];
                    Gridans[k][4] = Gridhardans[k][4];
                    Gridans[k][5] = Gridhardans[k][5];
                    Gridans[k][6] = Gridhardans[k][6];
                    Gridans[k][7] = Gridhardans[k][7];
                    Gridans[k][8] = Gridhardans[k][8];
                }
                cout << "           You can make upto " << hard.numistakes << " mistakes \n";
                cout << "           You can get upto " << hard.hints << " hints \n";
            }
            else if(findgrid == 6) {            // if the random gets 6, means second puzzle in the hard grid
                correct = hard2.question;
                hintnum = hard2.hints;
                mistakes = hard2.numistakes;
                
                for (int i = 0; i <= 8; i++){
                    Grid[i][0] = Gridhard2[i][0];
                    Grid[i][1] = Gridhard2[i][1];
                    Grid[i][2] = Gridhard2[i][2];
                    Grid[i][3] = Gridhard2[i][3];
                    Grid[i][4] = Gridhard2[i][4];
                    Grid[i][5] = Gridhard2[i][5];
                    Grid[i][6] = Gridhard2[i][6];
                    Grid[i][7] = Gridhard2[i][7];
                    Grid[i][8] = Gridhard2[i][8];
                    
                    Gridans[i][0] = Gridhard2ans[i][0];
                    Gridans[i][1] = Gridhard2ans[i][1];
                    Gridans[i][2] = Gridhard2ans[i][2];
                    Gridans[i][3] = Gridhard2ans[i][3];
                    Gridans[i][4] = Gridhard2ans[i][4];
                    Gridans[i][5] = Gridhard2ans[i][5];
                    Gridans[i][6] = Gridhard2ans[i][6];
                    Gridans[i][7] = Gridhard2ans[i][7];
                    Gridans[i][8] = Gridhard2ans[i][8];
                }
                cout << "           You can make upto " << hard2.numistakes << " mistakes \n";
                cout << "           You can get upto " << hard2.hints << " hints \n";
            }
        }
        
        cout << "           Please enter on the places where 0's are placed \n\n";
        
        gridoutput();      // outputs the puzzle
        
        
        while (num <= correct && mistakes >= 1){        // this while loops keeps the game going until # of mistakes gets to 1 and all grids are filled correctly
            while (reset== 'y' || reset == 'Y'){        //  this while loops restarts the game if the user wants to play it again
                
                if(hintnum >= 0 && hintnone == false){       // if the user has hints left then give them option for a hint
                    hintstop = false;
                    cout << "           Enter 'H' for a hints and 'N' for none ";       // asking for hints
                    cin >> hint;
                    while(hint != 'H' && hint != 'h'&& hint != 'N' && hint != 'n'){          // if user enters an invalid option then ask again
                        cout << "           Invalid, enter (H/N): ";
                        cin >> hint;
                    }
                
                    if(hint == 'H' || hint == 'h') {      // if the user asks for a hint then ...
                        hintnum -= 1;      // suntract 1 hint from the variable
                        if (hintnum <= 0){       // if hints are get to zero, then true so that the used doesnt get more hints
                            hintnone = true;
                        }
                        hintstop = true; //    // if user takes a hint then hintstop is true so that it doesnt ask for column and row again
                        cout << "           Enter the details asked and you will get the answer: \n";
                        cout << "           Enter column number (1-9): ";       // asking for column
                        cin >> column;
                        while (column > 9 || column <= 0){          // if the user enters an invalid number then ask again
                            cout << "           Invalid column number, enter again: ";
                            cin >> column;
                        }
                        cout << "           Enter row number (1-9): ";        // asking for row
                        cin >> row;
                        while (row > 9 || row <= 0){
                            cout << "           Invalid row number, enter again: ";        // if the user enters an invalid number then ask again
                            cin >> row;
                        }
                        while (Grid[column - 1][row - 1] != 0){           // if the user's choice of grid is already filled then ask them to enter again
                            cout << "           grid already taken, try again: \n\n";
                                
                            cout << "           Enter column number (1-9): ";
                            cin >> column;
                            while (column > 9 || column <= 0){
                                cout << "           Invalid column number, enter again: ";
                                cin >> column;
                            }
                            cout << "           Enter row number (1-9): ";
                            cin >> row;
                            while (row > 9 || row <= 0){
                                cout << "           Invalid row number, enter again: ";
                                cin >> row;
                            }
                        }
                        
                        usergrid = Grid[column - 1][row - 1] = Gridans[column - 1][row - 1];        // entering the key to the grid of the puzzle using column and row
                        
                        cout << "           Column: " << column << " Row: " << row << " Number: " << Gridans[column - 1][row - 1] << " \n\n";    // displaying the key of the grid to the user
                        
                        gridoutput();     // displaying the puzzle
                    }
                }
            
                if(hintstop == false || hintnone == true){           // if hintstop is false meaning the user did not take hint or user doesnt have any hints left then...
                    cout << "           Enter column number (1-9): ";     // asking for column
                    cin >> column;
                    while (column > 9 || column <= 0){               // while user enters invalid number, ask again
                        cout << "           Invalid column number, enter again: ";
                        cin >> column;
                    }
                    cout << "           Enter row number (1-9): ";       // asking for row
                    cin >> row;
                    while (row > 9 || row <= 0){
                        cout << "           Invalid row number, enter again: ";
                        cin >> row;
                    }
                    while (Grid[column - 1][row - 1] != 0){             // if the user's choice of grid is already filled then ask them to enter again
                        cout << "           grid already taken, try again: \n\n";
                                
                        cout << "           Enter column number (1-9): ";
                        cin >> column;
                        while (column > 9 || column <= 0){
                            cout << "           Invalid column number, enter again: \n";
                            cin >> column;
                        }
                        cout << "           Enter row number (1-9): ";
                        cin >> row;
                        while (row > 9 || row <= 0){
                            cout << "           Invalid row 2number, enter again: ";
                            cin >> row;
                        }
                    }
                    cout << "           Enter number (1-9): ";          //  asling to enter the number the user want to fill in
                    cin >> placenum;
                    while (placenum > 9 || placenum <= 0){            // while user enters invalid number, ask again
                        cout << "           Invalid number, enter again: ";
                        cin >> placenum;
                    }
                    placemark(column,row,placenum);      // calling this function to place them number in the grid using parameters
                    if (mistakes >= 1){          // outputs the puzzle if mistakes are over 1 meaning the game is not over
                        gridoutput();
                    }
                    
                    if(num == correct ){       // if users fills all grids correctly, then gameover becomes true
                        gameover = true;
                    }
                    
                    if(mistakes < 1){  // if the user makes mistakes allocated to them according to the level, then...
                        // these if statements announce the users that they have lost the game
                        if (mode == 'e' || mode == 'E'){
                            cout << "           You made " << easy.numistakes << " mistakes and lost the game  \n\n";
                        }
                        else if (mode == 'a'|| mode == 'A'){
                            cout << "           You made " << amateur.numistakes << " mistakes and lost the game \n\n";
                        }
                        else if (mode == 'h' || mode == 'H'){
                            cout << "           You made " << hard.numistakes << " mistakes and lost the game  \n\n";
                        }
                        cout << "           This is the key to the puzzle \n\n";      //  displaying the key to puzzle using for loop
                        cout << "           *************************************************************** \n";
                        for (int n = 0; n <= 8; n++) {
                            cout << "           *   " << Gridans[n][0] << "  |  " << Gridans[n][1] << "  |  " << Gridans[n][2] << "   ||   " << Gridans[n][3] << "  |  " << Gridans[n][4] << "  |  " << Gridans[n][5] << "   ||   " << Gridans[n][6] << "  |  " << Gridans[n][7] << "  |  " << Gridans[n][8] << "   *\n";
                        }
                        cout << "           *************************************************************** \n";
                    }
                    else if (gameover == true) {        // if the user filled all grids correctly, they win the game
                        cout << "           You won the game!! \n";
                    }
                    
                    if (mistakes < 1 || gameover == true){      // if the user won or lost, ask them to play again
                        cout << "\n\n";
                        cout << "           Would you like to play again (Y/N)? ";
                        cin >> reset;
                        
                        if (reset == 'y' || reset == 'Y'){    // if the users wants to replay then ...
                            hintstop = false;  // reseting the boolean variables
                            hintnone = false;
                            gameover = false;
                            cout << "\n\n\n";
                            cout << "           What mode would you like to play (E/A/H)? ";        // asking for mode again
                            cin >> mode;
                            
                            if(mode == 'e'|| mode == 'E'){        // if user chooses easy mode then ...
                                srand (time(NULL));
                                findgrid = (rand() % 2) + 1;             // this random function generates a number between 1 and 2 to help me choose a puzzle between 2 puzzles in easy level
                            
                                if(findgrid == 1) {        // if the random gets 1, means first puzzle in the easy grid
                                    correct = easy.question;        // saving classes in a common variable
                                    hintnum = easy.hints;
                                    mistakes = easy.numistakes;
                                    
                                    for (int i = 0; i <= 8; i++){        // this for loops helps to save the array with numbers to a common array
                                        Grid[i][0] = Grideasy[i][0];
                                        Grid[i][1] = Grideasy[i][1];
                                        Grid[i][2] = Grideasy[i][2];
                                        Grid[i][3] = Grideasy[i][3];
                                        Grid[i][4] = Grideasy[i][4];
                                        Grid[i][5] = Grideasy[i][5];
                                        Grid[i][6] = Grideasy[i][6];
                                        Grid[i][7] = Grideasy[i][7];
                                        Grid[i][8] = Grideasy[i][8];
                                        
                                        Gridans[i][0] = Grideasyans[i][0];
                                        Gridans[i][1] = Grideasyans[i][1];
                                        Gridans[i][2] = Grideasyans[i][2];
                                        Gridans[i][3] = Grideasyans[i][3];
                                        Gridans[i][4] = Grideasyans[i][4];
                                        Gridans[i][5] = Grideasyans[i][5];
                                        Gridans[i][6] = Grideasyans[i][6];
                                        Gridans[i][7] = Grideasyans[i][7];
                                        Gridans[i][8] = Grideasyans[i][8];
                                    }
                                    cout << "           You can make upto " << easy.numistakes << " mistakes \n";        // outputting the number of mistakes and hints user has based on their level
                                    cout << "           You can get upto " << easy.hints << " hints \n";
                                }
                                else if(findgrid == 2) {        // if the random gets 2, means second puzzle in the easy grid
                                    correct = easy2.question;
                                    hintnum = easy2.hints;
                                    mistakes = easy2.numistakes;
                                    
                                    for (int j = 0; j <= 8; j++){
                                        Grid[j][0] = Grideasy2[j][0];
                                        Grid[j][1] = Grideasy2[j][1];
                                        Grid[j][2] = Grideasy2[j][2];
                                        Grid[j][3] = Grideasy2[j][3];
                                        Grid[j][4] = Grideasy2[j][4];
                                        Grid[j][5] = Grideasy2[j][5];
                                        Grid[j][6] = Grideasy2[j][6];
                                        Grid[j][7] = Grideasy2[j][7];
                                        Grid[j][8] = Grideasy2[j][8];
                                        
                                        Gridans[j][0] = Grideasy2ans[j][0];
                                        Gridans[j][1] = Grideasy2ans[j][1];
                                        Gridans[j][2] = Grideasy2ans[j][2];
                                        Gridans[j][3] = Grideasy2ans[j][3];
                                        Gridans[j][4] = Grideasy2ans[j][4];
                                        Gridans[j][5] = Grideasy2ans[j][5];
                                        Gridans[j][6] = Grideasy2ans[j][6];
                                        Gridans[j][7] = Grideasy2ans[j][7];
                                        Gridans[j][8] = Grideasy2ans[j][8];
                                    }
                                    cout << "           You can make upto " << easy2.numistakes << " mistakes \n";
                                    cout << "           You can get upto " << easy2.hints << " hints \n";
                                }
                            }
                            else if (mode == 'a'|| mode == 'A'){      // if the user chooses amateur mode then ...
                                srand (time(NULL));
                                int findgrid = rand() %(4-3 +1)+3;                 // this random function generates a number between 3 and 4 to help me choose a puzzle between 2 puzzles in amateur level
                                
                                if(findgrid == 3) {              // if the random gets 3, means first puzzle in the amateur grid
                                    correct = amateur.question;
                                    hintnum = amateur.hints;
                                    mistakes = amateur.numistakes;
                                    
                                    for (int i = 0; i <= 8; i++){
                                        Grid[i][0] = Gridamateur[i][0];
                                        Grid[i][1] = Gridamateur[i][1];
                                        Grid[i][2] = Gridamateur[i][2];
                                        Grid[i][3] = Gridamateur[i][3];
                                        Grid[i][4] = Gridamateur[i][4];
                                        Grid[i][5] = Gridamateur[i][5];
                                        Grid[i][6] = Gridamateur[i][6];
                                        Grid[i][7] = Gridamateur[i][7];
                                        Grid[i][8] = Gridamateur[i][8];
                                        
                                        Gridans[i][0] = Gridamateurans[i][0];
                                        Gridans[i][1] = Gridamateurans[i][1];
                                        Gridans[i][2] = Gridamateurans[i][2];
                                        Gridans[i][3] = Gridamateurans[i][3];
                                        Gridans[i][4] = Gridamateurans[i][4];
                                        Gridans[i][5] = Gridamateurans[i][5];
                                        Gridans[i][6] = Gridamateurans[i][6];
                                        Gridans[i][7] = Gridamateurans[i][7];
                                        Gridans[i][8] = Gridamateurans[i][8];
                                    }
                                    cout << "           You can make upto " << amateur.numistakes << " mistakes \n";
                                    cout << "           You can get upto " << amateur.hints << " hints \n";
                                }
                                else if(findgrid == 4) {            // if the random gets 4, means second puzzle in the amateur grid
                                    correct = amateur2.question;
                                    hintnum = amateur2.hints;
                                    mistakes = amateur2.numistakes;
                                    
                                    for (int i = 0; i <= 8; i++){
                                        Grid[i][0] = Gridamateur2[i][0];
                                        Grid[i][1] = Gridamateur2[i][1];
                                        Grid[i][2] = Gridamateur2[i][2];
                                        Grid[i][3] = Gridamateur2[i][3];
                                        Grid[i][4] = Gridamateur2[i][4];
                                        Grid[i][5] = Gridamateur2[i][5];
                                        Grid[i][6] = Gridamateur2[i][6];
                                        Grid[i][7] = Gridamateur2[i][7];
                                        Grid[i][8] = Gridamateur2[i][8];
                                        
                                        Gridans[i][0] = Gridamateur2ans[i][0];
                                        Gridans[i][1] = Gridamateur2ans[i][1];
                                        Gridans[i][2] = Gridamateur2ans[i][2];
                                        Gridans[i][3] = Gridamateur2ans[i][3];
                                        Gridans[i][4] = Gridamateur2ans[i][4];
                                        Gridans[i][5] = Gridamateur2ans[i][5];
                                        Gridans[i][6] = Gridamateur2ans[i][6];
                                        Gridans[i][7] = Gridamateur2ans[i][7];
                                        Gridans[i][8] = Gridamateur2ans[i][8];
                                    }
                                    cout << "           You can make upto " << amateur2.numistakes << " mistakes \n";
                                    cout << "           You can get upto " << amateur2.hints << " hints \n";
                                }
                                
                            }
                            else if (mode == 'h'|| mode == 'H'){              // if the user chooses hard mode then ...
                                srand (time(NULL));
                                int findgrid = rand() %(6-5 +1)+5;          // this random function generates a number between 5 and 6 to help me choose a puzzle between 2 puzzles in hard level
                                
                                if(findgrid == 5) {                 // if the random gets 5, means first puzzle in the hard grid
                                    correct = hard.question;
                                    hintnum = hard.hints;
                                    mistakes = hard.numistakes;
                                    
                                    for (int k = 0; k <= 8; k++){
                                        Grid[k][0] = Gridhard[k][0];
                                        Grid[k][1] = Gridhard[k][1];
                                        Grid[k][2] = Gridhard[k][2];
                                        Grid[k][3] = Gridhard[k][3];
                                        Grid[k][4] = Gridhard[k][4];
                                        Grid[k][5] = Gridhard[k][5];
                                        Grid[k][6] = Gridhard[k][6];
                                        Grid[k][7] = Gridhard[k][7];
                                        Grid[k][8] = Gridhard[k][8];
                                        
                                        Gridans[k][0] = Gridhardans[k][0];
                                        Gridans[k][1] = Gridhardans[k][1];
                                        Gridans[k][2] = Gridhardans[k][2];
                                        Gridans[k][3] = Gridhardans[k][3];
                                        Gridans[k][4] = Gridhardans[k][4];
                                        Gridans[k][5] = Gridhardans[k][5];
                                        Gridans[k][6] = Gridhardans[k][6];
                                        Gridans[k][7] = Gridhardans[k][7];
                                        Gridans[k][8] = Gridhardans[k][8];
                                    }
                                    cout << "           You can make upto " << hard.numistakes << " mistakes \n";
                                    cout << "           You can get upto " << hard.hints << " hints \n";
                                }
                                else if(findgrid == 6) {            // if the random gets 6, means second puzzle in the hard grid
                                    correct = hard2.question;
                                    hintnum = hard2.hints;
                                    mistakes = hard2.numistakes;
                                    
                                    for (int i = 0; i <= 8; i++){
                                        Grid[i][0] = Gridhard2[i][0];
                                        Grid[i][1] = Gridhard2[i][1];
                                        Grid[i][2] = Gridhard2[i][2];
                                        Grid[i][3] = Gridhard2[i][3];
                                        Grid[i][4] = Gridhard2[i][4];
                                        Grid[i][5] = Gridhard2[i][5];
                                        Grid[i][6] = Gridhard2[i][6];
                                        Grid[i][7] = Gridhard2[i][7];
                                        Grid[i][8] = Gridhard2[i][8];
                                        
                                        Gridans[i][0] = Gridhard2ans[i][0];
                                        Gridans[i][1] = Gridhard2ans[i][1];
                                        Gridans[i][2] = Gridhard2ans[i][2];
                                        Gridans[i][3] = Gridhard2ans[i][3];
                                        Gridans[i][4] = Gridhard2ans[i][4];
                                        Gridans[i][5] = Gridhard2ans[i][5];
                                        Gridans[i][6] = Gridhard2ans[i][6];
                                        Gridans[i][7] = Gridhard2ans[i][7];
                                        Gridans[i][8] = Gridhard2ans[i][8];
                                    }
                                    cout << "           You can make upto " << hard2.numistakes << " mistakes \n";
                                    cout << "           You can get upto " << hard2.hints << " hints \n";
                                }
                            }
                            
                            cout << "           Please enter on the places where 0's are placed \n\n";
                            
                            gridoutput();     // displying the puzzle
                        }
                        
                        else{    // if they user doesnt want to replay the game then ...
                            cout << "           Thankyou for playing my game!! \n\n\n\n\n";
                        }
                    }
                }
            }
        }
    }
    
    else {      // if the users enters something invalid and doesnt enter a key to continue, then...
        cout << "           Game finished";
    }
}
