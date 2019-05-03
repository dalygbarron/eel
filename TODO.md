# Structure
I was just thinking that with this immediate mode gui code we are going to have in the lua stuff, there is actually no
need to have any different game scenes in this game. However, actually that is incorrect because if this engine is
expanded to allow extra play modes they will need their own scene.

# bullet stuff.
Going to have a seperate array for each type of bullet so that we do not have to switch textures due to them all being
in one list. This will mean there is a lot of empty arrays for bullets but who cares. This also means that we can load
in all the different bullet types and their properties at the start of the game from a list and we can then use these

See if I can bind a shader without raping the performance and use that to allow the same texture to be used for bullets
of different colours. Maybe also make them look cool and shiny or something if it's still not too slow. Technically
we could also make them purely shader generated but we will see how that goes.
