#include "model.hxx"

Model::Model()
    : pieces{}
    , board_()
{

    //sets up the pawns
    for (int ii = 0; ii < 8; ++ii)
    {
        pieces.push_back(new Pawn({ii,1}, Player::dark, board_));
        pieces.push_back(new Pawn({ii,6}, Player::light, board_));
    }

    //sets up the rooks
    pieces.push_back(new Rook({0, 0}, Player::dark, board_));
    pieces.push_back(new Rook({7, 0}, Player::dark, board_));
    pieces.push_back(new Rook({0, 7}, Player::light, board_));
    pieces.push_back(new Rook({7, 7}, Player::light, board_));

    //sets up the knights
    pieces.push_back(new Knight({1, 0}, Player::dark, board_));
    pieces.push_back(new Knight({6, 0}, Player::dark, board_));
    pieces.push_back(new Knight({1, 7}, Player::light, board_));
    pieces.push_back(new Knight({6, 7}, Player::light, board_));

    //sets up the bishops
    pieces.push_back(new Bishop({2, 0}, Player::dark, board_));
    pieces.push_back(new Bishop({5, 0}, Player::dark, board_));
    pieces.push_back(new Bishop({2, 7}, Player::light, board_));
    pieces.push_back(new Bishop({5, 7}, Player::light, board_));

    //sets up the queens
    pieces.push_back(new Queen({3, 0}, Player::dark, board_));
    pieces.push_back(new Queen({3, 7}, Player::light, board_));

    //sets up the kings
    pieces.push_back(new King({4,0}, Player::dark, board_));
    pieces.push_back(new King({4,7}, Player::light, board_));
}

void Model::set_game_over_()
{
    turn = Player::neither;
}

bool Model::valid_move_(const Piece& to_be_moved, Position final)
{
    // check to make sure that the move is in bounds, as well as that the piece being moved belongs to the player
    // making the move, and also check to make sure the game isn't over
    if (Board::in_bounds(final) && to_be_moved.owner == turn  && !is_game_over_())
    {
        // if the aforementioned conditions hold, iterate through the pset of the piece being moved
        // if the position that the piece is being moved to is in the pset, then the move is valid
        for (auto posn : to_be_moved.pset)
        {
            if (posn == final)
                return true;
        }
    }

    return false;
}



void Model::play_move(Position initial, Position final)
{
    // create a pointer to the piece being moved
    Piece* moving = find_piece_by_pos(initial);

    // null-check the pointer
    if (!moving)
        return;

    //check to see if valid move, then if it is do the move
    if (valid_move_(*moving, final))
    {
        //first, deal with any captures
        if (board_[final] == other_player(turn))
            eliminate_piece_(final);

        // next, update the board to reflect player positions
        board_.set(initial, Player::neither);
        board_.set(final, turn);

        // next, deal with pawn promotion, else move as normal
        if ((turn == Player::dark && moving->name == "pawn" && final.y == 7) || (turn == Player::light && moving->name == "pawn" && final.y == 0))
            pawn_promotion_(initial, final);
        else
            (*moving).set_position(final, board_);

        //check to see if a player has lost all their pieces, if not change the turn, and recompute possible moves
        if (is_game_over_())
            set_game_over_();
        else
            turn = other_player(turn);

    }

    for (int ii = 0; ii < pieces.size(); ++ii)
    {
        pieces[ii]->compute_moves(board_);
    }
}

bool Model::is_game_over_() {
    //checks to see if either player has been wiped from the board
    return board_.count_player(Player::light) == 0 || board_.count_player(Player::dark) == 0;
}

Piece *Model::find_piece_by_pos(Position posn) {
    // iterates over the pieces vector, and tries to find the piece at the position
    // if the piece is found, its pointer is returned, otherwise a null pointer is returned
    for (auto & piece : pieces)
    {
        if (piece->get_position() == posn)
            return piece;
    }

    return nullptr;
}

void Model::eliminate_piece_(Position posn) {
    int index = piece_index_(posn);

    // bounds checks the posn of the piece to be eliminated,
    // to ensure that the vector isn't called out of bounds
    // also checks to make sure that there is a piece at the position,
    // to prevent an attempted write at a negative index
    if (!Board::in_bounds(posn) || index == -1)
        return;

    delete(pieces[index]);

    // erases a piece from the pieces vector, for either captures or pawn promotions
    pieces.erase(pieces.begin() + index);
}

int Model::piece_index_(Position posn) {
    // iterate over the pieces array, and find the index of the piece at a given position
    for (int ii = 0; ii < pieces.size(); ++ii)
    {
        if (pieces[ii]->get_position() == posn)
            return ii;
    }

    // in the event the piece isn't found, -1 will be returned, and bad things will happen
    return -1;
}

void Model::pawn_promotion_(Position initial, Position final) {
    // first, start by eliminating the pawn
    eliminate_piece_(initial);

    // once the pawn has been eliminated, add a queen at the final position
    pieces.push_back(new Queen(final, turn, board_));
}

Model::~Model() {
    /*
    if (pieces.empty())
        return;
    for (auto piece : pieces)
        delete(piece);
        */
}

