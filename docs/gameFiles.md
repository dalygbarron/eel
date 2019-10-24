# Game Files
The game will consist of an generic executable, one root configuration file, several other data files, and then asset
files. No folder structure is enforced.

## Asset File Types
The asset files will have the following formats, which should be fairly self explanatory except maybe .rat which
is a custom texture packing format which you can find at https://github.com/dalygbarron/rat.
 - .wav for sounds.
 - .ogg for musics.
 - .xml for spritesheets
 - .png for non spritesheet pictures.
 - .ttf for fonts.
 - .lua for scripts.
 - .frag for fragment shaders.
 - .vert for vertex shaders.

## Data File Format
All data files are .ini format. They allow sections contained in [] signs, can use = or : for setting a value, and they
allow multiple values for a field by specifying it multiple times. Multiple values for a field that does not anticipate
multiple fields will cause undefined behavior but probably it will use the last value specified.

## Data Types
This section seems a bit pointless right now but I will probably add some enums and weird things eventually so this is a place to document how to use those.
### int
Normal int just used to represent a number.

### string
Normal string of text being used for whatever.

# Config File
This is the first file loaded by the game engine and by default, the game will search for it in the current directory
as game.ini. Once the config file has been loaded, the folder that it was in becomes the relative root directory of the
game.

The required fields are:
 - string **title**: title of the game as written on the window heading.
 - string **version**: the version of the game that this is. Just used as a piece of text so write whatever you want.
 - int **engine**: two bytes, the first being the major version of eel that this game requires, and the second being the
   minimum minor version of eel the game requires.
 - int **width**: width of the game screen.
 - int **height**: height of the game screen.
 - string **guiSpritesheet**: filename of spritesheet for rendering gui elements.
 - string **guiBase**: name of 9patch inside gui spritesheet for rendering normal gui elements.
 - string **guiHighlighted**: name of 9patch inside gui spritesheet for rendering highlighted gui elements.
 - string **guiDisabled**: name of 9patch inside gui spritesheet for rendering disabled gui elements.
 - string **bullets**: name of the bullets data file relative to this file.
 - string **fishes**: name of the fishes data file relative to this file.

# Bullets File
This file contains info on bullets. It first has a sectionless part which contains general bullet data, and then there
is a section for each bullet named after the bullet's name which is used to spawn it etc.

The required fields are:
 - string **spritesheet**: file containing the rat file used to render all bullets.
 - ... [bulletName]
    - string **sprite**: name of the sprite within the spritesheet to represent this bullet with.
    - int **radius**: the radius of the bullet for collision detection.
    - int **speed**: the speed at which the bullet moves unless altered in game on a per bullet instance basis.

# Fishes File
Dunno yet.
