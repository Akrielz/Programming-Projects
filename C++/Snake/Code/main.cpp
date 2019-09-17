//-----------[Libraries]---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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

using namespace std;

//-----------[Useful Stuff]----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define COLOR(a) SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), a )

#define Dark_Blue 1
#define Dark_Green 2
#define Dark_Teal 3
#define Dark_Red 4
#define Dark_Purple 5
#define Dark_Yellow 6
#define Light_Gray 7
#define Gray 8
#define Blue 9
#define Green 10
#define Teal 11
#define Red 12
#define Purple 13
#define Yellow 14
#define White 15

#define Dark_Blue_Pixel 17
#define Dark_Green_Pixel 34
#define Dark_Teal_Pixel 51
#define Dark_Red_Pixel 68
#define Dark_Purple_Pixel 85
#define Dark_Yellow_Pixel 102
#define Light_Gray_Pixel 119
#define Gray_Pixel 136
#define Blue_Pixel 153
#define Green_Pixel 170
#define Teal_Pixel 187
#define Red_Pixel 204
#define Purple_Pixel 221
#define Yellow_Pixel 238
#define White_Pixel 255
#define Black_Pixel 256

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT  75
#define KEY_RIGHT 77

#define KEY_ENTER 13
#define KEY_ESCAPE 27

#define Easy 8
#define Medium 4
#define Hard 2
#define Insane 1

#define Easy_Delay 60
#define Medium_Delay 30
#define Hard_Delay 15
#define Insane_Delay 1

int Toggle1 = 1 , Toggle2, Toggle3 = 3, Toggle4 = 1, Score, HighScore,
    Color_For_Snake[] = { Yellow_Pixel, Green_Pixel, Teal_Pixel, Red_Pixel, Purple_Pixel, Blue_Pixel, White_Pixel },
    Color_For_Selector[] = { Yellow, Green, Teal, Red, Purple, Blue, White },
    Diffuclty[] = { Easy, Medium, Hard, Insane },
    Delay[] = { Easy_Delay, Medium_Delay, Hard_Delay, Insane_Delay };

void Paint_Text ( char Text_Incoming[], int Color )
{
    COLOR(Color);
    cout << Text_Incoming;
    COLOR(White);
}

void Paint_Element( int Text_Incoming, int Color )
{
    COLOR(Color);
    cout << Text_Incoming << Text_Incoming;
    COLOR(White);
}

void Explaining( char Text[], char Description[] )
{
    cout << '\t' << "   ";
    Paint_Text ( Text, Green );
    cout << '\t' <<'\t' << Description << endl << endl << endl;
}

//-----------[Save and Load]---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Load_The_Settings()
{
    string Description;
    ifstream Read_In ( "Settings.stgs" );
    Read_In >> Description >> Toggle1 >> Description >> Toggle2 >> Description >> Toggle3 >> Description >> Toggle4;
    Read_In.close();
}

void Save_The_Settings()
{
    ofstream Write_Out ( "Settings.stgs" );
    Write_Out << "Difficulty: " << Toggle1 << '\n' << "Color-of-Snake: " << Toggle2 << '\n' << "Color-of-Selector: " << Toggle3 << "\nWalls: " << Toggle4;
    Write_Out.close();
}

void Load_The_HighScore()
{
    string Description;
    ifstream Read_In ( "HighScore.stgs" );
    Read_In >>  Description >> HighScore;
    Read_In.close();
}

void Save_The_HighScore()
{
    ofstream Write_Out ( "HighScore.stgs" );
    Write_Out << "HighScore: " << HighScore;
    Write_Out.close();
}

//-----------[Snake]-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define Head 0
#define Bars 13
#define length 24
#define height 24
#define Forward(component)  platform [ Snake[component].position_y + direction_y[direction] ] [ Snake[component].position_x + direction_x[direction] ]

int platform [length][height], exit_var, Food_Existence, Seconds_Passed, Special_Food_Existence, Bonus_Points;
int xLeft = 1, xRight, xUp, xDown;
int direction, Key_Substitute, Lost, Food_Spawned, Snake_Dimension = 1, Time_Bar[Bars], Pause, Ultra;

int direction_x[] = { -1, 0, 1, 0 }; // Left, Down, Right, Up
int direction_y[] = { 0, 1, 0, -1 }; //

struct Coordonates
{
    int position_x, position_y;
}Snake[length*height], Food, Last_Position, Aux_Coords, Special_Food;

void Pressing_Buttons()
{
    if ( _kbhit() )
    {
        Key_Substitute = 0;
        char Key = _getch();
        Key_Substitute = Key;
        switch ( Key_Substitute )
        {
            case KEY_LEFT :
            {
                if ( xRight == 0 and xLeft == 0 )
                {
                    xLeft = 1;
                    xRight = xUp = xDown = 0;
                    direction = 0;
                }
                break;
            }
            case KEY_RIGHT :
            {
                if ( xLeft == 0 and xRight == 0 )
                {
                    xRight = 1;
                    xLeft = xUp = xDown = 0;
                    direction = 2;
                }
                break;
            }
            case KEY_UP :
            {
                if ( xDown == 0 and xUp == 0 )
                {
                    xUp = 1;
                    xLeft = xRight = xDown = 0;
                    direction = 3;
                }
                break;
            }
            case KEY_DOWN :
            {
                if ( xUp == 0 and xDown == 0 )
                {
                    xDown = 1;
                    xLeft = xRight = xUp = 0;
                    direction = 1;
                }
                break;
            }
            case KEY_ENTER :
            {
                Pause = 1;
                break;
            }
            case KEY_ESCAPE :
            {
                exit_var = 1;
                break;
            }
        }
    }
}

void Pressing_Buttons_While_Pause()
{
    while ( true )
    {
        int Leave_Loop = 0;
        Key_Substitute = 0;
        switch ( Key_Substitute = _getch() )
        {
            case KEY_ENTER :
            {
                Pause = 0;
                Leave_Loop = 1;
                break;
            }
            case KEY_ESCAPE :
            {
                exit_var = Leave_Loop = 1;
                break;
            }
        }
        if ( Leave_Loop )
            break;
    }
}

void Reinitialize_Variables()
{
    Lost = exit_var = Food_Existence = Bonus_Points = Food_Spawned = Score = 0;
    Ultra = Snake_Dimension = 1;
}

void Rebuild_Snake_Platform()
{
    for ( int index1 = 0 ; index1 < height ; index1 ++ )
        for ( int index2 = 0 ; index2 < length ; index2 ++ )
        {
            if ( index1 == 0 or index1 == height-1 or index2 == 0 or index2 == length - 1 )
                platform [index1][index2] = 2;
            else
                platform [index1][index2] = 0;
        }
}

void Show_Platform()
{
    for ( int index1 = 0 ; index1 < height ; index1++ )
    {
        for ( int index2 = 0 ; index2 < length ; index2++ )
        {
            if ( platform [index1][index2] == 0 ) // Blank
                Paint_Element ( platform[index1][index2], Black_Pixel );
            if ( platform [index1][index2] == 1 ) // Snake
                Paint_Element ( platform[index1][index2], Color_For_Snake[Toggle2] );
            if ( platform [index1][index2] == 2 ) // Walls
            {
                if ( Toggle4 )
                {
                    if ( Color_For_Snake[Toggle2] == Red_Pixel)
                        Paint_Element ( platform[index1][index2], Dark_Purple_Pixel );
                    else
                        Paint_Element ( platform[index1][index2], Red_Pixel );
                }
                else
                {
                    if ( index2 != length - 1 )
                        Paint_Element ( platform[index1][index2], Black_Pixel );
                    else
                        Paint_Element ( platform[index1][index2], Light_Gray_Pixel );
                }

            }
            if ( platform [index1][index2] == 3 ) // Food
            {
                if ( Color_For_Snake[Toggle2] == Green_Pixel )
                    Paint_Element ( platform[index1][index2], Yellow_Pixel );
                else
                    Paint_Element ( platform[index1][index2], Green_Pixel );
            }
            if ( platform [index1][index2] == 4 ) // Special Food
            {
                if ( Color_For_Snake[Toggle2] == Teal_Pixel )
                    Paint_Element ( platform[index1][index2], Blue_Pixel );
                else
                    Paint_Element ( platform[index1][index2], Teal_Pixel );
            }

        }
        if ( index1 == 6 )
            cout << '\t' << "Your Score is: ";
        if ( index1 == 7 )
            cout << '\t' << "      " << Score;
        if ( Special_Food_Existence == 1 )
        {
            if ( index1 == 13 )
                cout << '\t' << "Special event ends in: ";
            if ( index1 == 14 )
            {
                cout << "  ";
                for ( int index3 = 0 ; index3 < Bars  ; index3++ )
                {
                    if ( index3 < Bonus_Points / 32 )
                        Paint_Element ( Time_Bar[index3], Teal_Pixel ); // Time Bar
                    else
                        Paint_Element ( Time_Bar[index3], Black_Pixel );
                }
            }
        }
        cout << endl ;
    }
}

void Clear_Screen()
{
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

void Generate_Food()
{
    while ( true )
    {
        Food.position_x = rand() % length;
        Food.position_y = rand() % height;
        if ( platform[Food.position_y][Food.position_x] == 0 and Food.position_x and Food.position_y )
        {
            platform[Food.position_y][Food.position_x] = 3;
            Food_Existence = 1;
            if ( Special_Food_Existence == 0 )
                Food_Spawned ++;
            break;
        }
    }
}

void Bonus_Points_System()
{
    if ( Bonus_Points )
        Bonus_Points -= 16;
    if ( Bonus_Points == 0 and Special_Food_Existence == 1 )
    {
        Special_Food_Existence = 0;
        platform[Special_Food.position_y][Special_Food.position_x] = platform[Special_Food.position_y][Special_Food.position_x + 1] =
        platform[Special_Food.position_y + 1][Special_Food.position_x] = platform[Special_Food.position_y + 1][Special_Food.position_x + 1] = 0;
        Food_Spawned ++;
        system("CLS");
    }
}

void Generate_Special_Food()
{
    while ( true )
    {
        Special_Food.position_x = rand() % (length -1);
        Special_Food.position_y = rand() % (height -1);
        if ( platform[Special_Food.position_y][Special_Food.position_x] == 0 and platform[Special_Food.position_y + 1][Special_Food.position_x] == 0 and
        platform[Special_Food.position_y][Special_Food.position_x + 1] == 0 and platform[Special_Food.position_y + 1][Special_Food.position_x + 1] == 0 )
        {
            platform[Special_Food.position_y][Special_Food.position_x] = platform[Special_Food.position_y][Special_Food.position_x + 1] =
            platform[Special_Food.position_y + 1][Special_Food.position_x] = platform[Special_Food.position_y + 1][Special_Food.position_x + 1] = 4;
            Special_Food_Existence = 1;
            Bonus_Points = 416;
            break;
        }
    }
}

void Snake_Starting_Position()
{
    Snake[0].position_x = length / 2;
    Snake[0].position_y = height / 2;
    platform [Snake[0].position_x][Snake[0].position_y] = 1;
}

void Swap_Elements(int &First, int &Second)
{
    int Auxilliary = First;
    First = Second;
    Second = Auxilliary;
}

void Snake_Move()
{
    Last_Position = Snake[0];
    Swap_Elements( platform [Snake[0].position_y][Snake[0].position_x], Forward(0) );
    Snake[0].position_y += direction_y[direction];
    Snake[0].position_x += direction_x[direction];
    platform [Snake[Ultra].position_y][Snake[Ultra].position_x] = 0;
    platform[Last_Position.position_y][Last_Position.position_x] = 1;
    Snake[Ultra] = Last_Position;
    Ultra--;
    if ( Ultra == 0)
        Ultra = Snake_Dimension;
}

void Snake_Teleports()
{
    Last_Position = Snake[0];

    if ( Snake[0].position_x == 1 )
        Snake[0].position_x = length - 2;
    else
    if ( Snake[0].position_x == length - 2 )
        Snake[0].position_x = 1;

    if ( Snake[0].position_y == 1 )
        Snake[0].position_y = height - 2;
    else
    if ( Snake[0].position_y == height - 2 )
        Snake[0].position_y = 1;

    Swap_Elements( platform [Last_Position.position_y][Last_Position.position_x], platform [Snake[0].position_y][Snake[0].position_x] );
}

void Snake_Eat()
{
    Food_Existence = 0;
    Snake_Dimension ++;
    Forward(0) = 0;
    Score += ( 8 / Diffuclty[Toggle1] );
}

void Special_Eat()
{
    Snake_Dimension ++;
    Score += ( Bonus_Points / Diffuclty[Toggle1] );
    Bonus_Points = 0;
    platform[Special_Food.position_y][Special_Food.position_x] = platform[Special_Food.position_y][Special_Food.position_x + 1] =
    platform[Special_Food.position_y + 1][Special_Food.position_x] = platform[Special_Food.position_y + 1][Special_Food.position_x + 1] = 0;
    system("CLS");
}

void Snake_Move_Logic()
{
    if ( Forward(0) == 1 )
        Lost = 1;
    if ( Forward(0) == 2 )
    {
        if ( Toggle4 )
            Lost = 1;
        else
           Snake_Teleports();
    }
    if ( Forward(0) == 3 )
        Snake_Eat();
    if ( Forward(0) == 4 )
        Special_Eat();
    if ( Forward(0) == 0 )
        Snake_Move();
}

void Possibility_of_Leaving()
{
    if ( exit_var )
    {
        if ( Score > HighScore )
            HighScore = Score;
        Save_The_HighScore();
        system("CLS");
        for ( int index1 = 0 ; index1 < height / 2 - 1 ; index1 ++ )
            cout << endl;
        cout << '\t' << '\t' << '\t' << "   You have left the game.";
        Sleep(2500);
    }
}

void Possibility_of_Losing()
{
    if ( Lost )
    {
        if ( Score > HighScore )
            HighScore = Score;
        Save_The_HighScore();
        Sleep(500);
        system("CLS");
        for ( int index1 = 0 ; index1 < height / 2 - 3 ; index1++ )
            cout << endl;
        cout << '\t' << '\t' << '\t' << '\t' << " ";
        Paint_Text ( "DEFEAT", Red );
        cout << endl << endl << '\t' << '\t' << '\t' << "     " << "Your Score: ";
        COLOR ( Green );
        cout << Score;
        COLOR ( White );
        cout << endl << endl;
        Sleep(2500);
    }
}

void Pause_Message()
{
    system("CLS");
    for ( int index1 = 0 ; index1 < height / 2 - 1 ; index1++ )
        cout << endl;
    cout << '\t' << '\t' << "The game is paused, press ";
    Paint_Text( "<Enter>", Teal );
    cout << " to resume";
}

void Snake_Game()
{
    Reinitialize_Variables();
    Rebuild_Snake_Platform();
    Snake_Starting_Position();
    srand ( time ( NULL ) );
    while ( exit_var == 0 and Lost == 0 )
    {
        if ( Pause == 0 )
        {
            if ( Food_Existence == 0 )
                Generate_Food();
            if ( Food_Spawned % 6 == 0 and Special_Food_Existence == 0 )
                Generate_Special_Food();
            Seconds_Passed ++;
            Seconds_Passed %= 2;
            Pressing_Buttons();
            if ( Seconds_Passed % 2 )
            {
                Snake_Move_Logic();
                Bonus_Points_System();
            }
            Clear_Screen();
            Show_Platform();
            Sleep( Delay[Toggle1] );
            Possibility_of_Leaving();
            Possibility_of_Losing();
        }
        else
        {
            Pause_Message();
            Pressing_Buttons_While_Pause();
            system("CLS");
            Possibility_of_Leaving();
        }
    }
}

//-----------[Menu]------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define Number_Menu 4
#define Number_Exit_Menu 2
#define Number_Chosen_Difficulty 4
#define Number_Settings_Menu 5
#define Number_Colors 7
#define Number_Chosen_Walls 2
#define Number_Chars 265

// Main Menu
#define Play 0
#define Settings 1
#define Controls 2
#define Exit 3

// Exit Menu
#define Yes 0
#define No 1

char Text_Menu[Number_Menu][Number_Chars] = { "Play", "Settings", "Controls", "Exit" },
     Text_Settings_Menu[Number_Settings_Menu][Number_Chars] = { "Difficulty: ", "Snake's Color: ", "Selector's Color: ", "Walls: ", "Back" },
     Text_Chosen_Diffuclty[Number_Chosen_Difficulty][Number_Chars] = { "Easy", "Medium", "Hard", "Insane" },
     Text_Exit_Menu[Number_Exit_Menu][Number_Chars] = { "Yes", "No" },
     Text_Chosen_Colors[Number_Colors][Number_Chars] = { "Yellow", "Green", "Teal", "Red", "Purple", "Blue", "White" },
     Text_Chosen_Walls[Number_Chosen_Walls][Number_Chars] = { "Off", "On" };

int Selection_In_Main_Menu, Selection_In_Exit_Menu, Selection_In_Settings_Menu, Key_Selected,
    Back1, Back2, Back3, Back4, Back5, Exit_Game;

void Show_Main_Menu()
{
    Clear_Screen();
    for ( int index1 = 0 ; index1 < height / 2 - 4 ; index1 ++ )
    {
        if ( index1 == 3 )
        {
            cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' ;
            Paint_Text ( "HighScore: " , Yellow );
            COLOR ( Green );
            cout << HighScore;
            COLOR ( White );
        }
        cout << endl;
    }
    for ( int index1 = 0 ; index1 < Number_Menu ; index1 ++ )
    {
        cout << '\t' << '\t' << '\t' << '\t';
        if ( Selection_In_Main_Menu == index1 )
            Paint_Text ( Text_Menu[index1] , Color_For_Selector[Toggle3] );
        else
            cout << Text_Menu[index1];
        if ( index1 != Number_Menu - 1 )
            cout << endl << endl;
    }
}

void Show_Exit_Menu()
{
    Clear_Screen();
    for ( int index1 = 0 ; index1 < height / 2 - 4 ; index1 ++ )
            cout << endl;
    cout << '\t' << '\t' << '\t' << '\t' << "Are you sure?" << endl << endl << '\t' << '\t' << '\t' << '\t' << "  " ;
    for ( int index1 = 0 ; index1 < Number_Exit_Menu ; index1 ++ )
    {
        if ( index1 == Selection_In_Exit_Menu )
            Paint_Text ( Text_Exit_Menu[index1], Color_For_Selector[Toggle3] );
        else
            cout << Text_Exit_Menu[index1];
        if ( index1 == 0 )
            cout << " / ";
    }
}

void Pressing_Enter_In_Exit_Menu()
{
    if ( Selection_In_Exit_Menu == Yes )
        Exit_Game = 1;
    if ( Selection_In_Exit_Menu == No )
        Back3 = 1;
}

void Pressing_Buttons_In_Exit_Menu()
{
    while ( true )
    {
        Back2 = Key_Selected = 0;
        switch ( Key_Selected = _getch() )
        {
            case KEY_LEFT :
            {
                if ( Selection_In_Exit_Menu == 0 )
                    Selection_In_Exit_Menu = Number_Exit_Menu;
                Selection_In_Exit_Menu --;
                Back2 = 1;
                break;
            }
            case KEY_RIGHT :
            {
                Selection_In_Exit_Menu ++;
                Selection_In_Exit_Menu %= Number_Exit_Menu;
                Back2 = 1;
                break;
            }
            case KEY_ENTER :
            {
                Pressing_Enter_In_Exit_Menu();
                system("CLS");
                Back2 = 1;
                break;
            }
        }
        if ( Back2 )
            break;
    }
}

void Exit_Menu()
{
    Selection_In_Exit_Menu = 0;
    while ( true )
    {
        Back3 = 0;
        Show_Exit_Menu();
        Pressing_Buttons_In_Exit_Menu();
        if ( Back3 or Exit_Game )
            break;
    }
}

void Show_Controls()
{
    for ( int index1 = 0 ; index1 < height / 6 - 3 ; index1 ++ )
        cout << endl;
    cout << '\t' << "The controls are: " << endl << endl << endl;
    Explaining( "<Left Key>", "Moves the Snake to Left" );
    Explaining( "<Right Key>", "Moves the Snake to Right" );
    Explaining( "<Up Key>", "Moves the Snake to Up" );
    Explaining( "<Down Key>", "Moves the Snake to Down" );
    Explaining( "<Enter Key>", "Toggles the pause mode" );
    Explaining( "<Escape Key>", "Exits the game");
    cout << endl << '\t' << "Press ";
    Paint_Text ( "<Any Key>", Color_For_Selector[Toggle3] );
    cout << " to return to to main menu.";
    _getch();
}

void Show_Settings()
{
    Clear_Screen();
    for ( int index1 = 0 ; index1 < height / 6 - 3 ; index1 ++ )
        cout << endl;
    cout << '\t' << "Settings: " << endl << endl << endl << endl;
    for ( int index1 = 0 ; index1 < Number_Settings_Menu ; index1 ++ )
    {
        cout << '\t' << "   ";
        if ( Selection_In_Settings_Menu == index1 )
            Paint_Text ( Text_Settings_Menu[index1], Color_For_Selector[Toggle3] );
        else
            cout << Text_Settings_Menu[index1];
        if ( index1 == 0 )
            cout << '\t';
        cout << '\t' ;
        if ( index1 == 0 )
            cout << Text_Chosen_Diffuclty[Toggle1];
        if ( index1 == 1 )
            Paint_Text( Text_Chosen_Colors[Toggle2], Color_For_Selector[Toggle2] );
        if ( index1 == 2 )
            Paint_Text( Text_Chosen_Colors[Toggle3], Color_For_Selector[Toggle3] );
        if ( index1 == 3 )
            cout << '\t' << Text_Chosen_Walls[Toggle4] << endl;
        if ( index1 != 4 )
            cout << endl << endl << endl << endl;
    }
}

void Pressing_Enter_In_Settings_Menu()
{
    if ( Selection_In_Settings_Menu == 0 )
    {
        Toggle1 ++;
        Toggle1 %= Number_Chosen_Difficulty;
        Save_The_Settings();
    }
    if ( Selection_In_Settings_Menu == 1 )
    {
        Toggle2 ++;
        Toggle2 %= Number_Colors;
        Save_The_Settings();
    }
    if ( Selection_In_Settings_Menu == 2 )
    {
        Toggle3 ++;
        Toggle3 %= ( Number_Colors - 1 );
        Save_The_Settings();
    }
    if ( Selection_In_Settings_Menu == 3 )
    {
        Toggle4 ++;
        Toggle4 %= Number_Chosen_Walls;
        Save_The_Settings();
    }
    if ( Selection_In_Settings_Menu == 4 )
        Back4 = 1;
}

void Pressing_Buttons_In_Setttings_Menu()
{
    while ( true )
    {
        Back5 = Key_Selected = 0;
        switch ( Key_Selected = _getch() )
        {
            case KEY_UP :
            {
                if ( Selection_In_Settings_Menu == 0 )
                    Selection_In_Settings_Menu = Number_Settings_Menu;
                Selection_In_Settings_Menu --;
                Back5 = 1;
                break;
            }
            case KEY_DOWN :
            {
                Selection_In_Settings_Menu ++;
                Selection_In_Settings_Menu %= Number_Settings_Menu;
                Back5 = 1;
                break;
            }
            case KEY_ENTER :
            {
                Pressing_Enter_In_Settings_Menu();
                system("CLS");
                Back5 = 1;
                break;
            }
        }
        if ( Back5 )
            break;
    }
}

void Settings_Menu()
{
    Selection_In_Settings_Menu = 0;
    while ( true )
    {
        Back4 = 0;
        Show_Settings();
        Pressing_Buttons_In_Setttings_Menu();
        if ( Back4 )
            break;
    }
}

void Pressing_Enter_In_Main_Menu()
{
    if ( Selection_In_Main_Menu == Play )
    {
        system("CLS");
        Snake_Game();
    }
    if ( Selection_In_Main_Menu == Settings )
    {
        system("CLS");
        Settings_Menu();
    }
    if ( Selection_In_Main_Menu == Controls )
    {
        system("CLS");
        Show_Controls();
    }
    if ( Selection_In_Main_Menu == Exit )
    {
        system("CLS");
        Exit_Menu();
    }
}

void Pressing_Buttons_In_Main_Menu()
{
    while ( true )
    {
        Back1 = Key_Selected = 0;
        switch ( Key_Selected = _getch() )
        {
            case KEY_UP :
            {
                if ( Selection_In_Main_Menu == 0 )
                    Selection_In_Main_Menu = Number_Menu;
                Selection_In_Main_Menu --;
                Back1 = 1;
                break;
            }
            case KEY_DOWN :
            {
                Selection_In_Main_Menu ++;
                Selection_In_Main_Menu %= Number_Menu;
                Back1 = 1;
                break;
            }
            case KEY_ENTER :
            {
                Pressing_Enter_In_Main_Menu();
                system("CLS");
                Back1 = 1;
                break;
            }
            case KEY_ESCAPE :
            {
                system("CLS");
                Exit_Menu();
                Back1 = 1;
                break;
            }
        }
        if ( Back1 )
            break;
    }
}

void Main_Menu()
{
    Load_The_Settings();
    Load_The_HighScore();
    while ( true )
    {
        Show_Main_Menu();
        Pressing_Buttons_In_Main_Menu();
        if ( Exit_Game )
            break;
    }
}

//-----------[Main]------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
    SetConsoleTitle("Snake made by Akriel");
    Main_Menu();
}
