# segfaults on startup occasionally
Look into that some time when I am on linux and can use gdb. lldb is annoying. I would not be surprised if it was
connected with that warning about uniform not found that the shader complains about.

# Scene
A scene must be scriptable and have it's own main script kinda. When a scene is revealed on the stack, it's script
should be passed a value that was sent from the scene that was on top of it on the stack. That would be the most df


# Scripts and GUI
Two possibilities for interaction of scripts and GUI:
    - Immediate mode gui where the script sets up the gui each frame and has to pause and unpause everything else
      running.
    - Normal GUI where it gets opened up and nothing else runs while it is open, then when it finishes it returns
      something to the calling script.
Ok I thought immediate mode would be cool but actually I think the normal GUI sounds like a lot less of a pain to do.


# Returning data from widgets and nested scenes
ok so when you return a value from a widget it goes to the parent widget and back to the scene.
When you return a value from a scene on top I beleive it have removed all widgets on exit so there will be none and then
it will use that value in the same way it would as if it had come from a widget hell yeah.

Are we safe to remove all widgets before changing scene? Depends on what you call a widget. We probably need two
categories. One category for widgets that are blocking and then another for non blocking gui stuff. I do not know if
we will implement these through the same code though. Yeah I think we might as well still implement those as widgets.
However, we need some name for the specially selected widgets like text boxes that temporarily take over the game, these
are also stored in that special widget list in the scene.

OK WAIT. We are not capable of coping with a widget list. We need a single widget. thing about it. so we have a script,
we create a textbox, and then we yield until they press 'next' or whatever. There is no room in there for nested levels
of GUI shit. Therefore, there is no need to worry about this shit. and on the same hand, we do not start that sub scene
until the text box has run and then we make sub scene and yield again and what is passed to that yield will be the value
from the sub scene.

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


# stop using drawable interface
It forces you to use references and stuff which is making my code dumb for no reason and it's probably slower. I think
I will be best off just making my own render function. I don't think I have any need for an interface but I can make
one if I am desperate for something inane to do.

Man I really hate the things C++ has done to C. Adding classes is quite handy, but references are garbo that pollute
the language and subvert it. All those extra keywords like constexpr are the same. Override is one which I like though.


# Widget placement and sizing etc
Ok so we need to think about what the process is that a widget goes through in the process of nesting a bunch of them
up and chucking them on the screen.

Ok so first of all some parent panel is created which will be given a fixed size and position.

Next, we create a text box but it will not know what space it needs to fit into until it is shown to the box, and at
that point it will need to sort itself out in order to fit inside.

We then create a vertical selector, and when it is resized, it will actually use that as an opportunity to expand itself
to fit into the space given to it.

## Resize
Ok so we are going to need a kind of resize function for widgets. Widgets will store their current dimensions, but
when it is first created this will not yet be set. When a widget is added as the master panel, you will want to manually
resize it to the size you want before adding stuff to it.

When you add a widget into a panel or whatever, it will get it's resize function called which will render it and set it
up to display within the bounds given to it in whichever way it sees fit. For certain objects like the vertical selector
it will actually take it as an opportunity to take up all the horizontal space available to it.

Ok so resize will be called sequentially on each element. So you call it on a text box giving it the maximum bounds it
is allowed, and when that is done you check what it's new dimensions are in order to tell the next element how much
space it is allowed which will be what is left and not what the last element took up.

This function will also be where vertices and stuff like that are moved into position, and I think that if you wanted
to move a window you would probably have to call this too. That would not be very efficient but if I ever needed to use
it much I could add a move method.

There will be certain widgets to which you must pass a size vector at creation time so that they actually know how much
space they ought to be taking up. Maybe instead of passing them a hard value, you can pass them a proportion of the
available space to fill. That way it is agnostic of screen resolution and shit like that.

Hmmm it could also be necessary to give them a minimum size method which returns the minimum size they need so that you
could know how big some thingies should be because for example a button would probably collapse to nothing if it had
nothing inside it, it needs something like an image or a piece of text to tell it what it's size is.



# Gui construction.
Might make a class or something specifically for building gui elements because that way it could pass in configuration
values like colours and sizes and keep track of them all after getting them out of config.

Also, gui stuff should be restructured somewhat. All the interfaces needed by the GUI should be defined in the gui
folder and they should not have to include anything at all from outside that folder (except external dependencies like
sfml). That way if I ever code something else this code will still be useful.

Only annoying thing is I will not be able to use Utils if I do that, unless I make an exception for it since I could
include it in another project too since it's useful.
