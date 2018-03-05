#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    board = new Board();
    pside = side;

    oside = WHITE;
    if (pside == WHITE) {
        oside = BLACK;
    }
}

/*
 * Destructor for the player.
 */
Player::~Player() {

// deconstruct anything necessary

    delete board;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {

    if (opponentsMove != nullptr) {
        board->doMove(opponentsMove, oside);
    }

    vector<Move*> moves;

    if (board->hasMoves(pside)) {

        moves = board->getMoves(pside);

        Move * chosenMove = nullptr;

        chosenMove = prioritySpot(moves);
        if (chosenMove == nullptr) {
            chosenMove = minimax(moves);
        }

        board->doMove(chosenMove, pside);
        return chosenMove;
    }

    return nullptr;
}

Move *Player::prioritySpot(vector<Move*> moves) {
    // if we can get a corner, or an edge, we should
    // prioritize those moves

    // prioritize corners over edges
    for (unsigned int i = 0; i < moves.size(); i++) {
        int x = moves[i]->getX();
        int y = moves[i]->getY();
        if ((x == 0 && y == 0) || (x == 0 && y == 7) ||
            (x == 7 && y == 0) || (x == 7 && y == 7)) {
            return moves[i];
        }
    }

    // then check edges
    for (unsigned int i = 0; i < moves.size(); i++) {
        int x = moves[i]->getX();
        int y = moves[i]->getY();
        if (x == 0 || x == 7 || y == 0 || y == 7) {
            return moves[i];
        }
    }
    return nullptr;
}

Move *Player::minimax(vector<Move*> moves) {
    Move * chosenMove = moves[0];

    int minOBest = 65;
    for (unsigned int i = 0; i < moves.size(); i++) {
        // check all states after our possible moves
        Board * possBoard = board->copy();
        possBoard->doMove(moves[i], pside);
        vector<Move*> omoves = possBoard->getMoves(oside);
        
        int bestOTotal = 0;
        for (unsigned int j = 0; j < omoves.size(); j++) {
            // check all states after opponent's moves, given our move
            Board * futureBoard = board->copy();
            futureBoard->doMove(omoves[j], oside);
            int ototal = futureBoard->count(oside);
            if (ototal > bestOTotal) {
                bestOTotal = ototal;
            }
        }

        // want to minimize our opponent's best option
        if (bestOTotal < minOBest) {
            minOBest = bestOTotal;
            chosenMove = moves[i];
        }
    }
    return chosenMove;
}
