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

### Versioning
The engine stores a Major, Minor, and Revision version number ie Version 1.3.1 or something like that. As a whole these
three numbers make up the specific version of the engine, but each one has a bit of a different meaning.

The revision number means that it is an iteration from the previous revision version due to bugs, therefore it can
break with functionality in the previous revision assuming that the functionality was a bug if you know what I mean.

The minor version number means that it has new features compared to the previous version, and so a game can say that
it only compatible with a given major.minor version and higher.

The Major version groups a collection of versions that are all backwards compatible, so therefore any game which
specifies a given major version will work with any version that has the same major version and the same or higher
minor version. It will not work with lower minor versions, or different major versions.

The game itself will only store the major and minor versions and not the revision number as you do not need to specify
that your game is only compatible with the non buggy version, that would be stupid.

### Gui does not depend on engine as a whole
I am real sick of writing a new GUI for every game and engine, so I will write the GUI code so that everything to do
with it is in it's own folder, and it does not include anything from outside that folder other than external
dependencies like SFML.

The game engine can obviously include the gui code and even use it's utils etc which it will use maybe for manipulating
vertices.
