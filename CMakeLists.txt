cmake_minimum_required(VERSION 3.3)
project(final-project CXX)
include(.cs211/cmake/CMakeLists.txt)

set(MODEL_SRC
        # LIST ADDITIONAL MODEL .cxx FILES HERE:
        src/model.cxx
        src/board.cxx
        src/piece.cxx
        src/player.cxx)


add_program(play
        src/chess_to_the_death.cxx
        src/view.cxx
        src/controller.cxx

    ${MODEL_SRC})
target_link_libraries(play ge211)

add_test_program(model_test
    test/model_test.cxx
    ${MODEL_SRC})
target_link_libraries(model_test ge211)

# vim: ft=cmake