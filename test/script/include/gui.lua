local gui = {};

function gui.say(word)
    howdy(string.format("word is %s!", word));
end

return gui;
