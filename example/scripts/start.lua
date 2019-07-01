local gui = require("example.scripts.gui")

function main()
    local count = 0
    for i = 1, 50000 do
        gui.declare(string.format("%d %d", i, i));
        count = count + 1;
    end
end
