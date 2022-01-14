#include "view.hxx"

using namespace ge211;


View::View(Model const& model)
        : model_(model)
        , dark_pawn_("Black_Pawn.png")
        , light_pawn_("White_Pawn.png")
        , dark_rook_("Black_Rook.png")
        , light_rook_("White_Rook.png")
        , dark_knight_("Black_Horse.png")
        , light_knight_("White_Horse.png")
        , dark_bishop_("Black_Bishop.png")
        , light_bishop_("White_Bishop.png")
        , dark_queen_("Black_Queen.png")
        , light_queen_("White_Queen.png")
        , dark_king_("Black_King.png")
        , light_king_("White_King.png")
{}

void View::draw(Sprite_set& set, ge211::Position mouse_position)
{
    // draws the actual board, by which I mean the tiles
    for (int ii=0; ii < 8; ++ii)
    {
        for (int jj = 0; jj < 8; ++jj)
        {
            if ((ii+jj) % 2 == 0)
                set.add_sprite(light_tile_, {rect_size * ii, rect_size * jj}, 0);
            else
                set.add_sprite(dark_tile_, {rect_size * ii, rect_size * jj}, 0);
        }
    }

    // draws all the pieces, by checking the name of the piece and then drawing the appropriate sprite
    for (auto & piece : model_.pieces)
    {
        if ((piece->name) == "pawn" && piece->owner == Player::light)
            set.add_sprite(light_pawn_, piece_conversion_(piece->get_position()), 2);
        else if ((piece->name) == "pawn" && piece->owner == Player::dark)
            set.add_sprite(dark_pawn_, piece_conversion_(piece->get_position()), 2);
        else if ((piece->name) == "rook" && piece->owner == Player::light)
            set.add_sprite(light_rook_, piece_conversion_(piece->get_position()), 2);
        else if ((piece->name) == "rook" && piece->owner == Player::dark)
            set.add_sprite(dark_rook_, piece_conversion_(piece->get_position()), 2);
        else if ((piece->name) == "knight" && piece->owner == Player::light)
            set.add_sprite(light_knight_, piece_conversion_(piece->get_position()), 2);
        else if ((piece->name) == "knight" && piece->owner == Player::dark)
            set.add_sprite(dark_knight_, piece_conversion_(piece->get_position()), 2);
        else if ((piece->name) == "bishop" && piece->owner == Player::light)
            set.add_sprite(light_bishop_, piece_conversion_(piece->get_position()), 2);
        else if ((piece->name) == "bishop" && piece->owner == Player::dark)
            set.add_sprite(dark_bishop_, piece_conversion_(piece->get_position()), 2);
        else if ((piece->name) == "queen" && piece->owner == Player::light)
            set.add_sprite(light_queen_, piece_conversion_(piece->get_position()), 2);
        else if ((piece->name) == "queen" && piece->owner == Player::dark)
            set.add_sprite(dark_queen_, piece_conversion_(piece->get_position()), 2);
        else if ((piece->name) == "king" && piece->owner == Player::light)
            set.add_sprite(light_king_, piece_conversion_(piece->get_position()), 2);
        else if ((piece->name) == "king" && piece->owner == Player::dark)
            set.add_sprite(dark_king_, piece_conversion_(piece->get_position()), 2);
        else
            return;
        }

    // draws the highlighted possible positions
    //set.add_sprite(highlight_, conversion_(reverse_conversion(mouse_position)), 3);
    if (!model_.find_piece_by_pos(reverse_conversion(mouse_position)))
        return;
     if ((model_.find_piece_by_pos(reverse_conversion(mouse_position))->pset).empty())
         return;

     if(model_.find_piece_by_pos(reverse_conversion(mouse_position)))
     {
         if (model_.find_piece_by_pos(reverse_conversion(mouse_position))->owner == model_.turn)
         {
             for (auto pos : model_.find_piece_by_pos(reverse_conversion(mouse_position))->pset)
                 set.add_sprite(highlight_, conversion_(pos), 3);
         }
     }




}

Dimensions View::initial_window_dimensions() const
{
    // controls window size, where grid size is the size of each square
    Dimensions dims;
    dims.width = 8;
    dims.height = 8;
    return rect_size * dims;
}

std::string View::initial_window_title() const
{
    // displays the title
    return "Chess to the Death";
}


Position View::conversion_(Position posn) {
    return {posn.x * rect_size, posn.y * rect_size};
}

Position View::piece_conversion_(Position posn) {
    return {posn.x * rect_size + 5, posn.y * rect_size + 5};
}

Position View::reverse_conversion(Position posn) {
    return {posn.x / rect_size, posn.y / rect_size};
}

void View::model_update(Model &model) {
    model_ = model;
}
