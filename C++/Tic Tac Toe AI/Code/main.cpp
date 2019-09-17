#include <bits/stdc++.h>

#define BLANK '_'

using namespace std;

typedef vector<string> Board;

class TicTacToe{
public:
    TicTacToe();
    void readInput();

private:
    Board _board;
    char _player;
    char _enemy;
    bool _isWon;
    bool _hasManualMove;
    pair <unsigned, unsigned> _nextMove;

    void printMove();
    void searchWinPosibility(char player);
    void determineManualMove();
    unsigned determineFreeMove(char player);
};

TicTacToe :: TicTacToe(){
    _isWon         = false;
    _hasManualMove = false;

    readInput();

    //Can win
    searchWinPosibility(_player);
    if ( _isWon ){
        printMove();
        return;
    }

    //Needs to block
    searchWinPosibility(_enemy);
    if ( _isWon ){
        printMove();
        return;
    }

    //Manual move
    determineManualMove();
    if ( _hasManualMove ){
        printMove();
        return;
    }

    //Picks or Blocks the best free move
    unsigned playerValue = determineFreeMove(_player);
    pair <unsigned, unsigned> playerMove = _nextMove;

    unsigned enemyValue = determineFreeMove(_enemy);
    pair <unsigned, unsigned> enemyMove = _nextMove;

    if ( playerValue >= enemyValue ){
        _nextMove = playerMove;
    }
    else
        _nextMove = enemyMove;

    printMove();
    return;
}

void TicTacToe :: printMove(){
    cout << _nextMove.first << " " << _nextMove.second;
}

void TicTacToe :: readInput(){
    cin >> _player;

    if ( _player == 'X' )
        _enemy = 'O';
    else
        _enemy = 'X';

    string inputRow;
    for ( unsigned row = 0; row < 3; row ++ ){
        cin >> inputRow;
        _board.push_back(inputRow);
    }
}

void TicTacToe :: searchWinPosibility(char player){

    //Horizontal Check
    for ( unsigned row = 0; row < 3; row ++ ){
        unsigned counter = 0;
        bool isBlank = false;
        pair <unsigned, unsigned> blankPosition;

        for ( unsigned column = 0; column < 3; column ++ ){
            if ( _board[row][column] == player )
                counter ++;

            if ( _board[row][column] == BLANK ){
                isBlank = true;
                blankPosition.first  = row;    // y
                blankPosition.second = column; // x
            }
        }

        if ( isBlank and counter == 2 ){
            _isWon = true;
            _nextMove = blankPosition;
            return;
        }
    }

    //Vertical Check
    for ( unsigned column = 0; column < 3; column ++ ){
        unsigned counter = 0;
        bool isBlank = false;
        pair <unsigned, unsigned> blankPosition;

        for ( unsigned row = 0; row < 3; row ++ ){
            if ( _board[row][column] == player )
                counter ++;

            if ( _board[row][column] == BLANK ){
                isBlank = true;
                blankPosition.first  = row;    // y
                blankPosition.second = column; // x
            }
        }

        if ( isBlank and counter == 2 ){
            _isWon = true;
            _nextMove = blankPosition;
            return;
        }
    }

    //Main Diagonal Check
    unsigned counter = 0;
    bool isBlank = false;
    pair <unsigned, unsigned> blankPosition;

    for ( unsigned index = 0; index < 3; index ++ ){
        unsigned row    = index;
        unsigned column = index;

        if ( _board[row][column] == player )
            counter++;

        if ( _board[row][column] == BLANK ){
            isBlank = true;
            blankPosition.first  = row;    // y
            blankPosition.second = column; // x
        }
    }

    if ( isBlank and counter == 2 ){
        _isWon = true;
        _nextMove = blankPosition;
        return;
    }

    //Secondary Diagonal Check
    counter = 0;
    isBlank = false;

    for ( unsigned index = 0; index < 3; index ++ ){
        unsigned row    = index;
        unsigned column = 2-index;

        if ( _board[row][column] == player )
            counter++;

        if ( _board[row][column] == BLANK ){
            isBlank = true;
            blankPosition.first  = row;    // y
            blankPosition.second = column; // x
        }
    }

    if ( isBlank and counter == 2 ){
        _isWon = true;
        _nextMove = blankPosition;
        return;
    }
}

void TicTacToe :: determineManualMove(){
    unsigned counter = 0;
    for ( unsigned row = 0; row < 3; row++ )
        for ( unsigned column = 0; column < 3; column++ )
            if ( _board[row][column] == BLANK )
                counter++;

    if ( counter == 9 ){
        _hasManualMove = true;
        _nextMove.first = 1;
        _nextMove.second = 1;
    }

    if ( counter == 8 ){
        _hasManualMove = true;
        if ( _board[1][1] != BLANK ){
            _nextMove.first = 0;
            _nextMove.second = 0;
        }
        else{
            _nextMove.first = 1;
            _nextMove.second = 1;
        }
    }

    if ( counter == 7 ){
        pair <unsigned, unsigned> enemy;
        for ( unsigned row = 0; row < 3; row++ ){
            for ( unsigned column = 0; column < 3; column++ ){
                if ( _board[row][column] == _enemy ){
                    enemy.first  = row;
                    enemy.second = column;
                }
            }
        }

        if ( (enemy.first == 0 or enemy.first == 2) and (enemy.second == 0 or enemy.second == 2) ){
            _hasManualMove = true;
            _nextMove.first  = 2-enemy.first;
            _nextMove.second = 2-enemy.second;
        }

    }

    if ( counter == 6 and _board[1][1] == _player ){
        vector <pair <unsigned, unsigned> > enemyPositions;

        for ( unsigned row = 0; row < 3; row++ ){
            for ( unsigned column = 0; column < 3; column++ ){
                if ( _board[row][column] == _enemy ){
                    pair <unsigned, unsigned> enemy;
                    enemy.first  = row;
                    enemy.second = column;
                    enemyPositions.push_back(enemy);
                }
            }
        }

        if ( enemyPositions[0].first == 0 and enemyPositions[0].second == 0 and enemyPositions[1].first == 2 and enemyPositions[1].second == 2 ){
            _hasManualMove = true;
            _nextMove.first  = 0;
            _nextMove.second = 1;
        }

        if ( enemyPositions[0].first == 0 and enemyPositions[0].second == 2 and enemyPositions[1].first == 2 and enemyPositions[1].second == 0 ){
            _hasManualMove = true;
            _nextMove.first  = 0;
            _nextMove.second = 1;
        }
    }

    if ( counter == 1 ){
        for ( unsigned row = 0; row < 3; row++ ){
            for ( unsigned column = 0; column < 3; column++ ){
                if ( _board[row][column] == BLANK ){
                    _hasManualMove = true;
                    _nextMove.first  = row;
                    _nextMove.second = column;
                }
            }
        }
    }
}

unsigned TicTacToe :: determineFreeMove(char player){
    unsigned maxValue = 0;
    pair <unsigned, unsigned> maxValuePosition;
    char enemy;
    if ( player == 'X')
        enemy = 'O';
    else
        enemy = 'X';


    for ( unsigned preRow = 0; preRow < 3; preRow++ ){
        for ( unsigned preColumn = 0; preColumn < 3; preColumn++ ){
            if ( _board[preRow][preColumn] == BLANK ){
                //PreMove
                _board[preRow][preColumn] = player;
                unsigned valueMove = 0;

                searchWinPosibility(enemy);
                if ( _isWon ){
                    _board[_nextMove.first][_nextMove.second] = enemy;
                }

                //Horizontal Check
                for ( unsigned row = 0; row < 3; row ++ ){
                    unsigned counter = 0;
                    bool isBlank = false;
                    pair <unsigned, unsigned> blankPosition;

                    for ( unsigned column = 0; column < 3; column ++ ){
                        if ( _board[row][column] == player )
                            counter ++;

                        if ( _board[row][column] == BLANK ){
                            isBlank = true;
                            blankPosition.first  = row;    // y
                            blankPosition.second = column; // x
                        }
                    }

                    if ( isBlank and counter == 2 ){
                        valueMove++;
                    }
                }

                //Vertical Check
                for ( unsigned column = 0; column < 3; column ++ ){
                    unsigned counter = 0;
                    bool isBlank = false;
                    pair <unsigned, unsigned> blankPosition;

                    for ( unsigned row = 0; row < 3; row ++ ){
                        if ( _board[row][column] == player )
                            counter ++;

                        if ( _board[row][column] == BLANK ){
                            isBlank = true;
                            blankPosition.first  = row;    // y
                            blankPosition.second = column; // x
                        }
                    }

                    if ( isBlank and counter == 2 ){
                        valueMove++;
                    }
                }

                //Main Diagonal Check
                unsigned counter = 0;
                bool isBlank = false;
                pair <unsigned, unsigned> blankPosition;

                for ( unsigned index = 0; index < 3; index ++ ){
                    unsigned row    = index;
                    unsigned column = index;

                    if ( _board[row][column] == player )
                        counter++;

                    if ( _board[row][column] == BLANK ){
                        isBlank = true;
                        blankPosition.first  = row;    // y
                        blankPosition.second = column; // x
                    }
                }

                if ( isBlank and counter == 2 ){
                    valueMove++;
                }

                //Secondary Diagonal Check
                counter = 0;
                isBlank = false;

                for ( unsigned index = 0; index < 3; index ++ ){
                    unsigned row    = index;
                    unsigned column = 2-index;

                    if ( _board[row][column] == player )
                        counter++;

                    if ( _board[row][column] == BLANK ){
                        isBlank = true;
                        blankPosition.first  = row;    // y
                        blankPosition.second = column; // x
                    }
                }

                if ( isBlank and counter == 2 ){
                    valueMove++;
                }

                //Update Value
                if ( maxValue < valueMove ){
                    maxValue = valueMove;
                    maxValuePosition.first  = preRow;
                    maxValuePosition.second = preColumn;
                }

                //Reset PreMove
                _board[preRow][preColumn] = BLANK;
                if ( _isWon )
                    _board[_nextMove.first][_nextMove.second] = BLANK;
            }
        }
    }

    _nextMove = maxValuePosition;
    return maxValue;
}

int main()
{
    TicTacToe NewGame;
    return 0;
}
