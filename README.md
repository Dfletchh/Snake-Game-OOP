# Welcome to my custom Snake Game

## How-to File:
Welcome, you have made it to my version of the classic Snake game! This document will give
you the necessary knowledge to get this program up and running on your machine. 

If you are reading this, I can assume that you have downloaded the appropriate files and are 
aware of their location.

## To Begin:
Navigate to your terminal and change your directory to the “SnakeGame” file.

Enter the following command:  
    `g++ -std=c++11 main.cpp Snake.cpp Mamba.cpp Food.cpp Board.cpp FileIO.cpp -lcurses`  
    `./a.out`  

If all is well then, your program should now be up and running! You will be prompted to type
your preferred version. At this point, you should read through the rules before making a choice.

Now type **Viper** or **Mamba** then press enter. Next, you will be asked for your players
name, this will be used for the High Score leaderboard... if you have what it takes to beat out
previous champs.  

## Rules:  

### *Mamba:*  
This version is faster than the two versions you can play. To offset this the map is larger
and you have the ability to transit through walls. To add difficulty there are rock objects
represented as “##.” If your snake collides with one of these buggers the game will end. As you
grow be careful to not run into yourself as this will also end the game.  

### *Viper:*  
This version is for the person seeking a classic arcade style of gameplay. This snake
chugs along at a reasonable speed given its confined environment. There aren't any special abilities
in this version. If you run into a wall or yourself then the game is over.  

### *Score Board:*
If are skilled enough to top some of the legends on the High Score list, then you will be
forever saved as a Snake champion.  

## Tips:  
I did my best to create the most stable gaming environment for you. With that said this
program is at the mercy of your computer. I suggest you start with a fresh terminal and try to
avoid multitasking while running this program. The consequence of not doing so will degrade
performance. For example, you will notice this when a key is pressed but is not registered. This is 
because the key press occurred while other operations were being performed. Simply put the faster 
your computer is the less of a chance for this to occur.
