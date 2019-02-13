**Here's how we will play duck duck goose.

First, the "it" player will go around the circle of players calling "duck" until they choose a player to be "goose". Then, the goose will chase "it" around the circle. If the goose catches "it", then the "it" player is out, and a new "it" is randomly selected from the players other than the goose. If "it" manages to run around the circle without being tagged, then "it" takes the goose's spot and the goose becomes the new "it".**

Make sure that the command line command for duck_duck_goose has two arguments where the first is of the configuration file (format guidelines below), and the second is a valid name for an output file (also a txt file).
-------------------------------------------------------------------------------
line 1: random seed (unsigned integer)
line 2: number of players in the game (1-indexed)
line 3: ID of "it" player
lines 4 to n+3: IDs of each seated player, from player 0 onward
