#ifndef TEXT_REPOSITORY_H
#define TEXT_REPOSITORY_H

#include "service/repository/Repository.hh"
#include "static/xml/pugixml.hpp"

/**
 * Repository for text files. Slightly unusual in that it gives you a pointer
 * to a null terminated array of characters, not just to one character.
 */
class TextRepository: public Repository<char> {
    public:
        /**
         * Creates the repository.
         * @param root is the base directory all files are loaded from.
         */
        TextRepository(char const &root);

    private:
        virtual char *create(char const &name, char const &key) const override;
};

#endif
