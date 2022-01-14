#include "controller.hxx"

using namespace ge211;

Controller::Controller()
        : model_()
        , view_(model_)
        , mouse_posn_(0,0)
        , clicked_piece_posn_(0,0)
        , draw_mouse_posn_(0,0)
{
    piece_clicked_ = false;
}


void Controller::draw(Sprite_set& sprites)
{
    view_.draw(sprites, draw_mouse_posn_);
}

Dimensions Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

void Controller::on_mouse_up(ge211::Mouse_button, ge211::Position)
{
    // firstly, check to make sure you're actually clicking on a piece,
    // or that a piece has already been clicked
    if (piece_clicked_ || model_.find_piece_by_pos(view_.reverse_conversion(mouse_posn_)))
    {
        // next, if something has already been clicked, then make a move
        if (piece_clicked_)
        {
            // make the move using the reversely converted mouse posn
            Position posn1 = view_.reverse_conversion(clicked_piece_posn_);
            Position posn2 = view_.reverse_conversion(mouse_posn_);
            model_.play_move(posn1, posn2);
            view_.model_update(model_);
        } else{
            // otherwise, a piece has been clicked, so store its posn
            clicked_piece_posn_ = mouse_posn_;
        }

        // lastly, toggle piece_clicked_
        piece_clicked_ = !piece_clicked_;
    }
}

void Controller::on_mouse_move(ge211::Position position)
{
    Position posn = position;

    //checks to make sure that the stored x positions aren't off the screen and therefore invalid/buggy
    if (posn.x < 0)
        posn.x = 0;
    else if (7 < view_.reverse_conversion(posn).x)
        posn.x = view_.initial_window_dimensions().width;

    //checks to make sure that the stored y positions aren't off the screen and therefore invalid/buggy
    if (posn.y < 0)
        posn.y = 0;
    else if (7 < view_.reverse_conversion(posn).y)
        posn.y = view_.initial_window_dimensions().height;

    // if a piece hasn't been clicked, then let the draw_mouse_posn_ vary with the actual position
    // this way, if a piece has been clicked, the position passed to draw won't change,
    // so that the highlight won't disappear when about to move
    if (!piece_clicked_)
        draw_mouse_posn_ = posn;

    // however, controller itself needs to know when you're moving the mouse,
    // so that it can try to make a move, so a separate mouse position is always updated
    mouse_posn_ = posn;
}
