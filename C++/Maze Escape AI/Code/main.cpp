#include <bits/stdc++.h>

#define WALL    '#'
#define BLANK   '-'
#define EXIT    'e'
#define UNKNOWN '@'

#define UP       0
#define RIGHT    1
#define DOWN     2
#define LEFT     3

#define startLocal {
#define endLocal   }

using namespace std;

typedef vector <string>            Board;
typedef vector <bool>              BinaryLine;
typedef vector <BinaryLine>        BinaryMap;
typedef vector <int>               ValueLine;
typedef vector <ValueLine>         ValueMap;
typedef pair <int, int>            Coordonates;
typedef const vector <string>      OutPuts;
typedef const vector <Coordonates> Directions;

Coordonates operator+(const Coordonates targetOne, const Coordonates targetTwo){
    Coordonates sum;

    sum.first  = targetOne.first  + targetTwo.first;
    sum.second = targetOne.second + targetTwo.second;

    return sum;
}

class Bot{
public:
    Bot();
    void getMap();
    void scanSurround();
    void attachToMap();
    void identifyTrueLocation();
    void analizeMap();
    void decideDirection();
    void updateInformation();
    void saveFile();
    void displayAnswer();

private:
    static OutPuts    _outPuts;
    static Directions _directions;

    Board             _trueMap;
    Board             _map;
    Board             _surround;
    ValueMap          _distances;
    BinaryMap         _visitedBefore;

    Coordonates       _position;
    Coordonates       _truePosition;
    Coordonates       _target;

    bool              _start;
    bool              _exitFound;
    bool              _trueLocationKnown;

    unsigned          _length;
    unsigned          _height;
    unsigned          _trueLength;
    unsigned          _trueHeight;
    unsigned          _indexDirection;

    void rotateMap(unsigned);
    bool checkIfFits(unsigned, unsigned);
};

OutPuts    Bot::_outPuts    = { "UP"  ,"RIGHT", "DOWN",  "LEFT"};
Directions Bot::_directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

Bot::Bot(){
    _position.first  = 1;
    _position.second = 1;

    _length = 3;
    _height = 3;

    _start             = false;
    _exitFound         = false;
    _trueLocationKnown = false;

    _trueMap = {
        "#######",
        "#--#--#",
        "#--#--#",
        "#--#--#",
        "e-----#",
        "#-----#",
        "#######",
    };
    _trueHeight = 7;
    _trueLength = 7;
}

void Bot::getMap(){
    ifstream fin("Memory.Aky");

    fin >> _position.first >> _position.second;

    _height = 0;
    _length = 0;

    fin >> _height >> _length;

    if ( _height == 0 or _length == 0 ){
        _length = 3;
        _height = 3;

        for ( unsigned row = 0; row < _height; row++ ){
            _map.push_back(string());
            _visitedBefore.push_back(BinaryLine());

            for ( unsigned column = 0; column < _length; column++ ){
                _map[row].push_back(UNKNOWN);
                _visitedBefore[row].push_back(false);
            }
        }
        _start = true;

        return;
    }

    startLocal;
    string newLine;
    for ( unsigned row = 0; row < _height; row++ ){
        fin >> newLine;
        _map.push_back(newLine);
    }
    endLocal;

    startLocal;
    string newLine;
    for ( unsigned row = 0; row < _height; row++ ){
        _visitedBefore.push_back(BinaryLine());
        fin >> newLine;

        bool temporary;
        for ( unsigned column = 0; column < _length; column++ ){
            temporary = newLine[column] - '0';
            _visitedBefore[row].push_back(temporary);
        }
    }
    endLocal;

    fin >> _trueLocationKnown;
}

void Bot::scanSurround(){
    startLocal;
    unsigned player;
    cin >> player;
    endLocal;

    string newLine;
    for ( unsigned row = 0; row < 3; row++ ){
        cin >> newLine;
        _surround.push_back(newLine);

        for ( unsigned column = 0; column < 3; column++ )
            if ( _surround[row][column] == EXIT )
                _exitFound = true;
    }
}

void Bot::attachToMap(){
    if ( _start == false ){
        if ( _position.first == 0 ){
            _height++;
            _visitedBefore[_position.first][_position.second] = true;
            _position.first++;

            startLocal;
            string newLine;
            for ( int column = 0; column < _length; column++ )
                newLine.push_back(UNKNOWN);

            for ( int column = -1; column <= 1; column++ )
                newLine[_position.second + column] = _surround[0][column+1];

            auto it = _map.begin();
            _map.insert(it, newLine);
            endLocal;

            startLocal;
            BinaryLine newLine;
            for ( int column = 0; column < _length; column++ )
                newLine.push_back(false);

            auto it = _visitedBefore.begin();
            _visitedBefore.insert(it, newLine);
            endLocal;
        }
        else{
            int row = _position.first - 1;
            for ( int column = -1; column <= 1; column++ )
                _map[row][_position.second + column] = _surround[0][column+1];
        }
    }
    else{
        _visitedBefore[_position.first][_position.second] = true;
        for ( int row = 0; row < _height; row++ ){
            for ( int column = 0; column < _height; column++ ){
                _map[row][column] = _surround[row][column];
            }
        }
    }
}

void Bot::identifyTrueLocation(){
    unsigned frequency = 0;
    unsigned rowFit;
    unsigned columnFit;
    unsigned rotationFit;

    for ( unsigned indexRotation = 0; indexRotation < 4; indexRotation++ ){
        rotateMap(RIGHT);

        for ( unsigned row = 0; row <= _trueHeight - _height; row++ ){
            for ( unsigned column = 3; column <= _trueLength-_length; column++ ){
                if ( checkIfFits(row, column) ){
                    frequency++;

                    rowFit    = row;
                    columnFit = column;
                    rotationFit = indexRotation;
                }
            }
        }
    }

    if ( frequency == 1 ){
        _trueLocationKnown = true;

        for ( unsigned indexRotation = 0; indexRotation <= rotationFit; indexRotation++ )
            rotateMap(RIGHT);

        _map = _trueMap;

        _length = _trueLength;
        _height = _trueHeight;

        _position.first  += rowFit;
        _position.second += columnFit;

        BinaryMap visited;
        for ( unsigned resetRow = 0; resetRow < _trueHeight; resetRow++ ){
            visited.push_back(BinaryLine());

            for ( unsigned resetColumn = 0; resetColumn < _trueLength; resetColumn++ )
                visited[resetRow].push_back(false);
        }
        _visitedBefore = visited;

        for ( unsigned reRotate = rotationFit+1; reRotate < 4; reRotate++ )
            rotateMap(RIGHT);

        return;
    }
}

bool Bot::checkIfFits(unsigned currentY, unsigned currentX){
    for ( unsigned row = currentY; row < currentY + _height; row++ ){
        for ( unsigned column = currentX; column < currentX + _length; column++ ){
            if ( _map[row-currentY][column-currentX] != _trueMap[row][column] and _map[row-currentY][column-currentX] != UNKNOWN )
                return false;
        }
    }

    return true;

}

void Bot::analizeMap(){
    queue <Coordonates> myQueue;
    _distances;

    for ( unsigned row = 0; row < _height; row++ ){
        _distances.push_back(ValueLine());
        for ( unsigned column = 0; column < _length; column++ ){
            _distances[row].push_back(0);
        }
    }

    _distances[_position.first][_position.second] = 2;

    Coordonates currentPosition;
    Coordonates nextPosition;

    char target;

    if ( _exitFound )
        target = EXIT;
    else
        target = BLANK;

    if ( _trueLocationKnown )
        target = EXIT;

    myQueue.push(_position);

    for ( ;myQueue.size(); myQueue.pop() ){
        currentPosition = myQueue.front();
        int currentY = currentPosition.first;
        int currentX = currentPosition.second;

        for ( unsigned index = 0; index < 4; index++ ){
            nextPosition = currentPosition + _directions[index];
            int nextY = nextPosition.first;
            int nextX = nextPosition.second;

            if ( nextY < 0 or nextY > _height-1 or nextX < 0 or nextX > _length-1 )
                continue;

            if ( _distances[nextY][nextX] == 0 ){

                if ( _map[nextY][nextX] != WALL ){
                    _distances[nextY][nextX] = _distances[currentY][currentX] + 1;
                    myQueue.push(nextPosition);

                    if ( _map[nextY][nextX] == target and _visitedBefore[nextY][nextX] == false ){
                        _target.first  = nextY;
                        _target.second = nextX;

                        return;
                    }
                }
            }
        }
    }
}

void Bot::decideDirection(){
    queue <Coordonates> myQueue;

    Coordonates currentPosition;
    Coordonates nextPosition;

    myQueue.push(_target);
    for ( ; myQueue.size(); myQueue.pop() ){
        currentPosition = myQueue.front();
        int currentY = currentPosition.first;
        int currentX = currentPosition.second;

        for ( unsigned index = 0; index < 4; index++ ){
            nextPosition = currentPosition + _directions[index];
            int nextY = nextPosition.first;
            int nextX = nextPosition.second;

            if ( nextY < 0 or nextY > _height-1 or nextX < 0 or nextX > _length-1 )
                continue;

            if ( _distances[nextY][nextX] == _distances[currentY][currentX] - 1 ){
                myQueue.push(nextPosition);

                if ( _distances[nextY][nextX] == 2 ){
                    if ( index >= 2 )
                        index -= 2;
                    else
                        index += 2;
                    _indexDirection = index;

                    return;
                }

                break;
            }
        }
    }
}

void Bot::updateInformation(){
    _position  = _position + _directions[_indexDirection];

    switch(_indexDirection){
    case UP:
        break;

    case RIGHT:
        rotateMap(LEFT);
        break;

    case DOWN:
        rotateMap(DOWN);
        break;

    case LEFT:
        rotateMap(RIGHT);
        break;
    }
}

void Bot::rotateMap(unsigned index){
    if ( index == RIGHT ){
        int previousRow;

        previousRow      = _position.first;
        _position.first  = _position.second;
        _position.second = _height - previousRow - 1;

        Board     rotatedMap;
        BinaryMap rotatedVisited;
        for ( unsigned row = 0; row < _length; row++ ){
            rotatedMap.push_back(string());
            rotatedVisited.push_back(BinaryLine());

            for ( unsigned column = 0; column < _height; column++ ){
                rotatedMap[row].push_back(char());
                rotatedVisited[row].push_back(false);
            }
        }

        for ( unsigned row = 0; row < _height; row++ ){
            for ( unsigned column = 0; column < _length; column++ ){
                unsigned currentRow    = row;
                unsigned currentColumn = column;

                previousRow   = currentRow;
                currentRow    = currentColumn;
                currentColumn = _height - previousRow - 1;

                rotatedMap[currentRow][currentColumn]     = _map[row][column];
                rotatedVisited[currentRow][currentColumn] = _visitedBefore[row][column];
            }
        }

        _map           = rotatedMap;
        _visitedBefore = rotatedVisited;

        swap(_height, _length);
    }
    else{
        for ( int indexRotate = 0; indexRotate < index ; indexRotate++ )
            rotateMap(RIGHT);
    }
}

void Bot::saveFile(){
    ofstream fout("Memory.Aky");

    fout << _position.first << " " << _position.second << "\n";
    fout << _height << " " << _length << "\n";

    for ( unsigned row = 0; row < _height; row++ ){
        for ( unsigned column = 0; column < _length; column++ )
            fout << _map[row][column];
        fout << "\n";
    }

    fout << "\n";

    for ( unsigned row = 0; row < _height; row++ ){
        for ( unsigned column = 0; column < _length; column++ )
            fout << _visitedBefore[row][column];
        fout << "\n";
    }

    fout << "\n";
    fout << _trueLocationKnown;
}

void Bot::displayAnswer(){
    cout << _outPuts[_indexDirection];
}

int main(){
    Bot newBot;
    newBot.getMap();
    newBot.scanSurround();
    newBot.attachToMap();
    newBot.identifyTrueLocation();
    newBot.analizeMap();
    newBot.decideDirection();
    newBot.updateInformation();
    newBot.saveFile();
    newBot.displayAnswer();

    return 0;
}
