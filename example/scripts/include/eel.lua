return function(context)
    local eel = {}

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

    return eel;
end
