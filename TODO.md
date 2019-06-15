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
