#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main()
{
    int secretNumber, guess;
    srand(time(0));
    secretNumber = rand() % 100 + 1;
    cout << "Guess the number (1 to 100): ";
    cin >> guess;
    while (guess != secretNumber)
    {
        if (guess > secretNumber)
            cout << "Too high! Try again: ";
        else
            cout << "Too low! Try again: ";
        cin >> guess;
    }
    cout << "You guessed it! The number was " << secretNumber << endl;
    return 0;
}