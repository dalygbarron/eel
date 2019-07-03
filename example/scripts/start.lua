function main(context)
    local e = require("example.scripts.include.eel")(context);
    local count = 0
    for i = 1, 30 do
        e.declare(string.format("%d bingoglgogo %d", i, i));
        count = count + 1;
        e.wait(count * 2);
    end
    e.radio.playSound("bongo")
    e.declare("Ok, I am bored of that, that is the ENDE!");
    e.radio.waitSound("bongo");
    e.declare("Goodbye, I miss you all very, very much. However, it is time for me to go because I can hear the microwave ringing and inside are my tendies hell yeah man. I am the greatest hell yeah.");
    e.radio.playSound("bongo")
end
