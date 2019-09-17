#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>

#define changeColor(a) SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), a )
#define Normal 15
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

using namespace std;

const int maxLength = 1e3;

const int xDirection[] = {0,1,0,-1};
const int yDirection[] = {1,0,-1,0};

pair <int, int> start, stop;

int usedLength = 33;
int acceptedLength = usedLength/1+1;

int matrix[maxLength][maxLength];
int labyrinthCode[maxLength][maxLength];

void clearScreen()
{
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

void drawPixel(int x, int y, int color){
    HANDLE hOut;
    COORD Position;
    Position.X = (x-1)*2;
    Position.Y = y-1;
    SetConsoleCursorPosition(hOut, Position);
    changeColor(color);
    cout << "  ";
    changeColor(Normal);
}

inline void display(int length, int matrix[][1000]){
    for ( int line = 1; line <= length; line++ ){
        for ( int column = 1; column <= length; column++ )
            if ( matrix[line][column] == 1 ){
                changeColor(White_Pixel);
                cout << "  ";
                changeColor(Normal);
            }
            else
            if ( matrix[line][column] == 3 ){
                changeColor(Green_Pixel);
                cout << "  ";
                changeColor(Normal);
            }
            else
                cout << "  ";
        cout << "\n";
    }
}

inline bool checkWallTop(int length, pair <int, int> leftTop){
    int x = leftTop.first;
    int y = leftTop.second;

    int walls = 0;
    for (int index = x; index <= x+length-1; index++ ){
        if ( matrix[y][index] == 1 )
            walls++;

        if ( walls >= 3 )
            return true;

        if ( matrix[y][index] == 2 )
            return true;
    }
    return false;
}

inline bool checkWallBot(int length, pair <int, int> leftTop){
    int x = leftTop.first;
    int y = leftTop.second;

    int walls = 0;
    for (int index = x; index <= x+length-1; index++ ){
        if ( matrix[y+length-1][index] == 1 )
            walls++;

        if ( walls >= 3 )
            return true;

        if ( matrix[y+length-1][index] == 2 )
            return true;
    }
    return false;
}

inline bool checkWallLeft(int length, pair <int, int> leftTop){
    int x = leftTop.first;
    int y = leftTop.second;

    int walls = 0;
    for (int index = y; index <= y+length-1; index++ ){
        if ( matrix[index][x] == 1 )
            walls++;

        if ( walls >= 3 )
            return true;

        if ( matrix[index][x] == 2 )
            return true;
    }
    return false;
}

inline bool checkWallRight(int length, pair <int, int> leftTop){
    int x = leftTop.first;
    int y = leftTop.second;

    int walls = 0;
    for (int index = y; index <= y+length-1; index++ ){
        if ( matrix[index][x+length-1] == 1 )
            walls++;

        if ( walls >= 3 )
            return true;

        if ( matrix[index][x+length-1] == 2 )
            return true;
    }
    return false;
}

inline void generateGate(int length, bool possible[4], int x, int y){
    //Choose random gate
    bool gateAvailable = false;
    for ( int index = 0; index < 4; index++)
        if ( possible[index] == 1 ){
            gateAvailable = true;
            break;
        }

    if ( gateAvailable ){
        pair <int, int> gate;

        int side;
        while( true ){
            side = rand()%4;
            if ( possible[side] )
                break;
        }

        switch(side){
            case 0:
                gate.first = rand()%length+x;
                if ( gate.first%2 ){
                    if ( gate.first == x+length-1 )
                        gate.first--;
                    else
                        gate.first++;
                }
                gate.second = y;
                possible[0] = false;
                break;

            case 1:
                gate.first = rand()%length+x;
                if ( gate.first%2 ){
                    if ( gate.first == x+length-1 )
                        gate.first--;
                    else
                        gate.first++;
                }
                gate.second = y+length-1;
                possible[1] = false;
                break;

            case 2:
                gate.first = x;

                gate.second = rand()%length+y;
                if ( gate.second%2 ){
                    if ( gate.second == y+length-1 )
                        gate.second--;
                    else
                        gate.second++;
                }
                possible[2] = false;
                break;

            case 3:
                gate.first = x+length-1;
                gate.second = rand()%length+y;
                if ( gate.second%2 ){
                    if ( gate.second == y+length-1 )
                        gate.second--;
                    else
                        gate.second++;
                }
                possible[3] = false;
                break;
        }
        matrix[gate.second][gate.first] = 2;
        if ( length == usedLength ){
            start = gate;
            matrix[2][1] = 2;
            stop = {1,2};
        }
    }

}

inline void labyrinthGenerator(int length = usedLength, pair <int, int> leftTop = {1,1}){
    int x = leftTop.first;
    int y = leftTop.second;

    bool possible[] = {0,0,0,0};

    //Top
    if ( !checkWallTop(length, leftTop) ){
        for ( int index = x; index <= x+length-1; index++ ){
            matrix[y][index] = true;
        }
        possible[0] = 1;
    }

    //Bot
    if ( !checkWallBot(length, leftTop) ){
        for ( int index = x; index <= x+length-1; index++ ){
            matrix[y+length-1][index] = true;
        }
        possible[1] = 1;
    }

    //Left
    if ( !checkWallLeft(length, leftTop) ){
        for ( int index = y; index <= y+length-1; index++ ){
            matrix[index][x] = true;
        }
        possible[2] = 1;
        if ( length == usedLength )
            possible[2] = 0;
    }

    //Right
    if ( !checkWallRight(length, leftTop) ){
        for (int index = y; index <= y+length-1; index++ ){
            matrix[index][x+length-1] = true;
        }
        possible[3] = 1;
    }

    //Generating Gates
    generateGate(length, possible, x, y);

    /*
    if ( length != usedLength ){
        if ( length == usedLength/4+1)
            generateGate(length, possible, x, y);
        else{
            int chance = rand()%5;
            if ( chance == 2 )
                generateGate(length, possible, x, y);
        }
    }
    */

    if ( length >= acceptedLength ){
        clearScreen();
        display(usedLength, matrix);
    }

    pair <int, int> nextLeftTop;
    if ( length >= 5 ){
        int middle = length/2+1;
        labyrinthGenerator(middle, leftTop);

        nextLeftTop = leftTop;
        nextLeftTop.first += middle-1;
        labyrinthGenerator(middle, nextLeftTop);

        nextLeftTop.first = leftTop.first;
        nextLeftTop.second += middle-1;
        labyrinthGenerator(middle, nextLeftTop);

        nextLeftTop.first += middle-1;
        labyrinthGenerator(middle, nextLeftTop);
    }
}

inline void convertToLabyrint(){
    for ( int line = 1; line <= usedLength; line++ ){
        for ( int column = 1; column <= usedLength; column++ )
            if ( matrix[line][column] == 1 )
                labyrinthCode[line][column] = -1;
            else
                labyrinthCode[line][column] = 0;
    }

    for ( int index = 0; index <= usedLength+1; index++ ){
        labyrinthCode[0][index] = -1;
        labyrinthCode[index][0] = -1;
        labyrinthCode[usedLength+1][index] = -1;
        labyrinthCode[index][usedLength+1] = -1;
    }
}

inline void solveLabyrinth(){
    queue <pair<int, int> > myQueue;
    myQueue.push(start);

    labyrinthCode[start.second][start.first] = 1;
    labyrinthCode[stop.second][stop.first] = -3;

    bool found = false;
    int xCurrent, yCurrent;
    int xNext, yNext;
    for ( ; myQueue.size(); ){
        xCurrent = myQueue.front().first;
        yCurrent = myQueue.front().second;

        myQueue.pop();

        for ( int index = 0; index < 4; index++ ){
            xNext = xCurrent + xDirection[index];
            yNext = yCurrent + yDirection[index];

            if ( labyrinthCode[yNext][xNext] == 0 ){
                labyrinthCode[yNext][xNext] = labyrinthCode[yCurrent][xCurrent] + 1;
                myQueue.push({xNext, yNext});
            }

            if ( labyrinthCode[yNext][xNext] == labyrinthCode[stop.second][stop.first] ){
                found = true;
                labyrinthCode[yNext][xNext] = labyrinthCode[yCurrent][xCurrent] + 1;
            }
        }
        if ( found )
            break;
    }
}

inline void showPathing(){
    queue <pair<int, int> > myQueue;
    myQueue.push(stop);
    bool found = false;
    int xCurrent, yCurrent;
    int xNext, yNext;
    matrix[stop.second][stop.first] = 3;
    for ( ; myQueue.size(); ){
        xCurrent = myQueue.front().first;
        yCurrent = myQueue.front().second;

        myQueue.pop();

        for ( int index = 0; index < 4; index++ ){
            xNext = xCurrent + xDirection[index];
            yNext = yCurrent + yDirection[index];

            if ( labyrinthCode[yNext][xNext] == labyrinthCode[yCurrent][xCurrent]-1 ){
                matrix[yNext][xNext] = 3;
                Sleep(20);
                clearScreen();
                drawPixel(xNext, yNext, Green_Pixel);
                myQueue.push({xNext, yNext});
                break;
            }
        }
        if ( found )
            break;
    }
}

inline void modifyConsole(){
    int lines = usedLength+4;
    int columns = usedLength*2;

    stringstream linesText;
    stringstream columnsText;

    linesText << lines;
    columnsText << columns;
    const string systemCommand = "mode CON: LINES=" + linesText.str() + " COLS=" + columnsText.str();
    system(systemCommand.c_str());
}

inline void clearMatrix(){
    for ( int line = 1; line <= usedLength; line++ )
        for ( int column = 1; column <= usedLength; column++ ){
            matrix[line][column] = false;
            labyrinthCode[line][column] = false;
        }
}

int main(){
    srand (time(NULL));
    modifyConsole();
    labyrinthGenerator(usedLength);
    clearScreen();
    display(usedLength, matrix);
    convertToLabyrint();
    solveLabyrinth();
    showPathing();
    clearScreen();
    display(usedLength, matrix);
    clearMatrix();
    main();
    return 0;
}
