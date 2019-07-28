# Scene Transition
Transition between scenes is requested via a string format which is written
into a buffer that is passed to the running scene.

## The format
If you want no transition to take place, then the string should simply start
with a null character. It should be safe to assume that this is what is passed
to the scene in the first place, so if you do not want anything to happen, you
should not have to do anything.

Otherwise, the first character should be one of the following depending on how
you want the transition to go:
 - `a` push the new scene onto the scene stack, keeping the current scene
       underneath.
 - `r` replace the current scene by removing it from the stack and then adding
       the new scene. If no scene details are included then the current scene
       is simply removed.

After the transition type character, the rest of the format is dependent on the
type of new scene to create.

### PlainScene
first character must be `p` and then give the filename of the script to execute
in the plain scene
