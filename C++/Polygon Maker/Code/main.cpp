#include <iostream>
#include <cmath>
#include <fstream>
#include <queue>

#define N 400
#define M 1000

#define PI 3.14159265

using namespace std;

ofstream writeOut ("Display.out");

class Map
{
    public :
        int value;
        bool check;
};

Map matrix[N][N];

pair <int, int> points[M];

int totalPoints;

int radius;

int xDirections[] {0,1,0,-1},
    yDirections[] {-1,0,1,0};

int xMin, xMax,
    yMin, yMax;

int totalMoves;

char answerFill;

inline void readVariables()
{
    cout << "How many sides should this polygon have?: ";
    cin >> totalPoints;
    cout << "How big shall it be?: ";
    cin >> radius;
    cout << "And do you wish to fill it?(y/n): ";
    cin >> answerFill;
}

inline void displayMatrix()
{
    for ( int indexY = yMin; indexY <= yMax; indexY++ )
    {
        for ( int indexX = xMin; indexX <= xMax; indexX++ )
        {
            if ( matrix[indexY][indexX].value )
                writeOut << "██";
            else
                writeOut << "  ";
        }
        writeOut << "\n";
    }
}

inline void clearMatrix()
{
    for ( int indexY = yMin; indexY <= yMax; indexY++ )
        for ( int indexX = xMin; indexX <= xMax; indexX++ )
            matrix[indexY][indexX].value = matrix[indexY][indexX].check;
}

bool compatibile( int x, int y )
{
    if ( x <= xMax and x >= xMin and y <= yMax and y >= yMin )
        return true;
    else
        return false;
}

inline void determinateLimits()
{
    xMax = xMin = points[1].first;
    yMax = yMin = points[1].second;
    for ( int index = 2; index <= totalPoints; index++ )
    {
        xMax = max ( xMax, points[index].first );
        yMax = max ( yMax, points[index].second );
        xMin = min ( xMin, points[index].first );
        yMin = min ( yMin, points[index].second );
    }
}

inline void determinatePoints()
{
    double angle = 360 / totalPoints;

    for ( int index = 1; index <= totalPoints; index++ )
    {
        int x = cos( angle * PI * index / 180 ) * radius + radius;
        int y = sin( angle * PI * index / 180 ) * radius + radius;
        points[index] = make_pair( x, y );
        matrix[y][x].check = true;
    }
}

void makePathY( pair < int, int > firstPoint, pair < int, int > secondPoint )
{
    if ( ( firstPoint.second>=secondPoint.second and firstPoint.second-secondPoint.second<=1 ) or ( firstPoint.second<=secondPoint.second and secondPoint.second-firstPoint.second<=1 ) )
        return;
    if ( firstPoint.second > secondPoint.second)
        makePathY( secondPoint, firstPoint );
    if ( firstPoint.second < secondPoint.second)
    {
        int x, y;
        x = (firstPoint.first + secondPoint.first) / 2;
        y = (firstPoint.second + secondPoint.second) / 2;
        matrix[y][x].check = true;
        pair < int, int > middlePoint = make_pair(x, y);
        makePathY(firstPoint, middlePoint);
        makePathY(middlePoint, secondPoint);
    }
}

void makePathX( pair < int, int > firstPoint, pair < int, int > secondPoint )
{
    if ( ( firstPoint.first>=secondPoint.first and firstPoint.first-secondPoint.first<=1 ) or ( firstPoint.first<=secondPoint.first and secondPoint.first-firstPoint.first<=1 ) )
        return makePathY(firstPoint, secondPoint);
    if ( firstPoint.first > secondPoint.first)
        makePathX( secondPoint, firstPoint );
    if ( firstPoint.first < secondPoint.first)
    {
        int x, y;
        x = (firstPoint.first + secondPoint.first) / 2;
        y = (firstPoint.second + secondPoint.second) / 2;
        matrix[y][x].check = true;
        pair < int, int > middlePoint = make_pair(x, y);
        makePathX(firstPoint, middlePoint);
        makePathX(middlePoint, secondPoint);
    }
}

void fillSpace(int x, int y)
{
    int xNext, yNext;

    matrix[y][x].check = true;
    for ( int index = 0; index < 4; index++ )
    {
        xNext = x + xDirections[index];
        yNext = y + yDirections[index];
        if ( matrix[yNext][xNext].check == false and compatibile(xNext, yNext) )
            fillSpace(xNext, yNext);
    }
}

inline void drawLines()
{
    for ( int index = 1; index < totalPoints; index++ )
        makePathX( points[index], points[index+1]);
    makePathX( points[totalPoints], points[1]);
    if ( answerFill == 'Y' xor answerFill == 'y' )
        fillSpace(radius, radius);
}

int main()
{
    readVariables();
    determinatePoints();
    determinateLimits();
    drawLines();
    clearMatrix();
    displayMatrix();
}
