# Source Folders
Going to work on putting almost every file in the codebase into a folder. They will be:

## Controls
For gui widgets.

## Scenes
For scenes.

## Services
For classes that a given game should only have one of. Guess that means it includes the Game class since there is only
one of it per game as well.
 - builder
 - config
 - repository
 - game
 - timer

## Interfaces
For classes that define some vague interfaces and stuff that get used somewhere else.

## Models
Objects that need to be created per scene. Some will be a lot dumber than others.
 - Actor
 - Bullet
 - BulletManager

## Static
for files that only contain global functions (no global state allowed but global functions and constants are allowed.)
 - Utils
 - Constant
