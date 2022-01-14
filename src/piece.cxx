#include <utility>

#include "piece.hxx"

Piece::Piece(Position posn, Player owns, const Board& board)
    : posi_(posn)
{
    owner = owns;
    pset = {};
}

Position Piece::get_position() const {
    //simply the position of the piece is returned
    return posi_;
}

void Piece::set_position(Position final, Board board) {
    // the position is set
    posi_ = final;
    compute_moves(board);
}

void Piece::compute_moves(Board board) {pset.clear(); }

Piece::~Piece() = default;

Pawn::Pawn(Position posn, Player owner, const Board& board)
    : Piece(posn, owner, board)
{
    Pawn::compute_moves(board);
    name = "pawn";
    has_moved_ = false;
}


void Pawn::compute_moves(Board board)
{
    pset.clear();

    // defines the four moves a light pawn can make
    // to get the dark pawn moves, simply invert
    ge211::Dimensions dim1 = {0,-1};
    ge211::Dimensions dim2 = {0,-2};
    ge211::Dimensions dim3 = {-1,-1};
    ge211::Dimensions dim4 = {1,-1};

    // computes the moves if the pawn is a light pawn
    if (owner == Player::light)
    {
        if (posi_.y != 6)
            has_moved_ = true;
        if (board[posi_ + dim1] == Player::neither)
        {
            pset.push_back(posi_ + dim1);

            // if the pawn hasn't moved, and the position two tiles ahead of it is vacant,
            // then the position two tiles ahead of it is added to the pset
            if (!has_moved_ && board[posi_ + dim2] == Player::neither)
                pset.push_back(posi_ + dim2);
        }

        // next, we deal with diagonal captures, by checking to see if the alternate player is in either tile
        // if they are, then that tile can be captured, and we add it to the pset
        if (posi_.x - 1 >= 0 && board[posi_ + dim3] == Player::dark)
            pset.push_back(posi_ + dim3);

        if (posi_.x + 1 != 8 && board[posi_ + dim4]== Player::dark)
            pset.push_back(posi_ + dim4);
    }

    // same thing as before, but for the opposite player
    if (owner == Player::dark)
    {
        if (posi_.y != 1)
            has_moved_ = true;
        if (board[posi_ - dim1] == Player::neither)
        {
            pset.push_back(posi_ - dim1);

            // if the pawn hasn't moved, and the position two tiles ahead of it is vacant,
            // then the position two tiles ahead of it is added to the pset
            if (!has_moved_ && board[posi_ - dim2] == Player::neither)
                pset.push_back(posi_ - dim2);
        }

        // next, we deal with diagonal captures, by checking to see if the alternate player is in either tile
        // if they are, then that tile can be captured, and we add it to the pset
        if (posi_.x + 1 < 8 && board[posi_ - dim3] == Player::light)
            pset.push_back(posi_ - dim3);

        if (posi_.x - 1 >= 0 && board[posi_ - dim4]== Player::light)
            pset.push_back(posi_ - dim4);
    }
}


Bishop::Bishop(Position posn, Player owner, const Board& board)
        : Piece(posn, owner, board)
{
    Bishop::compute_moves(board);
    name = "bishop";
}

void Bishop::compute_moves(Board board)
{
    pset.clear();
    Position posn(0,0);

    // iterate over all directions that a bishop can move (defined in .hxx)
    for (auto dir : dirs)
    {
        // calculates the next position a bishop would move to in a given direction
        posn = posi_ + dir;

        // as long as the tile the bishop would move to is in bounds and empty, add it to pset
        while (Board::in_bounds(posn) && board[posn]== Player::neither)
        {
            pset.push_back(posn);
            posn += dir;
        }

        // if the final tile the bishop would move to in a given direction is in bounds, and owned by the other player,
        // then there's a capturable tile, and it should be added to pset
        if (Board::in_bounds(posn) && board[posn] == other_player(owner))
            pset.push_back(posn);
    }
}

Knight::Knight(Position posn, Player owner, const Board& board)
        : Piece(posn, owner, board)
{
    Knight::compute_moves(board);

    name = "knight";
}

void Knight::compute_moves(Board board)
{
    pset.clear();
    Position posn(0,0);

    // iterate over all the possible directions a knight can move
    for (auto dir : dirs)
    {
        posn = posi_ + dir;

        // if the tile the knight would move to in a given direction is in bounds
        // and the player doesn't own the tile already , add the tile to the pset
        if(Board::in_bounds(posn) && board[posn]!= owner)
            pset.push_back(posn);
    }
}


Rook::Rook(Position posn, Player owner, const Board& board)
        : Piece(posn, owner, board)
{
    Rook::compute_moves(board);
    name = "rook";
}

void Rook::compute_moves(Board board)
{
    pset.clear();
    // legitimately the exact same as the bishop, but with different directions

    Position posn(0,0);

    for (auto dir : dirs)
    {
        posn = posi_ + dir;

        while (Board::in_bounds(posn) && board[posn]== Player::neither)
        {
            pset.push_back(posn);
            posn += dir;
        }

        if (Board::in_bounds(posn) && board[posn]== other_player(owner))
            pset.push_back(posn);
    }
}

Queen::Queen(Position posn, Player owner, const Board& board)
        : Piece(posn, owner, board)
{
    Queen::compute_moves(board);
    name = "queen";
}

void Queen::compute_moves(Board board)
{
    pset.clear();
    // same as for bishop and rook, but with different directions

    Position posn(0,0);

    for (auto dir : dirs)
    {
        posn = posi_ + dir;

        while (Board::in_bounds(posn) && board[posn] == Player::neither)
        {
            pset.push_back(posn);
            posn += dir;
        }

        if (Board::in_bounds(posn) && board[posn] == other_player(owner))
            pset.push_back(posn);
    }
}


King::King(Position posn, Player owner, const Board& board)
        : Piece(posn, owner, board)
{
    King::compute_moves(board);
    name = "king";
}

void King::compute_moves(Board board)
{
    pset.clear();
    // same as knight, but with different directions

    Position posn(0,0);

    for (auto dir : dirs)
    {
        posn = posi_ + dir;

        if (Board::in_bounds(posn) && board[posn]!= owner)
            pset.push_back(posn);
    }
}



