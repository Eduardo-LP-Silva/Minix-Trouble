# Minix Trouble

![image](https://user-images.githubusercontent.com/32617691/41675835-b15a8a9a-74bb-11e8-9649-6c39e2872995.png)

## Overview

This is a game developed during the course "Computer Laboratory" (LCOM) at FEUP, based on the Minix operating system. It was inspired
by 90s arcade games and the this course in particular.

In this game, the player controls a character whose main objective is to keep the servers running in good condition, more specifically, to make sure
there is at least one server running at a time. In order to accomplish this, the player must reactive any downed servers individually.
As time goes on, this mission becomes increasingly dificult, therefore the player will be awarded progressively more points.

### Main Menu

![image](https://user-images.githubusercontent.com/32617691/41676160-9b901b8e-74bc-11e8-9a86-d5d75b631f3e.png)

This a simple menu that allows the player to start the game or exit the application. He needs to simply drag the mouse over the option
he wishes to pick and click it with the left mouse button.

### Gameplay

The game area consists of a room with 4 servers close to each corner. At first all servers are running fine, giving the player some time
to adjust to the controls. He can move the character up/left/down/right with the WASD keys, respectively.

![image](https://user-images.githubusercontent.com/32617691/41676484-96699e36-74bd-11e8-9d65-7f3d346a8bbb.png)

After some time, one the servers will crash, turning red.

![image](https://user-images.githubusercontent.com/32617691/41676535-c4a4ac96-74bd-11e8-82b8-0dc515fc7028.png)|![image](https://user-images.githubusercontent.com/32617691/41676584-e8dc69aa-74bd-11e8-864c-f990c32439e0.png)
--------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------
Active Server | Downed server

To fix a server, the player will have to move next to it and press the 'E' key, earning some points in the process. 
That's it! As time progresses, the time between each server crash will decrease, so the user will have to react more quickly to 
each event. The longer he lasts the bigger his score at the end!

**Note:** The user can exit at any time by pressing the ESC key.

### Game Over

If all the servers are down at the same time, the player looses and is showed his final score on the screen.

![image](https://user-images.githubusercontent.com/32617691/41677220-998a82fe-74bf-11e8-8f75-3fefde0039c3.png)

He can now press the ESC key to go back to the main menu.

## Technical notes

The Bitmap.c module was taken from http://difusal.blogspot.pt/2014/09/minixtutorial-8-loading-bmp-images.html which was made
by Henrique Ferrolho, a former MIEIC student. It allowed us to load, use and display .bmp images. However, some changes were made, 
including the creation of a new function that ignored pixels of a certain color (background color) and the modification of the
original function to map the image to an auxiliar buffer instead of the original one.

### Function Call Graph

![image](https://user-images.githubusercontent.com/32617691/41677680-e5d300fe-74c0-11e8-83a6-8c4de00c0841.png)

### Known Issues

* In the main menu, the cursor movement can be quite sluggish. It is therefore advisable to move the mouse in short intervals,
allowing the cursor in the screen to "catch up" with the real life movement.

* During the game itself, if the player moves too close to the edges of the map, some visual bugs might occur.
