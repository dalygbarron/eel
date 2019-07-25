local scripts = {};

--- Adds a script to the script runner.
-- @param string file is the lua version of the file path
-- @return int the index of the file in this runner.
function addScript(file)
    local script = require(file);
    local i = #scripts;
    scripts[i] = script;
    return i;
end

--- Makes a script in the script runner listen to an event
-- @param int script is the index of the script getting the event.
-- @param int value  is the event value itself.
-- @return int whatever the script returned.
function listen(script, value)
    return coroutine.resume(scripts[script], value);
end
