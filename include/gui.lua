--- Creates a gui speech box.
-- Yields until the speech box has been closed by the player.
-- @param name is the name to put on the box as the speaker.
-- @param text is the text to write in the box.
function say(name, text)
    box = _createPanel()
    _appendControl(box, _createText(name))
    _appendControl(box, _createText(text))
    _setGui(box)
    coroutine.yield()
end

--- Creates a gui text box.
-- Yields until the text box has been closed by the player.
-- @param text is the text to write in the box.
function declare(text)
    box = _createPanel()
    --_appendControl(box, _createText(name))
    --_appendControl(box, _createText(text))
    _setGui(box)
    coroutine.yield()
end
