#ifndef PATH_H
#define PATH_H

/**
 * Represents a filesystem path that can be moved around the joint from a root.
 */
class Path {
    public:
        constexpr static int const TEXT_BUFFER_SIZE = 128;

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
         * Adds the name of a file onto the end of the path temporarily without
         * affecting how applies and removes will affect it. Only the name part
         * not the file path part.
         * @param file is the name of the file to put on the end.
         * @return a pointer to the rendered file path. It is subject to change
         *         save it if you want it.
         */
        char const *in(char const *file);

        /**
         * Appends a whole path onto the rendered path for when you are only
         * getting on thing so apply and remove are a waste of time.
         * @param file is the path to add onto the main path.
         * @return the newly rendered whole path.
         */
        char const *inWhole(char const *file);

        /**
         * Takes in the start point of a token in a string and then returns how
         * long that token is so you can do stuff to it easily.
         * @param start is the start of the token.
         * @return the number of characters until it ends.
         */
        static int token(char const *start);

    private:
        int n;
        int rn;
        char text[Path::TEXT_BUFFER_SIZE];
        char rendered[Path::TEXT_BUFFER_SIZE];
};

#endif
