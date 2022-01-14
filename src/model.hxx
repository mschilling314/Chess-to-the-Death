#pragma once

#include <ge211.hxx>
#include "player.hxx"
#include "piece.hxx"
#include <vector>
#include "board.hxx"
#include <iostream>

using Position = ge211::Position;

using Pieces = std::vector<Piece*>;

class Model
{
    public:
    Model();

    // describes whose turn it is, always starts with light
    Player turn   = Player::light;

    // this is a vector of all pieces that are alive
    Pieces pieces;

    // makes a move
    void play_move(Position initial, Position final);

    // returns a pointer to a piece based on position
    Piece* find_piece_by_pos(Position posn);

    ~Model();

private:
    // this is used to store player positions throughout the board
    Board board_;

    // sets turn to neither in event game is over
    void set_game_over_();

    // checks to see if the game is over
    bool is_game_over_();

    // helper for move, checks to see if move is valid
    bool valid_move_(const Piece& to_be_moved, Position final);

    // helper for eliminate_piece_, finds index of a piece given a position
    int piece_index_(Position posn);

    // helper for move and pawn_promotion_, deals with the deletion of a piece
    void eliminate_piece_(Position posn);

    // helper for move, deals with pawn promotion
    void pawn_promotion_(Position initial, Position final);

};