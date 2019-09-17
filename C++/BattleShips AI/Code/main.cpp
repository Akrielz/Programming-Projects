#include <bits/stdc++.h>
#include <chrono>

/*
10
----------
----------
----------
----------
----------
----------
----------
----------
----------
----------
*/

#define MISSED    'm'
#define HIT       'h'
#define DESTROYED 'd'
#define UNKNOWN   '-'

using namespace std;
using namespace std::chrono;

typedef vector<string> Board;
typedef pair<int, int> Coordonates;

// --- Ultility Functions --- \\

int convertStringToInteger(string word){
    int number = 0;
    for ( auto character : word ){
        number *= 10;
        number += character - '0';
    }

    return number;
}

// --- Ship Struct --- \\

struct Ship{
    Ship();
    Ship(Coordonates);
    Ship(Coordonates, Coordonates);

    void setPosition(Coordonates);
    void setPosition(Coordonates, Coordonates);
    void reversePosition();
    void rotatePositionToRight();
    void displayCoordonates();

    Coordonates head;
    Coordonates tail;
};

Ship::Ship(){
    ;
}

Ship::Ship(Coordonates position){
    setPosition(position);
}

Ship::Ship(Coordonates head, Coordonates tail){
    setPosition(head, tail);
}

void Ship::setPosition(Coordonates position){
    head = position;
    tail = position;
}

void Ship::setPosition(Coordonates head, Coordonates tail){
    this->head = head;
    this->tail = tail;
}

void Ship::reversePosition(){
    head.first  = 9 - head.first;
    head.second = 9 - head.second;
    tail.first  = 9 - tail.first;
    tail.second = 9 - tail.second;
}

void Ship::rotatePositionToRight(){
    int previousRow;

    previousRow = head.first;
    head.first = head.second;
    head.second = 9 - previousRow;

    previousRow = tail.first;
    tail.first = tail.second;
    tail.second = 9 - previousRow;
}

void Ship::displayCoordonates(){
    cout << head.first << " " << head.second;
    if ( head == tail ){
        cout << "\n";
        return;
    }
    cout << ":" << tail.first << " " << tail.second << "\n";
}

// --- Game Class --- \\

class Game{
public:
    Game();
    void readInput();
    void makeDecision();

private:
    Board _board;
    Board _previousBoard;
    Coordonates _target;
    unsigned _rotations;
    unsigned _length;
    milliseconds _timer;

    void displayTarget();
    void setFormation();
    bool huntMode();
    bool tileMode();
};

Game::Game(){
    _rotations = false;
    _length = 0;
}

void Game::readInput(){
    string type;
    cin >> type;
    if ( type == "INIT" ){
        _timer = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
        );
        srand(_timer.count());
        _rotations = (rand()) % 4;
        setFormation();
        return;
    }

    _length = convertStringToInteger(type);

    string newLine;
    for ( unsigned row = 0; row < _length; row++ ){
        cin >> newLine;
        _board.push_back(newLine);
    }
}

void Game::makeDecision(){
    if ( _length == 0 )
        return;

    if ( huntMode() ){
        displayTarget();
        return;
    }

    if ( tileMode() ){
        displayTarget();
        return;
    }
}

void Game::displayTarget(){
    cout << _target.first << " " << _target.second;
}

void Game::setFormation(){
    vector <Ship> ships;

    _timer = duration_cast< milliseconds >(
        system_clock::now().time_since_epoch()
    );
    srand(_timer.count());

    unsigned indexForamtion = rand()%3;

    switch(indexForamtion){
    case 0:
        ships.push_back(Ship({0, 1}));
        ships.push_back(Ship({9, 9}));
        ships.push_back(Ship({7, 7}, {8, 7}));
        ships.push_back(Ship({7, 2}, {8, 2}));
        ships.push_back(Ship({1, 9}, {3, 9}));
        ships.push_back(Ship({1, 0}, {4, 0}));
        ships.push_back(Ship({5, 5}, {9, 5}));
        break;
    case 1:
        ships.push_back(Ship({8, 1}));
        ships.push_back(Ship({8, 8}));
        ships.push_back(Ship({4, 1}, {4, 2}));
        ships.push_back(Ship({3, 5}, {4, 5}));
        ships.push_back(Ship({7, 3}, {7, 5}));
        ships.push_back(Ship({1, 1}, {1, 4}));
        ships.push_back(Ship({1, 8}, {5, 8}));
        break;
    case 2:
        ships.push_back(Ship({0, 0}));
        ships.push_back(Ship({8, 9}));
        ships.push_back(Ship({2, 1}, {3, 1}));
        ships.push_back(Ship({7, 1}, {8, 1}));
        ships.push_back(Ship({1, 5}, {3, 5}));
        ships.push_back(Ship({1, 8}, {4, 8}));
        ships.push_back(Ship({6, 3}, {6, 7}));
        break;
    }

    for ( auto &element : ships ){
        for ( unsigned index = 0; index < _rotations; index++ )
            element.rotatePositionToRight();
    }

    for ( auto element : ships )
        element.displayCoordonates();
}

bool Game::huntMode(){
    vector<Coordonates> hitPosition;
    bool hitFound = false;

    for ( unsigned row = 0; row < _length; row++ ){
        for ( unsigned column = 0; column < _length; column++ ){
            if ( _board[row][column] == HIT ){
                Coordonates hitCurrent;
                hitCurrent.first  = row;
                hitCurrent.second = column;
                hitPosition.push_back(hitCurrent);
                hitFound = true;
            }
        }
    }

    if ( hitFound == false )
        return false;

    const int xDirection[] = {0, 1, 0, -1};
    const int yDirection[] = {-1, 0, 1, 0};

    Coordonates nextPosition;
    bool vertically   = false;
    bool horizontally = false;

    for ( unsigned index = 0; index < 4; index++ ){
        nextPosition.first  = hitPosition[0].first  + yDirection[index];
        nextPosition.second = hitPosition[0].second + xDirection[index];

        if ( nextPosition.first < 0 or nextPosition.first >= _length )
            continue;

        if ( nextPosition.second < 0 or nextPosition.second >= _length )
            continue;

        if ( _board[nextPosition.first][nextPosition.second] == HIT ){
            Coordonates difference;
            difference.first  = nextPosition.first  - hitPosition[0].first;
            difference.second = nextPosition.second - hitPosition[0].second;

            if ( difference.first )
                vertically = true;

            if ( difference.second )
                horizontally = true;
        }
    }

    if ( vertically ){
        for ( auto &element : hitPosition ){
            for ( unsigned index = 0; index < 4; index += 2 ){
                nextPosition.first  = element.first  + yDirection[index];
                nextPosition.second = element.second + xDirection[index];

                if ( nextPosition.first < 0 or nextPosition.first >= _length )
                    continue;

                if ( nextPosition.second < 0 or nextPosition.second >= _length )
                    continue;

                if ( _board[nextPosition.first][nextPosition.second] == UNKNOWN ){
                    _target = nextPosition;
                    return true;
                }
            }
        }
    }

    if ( horizontally ){
        for ( auto &element : hitPosition ){
            for ( unsigned index = 1; index < 4; index += 2 ){
                nextPosition.first  = element.first  + yDirection[index];
                nextPosition.second = element.second + xDirection[index];

                if ( nextPosition.first < 0 or nextPosition.first >= _length )
                    continue;

                if ( nextPosition.second < 0 or nextPosition.second >= _length )
                    continue;

                if ( _board[nextPosition.first][nextPosition.second] == UNKNOWN ){
                    _target = nextPosition;
                    return true;
                }
            }
        }
    }

    for ( unsigned index = 0; index < 4; index++ ){
        nextPosition.first  = hitPosition[0].first  + yDirection[index];
        nextPosition.second = hitPosition[0].second + xDirection[index];

        if ( nextPosition.first < 0 or nextPosition.first >= _length )
            continue;

        if ( nextPosition.second < 0 or nextPosition.second >= _length )
            continue;

        if ( _board[nextPosition.first][nextPosition.second] == UNKNOWN ){
            _target = nextPosition;
            return true;
        }
    }

    return true;
}

bool Game::tileMode(){
    vector <Coordonates> whiteTiles;
    vector <Coordonates> blackTiles;

    for ( unsigned row = 0; row < _length; row++ ){
        for ( unsigned column = 0; column < _length; column++ ){
            if ( _board[row][column] == UNKNOWN ){
                Coordonates location;
                location.first  = row;
                location.second = column;

                if ( (row+column) % 2 != 0 )
                    blackTiles.push_back(location);
                else
                    whiteTiles.push_back(location);
            }
        }
    }

    _timer = duration_cast< milliseconds >(
        system_clock::now().time_since_epoch()
    );
    srand(_timer.count());

    unsigned numberWhiteTiles = whiteTiles.size();
    unsigned numberBlackTiles = blackTiles.size();

    if ( numberWhiteTiles ){
        unsigned index;
        index   = rand()%numberWhiteTiles;
        _target = whiteTiles[index];
        return true;
    }
    else{
        unsigned index;
        index   = rand()%numberBlackTiles;
        _target = blackTiles[index];
        return true;
    }
}

int main(){
    Game newGame;
    newGame.readInput();
    newGame.makeDecision();

    return 0;
}
