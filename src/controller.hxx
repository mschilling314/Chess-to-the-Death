#pragma once

#include "model.hxx"
#include "view.hxx"

// The main game class for Reversi.
class Controller : public ge211::Abstract_game
{
public:
    Controller();

// `protected` means that GE211 (via base class `ge211::Abstract_game`)
// can access these members, but arbitrary other code cannot:
protected:
    //
    // Controller operations called by GE211
    //


    // Defines how the game responds to mouse clicks (which is by attempting
    // to make a move at that position).
    void on_mouse_up(ge211::Mouse_button, ge211::Position) override;

    // Defines how the game responds to mouse motion (which is by moving
    // where the token will be placed).
    void on_mouse_move(ge211::Position) override;

    // These three delegate to the view:
    void draw(ge211::Sprite_set&) override;
    ge211::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;

private:
    Model            model_;
    View             view_;

    bool piece_clicked_;

    ge211::Position draw_mouse_posn_;
    ge211::Position mouse_posn_;
    ge211::Position clicked_piece_posn_;
};
