# Bubble Trouble

A game made using simplecpp graphics in C++

## Features Added

- Use `A` and `D` to move the shooter and `W` to shoot.
- Bubbles move vertically and follow  a parabolic path.
- When bubble and bullet collide, bubble and bullet disappear and radius of bubble hit is added to score.
- When shooter and bullet collide, health of shooter is reduced.
- There are 3 levels and in higher levels, balls are of larger size.
- Larger bubbles when hit by bullet are divided into two smaller bubbles moving in opposite directions.
- There is a timer, score counter, and health display. If timer goes off, the game ends.

## Playing the game

The repository contains `ELF 64-bit LSB pie executable` for the compiled game. [Click here](https://github.com/khushangsingla/Bubble-Trouble/raw/main/Bubble_Trouble) to download it.

### Compilation Instruction

Download simplecpp and build it using this [link](https://www.cse.iitb.ac.in/~ranade/simplecpp/). 
After that, in the repository, run the following command:

`s++ -o Bubble_Trouble source/shooter.cpp source/bullet.cpp source/bubble.cpp source/main.cpp`



### Video:
[Click here](https://github.com/khushangsingla/Bubble-Trouble/raw/main/Demo%20Video) to see the video reperesenting various features of the game.
