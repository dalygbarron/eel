#ifndef WALK_STAGE_REPOSITORY_H
#define WALK_STAGE_REPOSITORY_H

#include "service/repository/Repository.hh"
#include "model/WalkStage.hh"

/**
 * Repository for walk stages.
 */
class WalkStageRepository: public Repository<WalkStage> {
    public:
        /**
         * Creates the repository with it's dependencies injected.
         * @param root        is the root that files are loaded from.
         * @param textRepo    is used for loading xml files.
         * @param tilesetRepo is used to get tilesets for the stages.
         */
        WalkStageRepository(
            char const *root,
            Repository<char> const *textRepo,
            Repository<Tileset> const *tilesetRepo
        );

    private:
        Repository<char> const *textRepo;
        Repository<Tileset> const *tilesetRepo;

        virtual WalkStage *create(
            char const *filename,
            char const *key
        ) const override;
};

#endif
