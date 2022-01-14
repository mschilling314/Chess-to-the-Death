#include "board.hxx"

Board::Board()
    : board_(8,{8, Player::neither})
{
    // loop through the board vector and initialize the board to the appropriate players
    for (int ii = 0; ii < 8; ++ii)
    {
        for (int jj = 0; jj < 8; ++jj)
        {
            if (jj <= 1)
                board_[ii][jj] = Player::dark;
            else if (jj > 5)
                board_[ii][jj] = Player::light;
        }
    }
}


Player Board::operator[](Position posn) {
    return board_[posn.x][posn.y];
}

void Board::set(Position posn, Player player) {
    board_[posn.x][posn.y] = player;
}

int Board::count_player(Player player) {
    int count = 0;

    // iterate through the entirety of the board_ vector
    for(int ii = 0; ii < 7; ++ii)
    {
        for(int jj = 0; jj < 7; ++jj)
        {
            // find and count the instances of a player
            if (board_[ii][jj] == player)
                ++count;
        }
    }
    return count;
}

bool Board::in_bounds(Position posn)
{
    return 0 <= posn.x && posn.x < 8 && 0 <= posn.y && posn.y < 8;

}

