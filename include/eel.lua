--- Creates and runs a nested scene.
-- Yields until the completion of the scene and then returns it's status code.
-- @param sceneType is the code thing to make the scene based on.
-- @return the nested scene's response code.
function nestScene(sceneType)
    _createScene(sceneType)
    return coroutine.yield()
end
