#include "model.hxx"
#include <catch.hxx>

TEST_CASE("example test")
{
    CHECK( 1 + 1 == 2 );
}


TEST_CASE("pawn movement")
{
    Model model;
    CHECK(model.find_piece_by_pos({0,4}) == nullptr);
    model.play_move({0,6},{0,4});
    CHECK(model.find_piece_by_pos({0,4}) != nullptr);
    CHECK(model.find_piece_by_pos({0,4})->name == "pawn");
}

TEST_CASE("pawn to queen")
{
    Model model;
    model.play_move({0,6},{0,4});
    model.play_move({0,1},{0,3});
    model.play_move({1,6},{1,4});
    model.play_move({0,3},{1,4});
    model.play_move({0,4},{0,3});
    model.play_move({0,0},{0,2});
    model.play_move({2,6},{2,5});
    model.play_move({0,2},{2,2});
    model.play_move({0,3},{0,2});
    model.play_move({1,1},{1,3});
    model.play_move({0,2},{0,1});
    model.play_move({2,2},{4,2});
    model.play_move({0,1},{0,0});
    model.play_move({6,1},{6,2});
    model.play_move({0,0},{3,3});
    CHECK(model.find_piece_by_pos({3,3}) != nullptr);
    CHECK(model.find_piece_by_pos({3,3})->name == "queen");
}

TEST_CASE("rook movement")
{
    Model model;
    model.play_move({0,6},{0,4});
    model.play_move({0,1},{0,2});
    model.play_move({0,7},{0,5});
    CHECK(model.find_piece_by_pos({0,5})->name == "rook");
    model.play_move({0,2},{0,3});
    model.play_move({0,5}, {5,5});
    CHECK(model.find_piece_by_pos({5,5})->name == "rook");
    model.play_move({1,1}, {1,2});
    model.play_move({5,5},{5,6});
    CHECK(model.turn == Player::light);
    model.play_move({5,5},{5,1});
    CHECK(model.find_piece_by_pos({5,1})->owner == Player::light);
}

TEST_CASE("knight movement")
{
    Model model;
    model.play_move({1,7}, {0,5});
    CHECK(model.find_piece_by_pos({0,5})->name == "knight");
}

TEST_CASE("bishop movement")
{
    Model model;
    model.play_move({1,6},{1,5});
    model.play_move({1,1},{1,2});
    model.play_move({2,7},{0,5});
    CHECK(model.find_piece_by_pos({0,5})->name == "bishop");
}

TEST_CASE("queen movement")
{
    Model model;
    model.play_move({2,6},{2,5});
    model.play_move({1,1},{1,2});
    model.play_move({3,7},{0,4});
    CHECK(model.find_piece_by_pos({0,4})->name == "queen");
    model.play_move({1,2},{1,3});
    model.play_move({0,4}, {0,1});
    CHECK(model.find_piece_by_pos({0,1})->name == "queen");
}

TEST_CASE("king movement")
{
    Model model;
    model.play_move({3,6},{3,5});
    model.play_move({1,1},{1,2});
    model.play_move({4,7},{3,6});
    CHECK(model.find_piece_by_pos({3,6})->name == "king");
}


TEST_CASE("endgame")
{
    Model model;
    int siz = model.pieces.size();
    for (int ii = 0; ii < siz/2;)
    {
        if (model.pieces[ii]->owner == Player::dark)
            model.pieces.erase(model.pieces.begin() + ii);
        else
            ++ii;
    }
    model.play_move({0,6},{0,4});
    CHECK(model.turn == Player::neither);
}
