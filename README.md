# eel
Engine initially for bullet hell games eg touhou. Does not need to be able to support other kinds of games yet, but it must be built in such a way that it will be able to support other modes of play with a "stack" of play modes nesting one another (as in like being in one kind of scene and that scene initiating another kind of play for a bit and then it jumping right back into the middle of that scene.

## Dependencies
Engine currently relies upon SFML (https://github.com/SFML/SFML), Spdlog (https://github.com/gabime/spdlog), inih
(https://github.com/benhoyt/inih), Catch 2 (https://github.com/catchorg/Catch2), and Lua 5.3.

Inih and Spdlog are stored within this codebase and I think I have mangled the code slightly so that they would compile
in my codebase and such.

SFML and Lua 5.3 are external so you must install them yourself. I forget how to do it but I will write it down later.

## Features and non Features
### Fixed Framerate
Most games currently use a variable framerate so that it is more adaptable to different systems. However, for bullet
hell type games I think that this is shitty because it means that the game will behave in a slightly different way on
different computers. For this kind of game there should be absolutely only one TRUE behaviour of the game and so it must
be in a fixed framerate. I am hoping that this framerate will be 60 FPS but we will see what happens.

### No Weird shaped bullets
That is correct. All bullets will be spherical, and they will not rotate after being created because it would slow down
the moving code a heap. As far as I can think, bullets are the only thing in the game that will need to be rotated at
all, and this will only be at creation time.

Now, you may at first be saddened by the fact that I am not going to allow weirdly shaped bullets but I think that it
will make part of the vibe of the game that where normally there would be a weird shaped bullet, instead there will just
be two little bullets one after the other, and also, these little bullets can be strung together in different types. I
think they will look like little bits of interesting looking fishing tackle and stuff like that.
