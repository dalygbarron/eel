# eel
Engine for bullet hell games eg touhou.
Possibly will be expanded for other types of game as well.

## Fixed Framerate
Most games currently use a variable framerate so that it is more adaptable to different systems. However, for bullet
hell type games I think that this is shitty because it means that the game will behave in a slightly different way on
different computers. For this kind of game there should be absolutely only one TRUE behaviour of the game and so it must
be in a fixed framerate. I am hoping that this framerate will be 60 FPS but we will see what happens.

## Dependencies
Engine currently relies upon SFML (https://github.com/SFML/SFML), Spdlog (https://github.com/gabime/spdlog), inih
(https://github.com/benhoyt/inih), and Lua 5.3.

Inih and Spdlog are stored within this codebase and I think I have mangled the code slightly so that they would compile
in my codebase and such.

SFML and Lua 5.3 are external so you must install them yourself. I forget how to do it but I will write it down later.
