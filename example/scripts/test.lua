function main(context)
    local e = require("scripts.include.eel")(context);
    e.setRefresh(0x00ffffff);
    e.declare("Samwe thing but it's different hell yeah.");
    _transition("pwmaps/joint.tmx", context);
end
