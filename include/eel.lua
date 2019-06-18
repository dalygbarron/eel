--- Creates and runs a nested scene.
-- Yields until the completion of the scene and then returns it's status code.
-- @param sceneType is the code thing to make the scene based on.
-- @return the nested scene's response code.
function nestScene(sceneType)
    _createScene(sceneType)
    return coroutine.yield()
end

--- Creates a gui speech box.
-- Yields until the speech box has been closed by the player.
-- @param name is the name to put on the box as the speaker.
-- @param text is the text to write in the box.
function say(name, text)
    box = _createPanel()
    _appendWidget(box, _createText(name))
    _appendWidget(box, _createText(text))
    _setGui(box)
    coroutine.yield()
end
