# TO-DO list for strogue

## Add a separate window for interface

## Handle LOS
Right now, the whole map is always visible. Instead, ray-casting should be used to determine which tiles
should be currently visible to the player. Ideally, you also want to keep track of tiles that have been discovered,
but are not currently visible, and they should be displayed in a different color.

## Add health points
Right now everything dies in one hit, as soon as it touches any hostile tile. Instead, enemies and the player
should have HP that is depleted when fighting (and possibly recovers over time)

## Add depth
Right now, the map is completely static. Instead, every time the player goes up or down the stairs, the depth
should be increased or decreased accordingly and a new map should be generated. Possibly, enemies and gold
should spawn more frequently and/or have more hp/gold value as depth increases.
After a certain depth is reached, the game should end with a win screen.

## Add a main menu
Add a main menu with a fancy title that allows to start a new game, load the saved game, or view highscores.

## Add saving and loading
The state of the game (current depth, map, score, player, enemy and gold location, etc.) must be saved to a binary
file, and loaded in the main menu

## Add highscores
Every time a game ends, it should be added to the highscore list. The higscore list should be accessible in the main
menu

## Streamline code
The overall structure of the source code should be changed in order to better separate game logic and I/O.
Names of functions, parameters and types should be more consistent between libraries. For example, draw_player()
and print_map() should be changed so that they use the same verb.
