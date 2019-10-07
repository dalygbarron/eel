#ifndef TEXT_REPOSITORY_H
#define TEXT_REPOSITORY_H

#include "service/repository/Repository.hh"

/**
 * Repository for text files.
 */
class TextRepository: public Repository<char const *> {
    private:
        virtual char const *create(char const *name) override;
};

#endif
