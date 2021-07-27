# Tetris-Game
This is our C++ Tetris Game! 
It was developped as a part of a college course, and we had a lot of fun with it!
The assignment was to create a two-players tetris game with two unique qualities: 
1. A bomb that drops every few moves and clears a part of the board
2. An option to play against the computer.

we had to create an AI to play as the computer.

our algorithm:
in the "future position" function we are finding the ultimate position for the shape we just placed the board. 
we are checking 4 parameters to determine the best position: height differences between the columns(wether the shape has hightened the columns),
wether there are full lines we can clear, 
wether there are empty spots we cannot clear (jailes spaces) and bumpinness - height difference between all the columns.
each criteria gets a score, so we are saving the best score - and this is our best position.
then we are finding the correct path to it in the function called "pathFinding".
