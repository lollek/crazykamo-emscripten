crazykamo-emscripten
============

Crazy Witch game with chameleons

## About the game
Crazykamo is a game, where you need to lay 9 cards in a 3x3 grid, which makes a complete image.
There are 2 solution (with 4 rotations each), but it's really much harder than it looks.

## How to play:
Select one card and click another to swap them
Click a card twice to rotate it 90 degrees clockwise

## Technical information
Requires:
* GNU Make
* Emscripten

Run `make` and the html/javascript can be found in the target/-folder. If you
have python3 installed, you can run `make run` and then navigate to
http://localhost:8080/ to play
