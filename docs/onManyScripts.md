# On Running Many Scripts at the Same Time
I was just thinking that it would probably fuck performance to have a whole
heap of lua scripts running at the same time in their own threads and all that,
so I have got an idea for how to do mass scripting.

Basically, the actual running script will be some kind of manager script made
by me, and you will be able to hook in normal scripts to be run by it as
coroutines. It will load the coroutine, and then save it with an ID number and
return that ID.

When the coroutine is run, it will set itself up to get called again by
listening for events, and when the event happens, the event speaker will send
the event to the master script along with that ID number, and the master script
will send the event in to the coroutine that it belongs to.

It seems a bit dodgy to have coroutines start as soon as they are created, so
I think that there should be a method on the script called start or something
to start all the coroutines.

## Implementation
I will use my own script struct which I think will just store the lua state,
and the name of the script so that when we report errors we can say the name of
the script.

Every script will contain the same main lua code which is my master script, but
there will be two functions for creating a script; one which creates the master
script and nothing else, and one which creates the master script and loads
a baby script into it ready to go.

Hell yeah this sounds good to me.
