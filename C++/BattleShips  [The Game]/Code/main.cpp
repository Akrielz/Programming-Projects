///-------------[Libraries]----------------------------------------------------------------------------------------------------------------\\\

#include <chrono>       /* Time     */
#include <ctime>        /* Time     */
#include <fstream>      /* Files    */
#include <graphics.h>   /* Graphics */
#include <iomanip>      /* Debug    */
#include <iostream>     /* Debug    */
#include <stdlib.h>     /* Random   */
#include <windows.h>    /* Sleep    */

///-------------[GlobalVariables]----------------------------------------------------------------------------------------------------------\\\

using namespace std;

const int windowWidth  = 1280;
const int windowHeight = 720;

const int FONT_SIZE  = 4;
const int FONT_WIDTH = FONT_SIZE*5;

const int X_DIRECTION[] = {0,1,1,1,0,-1,-1,-1};
const int Y_DIRECTION[] = {-1,-1,0,1,1,1,0,-1};

const bool DEBUG_MODE = false;
const bool TIMER_MODE = false;

int optionsSelector[5];

///-------------[NameSpaces]---------------------------------------------------------------------------------------------------------------\\\

namespace MainMenu{
    inline void initialize();
    inline void display();
}

namespace GameMenu{
    inline void initialize();
    inline void display();
}

namespace OptionsMenu{
    inline void initialize();
    inline void display();
}

namespace HistoryMenu{
    inline void initialize();
    inline void display();
}

namespace Utility{
    int stringLenght(char *word){
        int letter = 0;
        for (; word[letter]; letter++);

        return letter;
    }

    void clearRectangle(int left, int top, int right, int bot, int color = BLACK){
        int points[] = {left, top, right, top, right, bot, left, bot};
        int previousColor = getcolor();

        setfillstyle(SOLID_FILL, color);
        setcolor(color);
        fillpoly(4, points);
        setcolor(previousColor);
        setfillstyle(SOLID_FILL, previousColor);
    }

    void clearScreen(int color = BLACK){
        clearRectangle(0, 0, windowWidth, windowHeight);
    }

    void drawText(int x, int y, char* text, int color = WHITE, int additionalSize = 0, int fontSize = 4){
        if (stringLenght(text) == 0)
            return;

        setcolor(color);
        settextstyle(COMPLEX_FONT, HORIZ_DIR, fontSize);

        int width = textwidth(text);
        int height = textheight(text);

        int letters = Utility::stringLenght(text);
        int offSet = width/2;

        int top   = y - height/2 - additionalSize/4;
        int left  = x - width /2 - additionalSize/2;
        int bot   = y + height/2 + additionalSize/4;
        int right = x + width /2 + additionalSize/2;

        clearRectangle(left, top, right, bot);

        outtextxy(x-offSet, y-FONT_SIZE*4, text);

        settextstyle(COMPLEX_FONT, HORIZ_DIR, FONT_SIZE);
    }

    char* concatenate(char *first, char* second){
        int lengthOne = stringLenght(first);
        int lengthTwo = stringLenght(second);

        int length = lengthOne + lengthTwo;
        char *result = new char[length+1];

        for (int index = 0; index < lengthOne; index++)
            result[index] = first[index];
        for (int index = 0; index < lengthTwo; index++)
            result[index+lengthOne] = second[index];
        result[length] = '\0';

        return result;
    }

    char* convertIntToChar(int number){
        if (number == 0)
            return "0";

        if (number < 0)
            return concatenate("-", convertIntToChar(-number));

        char* result = new char[32];

        char* digits = new char[32];
        int totalDigits = 0;

        for (; number; number/=10)
            digits[totalDigits++] = number%10+'0';

        for (int index = 0; index < totalDigits; index++)
            result[index] = digits[totalDigits-1-index];
        result[totalDigits] = '\0';

        return result;
    }

    int convertCharToInt(char *number){
        if (number[0] == '-')
            return -convertCharToInt(number+1);

        int digits = stringLenght(number);

        int result = 0;

        for (int index = 0; index < digits; index++)
            result = result*10+(number[index]-'0');

        return result;
    }

    double getProcent(int part, int total){
        double dPart  = part;
        double dTotal = total;

        return (100*dPart)/total;
    }
}

///-------------[BoatState]----------------------------------------------------------------------------------------------------------------\\\

struct BoatState{
    int x;
    int y;
    int direction;
    int damage;
    bool alive;
};

///-------------[EndInfo]------------------------------------------------------------------------------------------------------------------\\\

struct EndInfo{
    int difficulty;
    int gamemode;
    int reveal;
    int turns;
    int status;
    time_t time;
};

const int MAX_MATCHES = 1000;
int totalMatches;

EndInfo matches[MAX_MATCHES];

inline void readEndInfo(){
    ifstream fin ("History.stg");
    fin >> totalMatches;

    for (int index = 0; index < totalMatches; index++){
        fin >> matches[index].difficulty;
        fin >> matches[index].gamemode;
        fin >> matches[index].reveal;
        fin >> matches[index].turns;
        fin >> matches[index].status;
        fin >> matches[index].time;
    }

    fin.close();
}

inline void uploadEndInfo(EndInfo example){
    readEndInfo();
    totalMatches++;

    ofstream fout("History.stg");
    fout << totalMatches << "\n";

    fout << example.difficulty << " ";
    fout << example.gamemode << " ";
    fout << example.reveal << " ";
    fout << example.turns << " ";
    fout << example.status << " ";
    fout << example.time << "\n";

    for (int index = 0; index < totalMatches-1; index++){
        fout << matches[index].difficulty << " ";
        fout << matches[index].gamemode << " ";
        fout << matches[index].reveal << " ";
        fout << matches[index].turns << " ";
        fout << matches[index].status << " ";
        fout << matches[index].time << "\n";
    }

    fout.close();
    readEndInfo();
}

///-------------[Button]-------------------------------------------------------------------------------------------------------------------\\\

struct Button{
    int x;
    int y;

    int width;
    int height;

    char *text;

    bool selected;
    bool placed;
};

inline void drawButton(Button example, int color = WHITE, int FONT_SIZE = 4, int arrow = -1){
    int width  = example.width;
    int height = example.height;

    int FONT_WIDTH = FONT_SIZE*5;

    int top   = example.y-height/2;
    int left  = example.x-width /2;
    int bot   = example.y+height/2;
    int right = example.x+width /2;

    setcolor(color);

    rectangle(left, top, right, bot);

    if (arrow == -1){
        int letters = Utility::stringLenght(example.text);

        if (letters == 0){
            example.text = " ";
            letters = 1;
        }

        int offSet = (FONT_WIDTH*letters)/2;

        settextstyle(COMPLEX_FONT, HORIZ_DIR, FONT_SIZE);
        outtextxy(example.x-offSet, example.y-FONT_SIZE*4, example.text);
    }
    else
    if (0 <= arrow and arrow <= 7){
        width  = example.width-20;
        height = example.height-20;

        Utility::clearRectangle(left+10, top+10, right-10, bot-10);

        int x = example.x;
        int y = example.y;

        COORD points[4];
        points[0].X = x + X_DIRECTION[arrow]*(width/2);
        points[0].Y = y + Y_DIRECTION[arrow]*(height/2);

        points[1].X = x - X_DIRECTION[arrow]*(width/2);
        points[1].Y = y - Y_DIRECTION[arrow]*(height/2);

        x = points[0].X;
        y = points[0].Y;

        int rightDir = (arrow+1) % 8;
        points[2].X = x - X_DIRECTION[rightDir]*(width/2);
        points[2].Y = y - Y_DIRECTION[rightDir]*(height/2);

        int leftDir = arrow-1;
        if (leftDir == -1)
            leftDir = 7;

        points[3].X = x - X_DIRECTION[leftDir]*(width/2);
        points[3].Y = y - Y_DIRECTION[leftDir]*(height/2);

        line(points[0].X, points[0].Y, points[1].X, points[1].Y);
        line(points[0].X, points[0].Y, points[2].X, points[2].Y);
        line(points[0].X, points[0].Y, points[3].X, points[3].Y);
    }
    else{
        settextstyle(COMPLEX_FONT, HORIZ_DIR, FONT_SIZE);
        Utility::drawText(example.x, example.y, "?", color, 0, FONT_SIZE);
    }
}

inline bool isMouseOnButton(Button example, int additionSize = 0){
    int width  = example.width;
    int height = example.height;

    int top   = example.y-height/2 - additionSize/2;
    int left  = example.x-width /2 - additionSize/2;
    int bot   = example.y+height/2 + additionSize/2;
    int right = example.x+width /2 + additionSize/2;

    if ( mousey() > top and mousey() < bot and mousex() > left and mousex() < right )
        return true;

    return false;
}

///-------------[Options]------------------------------------------------------------------------------------------------------------------\\\

struct Option{
    int x;
    int y;

    int offSetX;

    int width;
    int height;
    int selected = 0;

    unsigned int MAX_POSSIBLITIES;

    char *description;
    char *possibilities[10];
};

inline void drawOption(Option &example){
    outtextxy(example.x, example.y, example.description);

    int gap = 200;
    int selected = example.selected;

    int letters = Utility::stringLenght(example.possibilities[selected]);
    int offSet = (FONT_WIDTH*letters)/2;

    example.offSetX = windowWidth - example.x - gap - offSet;

    int width  = example.width;
    int height = example.height;

    int top   = example.y-height/2 + FONT_SIZE*4;
    int left  = example.offSetX-width /2 + offSet;
    int bot   = example.y+height/2 + FONT_SIZE*4;
    int right = example.offSetX+width /2 + offSet;

    Utility::clearRectangle(left, top, right, bot);

    outtextxy(example.offSetX, example.y, example.possibilities[selected]);
}

int isMouseOnOption(Option example){
    int width  = example.width;
    int height = example.height;

    int selected = example.selected;

    int letters = Utility::stringLenght(example.possibilities[selected]);
    int offSet = (FONT_WIDTH*letters)/2;

    int top   = example.y-height/2 + FONT_SIZE*4;
    int left  = example.offSetX-width /2 + offSet;
    int bot   = example.y+height/2 + FONT_SIZE*4;
    int right = example.offSetX+width /2 + offSet;

    int middleX = (left+right) / 2;

    if (mousey() > top and mousey() < bot and mousex() > left and mousex() < middleX)
        return -1;

    if (mousey() > top and mousey() < bot and mousex() > middleX and mousex() < right)
        return 1;

    return 0;
}

///-------------[MainMenu]-----------------------------------------------------------------------------------------------------------------\\\

namespace MainMenu{
    const int MAX_BUTTONS = 4;
    Button buttons[MAX_BUTTONS];

    int selector = 0;
    int previousSelector = 0;

    int top;
    int bot;
    int left;
    int right;

    inline void initialize(){
        int gap = 100;
        int height = 50;
        int width = 240;

        if (optionsSelector[0] == 0){
            buttons[0].text = "Play";
            buttons[1].text = "Options";
            buttons[2].text = "History";
            buttons[3].text = "Exit";
        }
        if (optionsSelector[0] == 1){
            buttons[0].text = "Joaca";
            buttons[1].text = "Optiuni";
            buttons[2].text = "Istoric";
            buttons[3].text = "Iesire";
        }
        if (optionsSelector[0] == 2){
            buttons[0].text = "Jouer";
            buttons[1].text = "Options";
            buttons[2].text = "L'histoire";
            buttons[3].text = "Sortie";
        }

        int yStart = windowHeight/2 - (gap)*(MAX_BUTTONS-1)/2;
        for (int index = 0; index < MAX_BUTTONS; index++){
            buttons[index].height = height;
            buttons[index].width  = width;
            buttons[index].x = windowWidth/2;

            if (index == 0)
                buttons[index].y = yStart;
            else
                buttons[index].y = buttons[index-1].y + gap;
        }

        int additionalSize = 70;

        top   = yStart - additionalSize/2 - height/2;
        bot   = buttons[MAX_BUTTONS-1].y + additionalSize/2 + height/2;
        left  = windowWidth/2 - width/2 - additionalSize/2;
        right = windowWidth/2 + width/2 + additionalSize/2;
    }

    inline void drawButtons(){
        for (int index = 0; index < MAX_BUTTONS; index++)
            if (index == selector)
                drawButton(buttons[index], LIGHTBLUE);
            else
                drawButton(buttons[index], WHITE);
    }

    inline void drawTitle(){
        char *title;
        title = "BattleShips";

        int fontSize   = 6;
        int fontWidth  = 4;
        int fontHeight = 5;

        settextstyle(5, HORIZ_DIR, fontSize);

        int middle = (left+right)/2;
        int letters = Utility::stringLenght(title);
        int offSetX = (fontSize*fontWidth*letters)/2;
        int offSetY = fontSize*fontHeight;

        outtextxy(middle-offSetX, top-offSetY, title);

        settextstyle(COMPLEX_FONT, HORIZ_DIR, 4);
    }

    inline void display(){
        Utility::clearScreen();
        drawButtons();
        rectangle(left, top, right, bot);
        drawTitle();

        bool stop = false;
        while (!stop){
            for (int index = 0; index < MAX_BUTTONS; index++){
                if (isMouseOnButton(buttons[index])){

                    previousSelector = selector;
                    selector = index;

                    if (selector != previousSelector){
                        drawButton(buttons[selector], LIGHTBLUE);
                        drawButton(buttons[previousSelector], WHITE);
                    }
                }
            }

            if ( ismouseclick(WM_LBUTTONUP) ){
                clearmouseclick(WM_LBUTTONUP);

                switch(selector){
                case 0:
                    if (isMouseOnButton(buttons[selector])){
                        stop = true;
                        GameMenu::initialize();
                        GameMenu::display();
                        return;
                    }
                    break;

                case 1:
                    if (isMouseOnButton(buttons[selector])){
                        stop = true;
                        OptionsMenu::initialize();
                        OptionsMenu::display();
                        return;
                    }
                    break;

                case 2:
                    if (isMouseOnButton(buttons[selector])){
                        stop = true;
                        HistoryMenu::initialize();
                        HistoryMenu::display();
                        return;
                    }
                    break;

                case 3:
                    if (isMouseOnButton(buttons[selector])){
                        exit(0);
                        stop = true;
                    }
                    break;
                }
            }
        }
    }
}

///-------------[GameMenu]-----------------------------------------------------------------------------------------------------------------\\\

namespace GameMenu{
    const int MAX_LENGTH = 10;
    const int MAX_SHIPS = 4;
    const int MAX_SHIPS_SIZE = 11;
    const int MAX_CHESTS = 2;

    const int sizeShip[MAX_SHIPS] = {4, 3, 2, 2};

    Button matrixLeft [MAX_LENGTH][MAX_LENGTH];
    Button matrixRight[MAX_LENGTH][MAX_LENGTH];

    Button shipsLeft [MAX_SHIPS_SIZE];
    Button shipsRight[MAX_SHIPS_SIZE];

    Button goBack;
    Button endTurn;

    BoatState leftBoats [MAX_SHIPS];
    BoatState rightBoats[MAX_SHIPS];

    Button bonusChests[MAX_CHESTS];

    int leftRemained;
    int rightRemained;

    bool targetHard[MAX_LENGTH][MAX_LENGTH];

    inline void initialize(){
        int xStart = 220;
        int yStart = 150;
        int width  = 35;
        int height = 35;
        int gap    = 40;

        for (int line = 0; line < MAX_LENGTH; line++){
            for (int column = 0; column < MAX_LENGTH; column++){

                matrixLeft[line][column].width    = width;
                matrixLeft[line][column].height   = height;
                matrixLeft[line][column].text     = "";
                matrixLeft[line][column].selected = false;
                matrixLeft[line][column].placed   = false;

                if (line == 0)
                    matrixLeft[line][column].y = yStart;
                else
                    matrixLeft[line][column].y = matrixLeft[line-1][column].y + gap;

                if (column == 0)
                    matrixLeft[line][column].x = xStart;
                else
                    matrixLeft[line][column].x = matrixLeft[line][column-1].x + gap;
            }
        }

        for (int line = 0; line < MAX_LENGTH; line++){
            for (int column = MAX_LENGTH-1; column >= 0; column--){

                matrixRight[line][column].width    = width;
                matrixRight[line][column].height   = height;
                matrixRight[line][column].text     = "";
                matrixRight[line][column].selected = false;
                matrixRight[line][column].placed   = false;

                if (line == 0)
                    matrixRight[line][column].y = yStart;
                else
                    matrixRight[line][column].y = matrixRight[line-1][column].y + gap;

                if (column == MAX_LENGTH-1)
                    matrixRight[line][column].x = windowWidth - xStart;
                else
                    matrixRight[line][column].x = matrixRight[line][column+1].x - gap;
            }
        }

        double multiplier = 2.5;
        int ship = 0;
        int totalSize = 0;
        for (int index = 0; index < MAX_SHIPS_SIZE; index++){

            shipsLeft [index].width    = width;
            shipsLeft [index].height   = height;
            shipsLeft [index].text     = "";
            shipsLeft [index].selected = false;
            shipsLeft [index].placed   = false;
            shipsLeft [index].x        = xStart - gap * multiplier;

            shipsRight[index].width    = width;
            shipsRight[index].height   = height;
            shipsRight[index].text     = "";
            shipsRight[index].selected = false;
            shipsRight[index].placed   = false;
            shipsRight[index].x        = windowWidth -(xStart - gap * multiplier);

            if (index == 0){
                shipsLeft [index].y = yStart-35;
                shipsRight[index].y = yStart-35;
            }
            else{
                shipsLeft [index].y = shipsRight[index-1].y + gap;
                shipsRight[index].y = shipsLeft[index-1].y + gap;
            }

            if (index == totalSize+sizeShip[ship]){
                shipsLeft[index].y = shipsRight[index].y += gap/4;
                totalSize += sizeShip[ship];
                ship++;
            }

        }

        goBack.text   = "Back";
        goBack.width  = 300;
        goBack.height = 50;
        goBack.x      = xStart+goBack.width/2-width/2;
        goBack.y      = windowHeight-100;

        endTurn.text   = "End Turn";
        endTurn.width  = 300;
        endTurn.height = 50;
        endTurn.x      = windowWidth-(xStart+endTurn.width/2-width/2);
        endTurn.y      = windowHeight-100;

        if (optionsSelector[0] == 1){
            goBack.text  = "Inapoi";
            endTurn.text = "Incheie Tura";
        }
        if (optionsSelector[0] == 2){
            goBack.text  = "Retour";
            endTurn.text = "Fin de Tour";
        }

        for (int index = 0; index < MAX_SHIPS; index++){
            leftBoats[index].direction = -1;
            leftBoats[index].alive = true;
            leftBoats[index].damage = 0;
        }

        for (int index = 0; index < MAX_SHIPS; index++){
            rightBoats[index].direction = -1;
            rightBoats[index].alive = true;
            rightBoats[index].damage = 0;
        }

        leftRemained = 100;
        rightRemained = 100;

        if (optionsSelector[2]){
            for (int index = 0; index < MAX_CHESTS; index++){
                bonusChests[index].selected = false;
                bonusChests[index].placed   = false;
                bonusChests[index].width    = width;
                bonusChests[index].height   = height;
                bonusChests[index].text     = "";
                bonusChests[index].y        = windowHeight-(yStart - 50);
            }

            bonusChests[0].x = xStart-gap*multiplier;
            bonusChests[1].x = windowWidth-(xStart-gap*multiplier);
        }
        srand (time(NULL));
    }

    inline void drawBoard(Button matrix[MAX_LENGTH][MAX_LENGTH]){
        for (int line = 0; line < MAX_LENGTH; line++){
            for (int column = 0; column < MAX_LENGTH; column++){
                if (matrix[line][column].placed)
                    drawButton(matrix[line][column], GREEN, 3);
                else{
                    if (matrix[line][column].selected)
                        drawButton(matrix[line][column], LIGHTRED, 3);
                    else
                        drawButton(matrix[line][column], WHITE, 3);
                }
            }
        }
    }

    inline void drawShips(Button ships[MAX_SHIPS_SIZE]){
        int additionalSize = 30;

        int width  = ships[0].width  + additionalSize;
        int height = ships[0].height + additionalSize;

        int left  = ships[0].x - width/2;
        int right = ships[MAX_SHIPS_SIZE-1].x + width/2;
        int top   = ships[0].y - height/2;
        int bot   = ships[MAX_SHIPS_SIZE-1].y + height/2;

        for (int index = 0; index < MAX_SHIPS_SIZE; index++){
            if (Utility::stringLenght(ships[index].text) == 0)
                drawButton(ships[index], WHITE, 3);
            else
                drawButton(ships[index], RED, 3);
        }
        setcolor(WHITE);

        rectangle(left, top, right, bot);
    }

    inline void drawChest(Button chest){
        int additionalSize = 30;

        int width  = chest.width  + additionalSize;
        int height = chest.height + additionalSize;

        int left  = chest.x - width/2;
        int right = chest.x + width/2;
        int top   = chest.y - height/2;
        int bot   = chest.y + height/2;

        rectangle(left, top, right, bot);
        drawButton(chest);
    }

    inline void displayMessageBox(char* message, int color){
        int width = 400;
        int height = 250;

        int centerX = windowWidth/2;
        int centerY = windowHeight/2;

        int left  = centerX - width/2;
        int right = centerX + width/2;
        int top   = centerY - height/2;
        int bot   = centerY + height/2;

        Utility::clearRectangle(left, top, right, bot, color);
        Utility::clearRectangle(left+5, top+5, right-5, bot-5, BLACK);

        Utility::drawText(centerX, centerY, message, color);
        Sleep(5000);
    }

    inline void simulatePossibilities(int argument[MAX_LENGTH][MAX_LENGTH], Button matrix[MAX_LENGTH][MAX_LENGTH], int &best, bool skip = false){
        for (int line = 0; line < MAX_LENGTH; line++)
            for (int column = 0; column < MAX_LENGTH; column++)
                argument[line][column] = 0;

        best = 0;
        for (int line = 0; line < MAX_LENGTH; line++){
            for (int column = 0; column < MAX_LENGTH; column++){
                for (int direction = 0; direction < 8; direction++){
                    COORD current;
                    current.X = column;
                    current.Y = line;

                    for (int step = 0; step < 4; step++){
                        if (current.X < 0 or current.X >= MAX_LENGTH)
                            break;

                        if (current.Y < 0 or current.Y >= MAX_LENGTH)
                            break;

                        if (matrix[current.Y][current.X].selected == true)
                            break;

                        if (step == 1 and (leftBoats[2].alive or leftBoats[3].alive))
                            argument[line][column]++;

                        if (step == 2 and leftBoats[1].alive)
                            argument[line][column]++;

                        if (step == 3 and leftBoats[0].alive)
                            argument[line][column]++;

                        current.X += X_DIRECTION[direction];
                        current.Y += Y_DIRECTION[direction];
                    }

                    if (skip)
                        direction++;
                }
                best = max(best, argument[line][column]);
            }
        }
    }

    inline void display(){
        Utility::clearScreen();
        line(windowWidth/2, 100, windowWidth/2, windowHeight-100);

        drawShips(shipsLeft);
        if (optionsSelector[2])
            drawChest(bonusChests[0]);
        drawBoard(matrixLeft);

        drawBoard(matrixRight);
        drawShips(shipsRight);
        if (optionsSelector[2])
            drawChest(bonusChests[1]);

        drawButton(goBack);
        drawButton(endTurn);

        if (optionsSelector[0] == 0)
            Utility::drawText(windowWidth/2, 50, "Place Your Ships");
        if (optionsSelector[0] == 1)
            Utility::drawText(windowWidth/2, 50, "Plasati Navele");
        if (optionsSelector[0] == 2)
            Utility::drawText(windowWidth/2, 50, "Placez les Navires");

        bool boardDrawn[2][MAX_LENGTH][MAX_LENGTH];
        for (int dimension = 0; dimension < 2; dimension++)
            for (int line = 0; line < MAX_LENGTH; line++)
                for (int column = 0; column < MAX_LENGTH; column++)
                    boardDrawn[dimension][line][column] = false;

        bool shipDrawn[2][MAX_SHIPS];
        for (int dimension = 0; dimension < 2; dimension++)
            for (int index = 0; index < MAX_SHIPS; index++)
                shipDrawn[dimension][index] = false;

        int shipGaps[MAX_SHIPS+1];

        shipGaps[0] = 0;
        for (int index = 1; index <= MAX_SHIPS; index++){
            shipGaps[index] = sizeShip[index-1];
            if (index)
                shipGaps[index] += shipGaps[index-1];
        }

        bool goBackDrawn  = false;
        bool endTurnDrawn = false;

        int lastSelectedShip  = -1;
        int selectedShip      = -1;
        int selectedDirection = 0;

        bool attackTime = false;
        int turn = -1;

        int shots = 0;
        char *ammo;

        bool directionChanged = false;
        int frame = 0;

        chrono::time_point<chrono::system_clock> startTime = chrono::system_clock::now();
        while (true){
            if (TIMER_MODE) {
                if (frame % 10000 == 0){
                    chrono::time_point<chrono::system_clock> currentTime = chrono::system_clock::now();
                    chrono::duration<double> differenceTime = currentTime - startTime;

                    char* stringTime = Utility::convertIntToChar(differenceTime.count());
                    if (optionsSelector[0] == 0)
                        stringTime = Utility::concatenate("Time: ", stringTime);
                    if (optionsSelector[0] == 1)
                        stringTime = Utility::concatenate("Timp: ", stringTime);
                    if (optionsSelector[0] == 2)
                        stringTime = Utility::concatenate("Temps: ", stringTime);

                    Utility::drawText(windowWidth-110, 50, stringTime, WHITE, 20);

                    frame = 1;
                }
                else
                    frame++;
            }

            //AI Place
            if (turn == 0){
                for (int index = 0; index < MAX_SHIPS; index++){
                    rightBoats[index].alive = true;

                    bool satisfied = false;
                    while (true){
                        int newX = rand() % MAX_LENGTH;
                        int newY = rand() % MAX_LENGTH;

                        int newDirection = rand() % 8;
                        if (optionsSelector[4]){
                            if (newDirection % 2)
                                newDirection++;
                            if (newDirection == 8)
                                newDirection = 0;
                        }
                        int stopDirection = newDirection;

                        do{
                            int currentX = newX;
                            int currentY = newY;
                            bool isSafe = true;

                            for (int step = 0; step < sizeShip[index]; step++){
                                if (currentX < 0 or currentX >= MAX_LENGTH){
                                    isSafe = false;
                                    break;
                                }

                                if (currentY < 0 or currentY >= MAX_LENGTH){
                                    isSafe = false;
                                    break;
                                }

                                if (matrixRight[currentY][currentX].placed){
                                    isSafe = false;
                                    break;
                                }

                                currentX += X_DIRECTION[newDirection];
                                currentY += Y_DIRECTION[newDirection];
                            }

                            if (isSafe == true){
                                rightBoats[index].x = newX;
                                rightBoats[index].y = newY;
                                rightBoats[index].direction = newDirection;
                                satisfied = true;
                                break;
                            }
                            else{
                                newDirection++;
                                if (optionsSelector[4])
                                    newDirection++;

                                if (newDirection == 8)
                                    newDirection = 0;
                            }
                        }while(newDirection!=stopDirection);

                        if (satisfied){
                            int currentX = rightBoats[index].x;
                            int currentY = rightBoats[index].y;
                            int currentDirection = rightBoats[index].direction;

                            for (int step = 0; step < sizeShip[index]; step++){
                                matrixRight[currentY][currentX].placed = true;
                                if (optionsSelector[1])
                                    drawButton(matrixRight[currentY][currentX], MAGENTA, 3);
                                currentX += X_DIRECTION[currentDirection];
                                currentY += Y_DIRECTION[currentDirection];
                            }
                            break;
                        }
                        else
                            continue;
                    }
                }

                turn++;
                for (int index = 0; index < MAX_SHIPS; index++)
                    if (leftBoats[index].alive)
                        shots += sizeShip[index];

                shots = 6;
                if (optionsSelector[3] == 3)
                    shots = 11;

                if(shots == 0){
                    if (optionsSelector[0] == 0)
                        displayMessageBox("You lost!", LIGHTRED);
                    if (optionsSelector[0] == 1)
                        displayMessageBox("Ai pierdut!", LIGHTRED);
                    if (optionsSelector[0] == 2)
                        displayMessageBox("Tu as perdu!", LIGHTRED);

                    chrono::time_point<chrono::system_clock> getTime = chrono::system_clock::now();

                    EndInfo situation;
                    situation.difficulty = optionsSelector[3];
                    situation.gamemode   = optionsSelector[4];
                    situation.reveal     = optionsSelector[1];
                    situation.status     = 0;
                    situation.time       = chrono::system_clock::to_time_t(getTime);
                    situation.turns      = turn-1;

                    uploadEndInfo(situation);

                    MainMenu::initialize();
                    MainMenu::display();
                    return;
                }

                if(optionsSelector[4])
                    shots = 1;

                shots = min(shots, rightRemained);

                if (optionsSelector[0] == 0)
                    ammo = Utility::concatenate("Ammo: ", Utility::convertIntToChar(shots));
                if (optionsSelector[0] == 1)
                    ammo = Utility::concatenate("Rachete: ", Utility::convertIntToChar(shots));
                if (optionsSelector[0] == 2)
                    ammo = Utility::concatenate("Coups: ", Utility::convertIntToChar(shots));

                Utility::drawText(110, 50, ammo, WHITE, 20);
            }

            if (turn >= 2 and turn%2 == 0){
                shots = 0;
                for(int index = 0; index < MAX_SHIPS; index++){
                    if (rightBoats[index].alive)
                        shots += sizeShip[index];
                }

                if (shots == 0){

                    if (optionsSelector[0] == 0)
                        displayMessageBox("You won!", GREEN);
                    if (optionsSelector[0] == 1)
                        displayMessageBox("Ai castigat!", GREEN);
                    if (optionsSelector[0] == 2)
                        displayMessageBox("Tu as gagne!", GREEN);

                    chrono::time_point<chrono::system_clock> getTime = chrono::system_clock::now();

                    EndInfo situation;
                    situation.difficulty = optionsSelector[3];
                    situation.gamemode   = optionsSelector[4];
                    situation.reveal     = optionsSelector[1];
                    situation.status     = 1;
                    situation.time       = chrono::system_clock::to_time_t(getTime);
                    situation.turns      = turn-1;

                    uploadEndInfo(situation);

                    MainMenu::initialize();
                    MainMenu::display();
                    return;
                }

                if(optionsSelector[4])
                    shots = 1;

                shots = min(shots, leftRemained);

                bool normalActive;

                if (optionsSelector[4] == 0){
                    if (turn > 6 and optionsSelector[3] == 0)
                        normalActive = true;
                    else
                        normalActive = false;
                }
                else{
                    if (turn > 20 and optionsSelector[3] == 0)
                        normalActive = true;
                    else
                        normalActive = false;
                }

                COORD attacked;
                //Easy AI
                if (optionsSelector[3] == 0 and normalActive == false){
                    int leftNotPlaced[MAX_LENGTH*MAX_LENGTH];
                    int totalNotPlaced = 0;

                    for (int line = 0; line < MAX_LENGTH; line++)
                        for (int column = 0; column < MAX_LENGTH; column++)
                            if (matrixLeft[line][column].placed == false and matrixLeft[line][column].selected == false)
                                leftNotPlaced[totalNotPlaced++] = line*10+column;

                    for ( ;shots; shots--){
                        int target = rand()%totalNotPlaced;
                        int line   = leftNotPlaced[target]/10;
                        int column = leftNotPlaced[target]%10;

                        matrixLeft[line][column].selected = true;
                        matrixLeft[line][column].text = Utility::convertIntToChar(turn);

                        attacked.X = column;
                        attacked.Y = line;

                        totalNotPlaced--;
                        swap(leftNotPlaced[target], leftNotPlaced[totalNotPlaced]);
                    }
                }

                //Normal AI
                if (optionsSelector[3] == 1 or normalActive == true){
                    int leftNotSelected[MAX_LENGTH*MAX_LENGTH];
                    int totalNotSeleceted = 0;

                    for (int line = 0; line < MAX_LENGTH; line++)
                        for (int column = 0; column < MAX_LENGTH; column++)
                            if (matrixLeft[line][column].selected == false)
                                leftNotSelected[totalNotSeleceted++] = line*10+column;

                    for (; shots; shots--){
                        int target = rand()%totalNotSeleceted;
                        int line   = leftNotSelected[target]/10;
                        int column = leftNotSelected[target]%10;

                        matrixLeft[line][column].selected = true;
                        matrixLeft[line][column].text = Utility::convertIntToChar(turn);

                        leftRemained--;

                        attacked.X = column;
                        attacked.Y = line;

                        totalNotSeleceted--;
                        swap(leftNotSelected[target], leftNotSelected[totalNotSeleceted]);
                    }
                }

                //Hard AI V1
                if (optionsSelector[3] == 2 and optionsSelector[4] == false){
                    int targetChosen = -1;
                    int shipChosen   = -1;

                    for (int index = 0; index < MAX_SHIPS; index++){
                        if (leftBoats[index].alive){
                            int position = shipGaps[index]+leftBoats[index].damage-1;
                            if (position < shipGaps[index])
                                continue;

                            int hitTurn  = Utility::convertCharToInt(shipsLeft[position].text);
                            targetChosen = hitTurn;
                            shipChosen   = index;
                        }
                        if (targetChosen != -1)
                            break;
                    }

                    COORD myQueue[MAX_LENGTH*MAX_LENGTH];
                    int top = 0;
                    int bot = 0;
                    int line;
                    int column;

                    bool visited[MAX_LENGTH][MAX_LENGTH];
                    for (int y = 0; y < MAX_LENGTH; y++)
                        for (int x = 0; x < MAX_LENGTH; x++)
                            visited[y][x] = false;

                    if (targetChosen == -1){
                        int sizeGrid = 2;
                        for (int index = 0; index < MAX_SHIPS; index++)
                            if (leftBoats[index].alive and sizeShip[index] % 2 == 0)
                                sizeGrid = max(sizeGrid, sizeShip[index]);

                        for (int line = 0; line < MAX_LENGTH; line++){
                            for (int column = 0; column < MAX_LENGTH; column++){
                                targetHard[line][column] = true;

                                if (line % sizeGrid != sizeGrid-1 and column % sizeGrid != sizeGrid-1)
                                    targetHard[line][column] = false;
                            }
                        }

                        int best;
                        int choices[MAX_LENGTH][MAX_LENGTH];
                        simulatePossibilities(choices, matrixLeft, best);

                        COORD myList[MAX_LENGTH*MAX_LENGTH];
                        int totalPositions = 0;

                        for (int line = 0; line < MAX_LENGTH; line++){
                            for (int column = 0; column < MAX_LENGTH; column++){
                                if (choices[line][column] == best){
                                    myList[totalPositions].X = column;
                                    myList[totalPositions].Y = line;
                                    totalPositions++;
                                }
                            }
                        }

                        int item = rand()%totalPositions;

                        line   = myList[item].Y;
                        column = myList[item].X;

                        myQueue[top].X = column;
                        myQueue[top].Y = line;
                        top++;

                        visited[line][column] = true;
                    }
                    else{
                        char stop = false;
                        if (leftBoats[shipChosen].damage == 1){
                            for (int y = 0; y < MAX_LENGTH; y++){
                                for (int x = 0; x < MAX_LENGTH; x++){
                                    if (matrixLeft[y][x].selected){
                                        int hitTurn = Utility::convertCharToInt(matrixLeft[y][x].text);

                                        int box = shipGaps[shipChosen] + leftBoats[shipChosen].damage - 1;
                                        int turnChosen = Utility::convertCharToInt(shipsLeft[box].text);

                                        if (hitTurn == turnChosen){
                                            bool isSurrounded = true;
                                            for (int direction = 0; direction < 8; direction++){
                                                COORD neightbour;
                                                neightbour.X = x + X_DIRECTION[direction];
                                                neightbour.Y = y + Y_DIRECTION[direction];

                                                if (neightbour.X < 0 or neightbour.X >= MAX_LENGTH)
                                                    continue;

                                                if (neightbour.Y < 0 or neightbour.Y >= MAX_LENGTH)
                                                    continue;

                                                if (matrixLeft[neightbour.Y][neightbour.X].selected == false){
                                                    isSurrounded = false;
                                                    break;
                                                }

                                            }

                                            if (isSurrounded == false){
                                                myQueue[top].X = x;
                                                myQueue[top].Y = y;
                                                top++;
                                                visited[y][x] = true;
                                            }
                                        }


                                    }
                                }
                            }
                        }

                        if (leftBoats[shipChosen].damage != 1){
                            int firstPosition  = shipGaps[shipChosen] + leftBoats[shipChosen].damage-1;
                            int secondPosition = shipGaps[shipChosen] + leftBoats[shipChosen].damage-2;

                            int firstTurn  = Utility::convertCharToInt(shipsLeft[firstPosition].text);
                            int secondTurn = Utility::convertCharToInt(shipsLeft[secondPosition].text);

                            COORD firstQueue[MAX_LENGTH*MAX_LENGTH];
                            COORD secondQueue[MAX_LENGTH*MAX_LENGTH];

                            int firstTop  = 0;
                            int secondTop = 0;

                            for (int line = 0; line < MAX_LENGTH; line++){
                                for (int column = 0; column < MAX_LENGTH; column++){
                                    if (matrixLeft[line][column].selected){
                                        int turnChosen = Utility::convertCharToInt(matrixLeft[line][column].text);

                                        if (turnChosen == firstTurn){
                                            firstQueue[firstTop].X = column;
                                            firstQueue[firstTop].Y = line;
                                            firstTop++;
                                        }

                                        if (turnChosen == secondTurn){
                                            secondQueue[secondTop].X = column;
                                            secondQueue[secondTop].Y = line;
                                            secondTop++;
                                        }
                                    }
                                }
                            }

                            int minDistance = 1<<30;
                            COORD relation;
                            for (int indexOne = 0; indexOne < firstTop; indexOne++){
                                for (int indexTwo = 0; indexTwo < secondTop; indexTwo++){
                                    int xDistance = abs(firstQueue[indexOne].X - secondQueue[indexTwo].X);
                                    int yDistance = abs(firstQueue[indexOne].Y - secondQueue[indexTwo].Y);

                                    int squareDistance = max(xDistance, yDistance);
                                    if (squareDistance < minDistance){
                                        minDistance = squareDistance;
                                        relation.X = indexOne;
                                        relation.Y = indexTwo;
                                    }
                                }
                            }
                            int indexOne = relation.X;
                            int indexTwo = relation.Y;

                            COORD average;
                            average.X = (firstQueue[indexOne].X + secondQueue[indexTwo].X)/2;
                            average.Y = (firstQueue[indexOne].Y + secondQueue[indexTwo].Y)/2;

                            myQueue[top] = average;
                            top++;
                        }
                    }

                    COORD current;
                    COORD next;

                    for (;top;){
                        current = myQueue[bot];
                        bot++;

                        if (targetChosen == -1){
                            if (targetHard[current.Y][current.X] and !matrixLeft[current.Y][current.X].selected){
                                matrixLeft[current.Y][current.X].selected = true;
                                matrixLeft[current.Y][current.X].text = Utility::convertIntToChar(turn);
                                shots--;
                                leftRemained--;
                            }
                        }
                        else{
                            if (!matrixLeft[current.Y][current.X].selected){
                                matrixLeft[current.Y][current.X].selected = true;
                                matrixLeft[current.Y][current.X].text = Utility::convertIntToChar(turn);
                                shots--;
                                leftRemained--;
                            }
                        }

                        if (shots == 0)
                            break;

                        for(int direction = 0; direction < 8; direction++){
                            next.X = current.X + X_DIRECTION[direction];
                            next.Y = current.Y + Y_DIRECTION[direction];

                            if (next.X < 0 or next.X >= MAX_LENGTH)
                                continue;

                            if (next.Y < 0 or next.Y >= MAX_LENGTH)
                                continue;

                            if (visited[next.Y][next.X] == false){
                                visited[next.Y][next.X] = true;

                                myQueue[top].X = next.X;
                                myQueue[top].Y = next.Y;
                                top++;
                            }
                        }

                        if (bot > top)
                            break;
                    }

                    if (shots){
                        for (int line = 0; line < MAX_LENGTH; line++){
                            if (shots == 0)
                                break;

                            for (int column = 0; column < MAX_LENGTH; column++){
                                if (shots == 0)
                                    break;

                                if (matrixLeft[line][column].selected == false){
                                    matrixLeft[line][column].selected = true;
                                    matrixLeft[line][column].text = Utility::convertIntToChar(turn);
                                    shots--;
                                    leftRemained--;
                                }
                            }
                        }
                    }
                }

                //Hard AI V2
                if (optionsSelector[3] == 2 and optionsSelector[4] == true){
                    bool huntMode  = false;
                    int shipChosen = -1;

                    for (int index = 0; index < MAX_SHIPS; index++){
                        if (leftBoats[index].alive){
                            if (leftBoats[index].damage == 0)
                                continue;

                            shipChosen = index;
                            huntMode   = true;
                        }
                        if (shipChosen != -1)
                            break;
                    }

                    if (huntMode == false){
                        int best;
                        int choices[MAX_LENGTH][MAX_LENGTH];
                        simulatePossibilities(choices, matrixLeft, best, true);

                        if (DEBUG_MODE){
                            int sum = 0;
                            for (int line = 0; line < MAX_LENGTH; line++)
                                for (int column = 0; column < MAX_LENGTH; column++)
                                    sum += choices[line][column];

                            cout << "\n\n" << turn << "\n";
                            for (int line = 0; line < MAX_LENGTH; line++){
                                for (int column = 0; column < MAX_LENGTH; column++){
                                    cout << fixed << setprecision(2) << Utility::getProcent(choices[line][column], sum) << "%\t";
                                }
                                cout << "\n\n";
                            }
                        }

                        COORD myList[MAX_LENGTH*MAX_LENGTH];
                        int totalPositions = 0;

                        for (int line = 0; line < MAX_LENGTH; line++){
                            for (int column = 0; column < MAX_LENGTH; column++){
                                if (choices[line][column] == best and (column+line)%2 == 0){
                                    myList[totalPositions].X = column;
                                    myList[totalPositions].Y = line;
                                    totalPositions++;
                                }
                            }
                        }

                        if (totalPositions == 0){
                            for (int line = 0; line < MAX_LENGTH; line++){
                                for (int column = 0; column < MAX_LENGTH; column++){
                                    if (choices[line][column] == best-1 and (column+line)%2 == 0 and best != 1){
                                        myList[totalPositions].X = column;
                                        myList[totalPositions].Y = line;
                                        totalPositions++;
                                    }
                                }
                            }
                        }

                        if (totalPositions == 0){
                            for (int line = 0; line < MAX_LENGTH; line++){
                                for (int column = 0; column < MAX_LENGTH; column++){
                                    if (choices[line][column] == best){
                                        myList[totalPositions].X = column;
                                        myList[totalPositions].Y = line;
                                        totalPositions++;
                                    }
                                }
                            }
                        }

                        if (DEBUG_MODE){
                            cout << "Nr Possibilities: " << totalPositions << "\n";
                        }

                        int item = rand()%totalPositions;

                        int line   = myList[item].Y;
                        int column = myList[item].X;

                        matrixLeft[line][column].selected = true;
                        matrixLeft[line][column].text = Utility::convertIntToChar(turn);
                        shots--;
                        leftRemained--;

                        attacked.X = column;
                        attacked.Y = line;
                    }
                    else{
                        COORD myQueue[4];
                        int top = 0;

                        int currentX  = leftBoats[shipChosen].x;
                        int currentY  = leftBoats[shipChosen].y;
                        int direction = leftBoats[shipChosen].direction;

                        for(int step = 0; step < sizeShip[shipChosen]; step++){
                            if (matrixLeft[currentY][currentX].selected){
                                myQueue[top].X = currentX;
                                myQueue[top].Y = currentY;
                                top++;
                            }
                            currentX += X_DIRECTION[direction];
                            currentY += Y_DIRECTION[direction];
                        }

                        if (top == 1){
                            for (int direction = 0; direction < 8; direction += 2){
                                COORD neightbour;
                                neightbour.X = myQueue[0].X + X_DIRECTION[direction];
                                neightbour.Y = myQueue[0].Y + Y_DIRECTION[direction];

                                if (neightbour.X < 0 or neightbour.X >= MAX_LENGTH)
                                    continue;

                                if (neightbour.Y < 0 or neightbour.Y >= MAX_LENGTH)
                                    continue;

                                if (matrixLeft[neightbour.Y][neightbour.X].selected == false){
                                    matrixLeft[neightbour.Y][neightbour.X].selected = true;
                                    matrixLeft[neightbour.Y][neightbour.X].text = Utility::convertIntToChar(turn);
                                    shots--;
                                    leftRemained--;

                                    attacked.X = neightbour.X;
                                    attacked.Y = neightbour.Y;
                                    break;
                                }
                            }
                        }
                        else{
                            int horizontal = true;

                            COORD first = myQueue[0];
                            for (int index = 1; index < top; index++){
                                if (myQueue[index].Y != first.Y){
                                    horizontal = false;
                                    break;
                                }
                            }

                            if (horizontal){
                                int left  = first.X;
                                int right = first.X;
                                int y     = first.Y;

                                for (int index = 1; index < top; index++){
                                    left  = min(left, (int)(myQueue[index].X));
                                    right = max(right,(int)(myQueue[index].X));
                                }
                                left--;
                                right++;

                                if (left >= 0 and matrixLeft[y][left].selected == false){
                                    matrixLeft[y][left].selected = true;
                                    matrixLeft[y][left].text = Utility::convertIntToChar(turn);

                                    attacked.X = left;
                                    attacked.Y = y;
                                }
                                else{
                                    matrixLeft[y][right].selected = true;
                                    matrixLeft[y][right].text = Utility::convertIntToChar(turn);

                                    attacked.X = right;
                                    attacked.Y = y;
                                }
                                shots--;
                            }
                            else{
                                int up   = first.Y;
                                int down = first.Y;
                                int x    = first.X;

                                for (int index = 1; index < top; index++){
                                    up   = min(up,   (int)(myQueue[index].Y));
                                    down = max(down, (int)(myQueue[index].Y));
                                }
                                up--;
                                down++;

                                if (up >= 0 and matrixLeft[up][x].selected == false){
                                    matrixLeft[up][x].selected = true;
                                    matrixLeft[up][x].text = Utility::convertIntToChar(turn);

                                    attacked.X = x;
                                    attacked.Y = up;
                                }
                                else{
                                    matrixLeft[down][x].selected = true;
                                    matrixLeft[down][x].text = Utility::convertIntToChar(turn);

                                    attacked.X = x;
                                    attacked.Y = down;
                                }
                                shots--;
                            }
                        }
                    }
                }

                //Cheater AI
                if (optionsSelector[3] == 3){

                    for (int line = 0; line < MAX_LENGTH; line++){
                        if (shots == 0)
                            break;

                        for (int column = 0; column < MAX_LENGTH; column++){
                            if (shots == 0)
                                break;

                            if (matrixLeft[line][column].placed == true and matrixLeft[line][column].selected == false){
                                matrixLeft[line][column].selected = true;
                                matrixLeft[line][column].text = Utility::convertIntToChar(turn);
                                shots--;
                                leftRemained--;

                                attacked.X = column;
                                attacked.Y = line;
                            }
                        }
                    }

                    if (shots)
                        shots = 0;
                }

                //Check Damage
                bool found = false;

                for(int index = 0; index < MAX_SHIPS; index++){
                    if (found)
                        break;
                    int currentX  = leftBoats[index].x;
                    int currentY  = leftBoats[index].y;
                    int direction = leftBoats[index].direction;

                    if (leftBoats[index].alive == false)
                        continue;

                    for(int step = 0; step < sizeShip[index]; step++){
                        if (matrixLeft[currentY][currentX].selected){
                            int number = Utility::convertCharToInt(matrixLeft[currentY][currentX].text);

                            if (number == turn){
                                int position = shipGaps[index]+leftBoats[index].damage;
                                shipsLeft[position].text = Utility::convertIntToChar(turn);
                                leftBoats[index].damage++;
                                if (optionsSelector[4])
                                    found = true;
                            }

                            if (leftBoats[index].damage == sizeShip[index])
                                leftBoats[index].alive = false;

                            if (found)
                                break;
                        }
                        currentX += X_DIRECTION[direction];
                        currentY += Y_DIRECTION[direction];
                    }
                }

                drawShips(shipsLeft);
                if (optionsSelector[4] == 0)
                    drawBoard(matrixLeft);
                else{
                    if (DEBUG_MODE and optionsSelector[4])
                        cout << "Attacked: {" << attacked.Y << ", " << attacked.X << "}\n";

                    if (matrixLeft[attacked.Y][attacked.X].placed)
                        drawButton(matrixLeft[attacked.Y][attacked.X], GREEN, 3);
                    else{
                        if (matrixLeft[attacked.Y][attacked.X].selected)
                            drawButton(matrixLeft[attacked.Y][attacked.X], LIGHTRED, 3);
                        else
                            drawButton(matrixLeft[attacked.Y][attacked.X], WHITE, 3);
                    }
                }
                turn++;

                for (int index = 0; index < MAX_SHIPS; index++)
                    if (leftBoats[index].alive)
                        shots += sizeShip[index];

                if (shots == 0){
                    if (optionsSelector[0] == 0)
                        displayMessageBox("You lost!", LIGHTRED);
                    if (optionsSelector[0] == 1)
                        displayMessageBox("Ai pierdut!", LIGHTRED);
                    if (optionsSelector[0] == 2)
                        displayMessageBox("Tu as perdu!", LIGHTRED);

                    chrono::time_point<chrono::system_clock> getTime = chrono::system_clock::now();

                    EndInfo situation;
                    situation.difficulty = optionsSelector[3];
                    situation.gamemode   = optionsSelector[4];
                    situation.reveal     = optionsSelector[1];
                    situation.status     = 0;
                    situation.time       = chrono::system_clock::to_time_t(getTime);
                    situation.turns      = turn-1;

                    uploadEndInfo(situation);

                    MainMenu::initialize();
                    MainMenu::display();
                    return;
                }

                if(optionsSelector[4])
                    shots = 1;

                shots = min(shots, rightRemained);

                if (optionsSelector[0] == 0)
                    ammo = Utility::concatenate("Ammo: ", Utility::convertIntToChar(shots));
                if (optionsSelector[0] == 1)
                    ammo = Utility::concatenate("Rachete: ", Utility::convertIntToChar(shots));
                if (optionsSelector[0] == 2)
                    ammo = Utility::concatenate("Coups: ", Utility::convertIntToChar(shots));
                Utility::drawText(110, 50, ammo, WHITE, 20);
            }



            if (isMouseOnButton(goBack)){
                if (!goBackDrawn){
                    goBackDrawn = true;
                    drawButton(goBack, LIGHTBLUE);
                }
            }
            else{
                if (goBackDrawn){
                    goBackDrawn = false;
                    drawButton(goBack);
                }
            }

            if (isMouseOnButton(endTurn)){
                if (!endTurnDrawn){
                    endTurnDrawn = true;
                    drawButton(endTurn, LIGHTBLUE);
                }
            }
            else{
                if (endTurnDrawn){
                    endTurnDrawn = false;
                    drawButton(endTurn);
                }
            }

            if (ismouseclick(WM_LBUTTONUP)){
                clearmouseclick(WM_LBUTTONUP);

                if (isMouseOnButton(goBack)){
                    MainMenu::initialize();
                    MainMenu::display();
                    return;
                }

                if (isMouseOnButton(endTurn)){
                    bool available = true;

                    if (attackTime == false){
                        for (int index = 0; index < MAX_SHIPS; index++){
                            if (leftBoats[index].direction == -1)
                                available = false;
                        }

                        if (available){
                            attackTime = true;
                            turn++;
                            for (int ship = shipGaps[lastSelectedShip]; ship < shipGaps[lastSelectedShip+1]; ship++)
                                drawButton(shipsLeft[ship], WHITE, 3);

                            if (optionsSelector[0] == 0)
                                Utility::drawText(windowWidth/2, 50, "Attack the enemy");
                            if (optionsSelector[0] == 1)
                                Utility::drawText(windowWidth/2, 50, "Ataca inamicul", WHITE, 20);
                            if (optionsSelector[0] == 2)
                                Utility::drawText(windowWidth/2, 50, "Attaquer l'ennemi", WHITE, 20);
                        }
                    }
                    else{
                        if (shots == 0){
                            //CheckDamage
                            for(int index = 0; index < MAX_SHIPS; index++){
                                int currentX  = rightBoats[index].x;
                                int currentY  = rightBoats[index].y;
                                int direction = rightBoats[index].direction;

                                if (rightBoats[index].alive == false)
                                    continue;

                                for(int step = 0; step < sizeShip[index]; step++){
                                    if (matrixRight[currentY][currentX].selected){
                                        int number = Utility::convertCharToInt(matrixRight[currentY][currentX].text);
                                        if (number == turn){
                                            int position = shipGaps[index]+rightBoats[index].damage;
                                            shipsRight[position].text = Utility::convertIntToChar(turn);
                                            rightBoats[index].damage++;
                                        }
                                        if (rightBoats[index].damage == sizeShip[index])
                                            rightBoats[index].alive = false;
                                    }

                                    currentX += X_DIRECTION[direction];
                                    currentY += Y_DIRECTION[direction];
                                }
                            }
                            drawShips(shipsRight);
                            turn++;
                        }
                    }
                }

                //Select Ships
                if (attackTime == false){
                    for ( int index = 0; index < MAX_SHIPS_SIZE; index++ ){

                        for (int ship = 0; ship < MAX_SHIPS; ship++ ){
                            if ( shipGaps[ship] <= index and index < shipGaps[ship+1] and isMouseOnButton(shipsLeft[index], 7)){
                                selectedShip = ship;
                                break;
                            }
                        }
                    }
                    if (lastSelectedShip != -1 and lastSelectedShip != selectedShip){
                        for (int ship = shipGaps[lastSelectedShip]; ship < shipGaps[lastSelectedShip+1]; ship++)
                            drawButton(shipsLeft[ship], WHITE, 3);
                    }

                    if (selectedShip != -1){
                        for (int ship = shipGaps[selectedShip]; ship < shipGaps[selectedShip+1]; ship++)
                            drawButton(shipsLeft[ship], GREEN, 3);
                        lastSelectedShip = selectedShip;

                    }
                }

                //Select Matrix
                for ( int line = 0; line < MAX_LENGTH; line++ ){
                    for ( int column = 0; column < MAX_LENGTH; column++ ){
                        if ( isMouseOnButton(matrixLeft[line][column], 7) and attackTime == false){

                            if (selectedShip != -1){
                                if (leftBoats[selectedShip].direction != -1){
                                    int currentX = leftBoats[selectedShip].x;
                                    int currentY = leftBoats[selectedShip].y;
                                    int direction = leftBoats[selectedShip].direction;

                                    for (int step = 0; step < sizeShip[selectedShip]; step++){
                                        drawButton(matrixLeft[currentY][currentX], WHITE, 3);
                                        matrixLeft[currentY][currentX].placed= false;

                                        currentX += X_DIRECTION[direction];
                                        currentY += Y_DIRECTION[direction];
                                    }
                                }

                                int currentX = column;
                                int currentY = line;
                                bool isSafe = true;

                                for (int step = 0; step < sizeShip[selectedShip]; step++){
                                    if (matrixLeft[currentY][currentX].placed){
                                        isSafe = false;
                                        break;
                                    }
                                    if (currentX < 0 or currentX >= MAX_LENGTH){
                                        isSafe = false;
                                        break;
                                    }
                                    if (currentY < 0 or currentY >= MAX_LENGTH){
                                        isSafe = false;
                                        break;
                                    }

                                    currentX += X_DIRECTION[selectedDirection];
                                    currentY += Y_DIRECTION[selectedDirection];
                                }

                                if (isSafe  == false)
                                    continue;

                                currentX = column;
                                currentY = line;

                                for (int step = 0; step < sizeShip[selectedShip]; step++){
                                    drawButton(matrixLeft[currentY][currentX], GREEN, 3);
                                    matrixLeft[currentY][currentX].placed = true;

                                    currentX += X_DIRECTION[selectedDirection];
                                    currentY += Y_DIRECTION[selectedDirection];
                                }

                                leftBoats[selectedShip].x = column;
                                leftBoats[selectedShip].y = line;
                                leftBoats[selectedShip].direction = selectedDirection;
                            }
                        }

                        //Attack
                        if ( isMouseOnButton(matrixRight[line][column], 7) and attackTime == true ){
                            if (matrixRight[line][column].selected == false){
                                shots--;
                                rightRemained--;

                                if (shots != -1){
                                    matrixRight[line][column].text = Utility::convertIntToChar(turn);
                                    matrixRight[line][column].selected = true;
                                    drawButton(matrixRight[line][column], LIGHTRED, 3);
                                }

                                if (shots == -1){
                                    shots = 0;
                                    rightRemained++;
                                }

                                if (shots == 0 and optionsSelector[4]){
                                    //CheckDamage
                                    for(int index = 0; index < MAX_SHIPS; index++){
                                        int currentX  = rightBoats[index].x;
                                        int currentY  = rightBoats[index].y;
                                        int direction = rightBoats[index].direction;

                                        if (rightBoats[index].alive == false)
                                            continue;

                                        for(int step = 0; step < sizeShip[index]; step++){
                                            if (matrixRight[currentY][currentX].selected){
                                                int number = Utility::convertCharToInt(matrixRight[currentY][currentX].text);
                                                if (number == turn){
                                                    int position = shipGaps[index]+rightBoats[index].damage;
                                                    shipsRight[position].text = Utility::convertIntToChar(turn);
                                                    rightBoats[index].damage++;
                                                }
                                                if (rightBoats[index].damage == sizeShip[index])
                                                    rightBoats[index].alive = false;
                                            }

                                            currentX += X_DIRECTION[direction];
                                            currentY += Y_DIRECTION[direction];
                                        }
                                    }
                                    drawShips(shipsRight);
                                    turn++;
                                }
                            }
                            else{
                                int number = Utility::convertCharToInt(matrixRight[line][column].text);
                                if (number == turn){
                                    shots++;
                                    rightRemained++;
                                    matrixRight[line][column].selected = false;
                                    matrixRight[line][column].text = "  ";
                                    drawButton(matrixRight[line][column], YELLOW, 3);
                                }
                            }

                            if (optionsSelector[0] == 0)
                                ammo = Utility::concatenate("Ammo: ", Utility::convertIntToChar(shots));
                            if (optionsSelector[0] == 1)
                                ammo = Utility::concatenate("Rachete: ", Utility::convertIntToChar(shots));
                            if (optionsSelector[0] == 2)
                                ammo = Utility::concatenate("Coups: ", Utility::convertIntToChar(shots));
                            Utility::drawText(110, 50, ammo, WHITE, 20);
                        }
                    }
                }

            }

            if (ismouseclick(WM_RBUTTONUP)){
                clearmouseclick(WM_RBUTTONUP);
                selectedDirection++;
                if (optionsSelector[4])
                    selectedDirection++;
                if (selectedDirection == 8)
                    selectedDirection = 0;

                directionChanged = true;
            }

            //Preview
            for (int line = 0; line < MAX_LENGTH; line++){
                for (int column = 0; column < MAX_LENGTH; column++){
                    //Left
                    if (attackTime == false){
                        if (isMouseOnButton(matrixLeft[line][column], 7)){
                            if (!boardDrawn[0][line][column] or directionChanged){
                                boardDrawn[0][line][column] = true;
                                drawButton(matrixLeft[line][column], YELLOW, 3, selectedDirection);
                                directionChanged = false;
                            }
                        }
                        else{
                            if (boardDrawn[0][line][column]){
                                boardDrawn[0][line][column] = false;
                                if ( matrixLeft[line][column].placed )
                                    drawButton(matrixLeft[line][column], GREEN, 3);
                                else
                                    drawButton(matrixLeft[line][column], WHITE, 3);
                            }
                        }
                    }
                    else
                    //Right
                    if (isMouseOnButton(matrixRight[line][column], 7)){
                        if (!boardDrawn[1][line][column]){
                            boardDrawn[1][line][column] = true;
                            drawButton(matrixRight[line][column], YELLOW, 3);
                        }
                    }
                    else{
                        if (boardDrawn[1][line][column]){
                            boardDrawn[1][line][column] = false;
                            if (optionsSelector[1]){
                                if (matrixRight[line][column].selected)
                                    drawButton(matrixRight[line][column], LIGHTRED, 3);
                                else{
                                    if (matrixRight[line][column].placed)
                                        drawButton(matrixRight[line][column], MAGENTA, 3);
                                    else
                                        drawButton(matrixRight[line][column], WHITE, 3);
                                }
                            }
                            else{
                                if (matrixRight[line][column].selected)
                                    drawButton(matrixRight[line][column], LIGHTRED, 3);
                                else
                                    drawButton(matrixRight[line][column], WHITE, 3);
                            }
                        }
                    }
                }
            }
        }
    }
}

///-------------[OptionsMenu]--------------------------------------------------------------------------------------------------------------\\\

namespace OptionsMenu{
    const int MAX_OPTIONS = 5;
    Option options[MAX_OPTIONS];

    Button goBack;

    int selectorOption;
    int selectorPossibilities;

    inline void initialize(){
        if (optionsSelector[0] == 0){
            options[0].description = "Language";
            options[0].possibilities[0] = "English";
            options[0].possibilities[1] = "Romanian";
            options[0].possibilities[2] = "French";
            options[0].MAX_POSSIBLITIES = 3;

            options[1].description = "Reveal Enemy";
            options[1].possibilities[0] = "Off";
            options[1].possibilities[1] = "On";
            options[1].MAX_POSSIBLITIES = 2;

            options[2].description = "Bonus Chest";
            options[2].possibilities[0] = "Off";
            options[2].possibilities[1] = "On";
            options[2].MAX_POSSIBLITIES = 2;

            options[3].description = "Difficulty";
            options[3].possibilities[0] = "Easy";
            options[3].possibilities[1] = "Normal";
            options[3].possibilities[2] = "Hard";
            options[3].possibilities[3] = "Cheater";
            options[3].MAX_POSSIBLITIES = 4;

            options[4].description = "Game Mode";
            options[4].possibilities[0] = "Classic";
            options[4].possibilities[1] = "Modern";
            options[4].MAX_POSSIBLITIES = 2;
        }

        if (optionsSelector[0] == 1){
            options[0].description = "Limba";
            options[0].possibilities[0] = "Engleza";
            options[0].possibilities[1] = "Romana";
            options[0].possibilities[2] = "Franceza";
            options[0].MAX_POSSIBLITIES = 3;

            options[1].description = "Arata Inamicul";
            options[1].possibilities[0] = "Nu";
            options[1].possibilities[1] = "Da";
            options[1].MAX_POSSIBLITIES = 2;

            options[2].description = "Cufar Bonus";
            options[2].possibilities[0] = "Nu";
            options[2].possibilities[1] = "Da";
            options[2].MAX_POSSIBLITIES = 2;

            options[3].description = "Dificultate";
            options[3].possibilities[0] = "Usor";
            options[3].possibilities[1] = "Normal";
            options[3].possibilities[2] = "Greu";
            options[3].possibilities[3] = "Trisor";
            options[3].MAX_POSSIBLITIES = 4;

            options[4].description = "Mod de Joc";
            options[4].possibilities[0] = "Clasic";
            options[4].possibilities[1] = "Modern";
            options[4].MAX_POSSIBLITIES = 2;
        }

        if (optionsSelector[0] == 2){
            options[0].description = "Langue";
            options[0].possibilities[0] = "Anglaise";
            options[0].possibilities[1] = "Roumaine";
            options[0].possibilities[2] = "Française";
            options[0].MAX_POSSIBLITIES = 3;

            options[1].description = "Révéler l'ennemi";
            options[1].possibilities[0] = "Non";
            options[1].possibilities[1] = "Oui";
            options[1].MAX_POSSIBLITIES = 2;

            options[2].description = "Coffre Bonus";
            options[2].possibilities[0] = "Non";
            options[2].possibilities[1] = "Oui";
            options[2].MAX_POSSIBLITIES = 2;

            options[3].description = "Difficulté";
            options[3].possibilities[0] = "Facile";
            options[3].possibilities[1] = "Ordinaire";
            options[3].possibilities[2] = "Difficile";
            options[3].possibilities[3] = "Tricheur";
            options[3].MAX_POSSIBLITIES = 4;

            options[4].description = "Mode de Jeu";
            options[4].possibilities[0] = "Classique";
            options[4].possibilities[1] = "Moderne";
            options[4].MAX_POSSIBLITIES = 2;
        }

        int maxLength = 0;
        for (int index = 0; index < MAX_OPTIONS; index++){
            for (int selector = 0; selector < options[index].MAX_POSSIBLITIES; selector++){
                int length = Utility::stringLenght(options[index].possibilities[selector]);
                maxLength = max(maxLength, length);
            }
        }

        int gap = 50;
        int offsetX = 100;
        for (int index = 0; index < MAX_OPTIONS; index++){
            options[index].x = offsetX;
            options[index].width = 200;
            options[index].height = 50;

            if (index == 0)
                options[index].y = 100;
            else
                options[index].y = options[index-1].y + gap;

        }

        if (optionsSelector[0] == 0)
            goBack.text   = "Back";
        if (optionsSelector[0] == 1)
            goBack.text   = "Inapoi";
        if (optionsSelector[0] == 2)
            goBack.text   = "Retour";

        goBack.width  = 200;
        goBack.height = 50;
        goBack.x      = offsetX+goBack.width/2;
        goBack.y      = windowHeight-100;
    }

    inline void display(){
        Utility::clearScreen();

        for (int index = 0; index < MAX_OPTIONS; index++)
            drawOption(options[index]);

        drawButton(goBack);

        bool drawn = false;
        while (true){

            if (isMouseOnButton(goBack)){
                if (!drawn){
                    drawn = true;
                    drawButton(goBack, LIGHTBLUE);
                }

                if (ismouseclick(WM_LBUTTONUP)){
                    clearmouseclick(WM_LBUTTONUP);
                    MainMenu::initialize();
                    MainMenu::display();
                    return;
                }
            }
            else{
                if (drawn){
                    drawn = false;
                    drawButton(goBack);
                }
            }

            if (ismouseclick(WM_LBUTTONUP)){
                clearmouseclick(WM_LBUTTONUP);

                for (int index = 0; index < MAX_OPTIONS; index++){
                    if (isMouseOnOption(options[index]) == 1){
                        options[index].selected ++;

                        if (options[index].selected == options[index].MAX_POSSIBLITIES )
                            options[index].selected = 0;

                        optionsSelector[index] = options[index].selected;
                        drawOption(options[index]);
                        if (index == 0){
                            OptionsMenu::initialize();
                            OptionsMenu::display();
                            return;
                        }
                        break;
                    }
                    else
                    if (isMouseOnOption(options[index]) == -1){
                        options[index].selected--;

                        if (options[index].selected == -1)
                            options[index].selected = options[index].MAX_POSSIBLITIES-1;

                        optionsSelector[index] = options[index].selected;
                        drawOption(options[index]);
                        if (index == 0){
                            OptionsMenu::initialize();
                            OptionsMenu::display();
                            return;
                        }
                        break;
                    }
                }
            }
        }
    }
}

///-------------[HistoryMenu]--------------------------------------------------------------------------------------------------------------\\\

namespace HistoryMenu{
    int top;
    int bot;
    int right;
    int left;

    int marginWidth;
    int marginHeight;

    int tableWidth;
    int tableHeight;

    Button goBack;
    Button goUp;
    Button goDown;

    const int MAX_INFO = 6;
    const int SEPARATION_POINTS = MAX_INFO+1;

    int xPositions[SEPARATION_POINTS];
    int xText[MAX_INFO];

    int cellWidth[MAX_INFO];
    char* description[MAX_INFO];

    inline void initialize(){
        readEndInfo();
        marginWidth = 100;
        marginHeight = 150;

        top   = 50;
        bot   = windowHeight-marginHeight;
        right = windowWidth-marginWidth;
        left  = marginWidth;

        tableWidth  = right-left;
        tableHeight = bot-top;

        cellWidth[0] = 150;
        cellWidth[1] = 150;
        cellWidth[2] = 150;
        cellWidth[3] = 100;
        cellWidth[4] = 200;
        cellWidth[5] = tableWidth-150*5;

        for (int index = 0; index < SEPARATION_POINTS; index++){
            if (index == 0)
                xPositions[index] = left;
            else
                xPositions[index] = xPositions[index-1] + cellWidth[index-1];
        }

        for (int index = 0; index < MAX_INFO; index++)
            xText[index] = (xPositions[index] + xPositions[index+1])/2;

        //GoBack
        if (optionsSelector[0] == 0)
            goBack.text   = "Back";
        if (optionsSelector[0] == 1)
            goBack.text   = "Inapoi";
        if (optionsSelector[0] == 2)
            goBack.text   = "Retour";

        goBack.width  = 200;
        goBack.height = 50;
        goBack.x      = marginWidth+goBack.width/2;
        goBack.y      = windowHeight-100;

        //GoUp
        goUp.text   = "";
        goUp.width  = 50;
        goUp.height = 50;
        goUp.x      = windowWidth-(marginWidth+goUp.width/2);
        goUp.y      = windowHeight-100;

        //GoDown
        goDown.text   = "";
        goDown.width  = 50;
        goDown.height = 50;
        goDown.x      = goUp.x - goDown.width-5;
        goDown.y      = windowHeight-100;

        //Description
        if (optionsSelector[0] == 0){
            description[0] = "Versus";
            description[1] = "Game Mode";
            description[2] = "Reveal";
            description[3] = "Turns";
            description[4] = "Status";
            description[5] = "Date";
        }
        if (optionsSelector[0] == 1){
            description[0] = "Versus";
            description[1] = "Mod de Joc";
            description[2] = "Coduri";
            description[3] = "Ture";
            description[4] = "Statut";
            description[5] = "Data";
        }
        if (optionsSelector[0] == 2){
            description[0] = "Versus";
            description[1] = "Mode de Jeu";
            description[2] = "Révéler";
            description[3] = "Tours";
            description[4] = "Statut";
            description[5] = "Temps";
        }
    }

    inline void drawEndInfo(EndInfo example, int y){
        char* text[MAX_INFO];
        int colorText[MAX_INFO];

        switch(optionsSelector[0]){
        case 0:
            if (example.difficulty == 0)
                text[0] = "Easy";
            if (example.difficulty == 1)
                text[0] = "Normal";
            if (example.difficulty == 2)
                text[0] = "Hard";
            if (example.difficulty == 3)
                text[0] = "Cheater";

            if (example.gamemode == 0)
                text[1] = "Classic";
            else
                text[1] = "Modern";

            if (example.reveal == 0)
                text[2] = "Off";
            else
                text[2] = "On";

            text[3] = Utility::convertIntToChar(example.turns);

            if (example.status == 0)
                text[4] = "Defeat";
            else
                text[4] = "Victory";

            text[5] = ctime(&example.time);
            break;

        case 1:
            if (example.difficulty == 0)
                text[0] = "Usor";
            if (example.difficulty == 1)
                text[0] = "Normal";
            if (example.difficulty == 2)
                text[0] = "Greu";
            if (example.difficulty == 3)
                text[0] = "Trisor";

            if (example.gamemode == 0)
                text[1] = "Clasic";
            else
                text[1] = "Modern";

            if (example.reveal == 0)
                text[2] = "Nu";
            else
                text[2] = "Da";

            text[3] = Utility::convertIntToChar(example.turns);

            if (example.status == 0)
                text[4] = "Infrangere";
            else
                text[4] = "Victorie";

            text[5] = ctime(&example.time);
            break;

        case 2:
            if (example.difficulty == 0)
                text[0] = "Facile";
            if (example.difficulty == 1)
                text[0] = "Ordinaire";
            if (example.difficulty == 2)
                text[0] = "Difficile";
            if (example.difficulty == 3)
                text[0] = "Tricheur";

            if (example.gamemode == 0)
                text[1] = "Classique";
            else
                text[1] = "Moderne";

            if (example.reveal == 0)
                text[2] = "Non";
            else
                text[2] = "Oui";

            text[3] = Utility::convertIntToChar(example.turns);

            if (example.status == 0)
                text[4] = "Défaite";
            else
                text[4] = "Victoire";

            text[5] = ctime(&example.time);
            break;
        }

        for (int index = 0; index < MAX_INFO; index++)
            colorText[index] = WHITE;

        if (example.difficulty == 0)
            colorText[0] = LIGHTGREEN;
        if (example.difficulty == 1)
            colorText[0] = LIGHTBLUE;
        if (example.difficulty == 2)
            colorText[0] = LIGHTRED;
        if (example.difficulty == 3)
            colorText[0] = LIGHTMAGENTA;

        if (example.gamemode == 0)
            colorText[1] = YELLOW;
        else
            colorText[1] = BROWN;

        if (example.reveal == 0)
            colorText[2] = LIGHTRED;
        else
            colorText[2] = LIGHTGREEN;

        if (example.gamemode == 0){
            if (example.turns < 6)
                colorText[3] = LIGHTGREEN;
            else
            if (example.turns < 12)
                colorText[3] = LIGHTCYAN;
            else
            if (example.turns < 18)
                colorText[3] = LIGHTRED;
            else
                colorText[3] = MAGENTA;
        }
        else{
            if (example.turns < 50)
                colorText[3] = LIGHTGREEN;
            else
            if (example.turns < 100)
                colorText[3] = LIGHTCYAN;
            else
            if (example.turns < 150)
                colorText[3] = LIGHTRED;
            else
                colorText[3] = MAGENTA;
        }

        if (example.status == 0)
            colorText[4] = LIGHTRED;
        else
            colorText[4] = LIGHTGREEN;

        for (int index = 0; index < MAX_INFO; index++){
            Utility::drawText(xText[index], y, text[index], colorText[index], 10, 2);
        }
    }

    inline void display(){
        Utility::clearScreen();
        rectangle(left, top, right, bot);

        drawButton(goBack);
        drawButton(goUp,   WHITE, FONT_SIZE, 0);
        drawButton(goDown, WHITE, FONT_SIZE, 4);

        int maxDisplayed = min(9, totalMatches);
        int startIndex = 0;

        for (int index = 0; index < MAX_INFO; index++)
            Utility::drawText(xText[index], top+30, description[index], WHITE, 0, 3);
        line(left, top+50, right, top+50);

        for (int index = startIndex; index < startIndex+maxDisplayed; index++)
            drawEndInfo(matches[index], top+50+50*((index-startIndex)+1));

        bool goBackDrawn = false;
        bool goUpDrawn   = false;
        bool goDownDrawn = false;

        while (true){
            //Draw goBack
            if (isMouseOnButton(goBack)){
                if (!goBackDrawn){
                    goBackDrawn = true;
                    drawButton(goBack, LIGHTBLUE);
                }
            }
            else{
                if (goBackDrawn){
                    goBackDrawn = false;
                    drawButton(goBack);
                }
            }

            //Draw goUp
            if (isMouseOnButton(goUp)){
                if (!goUpDrawn){
                    goUpDrawn = true;
                    drawButton(goUp, LIGHTBLUE, FONT_SIZE, 0);
                }
            }
            else{
                if (goUpDrawn){
                    goUpDrawn = false;
                    drawButton(goUp, WHITE, FONT_SIZE, 0);
                }
            }

            //Draw goDown
            if (isMouseOnButton(goDown)){
                if (!goDownDrawn){
                    goDownDrawn = true;
                    drawButton(goDown, LIGHTBLUE, FONT_SIZE, 4);
                }
            }
            else{
                if (goDownDrawn){
                    goDownDrawn = false;
                    drawButton(goDown, WHITE, FONT_SIZE, 4);
                }
            }

            //Check Click
            if (ismouseclick(WM_LBUTTONUP)){
                clearmouseclick(WM_LBUTTONUP);

                if (isMouseOnButton(goBack)){
                    MainMenu::initialize();
                    MainMenu::display();
                    return;
                }

                if (isMouseOnButton(goUp)){
                    bool drawNecessary = true;

                    if(startIndex - 2 >= 0)
                        startIndex -= 2;
                    else
                    if(startIndex - 1 >= 0)
                        startIndex --;
                    else
                        drawNecessary = false;

                    if (drawNecessary){
                        setcolor(WHITE);
                        Utility::clearRectangle(left, top, right, bot);
                        rectangle(left, top, right, bot);

                        for (int index = 0; index < MAX_INFO; index++)
                            Utility::drawText(xText[index], top+30, description[index], WHITE, 0, 3);
                        line(left, top+50, right, top+50);

                        for (int index = startIndex; index < startIndex+maxDisplayed; index++)
                            drawEndInfo(matches[index], top+50+50*((index-startIndex)+1));
                    }
                }

                if (isMouseOnButton(goDown)){
                    bool drawNecessary = true;

                    if(startIndex + maxDisplayed + 2 <= totalMatches)
                        startIndex += 2;
                    else
                    if(startIndex + maxDisplayed + 1 <= totalMatches)
                        startIndex ++;
                    else
                        drawNecessary = false;

                    if (drawNecessary){
                        setcolor(WHITE);
                        Utility::clearRectangle(left, top, right, bot);
                        rectangle(left, top, right, bot);

                        for (int index = 0; index < MAX_INFO; index++)
                            Utility::drawText(xText[index], top+30, description[index], WHITE, 0, 3);
                        line(left, top+50, right, top+50);

                        for (int index = startIndex; index < startIndex+maxDisplayed; index++)
                            drawEndInfo(matches[index], top+50+50*((index-startIndex)+1));
                    }
                }
            }
        }
    }
}

///-------------[Main]---------------------------------------------------------------------------------------------------------------------\\\

int main(){
    initwindow(windowWidth, windowHeight, "BattleShips");

    MainMenu::initialize();
    MainMenu::display();
    return 0;
}
