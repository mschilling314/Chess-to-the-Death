#pragma once

#include "model.hxx"

#include <string>

class View
{
public:
    explicit View(Model const&);

    // draws the game, depending on model and a special mouse position
    void draw(ge211::Sprite_set& set, ge211::Position mouse_pos);

    // describes how big the game should be drawn
    ge211::Dimensions initial_window_dimensions() const;

    // gives the window a title
    std::string initial_window_title() const;

    // defines the size of a tile
    int rect_size = 80;

    // converts a UI position into a board position
    Position reverse_conversion(Position posn);

    void model_update(Model &model);

private:
    Model model_;

    // color of move highlights, meant to be slightly transparent so you can see the tiles
    ge211::Color high_light_ = ge211::Color(254, 255, 0, 120);

    // converts a board position into the corresponding UI position
    Position conversion_(Position posn);

    // does what conversion does, but also takes into account the centering of the piece sprites
    Position piece_conversion_(Position posn);

    // this is the sprite for highlighting possible moves
    ge211::Rectangle_sprite const
            highlight_   {ge211::Dimensions{rect_size,rect_size}, high_light_};

    // this is the sprite for dark tiles
    ge211::Rectangle_sprite const
            dark_tile_   {ge211::Dimensions{rect_size,rect_size}, ge211::Color::medium_magenta()};

    // this is the sprite for light tiles
    ge211::Rectangle_sprite const
            light_tile_   {ge211::Dimensions{rect_size,rect_size}, ge211::Color::white()};

    // these are the pawn sprites
    ge211::Image_sprite const dark_pawn_;
    ge211::Image_sprite const light_pawn_;

    // these are the rook sprites
    ge211::Image_sprite const dark_rook_;
    ge211::Image_sprite const light_rook_;

    // these are the knight sprites
    ge211::Image_sprite const dark_knight_;
    ge211::Image_sprite const light_knight_;

    // these are the bishop sprites
    ge211::Image_sprite const dark_bishop_;
    ge211::Image_sprite const light_bishop_;

    // these are the queen sprites
    ge211::Image_sprite const dark_queen_;
    ge211::Image_sprite const light_queen_;

    // these are the king sprites
    ge211::Image_sprite const dark_king_;
    ge211::Image_sprite const light_king_;
};

