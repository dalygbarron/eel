return function(context)
    local eel = {
        util = {},
        radio = {}
    };

    --- Wait for a given period of time.
    -- Yields until the given number of ticks have passed.
    -- @int ticks is the number of ticks to wait
    function eel.wait(ticks)
        for i = 1, ticks do
            coroutine.yield();
        end
    end

    --- Writes a text box with a name on it on the screen.
    -- @string name is the name to put on the box
    -- @string ... a bunch of text to write in the text box.
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

    function eel.dialogue(stage, dialogue)
        local d = _createDialogue(context);
        for k, v in pairs(stage.left) do
            _dialogueAddLeft(d, v, context);
        end
        for k, v in pairs(stage.right) do
            _dialogueAddRight(d, v, context);
        end
        for line in dialogue do
            _dialogueAdd(d, line[0], line[1], context);
        end
        _dialogue(d, context);
        return coroutine.yield();
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
