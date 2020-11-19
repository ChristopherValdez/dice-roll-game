/* 
 * File:    main.cpp 
 * Author:  Christopher Valdez
 * Date:    02/12/20
 * Purpose: Dice game version 8
 */

//System Libraries
#include <iostream>  //Input/Output Library
#include <string>
#include <iomanip>
#include <fstream>  //File in and out
#include <ctime>
#include <cmath>

using namespace std;
//User Libraries
//Global Constants, no Global Variables are allowed
//Math/Physics/Conversions/Higher Dimensions - i.e. PI, e, etc...
//Function Prototypes
int diceRoll();
void gameRules();
void playGame(int&, int&);
void gameRatio(int, int);
void highScores();
void sSort(string[],int = 4); //string sort default arg
void sSort(int[],int = 4);  //int sort default arg
int lnrSrch(string [], int);
void swap(int,int,string,string);
bool stop(bool);
void exit();
//Execution Begins Here!
int main(int argc, char** argv) {
    //Set the random number seed
    srand(time(NULL));
    //Declare Variables
    int choice, wins = 0, losses = 0;
    bool playing = true;
    string error = "Error: Invalid Entry, Please choose from the menu.";
    //Initialize or input i.e. set variable values
    //Map inputs -> outputs
    do
    {
        //Main Menu
        cout << "1. Play a round of Craps." << endl;
        cout << "2. View Win/Loss Ratio." << endl;
        cout << "3. View the Game Rules." << endl;
        cout << "4. View High Scores." << endl;
        cout << "5. Exit Program" << endl;
        cout << "Make your choice: ";
        cin >> choice;
        if(!cin)
        {
            cin.clear();
            cin.ignore(123, '\n');
            clog << "\n" << error << "\n" << endl;
        }
        else if(cin){
            switch(choice)
            {
                case 1:
                    playGame(wins, losses);
                    break;
                case 2:
                    gameRatio(wins, losses);
                    break;
                case 3:
                    gameRules();
                    break;
                case 4:
                    highScores();
                    break;
                case 5:
                    playing = stop(playing);
                    break;
                default:
                    cout << endl;
                    clog << error << endl;
                    cout << endl;
                    break;
            }
        }
    }while(playing == true);
    //Display the outputs
    
    //Exit stage right or left!
    exit();
    return 0;
}
int diceRoll()
{
    
    const int dice = 6;
    int gameResult = 0;
    int dResult1 = 0;
    int dResult2 = 0;
    
    dResult1 = rand() % dice + 1;
    dResult2 = rand() % dice + 1;
    
    cout << endl;
    cout << "You roll " << dResult1 << " and " << dResult2 << endl;
    
    gameResult = dResult1 + dResult2;
    return gameResult;
}
void gameRatio(int wins,int losses)
{
    int perConv = 100;
    float total = wins+losses;
    float ratio = 0.0f;
    cout << endl;
    cout << "Total Wins: " << wins << endl;
    cout << "Total Losses: " << losses << endl;
    if (wins == 0 || losses == 0){
        ratio = 0;
        cout << "";
    }
    else if (isgreaterequal(wins,losses)){
        ratio = wins/total;
        cout << "\nYou have a " << setprecision(1) << fixed << ratio*perConv << "% win rate." << endl;
    }
    else if(isgreater(losses, wins)){
        ratio = losses/total;
        cout << "\nYou have a " << setprecision(1) << fixed << ratio*perConv << "% loss rate." << endl;
    }
    cout << endl;
}
void playGame(int& wins,int& losses){
    int comeOut = 0, roll = 0, point = 0;
    bool reRoll = true;
    comeOut = diceRoll();
    cout << "Your total is " << comeOut << endl;
    cout << endl;
    if (comeOut == 7 || comeOut == 11){
        cout << "You have won the round!\n" << endl;
        wins++;
    }
    else if (comeOut == 2 || comeOut == 3 || comeOut == 12){
        cout << "You have lost the round.\n" << endl;
        losses++;
    }
    else{
        point = comeOut;
        cout << "point is " << point << endl;
        while(reRoll == true){
            roll = diceRoll();
            cout << "Your total is " << roll << endl;
            cout << endl;
            if (roll == point){
                cout << "You have won the round!\n" << endl;
                wins++;
                reRoll = false;
            }
            else{
                if (roll == 7){
                    cout << "You have lost the round.\n" << endl;
                    losses++;
                    reRoll = false;
                }
            }
        }
    }
}
void gameRules(){
    cout << endl;
    static int view = 0;    //static int to count page views
    for(int i=0; i<=70 ;i++){
        cout << "*";
    }
    cout << "\nCraps is a game of dice. The player rolls two dice and the " << endl;
    cout << "sum of the two dice is calculated. If the player rolls a 7 or 11, " << endl;
    cout << "The round is won. If the player rolls a 2, 3, or 12 the round is lost. " << endl;
    cout << "If the player rolls any other number it then becomes the point number. " << endl;
    cout << "The object of the game then is to roll the point number again before " << endl;
    cout << "rolling a 7." << endl;
    for(int i=0; i<=70 ;i++){
        cout << "*";
    }
    view++;
    cout << "\n" << endl;
    cout << "You have viewed this page " << view << " times.\n" << endl;
}
void highScores(){
    const int SCORE_SIZE = 4;
    string names[SCORE_SIZE];   //Names array
    int scores[SCORE_SIZE];   //Scores array
    ifstream inputFile;
    ofstream outputFile;

    inputFile.open("Score.txt");    //open input file
    
    for(int i=0; i<SCORE_SIZE; i++){    //for loop names and score into arrays
        inputFile >> names[i];
        inputFile >> scores[i];
    }
    inputFile.close();  //close file
    
    sSort(names);   //overloaded function with default arg int
    sSort(scores);  //overloaded function with default arg int
    
    cout << "\n" << setw(18) << "High Scores:\n" << endl;
    for (int i=0; i<SCORE_SIZE; i++){   //for loop output names
        cout << setw(11) << names[i];   //Score output
        cout << setw(5) << scores[i] << endl;
    }
    cout << endl;
    int index = lnrSrch(names, SCORE_SIZE); //Linear search
    if(index == -1){
        cout << "\nYour name is not on the high score list.\n" << endl;
    }
    else{
        cout << "\n" << "Your Score is: ";
        cout << scores[index] << "\n" << endl;
    }
    outputFile.open("HighScore.txt");    //open input file
    
    for(int i=0; i<SCORE_SIZE; i++){    //for loop names and score into arrays
        outputFile << names[i] << endl;
        outputFile << scores[i] << endl;
    }
    outputFile.close();  //close file
}
void sSort(string a[], int n){
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
void sSort(int a[], int n){
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
int lnrSrch(string a[], int n){
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
bool stop(bool playing){
    playing = false;
    return playing;
}
void exit(){
    cout << "\nClosing Program" << endl;
    exit(0);
}