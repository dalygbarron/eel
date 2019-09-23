#ifndef TILESET_H
#define TILESET_H

class Tileset {
    public:
        sf::Texture *texture;

        /**
         * Creates the tileset from the given data.
         * @param data is the contents of a tiled tileset xml file. If this
         *             file is screwed then I am ready and willing to crash the
         *             whole game so be good.
         */
        Tileset(char const *data);

        /**
         * Takes four vertices and makes them into a quad for the given tile.
         * @param vertices is a pointer to the first vertex.
         * @param id       is the id of the tile to make.
         */
        void buildQuad(sf::Vertex *vertices, unsigned char id);

    private:
        char *name;
};

#endif
