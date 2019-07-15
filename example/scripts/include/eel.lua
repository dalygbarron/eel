return function(context)
    local eel = {
        util = {},
        radio = {}
    };

    --- Wait for a given period of time.
    -- Yields until the given number of ticks have passed.
    -- @int ticks is the number of ticks to wait
    function eel.wait(ticks)
        _wait(ticks, context);
        coroutine.yield();
    end

    function eel.say(name, ...)
        local arg = {...}
        local text = ""
        for i = 1, #arg do
            text = text .. arg[i];
        end
        _say(name, text, context);
        coroutine.yield();
    end

    --- Creates a gui text box.
    -- Yields until the text box has been closed by the player.
    -- @string ... all the text to say which gets concatenated together.
    function eel.declare(...)
        local arg = {...}
        local text = ""
        for i = 1, #arg do
            text = text .. arg[i];
        end
        _declare(text, context);
        coroutine.yield();
    end

    --- Sets the scene's background colour.
    -- @number colour is the colour to set it to as a 32 bit int.
    function eel.setRefresh(colour)
        _setRefresh(colour, context);
    end

    --- Pushes a new scene on the stack and waits for it to return.
    -- @string text is the main body of the transition
    -- @return the return value of the on top scene.
    function eel.push(text)
        _transition("p"..text, context);
        return coroutine.yield();
    end

    --- Converts a time in seconds into a time in ticks.
    -- @number time is the number of seconds
    -- @return time in seconds multiplied by the framerate.
    function eel.util.seconds(time)
        return time * 60.0;
    end

    --- Plays a sound.
    -- @string sound is the name of the sound file to play.
    function eel.radio.playSound(sound)
        _playSound(sound, context);
    end

    --- Plays a sound and yields until it has ended.
    -- @string sound is the name of the sound file to play.
    function eel.radio.waitSound(sound)
        local length = _playSound(sound, context);
        eel.wait(length);
    end

    return eel;
end
