# Lunar Lander
(from https://www.cs.brandeis.edu/~mairson/Courses/cs21b/lunar.pdf)

C - TDD - allegro graphic library

## 01 - print Hello World on a graphic display - spike

## 02 - make the display size a command line arg - spike

## 03 - install and use a font for display - spike

## 04 - display the code of the key being hit - spike

## 05 - changes the color of display when space is pressed - spike

## 06 - display a tick counter at every redraw - spike

## 07 - display a square at a position that evolves at each tick count - spike

## 08 - a controller displays a message to a console when initializing - test first

## 09 - after 3 seconds (90 ticks) the controller displays height, velocity and fuel information - test first

## 10 - the initial state of the lander is height:50, velocity:0, fuel:20 - test first

## 11 - after 1 second with burn rate 0, the state of the lander is height:50.0, velocity:-0.5, fuel:20 - test first

## 12 - after 2 uptades of 1 second with burn rate 0 the state of the lander is height:49.5, velocity:-1, fuel:20 - test first

## 13 - after 2 uptades of 1 second with burn rate 1 the state of the lander is height:50.5, velocity:1, fuel:18 - test first

## 14 - with each tick the controller updates and displays the lander state -- refactoring

## 15 - with each tick the console displays the updated lander state

## 16 - when the space key is pressed the fuel burn rate is 1 instead of 0

## 17 - the controller calculates the relative position of the lander in its trajectory to the moon

## 18 - display a red square at a position relative to initial height

