#ifndef TEXT_REPOSITORY_H
#define TEXT_REPOSITORY_H

#include "service/repository/Repository.hh"
#include "static/xml/pugixml.hpp"

/**
 * Repository for text files.
 */
class TextRepository: public Repository<char const *> {
    public:
        /**
         * Creates the repository.
         * @param root is the base directory all files are loaded from.
         */
        TextRepository(char const *root);

        /**
         * Loads an xml node out of a text file.
         * @param name is the name of the text file.
         * @param tag  is the name of the top node to return.
         * @return the node which now becomes your problem to deal with if it
         *         needs freeing I dunno.
         */
        pugi::xml_node getXml(char const *name, char const *tag);

    private:
        virtual char const *create(char const *name, char const *key) override;
};

#endif
