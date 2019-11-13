all: sprites.xml images/sprites.png

sprites.xml images/sprites.png: meta/sprites/*.png
	rat -o images/sprites.png -f sprites.xml -d 2048:2048 -g 2048:288:tileset meta/sprites/*.png
