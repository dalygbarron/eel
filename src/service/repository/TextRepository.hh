#ifndef TEXT_REPOSITORY_H
#define TEXT_REPOSITORY_H

#include "service/repository/Repository.hh"

/**
 * Repository for text files.
 */
class TextRepository: public Repository<char const *> {
    public:
        /**
         * Creates the text repository.
         * @param config lets it find the root directory and stuff.
         */
        TextRepository(Config const *config);

    private:
        Config const *config;

        virtual char const *create(char const *name) override;
};

#endif
