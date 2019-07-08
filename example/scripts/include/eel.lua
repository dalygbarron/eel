return function(context)
    local eel = {radio = {}}

    --- Wait for a given period of time.
    -- Yields until the given number of ticks have passed.
    -- @int ticks is the number of ticks to wait
    function eel.wait(ticks)
        _wait(ticks, context);
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

    --- Plays a sound.
    -- @string sound is the name of the sound file to play.
    function eel.radio.playSound(sound)
        _playSound(sound, context);
    end

    --- Plays a sound and yields until it has ended.
    -- @string sound is the name of the sound file to play.
    function eel.radio.waitSound(sound)
        _playSoundListened(sound, context);
        coroutine.yield();
    end

    return eel;
end
