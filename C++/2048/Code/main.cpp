#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <dos.h>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <fstream>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

int table[5][5], check[5], condition_win, highscore = 0;
long long int score;

void paint_element(int element)
{
    int color;
    for ( color = 1 ; color <= 15 ; color ++ )
    {
        if ( pow ( 2, color ) == element )
        {
            if ( color <= 7 )
                SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), color + 8 );
            else
                SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), color - 7);
        }
    }
}

void switch_elements(int &first, int &second)
{
    int aux = first;
    first = second;
    second = aux;
}

void combine_elements(int &first, int &second)
{
    score += second * 2;
    second *= 2;
    first = 0;
}

void move_up()
{
    check[1] = 0;
    for ( int j = 4; j>= 1; j-- )
        for (int z = 1; z <= 3; z++)
            for ( int i = 2 ; i<= 4; i++)
            {
                if ( table[i][j] and !table[i-1][j])
                {
                    switch_elements( table[i][j], table[i-1][j] );
                    check[1] = 1;
                }
                if ( table[i][j] and table[i][j] == table[i-1][j])
                {
                    combine_elements( table[i][j], table[i-1][j] );
                    check[1] = 1;
                }
            }
}

void move_down()
{
    check[2] = 0;
    for (int j = 4; j>= 1; j-- )
        for (int z = 1; z <= 3; z++)
            for ( int i = 3 ; i >= 1 ; i--)
            {
                if ( table[i][j] and !table[i+1][j])
                {
                    switch_elements( table[i][j], table[i+1][j] );
                    check[2] = 1;
                }
                if ( table[i][j] and table[i][j] == table[i+1][j])
                {
                    combine_elements( table[i][j], table[i+1][j] );
                    check[2] = 1;
                }
            }
}

void move_left()
{
    check[3] = 0;
    for ( int i = 4; i >= 1; i-- )
        for ( int z = 1 ; z <= 3; z++)
            for ( int j = 2 ; j <= 4 ; j++)
            {
                if ( table[i][j] and !table[i][j-1])
                {
                    switch_elements( table[i][j], table[i][j-1] );
                    check[3] = 1;
                }
                if ( table[i][j] and table[i][j-1] == table[i][j])
                {
                    combine_elements( table[i][j], table[i][j-1] );
                    check[3] = 1;
                }
            }
}

void move_right()
{
    check[4] = 0;
    for ( int i = 4 ; i >= 1 ; i-- )
        for ( int z = 1 ; z <= 3; z++ )
            for ( int j = 3 ; j >= 1; j-- )
            {
                if ( table[i][j] and !table[i][j+1])
                {
                    switch_elements( table[i][j], table[i][j+1] );
                    check[4] = 1;
                }
                if ( table[i][j] and table[i][j+1] == table[i][j])
                {
                    combine_elements( table[i][j], table[i][j+1] );
                    check[4] = 1;
                }
            }
}

void show_table()
{
    system("CLS");
    cout << "Score: " << score << endl << endl << endl;
    for ( int i = 1 ; i <= 4; i++ )
    {
        for ( int j = 1; j <= 4; j++ )
        {
            paint_element( table[i][j] );
            cout << '\t' << table[i][j];
            SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7 );
        }
        cout << endl << endl << endl;
    }
    cout << "Enter direction: ";
}

void randomize()
{
    int random_value, random_location_x ,random_location_y, okay = 0;
    random_value = rand() % 6 + 1;
    while (okay == 0)
    {
        random_location_x = rand() % 4 + 1;
        random_location_y = rand() % 4 + 1;
        if ( table[random_location_x][random_location_y] == 0 )
        {
            okay = 1;
            if (random_value < 6)
                table[random_location_x][random_location_y] = 2;
            else
                table[random_location_x][random_location_y] = 4;
        }
    }
}

void initialize_game()
{
    srand (time(NULL));
    for ( int i = 1 ; i <= 4 ; i++ )
        for ( int j = 1 ; j <= 4; j++ )
            table[i][j] = 0;
    for ( int i = 1 ; i <= 4 ; i++ )
        check[i] = 1;
    score = 0;
    condition_win = 1;
}

int game_won()
{
    int okay = 0;
    if ( condition_win == 1 )
        for ( int i = 1 ; i <= 4 ; i++ )
            for ( int j = 1 ; j <= 4 ; j++ )
                if (table[i][j] == 2048)
                {
                    okay = 1;
                    break;
                }
    return okay;
}

int cant_move()
{
    check[1] = 0;
    for ( int j = 4; j>= 1; j-- )
        for ( int i = 2 ; i<= 4; i++)
        {
            if ( table[i][j] and !table[i-1][j])
                check[1] = 1;
            if ( table[i][j] and table[i][j] == table[i-1][j])
                check[1] = 1;
        }
    check[2] = 0;
    for (int j = 4; j>= 1; j-- )
        for ( int i = 3 ; i >= 1 ; i--)
        {
            if ( table[i][j] and !table[i+1][j])
                check[2] = 1;
            if ( table[i][j] and table[i][j] == table[i+1][j])
                check[2] = 1;
        }
    check[3] = 0;
    for ( int i = 4; i >= 1; i-- )
        for ( int j = 2 ; j <= 4 ; j++)
        {
            if ( table[i][j] and !table[i][j-1])
                check[3] = 1;
            if ( table[i][j] and table[i][j-1] == table[i][j])
                check[3] = 1;
        }
    check[4] = 0;
    for ( int i = 4 ; i >= 1 ; i-- )
        for ( int j = 3 ; j >= 1; j-- )
        {
            if ( table[i][j] and !table[i][j+1])
                check[4] = 1;
            if ( table[i][j] and table[i][j+1] == table[i][j])
                check[4] = 1;
        }
    int okay = 1;
    for ( int i = 1; i<=4 ; i++ )
        if ( check[i] )
        {
            okay = 0;
        }
    return okay;
}

int main()
{
    int direction, counter;
    char answer;
    SetConsoleTitle("2048 by Akriel");
    initialize_game();
    randomize();
    LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    while ( true )
    {
        randomize();
        show_table();
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 14 );
        counter = 0;
        if ( !cant_move() )
        {
            while ( true )
            {
                direction = 0;
                switch( ( direction = getch() ) )
                {
                    case KEY_UP:
                    {
                        move_up();
                        if (check[1])
                        {
                            cout << endl << "Up" << endl;
                            counter ++;
                        }
                        break;
                    }
                    case KEY_DOWN:
                    {
                        move_down();
                        if (check[2])
                        {
                            cout << endl << "Down" << endl;
                            counter ++;
                        }
                        break;
                    }
                    case KEY_LEFT:
                    {
                        move_left();
                        if (check[3])
                        {
                            cout << endl << "Left" << endl;
                            counter ++;
                        }
                        break;
                    }
                    case KEY_RIGHT:
                    {
                        move_right();
                        if (check[4])
                        {
                            cout << endl << "Right" << endl;
                            counter ++;
                        }
                        break;
                    }
                    default:
                        break;
                }
                if (counter)
                    break;
            }
        }
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7 );

        if ( game_won() )
        {
            SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 10 );
            cout << endl << endl << "Congratulations , you won this game, would you like to continue it?(Y/N): ";
            while ( true )
            {
                SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 12 );
                cin >> answer;
                if ( !strchr ("nNyY", answer ) )
                    cout << endl << " Your answer is invalid , please enter a valid answer: ";
                else
                    break;
            }
            SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7 );
            if ( strchr ("Yy", answer ) )
            {
                condition_win = 0;
                cout << endl << endl << "Good luck, you may need it.";
            }
            else
            {
                cout << endl << endl << "Would you like to restart the game?(Y/N): ";
                while ( true )
                {
                    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 10 );
                    cin >> answer;
                    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 12 );
                    if ( !strchr ("nNyY", answer ) )
                        cout << endl << " Your answer is invalid , please enter a valid answer: ";
                    else
                        break;
                }
                if ( strchr ("Yy", answer ) )
                {
                    cout << "Reinitializing the game.. Good luck";
                    Sleep(3000);
                    initialize_game();
                }
                else
                {
                    cout << endl << endl << "Thanks for playing, have a nice day.";
                    break;
                }

            }
        }

        if ( cant_move() )
        {
            SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 12 );
            cout << endl << endl << "You lost, but it's not over yet." << endl << "Would you like to give it another try?(Y/N): ";
            while ( true )
            {
                SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 10 );
                cin >> answer;
                SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 12 );
                if ( !strchr ("nNyY", answer ) )
                    cout << endl << " Your answer is invalid , please enter a valid answer: ";
                else
                    break;
            }
            SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 7 );
            if ( strchr ("Nn", answer ) )
            {
                cout << endl << endl << "Thanks for playing, have a nice day.";
                break;
            }
            else
            {
                cout << "Reinitializing the game.. Good luck";
                Sleep(3000);
                initialize_game();
            }
        }
        Sleep(150);
    }
    cout << endl << endl << endl ;
    return 0;
}
