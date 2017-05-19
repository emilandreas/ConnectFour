#include "connectfour.h"

ConnectFour::ConnectFour()
{

}

void ConnectFour::play(){
    int turn = 0;
    Board b;
    std::cout << "Welcome to ConnectFour! Want to start? (y/n)" << std::endl;
    char ans;
    std::cin >> ans;
    if (ans == 'y'){
        turn = 0;
    }
    else turn = 1;
    player currentPlayer;
    int move = -1;
    bool validMove;

    while(!b.gameOver()){
        currentPlayer = static_cast<player>(turn%2);
        std::cout << b << std::endl;

        if(currentPlayer == RED){
            std::cout << "Red players turn: (0-6): " << std::endl;
        }
        else std::cout << "Yellow players turn: (0-6): " << std::endl;
        validMove = false;
        while(!validMove){
            std::cin >> move;
            while(move < 0 or move >= WIDTH){
                std::cout << "Try again: ";
                std::cin >> move;
            }
            validMove = b.makeMove(move, currentPlayer);
        }


        turn++;
    }
    std::cout << b;
    std::cout << "GAME OVER" << std::endl;
    player winner = b.getWinner();
    switch(winner){
    case RED:
        std::cout << "Red is the winner!" << std::endl;
        break;
    case YELLOW:
        std::cout << "Yellow is the winner!" << std::endl;
        break;
    case NONE:
        std::cout << "It's a tie!" << std::endl;
        break;
    default:
        std::cout << "Something is wrong..." << std::endl;
        break;
    }
}

Board::Board(){
    this->init();
}
bool Board::makeMove(int col, player p){
    if(col < 0 or col >= WIDTH){
        return false;
    }
    for(int r = 0; r < HEIGHT; r++){
        if(getSquare(r,col) == '_'){
            setSquare(r, col, p);
            return true;
        }
    }
    return false;
}
bool Board::gameOver(){
    if(getWinner() != NONE){
        return true;
    }
    for(int r = 0; r < HEIGHT; r++){
        for(int c = 0; c < WIDTH; c++){
            if (getSquare(r,c) != 'X' and getSquare(r,c) != 'O'){
                return false;
            }
        }
    }
    return true;
}

bool Board::indexInBounce(int row, int col){
    if (row >= 0 and row < HEIGHT and col >= 0 and col < WIDTH){
        return true;
    }
    return false;
}

bool Board::searchHorizontalRight(int row, int col){
    char p = getSquare(row, col);
    for(int i = 1; i < 4; i++){
        if( indexInBounce(row, col+i) ){
            if( getSquare(row, col+i) != p){
                return false;
            }
        }
        else{
            return false;
        }
    }
    return true;

}

bool Board::searchVertical(int row, int col){
    char p = getSquare(row, col);
    for(int i = 1; i < 4; i++){
        if ( indexInBounce(row + i, col)){
            if( getSquare(row + i, col) != p){
                return false;
            }
        }
        else{
            return false;
        }
    }
    return true;
}
bool Board::searchDiagRight(int row, int col){
    char p = getSquare(row, col);
    for(int i = 1; i < 4; i++){
        if ( indexInBounce(row + i, col + i)){
            if( getSquare(row + i, col + i) != p){
                return false;
            }
        }
        else{
            return false;
        }
    }
    return true;
}
bool Board::searchDiagLeft(int row, int col){
    char p = getSquare(row, col);
    for(int i = 1; i < 4; i++){
        if ( indexInBounce(row + i, col - i)){
            if( getSquare(row + i, col - i) != p){
                return false;
            }
        }
        else{
            return false;
        }
    }
    return true;
}

player Board::getWinner(){
    char current;
    //HORIZONTAL
    for(int r = 0; r < HEIGHT; r++){
        for(int c = 0; c < WIDTH; c++){
            current = getSquare(r,c);
                if(current != '_'){
                    if(searchHorizontalRight(r,c) or
                        searchVertical(r,c) or
                        searchDiagLeft(r,c) or
                        searchDiagRight(r,c))
                    {
                    if(current == 'X'){
                       return RED;
                    }
                    else return YELLOW;
                }
            }
        }
    }
    return NONE;
}

char Board::getPiece(player p) const {
    if (p == RED){
        return 'X';
    }
    else{
        return 'O';
    }
}

void Board::setSquare(int row, int col, player p){
    char piece = getPiece(p);
    board[index(row, col)] = piece;
}

int Board::index(int row, int col) const {
    return row*WIDTH + col;
}

char Board::getSquare(int row, int col) const {
    return board[index(row,col)];
}

void Board::init(){
    if(board.size() != WIDTH*HEIGHT){
        board.resize(WIDTH*HEIGHT);
    }
    for(int r = 0; r < HEIGHT; r++){
        for(int c = 0; c < WIDTH; c++){
            board[index(r,c)] = '_';
        }
    }
}
std::ostream& operator<<(std::ostream& os, const Board& b){
    os << std::endl;
    for(int r = HEIGHT -1; r >= 0; r--){
        os << '|';
        for(int c = 0; c < WIDTH; c++){
            os << b.getSquare(r,c) << '|';
        }
        os << std::endl;
    }
    return os;
}
