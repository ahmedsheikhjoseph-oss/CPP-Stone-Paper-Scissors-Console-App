/*
Project: Stone, Paper, Scissors Game
Course: Programming Advices - Algorithms & Problem Solving Level 2
Purpose: Demonstrating Logical Thinking, Functions, Structs, and Enums in C++.
Author: [Ahmed Sheikh Aldeen Yusef]
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Using Enums for better code readability and maintenance
enum enGameChoices { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

// Struct to hold individual round details
struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoices PlayerChoice;
    enGameChoices ComputerChoice;
    enWinner RoundWinner;
    string WinnerName = "";
};

// Struct to hold final game statistics
struct stGameResults
{
    short GameRounds = 0;
    short Player1WinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

// Generates a random number within a specific range
short RandomNumber(short From, short To)
{
    return rand() % (To - From + 1) + From;
}

// Maps Winner Enum to string for display
string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = { "Player1", "Computer", "No Winner" };
    return arrWinnerName[Winner - 1];
}

// Core Game Logic: Decides the winner of each round
enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
        return enWinner::Draw;

    switch (RoundInfo.PlayerChoice)
    {
    case enGameChoices::Stone:
        return (RoundInfo.ComputerChoice == enGameChoices::Paper) ? enWinner::Computer : enWinner::Player1;
    case enGameChoices::Paper:
        return (RoundInfo.ComputerChoice == enGameChoices::Scissors) ? enWinner::Computer : enWinner::Player1;
    case enGameChoices::Scissors:
        return (RoundInfo.ComputerChoice == enGameChoices::Stone) ? enWinner::Computer : enWinner::Player1;
    }
    return enWinner::Draw; // Default fallback
}

// Maps Choice Enum to string for display
string ChoiceName(enGameChoices Choice)
{
    string arrChoiceName[3] = { "Stone", "Paper", "Scissors" };
    return arrChoiceName[Choice - 1];
}

// Enhances UI by changing console color based on result
void SetWinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case Player1:
        system("color 2F"); // Green for win
        break;
    case Computer:
        cout << "\a";       // Beep sound for loss
        system("color 4F"); // Red for loss
        break;
    default:
        system("color 6F"); // Yellow for draw
        break;
    }
}

// Displays individual round results to the user
void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << "\n----------------- Round [" << RoundInfo.RoundNumber << "] -----------------\n\n";
    cout << "Player1  Choice: " << ChoiceName(RoundInfo.PlayerChoice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
    cout << "\n---------------------------------------------\n\n";

    SetWinnerScreenColor(RoundInfo.RoundWinner);
}

// Decides the final winner based on total score
enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
    if (Player1WinTimes > ComputerWinTimes)
        return enWinner::Player1;
    else if (ComputerWinTimes > Player1WinTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

// Aggregates all game data into the results struct
stGameResults FillGameResult(short GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
    stGameResults GameResults;
    GameResults.GameRounds = GameRounds;
    GameResults.Player1WinTimes = Player1WinTimes;
    GameResults.ComputerWinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}

// Validates and reads player input
enGameChoices ReadPlayerChoice()
{
    short Choice = 1;
    do
    {
        cout << "\nYour Choice:[1]:Stone, [2]:Paper, [3]:Scissors ? ";
        cin >> Choice;
    } while (Choice <= 0 || Choice > 3);

    return (enGameChoices)Choice;
}

// Gets computer choice using random function
enGameChoices GetComputerChoice()
{
    return (enGameChoices)RandomNumber(1, 3);
}

// Main game loop logic
stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo; 
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begins:\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.PlayerChoice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.RoundWinner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.RoundWinner);

        if (RoundInfo.RoundWinner == enWinner::Player1) Player1WinTimes++;
        else if (RoundInfo.RoundWinner == enWinner::Computer) ComputerWinTimes++;
        else DrawTimes++;

        PrintRoundResults(RoundInfo);
    }

   return FillGameResult(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);
}

// Formats UI with tabs
string Tabs(short NumberOfTabs)
{
    string t = "";
    for (int i = 1; i <= NumberOfTabs; i++) t += "\t";
    return t;
}

void ShowGameOverScreen()
{
    cout << Tabs(2) << "___________________________________________________________________\n\n";
    cout << Tabs(2) << "                    +++ G a m e  O v e r +++\n";
    cout << Tabs(2) << "___________________________________________________________________\n\n";
}

void ShowFinalGameResults(stGameResults GameResults)
{
    cout << Tabs(2) << "___________________________[Game Results]_________________________\n\n";
    cout << Tabs(2) << "Game Rounds        : " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player1 Won times  : " << GameResults.Player1WinTimes << endl;
    cout << Tabs(2) << "Computer Won times : " << GameResults.ComputerWinTimes << endl;
    cout << Tabs(2) << "Draw times         : " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner       : " << GameResults.WinnerName << endl;
    cout << Tabs(2) << "___________________________________________________________________\n\n";

    SetWinnerScreenColor(GameResults.GameWinner);
}

short ReadHowManyRounds()
{
    short GameRounds = 0;
    do
    {
        cout << "How Many Rounds 1 to 10 ?" << endl;
        cin >> GameRounds;
    } while (GameRounds <= 0 || GameRounds > 10);

    return GameRounds;
}

// Resets terminal colors and clears screen
void ResetScreen()
{
    system("cls");
    system("color 0F"); // Reset to default
}

// Main game controller
void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());

        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);

        cout << Tabs(2) << "Do you want to play again? Y/N? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    // Initialize random seed based on current time
    srand((unsigned)time(NULL));

    // Launch the application
    StartGame();

    return 0;
}
