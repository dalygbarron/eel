local gui = {};

function gui.say(content, x, y, w, h)
    while (true) do
        box(BLUE, x, y, w, h);
        text(content, WHITE, x, y, w, h);
        if (aPressed() || bPressed()) break;
    end
end

return gui;
