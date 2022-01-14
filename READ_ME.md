# Proposal: Chess to the DEATH

## Synopsis

This game is like regular chess, with one big twist:
no one cares about the king.  That is, there are no checks,
no checkmates, no castling moves, and capturing the king does 
not end the game.  What then, does end the game?  Why of 
course, when one player has no pieces left to capture!

## Functional requirements

For the functional requirements, a standard chessboard will
be created, with pieces that work as in standard chess as
follows: 

-Pawn: can move forward one space, or two spaces if it's
the first time that this piece moves, unless obstructed by 
a piece.  Can only capture diagonally in one space.  If 
it makes it to the other side, it becomes a queen.  En
passant is not included.

-Rook/Castle:  can move forward or backwards or sideways,
any number of spaces, unless obstructed by a piece.  If that
piece is an enemy, it may capture that piece.

-Knight:  can move in a three square L, may jump over pieces
during that motion, may capture pieces at its destination.

-Bishop:  can move diagonally any number of spaces, unless
obstructed by a piece.  If that piece is an enemy, it may
caputre that piece.

-Queen:  acts as both a rook/castle and bishop, wrapped up
in one piece.

-King:  can move one space in any direction.

During a capture, the piece capturing takes the place of
the piece being captured, and the piece being captured is
removed from the board, never to be seen again.

To make a move, a player will hover over a piece, at which
point that piece's possible moves will light up. Then,
when the player clicks on the piece, the highlights will
remain, at which point the player may click on the highlight
and the piece will way.  

The light player will always start. The winner will simply
be whoever has pieces left on the board, at which point 
no further moves will be allowed.  There are no
stalemates (infinite games are possible, though boring).
