function main(context)
    local e = require("scripts.include.eel")(context);
    e.setRefresh(0xff00ffff);
    e.say("Dany Burton", "Hello and welcome to my game.");
    e.declare(
        "Gonna say a heap of dumb text hell yeah enjoy. ",
        "Real hard real good hell yeah man.\n",
        "Hell yeah man. 2"
    );
    for i = 1, 10 do
        e.declare(string.format("%d bingoglgogo %d", i, i));
        e.wait(i / 10);
    end
    e.radio.playSound("sounds/glomp.wav")
    e.declare("Ok, I am bored of that, that is the ENDE!");
    e.radio.waitSound("sounds/mlep.wav");
    e.declare(
        "Goodbye, I miss you all very, very much. However, it is time for me to go because I can hear the ",
        "microwave ringing and inside are my tendies hell yeah man. I am the greatest hell yeah."
    );
    e.radio.waitSound("sounds/glomp.wav");
    _transition("ppscripts/test.lua", context);
end
