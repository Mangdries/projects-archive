#include <iostream>
#include <string>

typedef enum {
    Red,
    Yellow,
    None,
} Piece;

namespace Turn {
    typedef enum {
        Red,
        Yellow,
    } Turn;
}

void init_board(Piece (&board)[6][7]);
void print_board(Piece board[6][7]);
Turn::Turn update_board(Piece (&board)[6][7], Turn::Turn turn);
bool check_win(Piece board[6][7], bool winner);

int positionsFilled = 0;

int main(int, char**) {
    Piece board[6][7];
    init_board(board);

    bool isWinner = false;
    Turn::Turn turn = Turn::Red;

        do {
            print_board(board);
            turn = update_board(board, turn);
            isWinner = check_win(board, isWinner);
        } while(!isWinner && positionsFilled < 42);

        print_board(board);

        if(isWinner == true) {
            switch(turn) {
                case Turn::Red:
                    std::cout << "Yellow wins!\n"; //Opposite because the last move was from the other color
                    break;
                case Turn::Yellow:
                    std::cout << "Red wins!\n";
                    break;
                default:
                    std::cout << "Nobody wins!\n";
                    break;
            }
        }

    return 0;
}

void init_board(Piece (&board)[6][7]) {
    for(int i = 0; i < 6; ++i) {
        for(int j = 0; j < 7; ++j) {
            board[i][j] = None;
        }
    };
}

void print_board(Piece board[6][7]) {
    for(int i = 0; i < 6; ++i) {
        std::cout << 6 - i << " ";
        for(int j = 0; j < 7; ++j) {
            switch(board[i][j]) {
                case None:
                    std::cout << "| ";
                    break;
                case Red:
                    std::cout << "|R";
                    break;
                case Yellow:
                    std::cout << "|Y";
                    break;
            }
        }
        std::cout << "|\n";
    };

    std::cout << "  ";
    for(int i = 0; i < 7; i++) {
        std::cout << " " << i + 1;
    }

    std::cout << "\n";
}

Turn::Turn update_board(Piece (&board)[6][7], Turn::Turn turn) {
    switch(turn) {
        case Turn::Red:
            std::cout << "Current turn: Red\n";
            break;
        default:
            std::cout << "Current turn: Yellow\n";
            break;
    }

    std::cout << "Your move: ";
    std::string playerMove;
    std::cin >> playerMove;

    if(playerMove == "clear" || playerMove == "Clear") {
        std::cout << "If you see this message the clear functionality doesn't work\n\
        \e[1;1H\e[2J";
        return turn;
    }

    int move = 0;
    try {
        move = std::stoi(playerMove);
    } catch(std::exception e) {
        std::cout << "Error: Number not entered\n";
        return turn;
    }

    if(move >= 1 && move <= 7) {
        move--;
        int yPos = 7;
        
        while(yPos >= 0) {
            if(board[yPos][move] == None) {
                if(turn == Turn::Red) {
                    board[yPos][move] = Red;
                    positionsFilled += 1;
                    break;
                } else if(turn == Turn::Yellow) {
                    board[yPos][move] = Yellow;
                    positionsFilled += 1;
                    break;
                }
            } else if(yPos == 0) {
                std::cout << "Position taken!\n";
                return turn;
                break;
            }
            yPos--;
        }
    } else {
        return turn;
    }

    switch(turn) {
        case Turn::Red:
            return Turn::Yellow;
        default:
            return Turn::Red;
    }
}

bool check_win(Piece board[6][7], bool winner) {
    Piece currentPiece = None; //Check if next piece is the same piece

    //Diagonals
    //I got lazy lmao
    //leaning left
    if(board[3][0] == Red && board[2][1] == Red && board[1][2] == Red && board[0][3] == Red ||
       board[4][0] == Red && board[3][1] == Red && board[2][2] == Red && board[1][3] == Red ||
       board[3][1] == Red && board[2][2] == Red && board[1][3] == Red && board[0][4] == Red ||
       board[5][0] == Red && board[4][1] == Red && board[3][2] == Red && board[2][3] == Red ||
       board[4][1] == Red && board[3][2] == Red && board[2][3] == Red && board[1][4] == Red ||
       board[3][2] == Red && board[2][3] == Red && board[1][4] == Red && board[0][5] == Red ||   //Moving diagonal now 
       board[5][1] == Red && board[4][2] == Red && board[3][3] == Red && board[2][4] == Red ||
       board[4][2] == Red && board[3][3] == Red && board[2][4] == Red && board[1][5] == Red ||
       board[3][3] == Red && board[2][4] == Red && board[1][5] == Red && board[0][6] == Red ||
       board[5][2] == Red && board[4][3] == Red && board[4][3] == Red && board[3][2] == Red ||
       board[4][3] == Red && board[3][4] == Red && board[2][5] == Red && board[1][6] == Red ||
       board[5][3] == Red && board[4][4] == Red && board[3][5] == Red && board[2][6] == Red) {
        currentPiece = Red;
       } else if(board[3][0] == Yellow && board[2][1] == Yellow && board[1][2] == Yellow && board[0][3] == Yellow ||
       board[4][0] == Yellow && board[3][1] == Yellow && board[2][2] == Yellow && board[1][3] == Yellow ||
       board[3][1] == Yellow && board[2][2] == Yellow && board[1][3] == Yellow && board[0][4] == Yellow ||
       board[5][0] == Yellow && board[4][1] == Yellow && board[3][2] == Yellow && board[2][3] == Yellow ||
       board[4][1] == Yellow && board[3][2] == Yellow && board[2][3] == Yellow && board[1][4] == Yellow ||
       board[3][2] == Yellow && board[2][3] == Yellow && board[1][4] == Yellow && board[0][5] == Yellow ||   //Moving diagonal now 
       board[5][1] == Yellow && board[4][2] == Yellow && board[3][3] == Yellow && board[2][4] == Yellow ||
       board[4][2] == Yellow && board[3][3] == Yellow && board[2][4] == Yellow && board[1][5] == Yellow ||
       board[3][3] == Yellow && board[2][4] == Yellow && board[1][5] == Yellow && board[0][6] == Yellow ||
       board[5][2] == Yellow && board[4][3] == Yellow && board[4][3] == Yellow && board[3][2] == Yellow ||
       board[4][3] == Yellow && board[3][4] == Yellow && board[2][5] == Yellow && board[1][6] == Yellow ||
       board[5][3] == Yellow && board[4][4] == Yellow && board[3][5] == Yellow && board[2][6] == Yellow) {
        currentPiece = Red;
       }

    //leaning right

    int x = 6;
    int holdX = x;
    int y = 3;
    int holdY = y;
    int count = 0;

    while (1) {
        if(y-3 >= 0 && x - 3 >= 0) {
            if(board[y][x] == Red && board[y-1][x-1] == Red && board[y-2][x-2] == Red && board[y-3][x-3] == Red) {
                currentPiece = Red;
                //std::cout << "REd\n";
                break;
            } else if(board[y][x] == Yellow && board[y-1][x-1] == Yellow && board[y-2][x-2] == Yellow && board[y-3][x-3] == Yellow) {
                currentPiece = Yellow;
                break;
            } else {
                y--;
                if(x > 0) {
                    //std::cout << x;
                    x--;
                }
            }
        } else {

            //std::cout << "x and y: " << x << " " << y << "\n";

            if(count == 12) {
                break;
            } else if(holdY < 5) {
                holdY++;
                x = holdX;
            } else {
                if(holdX > 0) {
                    holdX--;
                }
            }
            
            x = holdX;
            y = holdY;
            ++count;
        }
    }
    
    
   //Horizontal
   for(int i = 0; i < 6; ++i) {
        for(int j = 0; j < 4; ++j) {
            if(board[i][j] == Red && board[i][j+1] == Red && board[i][j+2] == Red && board[i][j+3] == Red) {
                currentPiece = Red;
                break;
            } else if(board[i][j] == Yellow && board[i][j+1] == Yellow && board[i][j+2] == Yellow && board[i][j+3] == Yellow) {
                currentPiece = Yellow;
                break;
            }
        }
    }

    //Vertical
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 7; ++j) {
            if(board[i][j] == Red && board[i+1][j] == Red && board[i+2][j] == Red && board[i+3][j] == Red) {
                currentPiece = Red;
                break;
            } else if(board[i][j] == Yellow && board[i+1][j] == Yellow && board[i+2][j] == Yellow && board[i+3][j] == Yellow) {
                currentPiece = Yellow;
                break;
            }
        }
    }

    if(currentPiece == Red || currentPiece == Yellow) {
        winner = true;
    }

    return winner;
}
