# Instructions

## Run and Build

### The Main Program

To compile the main program of the project:

```
make

make compile
```

To run the main program:

```
make run
```

### Additional Tool

This tool is used to add more monster and move data that can be read and processed by the main program. 

To compile the tool:

```
make compile-tool
```

To run the tool:

```
make tool
```

## Working Features

- Ability to load a save file. Requires an existing save file which means you need to call the `save` command in the client. `exit` will also save progress to the save file.
- Catch monsters using the monster use the `catch` command in the party screen.
- Initiate a connection to battle another player using the `battle -server [ip_address]`. Usage of the `battle -server` is shown below. The program will wait until another player, the client, connects to the battle using `battle -client [ip_address]` where the `ip_address` matches the IP address of server. 

```
// valid `battle -server` or `battle -s` calls. -server can be shortened to -s
battle -s 127.0.0.1         \\ IP address
battle -s                   \\ Using current IP address or localhost
battle -s localhost         \\ uses localhost

// invalid `battle -server` call
battle -s marge.stuy.edu    \\ invalid call

// valid `battle -client` or `battle -c` calls. -client can be shortened to -c
battle -c 127.0.0.1         \\ IP address to connect to
battle -c localhost

// How to initiate a battle between two clients.
    // server
    battle -s [optional_ip_address]
    battle -s 149.89.161.100    \\ example using marge IP address
    // client
    battle -c [ip_address of server]
    battle -c 149.89.161.100    \\ example using marge IP address
```

- Turned based battle using commands such as `move 1` and `move 2`. Communicates between the players using the socket until the battle is finished. If a monster's health goes to 0, it will be removed from the party.
- If a player in the battle disconnects before making their move, the other client will recieve a disconnection message. They will return back to the party screen afterwards. 
- Tool to create monsters and moves. Saves the monster and move data to `.data` files in the `res` directory. The tool assumes that the user is providing valid input. 

```
CREATE MOVE DATA
The name of the move has to be at most 31 characters excluding the null terminator. 
The move type has to be either "attack" or "heal"
The asked value in move has to be a positive integer.

CREATE MONSTER DATA
The name of the monster has to be at most 15 characters excluding the null terminator.
The maximum health has to be a positive integer.
```

## Bugs

- There is a desynchronization bug during the battle in which under some conditions. As a result, the two clients will show different health percentages which is an error. We believe that the error occurs when a healing move is used as one client will perform the heal while the other client will not perform the heal. This results in the desynchronization. An effect of this bug is a disconnection and one client completing the battle earlier than the other. 
  - tldr; Issue with battle synchronization between clients. Probably due to healing moves
  - We consider this bug as a low priority as it is a bug involving the battling. Our main focus was not on the battle mechanics, but to have communication between two players using sockets.
- A broken pipe error occurs in the following situation during the battle screen:
  - Player 2 performs a `move` command
  - Player 2 exits the program unexpectedly (e.g. `SIGTERM`)
  - Player 1 performs a `move` command. The battle screen will update as expected.
  - Player 1 enters another `move` as they are unaware the other user have disconnected. 
  - Upon the command, the broken pipe error occurs.
  - There may be other scenarios where a broken pipe occurs, but this is the one that we found.
  - However, if player 2 disconnects before performing a move, a broken pipe error does not occur and player 1 exits the battle scene normally.
- If the terminal size is too small, the program will not run and will terminate early. The terminal size must be at a minimum 79x24. Considering the standard terminal size is 80x24, this should not be an issue. However, there is no error message detailing this issue.
- Do not make the terminal window smaller when the program is running. This will mess up the TUI as it will display the TUI as if it was the previous size. It is, however, fine to make the window larger. 
