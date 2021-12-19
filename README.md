# Qwirkle Game

This is a multiplayer, CLI game based on the board game Qwirkle, written in C++

## Launch
At the main folder of this program, run the following command to start the game

```bash
./qwirkle
```

The main menu now should appear, the user can either choose to start a new game (type 1), or load a saved game (type 2)

## How to play
The rules for this game are mostly based on the board game rules. 

References: https://www.ultraboardgames.com/qwirkle/game-rules.php

To place a tile, use the command:

```bash
place [tile_name] at [grid_location]
```

To replace a tile in hand, use the command:

```bash
replace [tile_name]
```

Tile names are  represented by a 2-character code: [colour][shape]
  
| Colour | Colour Code | 
| ------------- | ------------- |
| Red | R |
| Orange | O |
| Yellow | Y |
| Green | G |
| Blue | B |
| Purple | P |

| Shape | Shape Code | 
| ------------- | ------------- |
| Circle | 1 |
| 4-Star | 2 |
| Diamond | 3 |
| Square | 4 |
| 6-Star | 5 |
| Clover | 6 |

Example: R3 for Red Diamond, G5 for Green 6-Star

## Saving
During a match, user can choose to save the game at anytime by using the command: 

```bash
save [file_name]
```



