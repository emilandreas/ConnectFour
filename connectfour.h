#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include <iostream>
#include <vector>

#define WIDTH 7
#define HEIGHT 6

enum player{
    RED = 0, // = 'X'
    YELLOW,	// = 'O'
    NONE
};

class ConnectFour
{
public:
    ConnectFour();
    void play();
};

class Board{
private:
    std::vector<char> board;
public:
    Board();
    void init();
    bool makeMove(int col, player p);
    void setSquare(int row, int col, player p);
    char getPiece(player p) const;
    int index(int row, int col) const;
    char getSquare(int row, int col) const;
    bool gameOver();
    bool indexInBounce(int row, int col);
    bool searchHorizontalRight(int row, int col);
    bool searchVertical(int row, int col);
    bool searchDiagRight(int row, int col);
    bool searchDiagLeft(int row, int col);
    player getWinner();
};

std::ostream& operator<<(std::ostream& os, const Board& b);

#endif // CONNECTFOUR_H
