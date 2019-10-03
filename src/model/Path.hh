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
         * Removes a path off the end of this path. The inverse of apply.
         * @param text is the path to remove.
         */
        void remove(char const *text);

        /**
         * Creates the actual text of the path as it currently is.
         * @return the path.
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
