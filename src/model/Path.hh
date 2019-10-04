#ifndef PATH_H
#define PATH_H

/**
 * Represents a filesystem path that can be moved around the joint from a root.
 */
class Path {
    public:
        constexpr static int const TEXT_BUFFER_SIZE = 1024;

        /**
         * Default constructor for empty path.
         */
        Path();

        /**
         * Copy constructor.
         */
        Path(Path const *parent);

        /**
         * Adds a path onto this path.
         * @param text is the path to add.
         */
        void apply(char const *text);

        /**
         * Applys the folder part of a path but not the filename.
         * @param text is the text containing folders and a filename.
         */
        void applyFolders(char const *text);

        /**
         * Removes a path off the end of this path. The inverse of apply.
         * Note that it is not validating, so if you enter weird inputs then
         * I do not know or care what will happen.
         * @param text is the path to remove.
         */
        void remove(char const *text);

        /**
         * Removes the folder part of a path off the end of this path. The
         * inverse of applyFolders. Again, input is not validated so be good.
         * Also, even though the file part is cut off, it still needs to be the
         * same thing that was passed to apply folders.
         * @param text is the text to remove.
         */
        void removeFolders(char const *text);

        /**
         * Creates the actual text of the path as it currently is.
         * @return the path. The data is subject to change so save it if you
         *         want it.
         */
        char const *render();

        /**
         * Takes in the start point of a token in a string and then returns how
         * long that token is so you can do stuff to it easily.
         * @param start is the start of the token.
         * @return the number of characters until it ends.
         */
        static int token(char const *start);

    private:
        int n;
        char text[Path::TEXT_BUFFER_SIZE];
        char rendered[Path::TEXT_BUFFER_SIZE];
};

#endif
