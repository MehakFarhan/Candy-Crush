# Candy-Crush
Console based game in C++. Designed using concepts of Programming Fundamentals and SFML library.

Hello and welcome to MY CANDY CRUSH!!!

This game is of swapping and matching similar tiles!

Extract the zip folder.
open the Executables of Candy Crush folder and right click on the candyCrush.exe to start yor game.

As simple as it sounds, just right click a candy and swap it with another tile horizontaly or verticaly by using arrow keys.
There are limited number of Moves i.e swaps and the goal is to reach the target score within those moves!

If some of the matches are already made the game removes them and add them to your score!

Press L key to load a previous game, from where you left off.
Press H key whenever you are stuck and the game will give you a hint. 

There are total 8 different types of candy
  ~ 6 of them are normal polygons
  ~ 2 of them are diamonds! These are special candy and they do not need to be matched with similar candy!

Different scores are given for different combinations of candy:
  ~ 3 same in a row, coloum or in a diagnol scores you +30.
  ~ 4 same in a row, coloum or in a diagnol scores you +40 and also makes a special white diamond.
  ~ 5 same in a row, coloum or in a diagnol scores you +50 and also makes a special black diamond.
  ~ Elbow / L shapes scores you +50 and also makes a special black diamond.
  ~ Swapping a special diamond shaped tile with any other neighbouring tile scores you +100

There are a lot of possible combinations!

  ~3 horizontal tiles      3 vertical tiles       3 diagonal tiles            3 tiles forming an elbow
                                                 (in any orientation)        (in any orientation)

  ~4 horizontal tiles      4 vertical tiles       4 diagonal tiles
                                                 (in any orientation)

  ~5 horizontal tiles      5 vertical tiles       5 diagonal tiles
                                                 (in any orientation)

  ~Any combination of 4 tiles gives you a special white diamond.
   swapping a white diamond with any other candy explodes 3 x 3 region around it.

  ~Any combination of 5 tiles gives you a special black diamond.
   swapping a black diamond with any other candy explodes the whole coloum and row.

If there are no possible swaps the game automatically shuffels the board.

The game automatically saves the game board in a txt file whenever you close it so that you can start where you left off.
Whenever you press L key, the last game will be loaded.

Pressing H would make a pink hightlight on any 2 tiles that can be swapped for your hint.

Rght Clicking on a tile would make a white highlight around the tile so you don't forget what tile you selected!

HAVE FUN PLAYING!!!



 
