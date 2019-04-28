function main()
    local gui = require "test.script.include.gui"
    local count = 0
    while true do
        gui.say("eh"..count)
        coroutine.yield(count);
        count = count + 1;
    end
end
