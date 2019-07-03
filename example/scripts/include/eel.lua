return function(context)
    local eel = {radio = {}}

    --- Wait for a given period of time.
    -- Yields until the given number of ticks have passed.
    -- @param ticks is the number of ticks to wait
    function eel.wait(ticks)
        _wait(ticks, context);
        coroutine.yield();
    end

    --- Creates a gui text box.
    -- Yields until the text box has been closed by the player.
    -- @param text    is the text to write in the box.
    function eel.declare(text)
        _declare(text, context);
        coroutine.yield();
    end

    --- Plays a sound.
    -- sound is the name of the sound file to play.
    function eel.radio.playSound(sound)
        _playSound(sound, context);
    end

    --- Plays a sound and yields until it has ended.
    -- sound is the name of the sound file to play.
    function eel.radio.waitSound(sound)
        _playSoundListened(sound, context);
        coroutine.yield();
    end

    return eel;
end
