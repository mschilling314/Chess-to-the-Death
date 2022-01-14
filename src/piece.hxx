#pragma once

#include <ge211.hxx>
#include "player.hxx"
#include <vector>
#include "board.hxx"
#include <iostream>

using Position = ge211::Position;
using Position_set = std::vector<Position>;
using Directions = std::vector<ge211::Dimensions>;

//this is an abstract class, meant to serve as a polymorphic input
class Piece
{
public:
    // this describes who owns the piece
    Player owner;

    // this is what the piece is called, used for differentiation when drawing
    std::string name;

    // this is the set of all places the piece can move to
    Position_set pset;

    // this function returns the current position, simple accessor
    Position get_position() const;

    Piece(Position posn, Player owns, const Board& board);

    //this function updates the piece's position
    void set_position(Position final, Board board);


    virtual ~Piece();


    // this generates a new pset every time it's called
    virtual void compute_moves(Board board);

protected:
    // this stores the piece's position on the board
    Position posi_;

};

class Pawn : public Piece
{
public:
    Pawn(Position posn, Player owns, const Board& board);

    virtual void compute_moves(Board board) override;
private:
    // this is just whether it's the pawn's first move or not
    bool has_moved_;
};

class Rook : public Piece
{
public:
    Rook(Position posn, Player owns, const Board& board);

    void compute_moves(Board board) override;
private:
    Directions dirs = {{-1,0},{1,0},{0,-1},{0,1}};

};

class Knight : public Piece
{
public:
    Knight(Position posn, Player owns, const Board& board);

    void compute_moves(Board board) override;
private:
    Directions dirs = {{-2,-1},{-2,1},{2,-1},{2,1},{-1,-2},{-1,2},{1,-2},{1,2}};

};

class Bishop : public Piece
{
public:
    Bishop(Position posn, Player own, const Board& board);

    void compute_moves(Board board) override;
private:
    Directions dirs = {{-1,-1},{-1,1},{1,-1},{1,1}};
};

class Queen : public Piece
{
public:
    Queen(Position posn, Player own, const Board& board);

    void compute_moves(Board board) override;
private:
    Directions dirs = {{-1,-1},{-1,1},{1,-1},{1,1},{-1,0},{1,0},{0,-1},{0,1}};

};

class King : public Piece
{
public:
    King(Position posn, Player own, const Board& board);

    void compute_moves(Board board) override;
private:
    Directions dirs = {{-1,-1},{-1,1},{1,-1},{1,1},{-1,0},{1,0},{0,-1},{0,1}};

};