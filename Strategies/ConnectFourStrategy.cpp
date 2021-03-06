#include <limits>
#include "ConnectFourStrategy.h"
#include "constants.h"
#include "Windows/ConnectFourWindow.h"

ConnectFourStrategy::ConnectFourStrategy(ConnectFourWindow* window)
{
    this->window = window;
}

void ConnectFourStrategy::computeMove(ConnectFourBoard board) const {
    QVector<Coordinates>* playableMoves = board.playableMoves(SQUARE_OPPONENT);

    if (playableMoves->empty()) {
        pass();
    } else {      
        move(playableMoves->at(qrand() % playableMoves->size()));
    }
}

void ConnectFourStrategy::move(Coordinates move) const {
    int row = move.row - 1;
    int col = move.col -1;

    int positionUI = row * window->board->getCols() + col;

    window->handleButton(positionUI);
}

void ConnectFourStrategy::pass() const {
    window->pass();
}

ConnectFourBoard* ConnectFourStrategy::newBoard(ConnectFourBoard board, Coordinates move) const {
    ConnectFourBoard* newBoard = new ConnectFourBoard(board);
    newBoard->move(SQUARE_OPPONENT, newBoard->coordinates2Array(move));
    return newBoard;
}


int ConnectFourStrategy::evaluate(ConnectFourBoard board, int player) const {
    int utility = 0;

    int *heuristics = board.heuristicBoard();

    for (int i = 1; i < (board.getCols()+1); i++) {
        for (int j = 1; j < (board.getRows()+1); j++) {
            int currentSquare = board.getSquareState(board.coordinates2Array(i, j));

            if (currentSquare == player) {
                utility += heuristics[board.coordinates2Array(i, j)];
            } else if (currentSquare == -player) {
                utility -= heuristics[board.coordinates2Array(i, j)];
            }
        }
    }

    return utility;
}

int ConnectFourStrategy::minimax(ConnectFourBoard board, int player, int depth) const {
    QVector<Coordinates>* playableMoves = board.playableMoves(SQUARE_OPPONENT);

    if (depth == 0 || playableMoves->empty()) {
        return evaluate(board, SQUARE_OPPONENT);
    }

    int bestValue = std::numeric_limits<int>::min();

    for (int i = 0; i < playableMoves->size(); i++) {
        ConnectFourBoard* newGameBoard = newBoard(board, playableMoves->at(i));
        int index = minimax(*newGameBoard, -player, depth-1);

        if (index > bestValue) {
            bestValue = index;
        }
    }

    return bestValue;
}
