# segfaults on startup occasionally
Look into that some time when I am on linux and can use gdb. lldb is annoying. I would not be surprised if it was
connected with that warning about uniform not found that the shader complains about.

## How will we know what script to yield that data back to?
Ok so here is a hypothetical situation that should work in this engine. You are walking around in an overworld scene
and you hit into an enemy which triggers a fighting scene, and then when you win you go back to where you were in the
overworld and the enemy does an animation and dies.

Keep in mind that this is a script which is triggered when the user collides with the enemy, not every frame, so when
it yields it should be reentered before the scene gets updated again. Actually this is irrelevant, either way this
script will get run again before update and it will be sent a special value that it would not normally receive which is
the return code from the nested scene.

Ok so we will have a function on the current scene or whatever which saves this script as being the chosen one and then
also makes the scene create a nested scene once it has finished updating. Then when it gets run next it will receive the
response code which tells it it has been buried so it finds the script that set it to be buried and if there is one it
reenters it and passes in the reponse from the nested scene as the argument.

I think that this should be fine to even place in the middle of functions that are normally supposed to be run every
frame, but all this stuff that interacts with the engine should be abstracted into a little library and not touched in
normal use.

# Consider swapping INI for JSON
There are going to be times when I need more complicated data than INI can do. Some of those times I am going to need
some custom binary format, but a lot of the time I think I will need JSON, so it might be best to just switch now.

Actually, I just saw a thing online where a guy was using Lua files as his config files. Not a bad idea tbh.
Hmm maybe it is a bad idea. Who can say?


# Gui use vertex buffer instead of vertex array
Probably not needed, but could improve performance somewhat by using a vertex buffer which stores the gui stuff in the
GPU and doesn't change it. Won't work for bullets since they change every frame so no point.

This will not matter unless a very large number of GUI things are being rendered.

# Scene stack requires all the game stuff to be reentrant
Therefore, we can't really have a master bullet manager that is used everywhere since we could potentially need multiple
states of bullet managers.

# Generalise repository
don't do some freaky shit with templates, it is not worth the pain. Just make helpful functions for each get method to
make use of so that you do not need to do that.

# Animated Actors
Actors will need to be able to handle a bunch of different picture configurations. Some will have 4 way movement, some
will have 2 way movement and some will be static. For a start, I think we will just do 2 way movement and static, and
do 4 way movement some other time when I can be bothered to make the graphics for it.

The number of animation frames (including 1) must also be able to be customised.

Also, the animation behaviour must be customisable as well. Some actors should be animated when they move, some should
be animated all the time, and some should only be animated upon some event occurring.

# Make scripts use pointers to their stuff hell yeah man
bingo bongo you get the idea.

# Change the order in header files for classes so that public goes before private
There is not really ever any public interface that requires private stuff, but there is sometimes private stuff that
requires public interface so therefore public should always go before private so that there is not a need to be
inconsistent.
