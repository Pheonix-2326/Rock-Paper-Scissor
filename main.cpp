#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <string>
#include <cctype>

/**
 * @file Main.cpp
 * @brief Rock, Paper and Scissors game without GUI.
 */

using namespace std;

void checker(char opt_1, int opt_2, int &win_count_1, int &win_count_2, int &win_count_3)
{
    if (opt_1 == '1' && opt_2 == 1)
    {
        win_count_3++;
    }
    else if (opt_1 == '1' && opt_2 == 2)
    {
        win_count_2++;
    }
    else if (opt_1 == '1' && opt_2 == 3)
    {
        win_count_1++;
    }
    else if (opt_1 == '2' && opt_2 == 2)
    {
        win_count_3++;
    }
    else if (opt_1 == '2' && opt_2 == 3)
    {
        win_count_2++;
    }
    else if (opt_1 == '2' && opt_2 == 1)
    {
        win_count_1++;
    }
    else if (opt_1 == '3' && opt_2 == 3)
    {
        win_count_3++;
    }
    else if (opt_1 == '3' && opt_2 == 1)
    {
        win_count_2++;
    }
    else if (opt_1 == '3' && opt_2 == 2)
    {
        win_count_1++;
    }
    else
    {
        // creates to cover up all cases
    }
}

void printline(int linetype)
{
    SetConsoleOutputCP(65001);  // Enable UTF-8 for proper character display
    int length = (linetype == 1) ? 32 : 37;

    for (size_t count = 0; count < length; count++)
    {
        cout << u8"\u2500 ";  // Unicode horizontal line '─'
    }
    cout << endl;
}

int main()
{
    srand(time(NULL));  // Initialize random seed

    string input;

    char user_choice, round_winner, replay;

    int iteration, total_rounds, count = 0;
    int comp_choice, user_score, comp_score, draw_score;
    int win_count_1 = 0, win_count_2 = 0, win_count_3 = 0;

    do
    {

        // Prompt user for number of rounds
        cout << "Enter the number of Matches(1 to 99): ";
        cin >> input;
        cout << endl << endl;

        // Validate that input is numeric
        for (char check : input)
        {
            if (!isdigit(check))
            {
                cerr << "[Error] Invalid input! Please enter a numeric value." << endl;
                return 0;
            }
        }

        // Convert valid string input to integer
        total_rounds = stoi(input);
        user_score = comp_score = draw_score = 0;

        // Validate the range
        if (total_rounds < 1 || total_rounds > 99)
        {
            cerr << "[Error] Out of range! Please choose between 1 and 99." << endl;
            return 0;
        }

        // Show option mapping to the user
        cout << "\033[1;34mChoose your move:\033[0m" << endl; // Blue bold
        cout << "  1 - Rock\n  2 - Paper\n  3 - Scissors\n" << endl;

        // Print the game table header
        printline(1);
        cout << "|   *   |" << setw(10) << "USER"
             << setw(8) << "|" << setw(12) << "COMPUTER"
             << setw(6) << "|" << setw(11) << "WINNER"
             << setw(7) << "|" << endl;
        printline(1);

        // Loop for each game round
        for (iteration = 0; iteration < total_rounds; iteration++)
        {
            cout << "|  " << setw(2) << iteration + 1 << ")  |" << setw(9);

            // Get user input using getch (hidden input)
            user_choice = getch();

            // Input validation
            if (user_choice < '1' || user_choice > '3')
            {
                cout << user_choice << setw(9) << "|" << setw(11)
                     << "ERROR" << setw(7) << "|" << setw(11)
                     << "ERROR" << setw(7) << "|" << endl;

                total_rounds++;
                count++;
                continue;
            }

            // Generate computer choice randomly (1 to 3)
            comp_choice = (rand() % 3) + 1;

            // Evaluate the round and determine winner
            checker(user_choice, comp_choice, win_count_1, win_count_2, win_count_3);

            // Decide round result: D - Draw, U - User, C - Computer
            round_winner = (win_count_1 == win_count_2) ? 'D' : (win_count_1 > win_count_2) ? 'U' : 'C';

            // Print round outcome
            cout << user_choice << setw(9) << "|" << setw(9)
                 << comp_choice << setw(9) << "|" << setw(9)
                 << round_winner << setw(9) << "|" << endl;

            // Update scores and reset round counters
            user_score += win_count_1;
            comp_score += win_count_2;
            draw_score += win_count_3;
            win_count_1 = win_count_2 = win_count_3 = 0;
        }

        printline(1);

        // Print final result table
        cout << endl << endl;
        cout << "Result: Total Rounds Played - " << total_rounds << endl;
        printline(2);
        cout << "|" << setw(10) << "USER" << setw(8)
             << "|" << setw(12) << "COMPUTER" << setw(6)
             << "|" << setw(10) << "DRAW" << setw(8)
             << "|" << setw(14) << "INVALID ATTEMPTS" << setw(2)
             << "|" << endl;
        printline(2);
        cout << "|" << setw(9) << user_score << setw(9)
             << "|" << setw(9) << comp_score << setw(9)
             << "|" << setw(9) << draw_score << setw(9)
             << "|" << setw(9) << count << setw(9)
             << "|" << endl;
        printline(2);

        // Declare final winner
        if (user_score == comp_score)
        {
            cout << endl << "Match Draw!" << endl;
        }
        else
        {
            cout << endl << ((user_score > comp_score) ? "User" : "Computer") << " Wins The Game!";
        }

        // Ask if user wants to play again
        cout << endl << "Do you Want To Play Again(Y/N):";
        cin >> replay;
        replay = toupper(replay);

    } while (replay == 'Y');

// Define ANSI color macros
#define RESET "\033[0m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"

    // Display colorful thank-you message
    cout << CYAN << "\n🎮════════════════════════════════════════🎮\n";
    cout << GREEN << "         🎉 Thank You for Playing! 🎉        \n";
    cout << CYAN << "🎮════════════════════════════════════════🎮\n" << RESET;

    return 0;
}
