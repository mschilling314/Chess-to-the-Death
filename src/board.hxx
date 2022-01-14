#pragma once

#include <ge211.hxx>
#include "player.hxx"

using Position = ge211::Position;

class Board
{
public:
    Board();

    // this is used to return the player at a position
    Player operator[](Position posn);

    // this is used to set a player to a position
    void set(Position posn, Player player);

    // this is used to count the number of pieces a given player has
    int count_player(Player player);

    // this checks to make sure a given position is in the bounds of the board
    static bool in_bounds(Position posn);

private:

    // defines Positions to be a vector of vectors of players
    using Positions = std::vector< std::vector<Player> >;

    // creates a vector of vectors to hold players at given positions
    Positions board_;

};