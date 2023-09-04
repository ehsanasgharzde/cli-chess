#include <iostream>
#include <vector>
#include <string>


using namespace std;


vector<int> getMove();
bool isHorizontalValid(int srcRow, int srcCol, int destRow, int destCol);
bool isVerticalValid(int srcRow, int srcCol, int destRow, int destCol);
bool isDiagonalValid(int srcRow, int srcCol, int destRow, int destCol);
bool isKnightValid(int srcRow, int srcCol, int destRow, int destCol);
bool isPawnStep(int srcRow, int srcCol, int destRow, int destCol, char currentPlayer);
bool isPawnAttacking(int srcRow, int srcCol, int destRow, int destCol);
bool isMoveValid(vector<int> move, vector<vector<char>> chessboard, char currentPlayer);
bool isHorizontalValid(int srcRow, int srcCol, int destRow, int destCol);
bool isVerticalValid(int srcRow, int srcCol, int destRow, int destCol);
bool isDiagonalValid(int srcRow, int srcCol, int destRow, int destCol);
bool isKnightValid(int srcRow, int srcCol, int destRow, int destCol);
bool isPawnFirst(int srcRow, char currentPlayer);
bool isCellOccupied(vector<vector<char>> chessboard, int srcRow, int srcCol, int destRow, int destCol, char currentPlayer);
bool isHorizontalBlocked(vector<vector<char>> chessboard, int srcRow, int srcCol, int destRow, int destCol);
bool isVerticalBlocked(vector<vector<char>> chessboard, int srcRow, int srcCol, int destRow, int destCol);
bool isDiagonalBlocked(vector<vector<char>> chessboard, int srcRow, int srcCol, int destRow, int destCol);
bool isObstacleFound(vector<vector<char>> chessboard, int srcRow, int srcCol, int destRow, int destCol);
bool isKingCaptured(vector<vector<char>> chessboard);
bool isPawnReached(int destRow, char piece);
void doMove(vector<vector<char>>& chessboard, vector<int> move);
void outBoard(vector<vector<char>> chessboard, char currentPlayer);
void applyPromotion(vector<vector<char>> chessboard, int destRow, int destCol, char promotionPiece);
char getPromotion();


int main() {
    vector<vector<char>> chessboard = {
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
    };
    char currentPlayer = 'W';

    while (true) {
        outBoard(chessboard, currentPlayer);
        cout << "Current player: " << (currentPlayer == 'W' ? "White" : "Black") << endl;

        vector<int> move = getMove();

        if (!isMoveValid(move, chessboard, currentPlayer)) {
            continue;
        }
        
        int srcRow = move[0];
        int srcCol = move[1];
        int destRow = move[2];
        int destCol = move[3];

        doMove(chessboard, move);

        if (isKingCaptured(chessboard)) {
            break;
        }

        if (isPawnReached(destRow, chessboard[destRow][destCol])) {
            char promotionPiece = getPromotion();
            applyPromotion(chessboard, destRow, destCol, promotionPiece);
        }

        currentPlayer = (currentPlayer == 'W' ? 'B' : 'W');
    }

    return 0;
}

vector<int> getMove() {
    vector<int> move(4);
    cout << "Enter your move (sourceRow sourceColumn destinationRow destinationColumn): ";
    int sourceRow, destinationRow;
    char sourceColumn, destinationColumn;
    cin >> sourceRow >> sourceColumn >> destinationRow >> destinationColumn;
    move[0] = sourceRow - 1;
    move[1] = sourceColumn - 'A';
    move[2] = destinationRow - 1;
    move[3] = destinationColumn - 'A';
    return move;
}


bool isHorizontalValid(int srcRow, int srcCol, int destRow, int destCol) {
    return srcRow == destRow;
}

bool isVerticalValid(int srcRow, int srcCol, int destRow, int destCol) {
    return srcCol == destCol;
}

bool isDiagonalValid(int srcRow, int srcCol, int destRow, int destCol) {
    int rowDiff = abs(destRow - srcRow);
    int colDiff = abs(destCol - srcCol);
    return rowDiff == colDiff;
}

bool isKnightValid(int srcRow, int srcCol, int destRow, int destCol) {
    int rowDiff = abs(destRow - srcRow);
    int colDiff = abs(destCol - srcCol);
    return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
}

bool isPawnStep(int srcRow, int srcCol, int destRow, int destCol, char currentPlayer) {
    int rowDiff = currentPlayer == 'W' ? destRow - srcRow : srcRow - destRow;
    if (isPawnFirst(srcRow, currentPlayer)) {
        return rowDiff == 1 || rowDiff == 2;
    }
    return rowDiff == 1;
}

bool isPawnAttacking(int srcRow, int srcCol, int destRow, int destCol) {
    int rowDiff = abs(destRow - srcRow);
    int colDiff = abs(destCol - srcCol);
    return rowDiff == 1 && colDiff == 1;
}

bool isCellOccupied(vector<vector<char>> chessboard, int srcRow, int srcCol, int destRow, int destCol, char currentPlayer) {
    char piece = chessboard[destRow][destCol];
    if ((currentPlayer == 'W' && isupper(piece)) ||
        (currentPlayer == 'B' && islower(piece))) {
        return true;
    }
    return false;
}

bool isPawnFirst(int srcRow, char currentPlayer) {
    if (currentPlayer == 'W') {
        return srcRow == 1; 
    } else {
        return srcRow == 6; 
    }
}

bool isMoveValid(vector<int> move, vector<vector<char>> chessboard, char currentPlayer) {
    int srcRow = move[0];
    int srcCol = move[1];
    int destRow = move[2];
    int destCol = move[3];

    char piece = chessboard[srcRow][srcCol];
    if (piece == ' ') {
        cout << "Invalid move! No piece at the source position." << endl;
        return false;
    }
    
    if ((currentPlayer == 'W' && islower(piece)) ||
        (currentPlayer == 'B' && isupper(piece))) {
        cout << "Choose from your own pieces." << endl;
        return false;
    }

    if (isCellOccupied(chessboard, srcRow, srcCol, destRow, destCol, currentPlayer)) {
        cout << "Invalid move! There's a piece of your pieces at the destination." << endl;
        return false;
    }

    char destPiece = chessboard[destRow][destCol];
    if (destRow < 0 || destRow >= 8 || destCol < 0 || destCol >= 8 ||
        (destPiece != ' ' && destPiece == piece)) {
        cout << "Invalid move! Destination position is not valid or occupied by own piece." << endl;
        return false;
    }

    if (isObstacleFound(chessboard, srcRow, srcCol, destRow, destCol)) {
        cout << "Invalid move! You can't reach the destination." << endl;
        return false;
    }

    

    switch (tolower(piece)) {
        case 'p': 
            if (isVerticalValid(srcRow, srcCol, destRow, destCol) && 
                isPawnStep(srcRow, srcCol, destRow, destCol, currentPlayer)) {
                return true;
            } 
            else if (isDiagonalValid(srcRow, srcCol, destRow, destCol) && 
                    isPawnAttacking(srcRow, srcCol, destRow, destCol) && 
                    isPawnStep(srcRow, srcCol, destRow, destCol, currentPlayer)) {
                return true;
            }
            cout << "Invalid move for pawn" << endl;
            return false;
            break;
        case 'r':
            if (isHorizontalValid(srcRow, srcCol, destRow, destCol) || 
                isVerticalValid(srcRow, srcCol, destRow, destCol)) {
                return true;
            }
            break;
        case 'n':
            if (isKnightValid(srcRow, srcCol, destRow, destCol)) {
                return true;
            }
            break;
        case 'b':
            if (isDiagonalValid(srcRow, srcCol, destRow, destCol)) {
                return true;
            }
            break;
        case 'q':
            if (isHorizontalValid(srcRow, srcCol, destRow, destCol) || 
                isVerticalValid(srcRow, srcCol, destRow, destCol) || 
                isDiagonalValid(srcRow, srcCol, destRow, destCol)) {
                return true;
            }
            break;
        case 'k':
            if (isHorizontalValid(srcRow, srcCol, destRow, destCol) || 
                isVerticalValid(srcRow, srcCol, destRow, destCol) || 
                isDiagonalValid(srcRow, srcCol, destRow, destCol) || 
                isKnightValid(srcRow, srcCol, destRow, destCol)) {
                return true;
            }
            break;
        default:
            break;
        cout << "Invalid move! The piece cannot move to the destination position." << endl;
        return false;
    }
}

bool isHorizontalBlocked(vector<vector<char>> chessboard, int srcRow, int srcCol, int destRow, int destCol) {
    int step = (srcCol < destCol) ? 1 : -1;
    
    for (int col = srcCol + step; col != destCol; col += step) {
        if (chessboard[srcRow][col] != ' ') {
            return true;
        }
    }
    
    return false;
}

bool isVerticalBlocked(vector<vector<char>> chessboard, int srcRow, int srcCol, int destRow, int destCol) {
    int step = (srcRow < destRow) ? 1 : -1;
    
    for (int row = srcRow + step; row != destRow; row += step) {
        if (chessboard[row][srcCol] != ' ') {
            return true;
        }
    }
    
    return false;
}

bool isDiagonalBlocked(vector<vector<char>> chessboard, int srcRow, int srcCol, int destRow, int destCol) {
    int rowStep = (srcRow < destRow) ? 1 : -1; 
    int colStep = (srcCol < destCol) ? 1 : -1;
    
    int row = srcRow + rowStep;
    int col = srcCol + colStep;
    
    while (row != destRow && col != destCol) {
        if (chessboard[row][col] != ' ') {
            return true; 
        }
        row += rowStep;
        col += colStep;
    }
    
    return false; 
}

bool isObstacleFound(vector<vector<char>> chessboard, int srcRow, int srcCol, int destRow, int destCol) {

    if (isHorizontalValid(srcRow, srcCol, destRow, destCol)) {
        return isHorizontalBlocked(chessboard, srcRow, srcCol, destRow, destCol);
    }

    else if (isVerticalValid(srcRow, srcCol, destRow, destCol)) {
        return isVerticalBlocked(chessboard, srcRow, srcCol, destRow, destRow);
    }

    else if (isDiagonalValid(srcRow, srcCol, destRow, destCol)) {
        return isDiagonalBlocked(chessboard, srcRow, srcCol, destRow, destCol);
    }
    
    return false;
}

void doMove(vector<vector<char>>& chessboard, vector<int> move) {
    int srcRow = move[0];
    int srcCol = move[1];
    int destRow = move[2];
    int destCol = move[3];

    chessboard[destRow][destCol] = chessboard[srcRow][srcCol];
    chessboard[srcRow][srcCol] = ' ';
}

void outBoard(vector<vector<char>> chessboard, char currentPlayer) {
    if (currentPlayer == 'W')
        cout << "              - WHITE -          " << endl;
    else
        cout << "                WHITE            " << endl;
    cout << "    A   B   C   D   E   F   G   H" << endl;
    cout << "  +---+---+---+---+---+---+---+---+" << endl;
    for (int i = 0; i < 8; i++) {
        cout << i + 1;
        for (int j = 0; j < 8; j++) {
            cout << " | " << chessboard[i][j]; 
        }
        cout << " | " << i + 1 << endl << "  +---+---+---+---+---+---+---+---+" << endl;
    }
    cout << "    A   B   C   D   E   F   G   H" << endl;
    if (currentPlayer == 'B')
        cout << "              - BLACK -          " << endl;
    else
        cout << "                BLACK            " << endl << endl;
}


bool isKingCaptured(vector<vector<char>> chessboard) {
    bool whiteKingFound = false;
    bool blackKingFound = false;

    int whiteKingRow = -1, whiteKingCol = -1;
    int blackKingRow = -1, blackKingCol = -1;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (chessboard[i][j] == 'K') {
                whiteKingFound = true;
                whiteKingRow = i;
                whiteKingCol = j;
            } else if (chessboard[i][j] == 'k') {
                blackKingFound = true;
                blackKingRow = i;
                blackKingCol = j;
            }
        }
    }

    if (!whiteKingFound) {
        cout << "White King captured! Black wins the game." << endl;
        return true;
    }
    if (!blackKingFound) {
        cout << "Black King captured! White wins the game." << endl;
        return true;
    }

    return false;
}

bool isPawnReached(int destRow, char piece) {
    if (piece == 'P' && destRow == 7) {
        return true;
    }
    if (piece == 'p' && destRow == 0) {
        return true;
    }
    return false;
}

char getPromotion() {
    char promotionPiece;
    cout << "Choose a piece for pawn promotion (R, B, Q, N): ";
    cin >> promotionPiece;
    return promotionPiece;
}

void applyPromotion(vector<vector<char>> chessboard, int destRow, int destCol, char promotionPiece) {
    chessboard[destRow][destCol] = promotionPiece;
}