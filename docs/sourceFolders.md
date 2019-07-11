# Source Folders
Going to work on putting almost every file in the codebase into a folder. They will be:

## Controls
For gui widgets.

## Scene
For scenes.

## Service
Classes with which a stack of scenes can work reentantly with the same instance.
 - config
 - repository
 - game
 - timer

## Service/builder
These are all builder classes but they do not inherit from a parent class because it would be inefficient and pointless
and they will all just reveal a bunch of random functions, so the grouping into the builder folder is just to be nice
and tidy.

## Interface
For classes that define some vague interfaces and stuff that get used somewhere else.

## Model
Classes that would have to be created on a per scene basis in order for scenes to stack reentrantly.. Some will be a lot
dumber than others. Doesn't fit that well to the normal meaning of model since they can do shit but whatever.
 - Actor
 - Bullet
 - BulletManager

## Static
for files that only contain global functions (no global state allowed but global functions and constants are allowed.)
 - Utils
 - Constant
