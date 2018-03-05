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
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                Move * move = new Move(x, y);
                if (board->checkMove(move, pside)) {
                    moves.push_back(move);
                }
            }
        }
        Move * chosenMove = moves[0];
        board->doMove(chosenMove, pside);
        return moves[0];
    }

    return nullptr;
}
