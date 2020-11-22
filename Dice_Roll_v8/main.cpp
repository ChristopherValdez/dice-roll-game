/* 
 * File:    main.cpp 
 * Author:  Christopher Valdez
 * Date:    02/12/20
 * Purpose: Dice game version 8. This game needed to include certain required functions and is not optimal. Some functions were added to meet grading requirements.
 */

// System Libraries
#include <iostream>  // Input/Output Library
#include <string>
#include <iomanip>
#include <fstream>  // File in and out
#include <ctime>
#include <cmath>

using namespace std;
// User Libraries
// Global Constants, no Global Variables are allowed
// Math/Physics/Conversions/Higher Dimensions - i.e. PI, e, etc...
// Function Prototypes
int diceRoll();
void gameRules();
void playGame(int&, int&);
void gameRatio(int, int);
void highScores();
void sSort(string[],int = 4); // String sort default arg
void sSort(int[],int = 4);  // Int sort default arg
int lnrSrch(string [], int);
void swap(int,int,string,string);
bool stop(bool);
void exit();
// Execution Begins Here!
int main(int argc, char** argv) {
    // Set the random number seed
    srand(time(NULL));
    // Declare Variables
    int choice, wins = 0, losses = 0;
    bool playing = true;
    string error = "Error: Invalid Entry, Please choose from the menu.";
    // Initialize or input i.e. set variable values
    // Map inputs -> outputs
    do
    {
        // Main Menu
        cout << "1. Play a round of Craps." << endl;
        cout << "2. View Win/Loss Ratio." << endl;
        cout << "3. View the Game Rules." << endl;
        cout << "4. View High Scores." << endl;
        cout << "5. Exit Program" << endl;
        cout << "Make your choice: ";   // Take user input
        cin >> choice;  // Store user input in var
        if(!cin)    // If the choice is not int clear and output error string
        {
            cin.clear();
            cin.ignore(123, '\n');
            clog << "\n" << error << "\n" << endl;
        }
        else if(cin){   // If input is integer then check switch case and run function
            switch(choice)
            {
                case 1: // Begin a game with var wins and losses
                    playGame(wins, losses);
                    break;
                case 2: // Display win/loss ratio
                    gameRatio(wins, losses);
                    break;
                case 3: // Display game rules
                    gameRules();
                    break;
                case 4: // Run highscore function
                    highScores();
                    break;
                case 5: // Change bool playing to false
                    playing = stop(playing);
                    break;
                default:    // If the user choice is not a valid choice output error string
                    cout << endl;
                    clog << error << endl;
                    cout << endl;
                    break;
            }
        }
    }while(playing == true);
    // Display the outputs
    
    // Exit stage right or left!
    exit();
    return 0;
}
int diceRoll()
{
    // Initialize variables
    const int dice = 6;
    int gameResult = 0;
    int dResult1 = 0;
    int dResult2 = 0;
    
    dResult1 = rand() % dice + 1;   // Generate a random number, modulo by 6 plus on to make the range of random number between 1 and 6.
    dResult2 = rand() % dice + 1;   // This is dome individually for both dice to simulate individual random rolls. The result is save to var.
    
    cout << endl;
    cout << "You roll " << dResult1 << " and " << dResult2 << endl; // Display the results of the roll.
    
    gameResult = dResult1 + dResult2;   // store rusults to var and return the var.
    return gameResult;
}
void gameRatio(int wins,int losses)
{
    // Initialize variables
    int perConv = 100;
    float total = wins+losses;
    float ratio = 0.0f;
    
    cout << endl;
    // Output wins and losses
    cout << "Total Wins: " << wins << endl;
    cout << "Total Losses: " << losses << endl;
    // If statment for when the wins and losses = 0 output nothing.
    if (wins == 0 || losses == 0){
        ratio = 0;
        cout << "";
    }
    // If wins are greater than losses a win rate is displayed and the ratio is output.
    else if (isgreaterequal(wins,losses)){
        ratio = wins/total;
        cout << "\nYou have a " << setprecision(1) << fixed << ratio*perConv << "% win rate." << endl;
    }
    // If losses are greater than wins a loss rate is displayed and the ratio is output.
    else if(isgreater(losses, wins)){
        ratio = losses/total;
        cout << "\nYou have a " << setprecision(1) << fixed << ratio*perConv << "% loss rate." << endl;
    }
    cout << endl;
}
void playGame(int& wins,int& losses){
    // Initialize variables
    int comeOut = 0, roll = 0, point = 0;
    bool reRoll = true;
    // Comeout is the first roll and is used to determine if the next roll wins losses or goes to next round.
    comeOut = diceRoll();
    cout << "Your total is " << comeOut << endl;
    cout << endl;
    // If 7 or 11 is rolled the user wins, win message is displayed and the win count is incremented
    if (comeOut == 7 || comeOut == 11){
        cout << "You have won the round!\n" << endl;
        wins++;
    }
    // If 2 or 3 or 12 is rolled the user losses, loss message is displayed and the loss count is incremented
    else if (comeOut == 2 || comeOut == 3 || comeOut == 12){
        cout << "You have lost the round.\n" << endl;
        losses++;
    }
    else{   // Otherwise the Comeout becomes the point and is checked against the roll var to determine if the user wins, losses or rerolls.
        point = comeOut;
        cout << "point is " << point << endl;
        // While the user does not roll the point or 7 the user rolls again.
        while(reRoll == true){
            // diceRoll function is called and stored to var roll
            roll = diceRoll();
            cout << "Your total is " << roll << endl;
            cout << endl;
            if (roll == point){ // If the user rolls the point they win.
                cout << "You have won the round!\n" << endl;    // Win message is displayed.
                wins++; // Win is incremented
                reRoll = false; // reRoll bool is changed to false.
            }
            else{
                if (roll == 7){ // If the user rolls 7 they loss.
                    cout << "You have lost the round.\n" << endl;   // loss message is displayed
                    losses++;   // losses incremented
                    reRoll = false; // reRoll var is changed to false
                }
            }
        }
    }
}
void gameRules(){
    cout << endl;
    static int view = 0;    // Static int to count page views
    for(int i=0; i<=70 ;i++){
        cout << "*";    // Boarder is with 71 * characters
    }
    // Game rules are displayed.
    cout << "\nCraps is a game of dice. The player rolls two dice and the " << endl;
    cout << "sum of the two dice is calculated. If the player rolls a 7 or 11, " << endl;
    cout << "The round is won. If the player rolls a 2, 3, or 12 the round is lost. " << endl;
    cout << "If the player rolls any other number it then becomes the point number. " << endl;
    cout << "The object of the game then is to roll the point number again before " << endl;
    cout << "rolling a 7." << endl;
    for(int i=0; i<=70 ;i++){
        cout << "*";
    }
    view++; // View count is incremented
    cout << "\n" << endl;
    cout << "You have viewed this page " << view << " times.\n" << endl;    // View count is displayed
}
void highScores(){
    const int SCORE_SIZE = 4;
    string names[SCORE_SIZE];   // Names array
    int scores[SCORE_SIZE];   // Scores array
    ifstream inputFile;
    ofstream outputFile;

    inputFile.open("Score.txt");    // Open input file
    
    for(int i=0; i<SCORE_SIZE; i++){    // For loop names and score into arrays
        inputFile >> names[i];
        inputFile >> scores[i];
    }
    inputFile.close();  // Close file
    
    sSort(names);   // Overloaded function with default arg int
    sSort(scores);  // Overloaded function with default arg int
    
    cout << "\n" << setw(18) << "High Scores:\n" << endl;
    for (int i=0; i<SCORE_SIZE; i++){   // For loop output names
        cout << setw(11) << names[i];   // Score output
        cout << setw(5) << scores[i] << endl;
    }
    cout << endl;
    int index = lnrSrch(names, SCORE_SIZE); // Linear search
    if(index == -1){
        cout << "\nYour name is not on the high score list.\n" << endl;
    }
    else{
        cout << "\n" << "Your Score is: ";
        cout << scores[index] << "\n" << endl;
    }
    outputFile.open("HighScore.txt");    // Open input file
    
    for(int i=0; i<SCORE_SIZE; i++){    // For loop names and score into arrays
        outputFile << names[i] << endl;
        outputFile << scores[i] << endl;
    }
    outputFile.close();  // Close file
}
void sSort(string a[], int n){  // Sort function for highscore names.
    int startScan, minIndex;
    string minValue;
    
    for (startScan = 0; startScan < (n - 1); startScan++){
        minIndex = startScan;
        minValue = a[startScan];
        for(int index = startScan + 1; index < n; index++){
            if (a[index] < minValue){
                minValue = a[index];
                minIndex = index;
            }
        }
        a[minIndex] = a[startScan];
        a[startScan] = minValue;
    }
}
void sSort(int a[], int n){ // Sort function for highscore scores.
    int startScan, minIndex, minValue;
    
    for (startScan = 0; startScan < (n - 1); startScan++){
        minIndex = startScan;
        minValue = a[startScan];
        for(int index = startScan + 1; index < n; index++){
            if (a[index] < minValue){
                minValue = a[index];
                minIndex = index;
            }
        }
        a[minIndex] = a[startScan];
        a[startScan] = minValue;
    }
}
int lnrSrch(string a[], int n){ // Linear search for user inout name from highscore list
    string val;
    cout << "What is your name: ";
    cin >> val;
    for (int i = 0; i < n; i++){
        if (val == a[i]){
            return i;
        }
    }
    return -1;
}
bool stop(bool playing){    // Stop function is called to end game
    playing = false;
    return playing;
}
void exit(){    // Exit function to close program
    cout << "\nClosing Program" << endl;
    exit(0);
}
