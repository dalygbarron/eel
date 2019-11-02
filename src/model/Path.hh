#ifndef PATH_H
#define PATH_H

/**
 * Represents a concatenation of two paths that can be stored on the stack and
 * automatically removes itself when it leaves the scope.
 */
class Path {
    public:
        constexpr static int const TEXT_BUFFER_SIZE = 128;

        /**
         * Creates the path to a given file appended onto a given base.
         * @param base is the base directory, anything after the last file
         *             seperator is ignored.
         * @param file is the file path to append onto the end of the base
         *             path. It is parsed for going back to parent directories
         *             and stuff like that.
         */
        Path(char const &base, char const &file);

        /**
         * Accesses the rendered path.
         * @return a pointer to the combined path.
         */
        char const &get();

    private:
        int n;
        char buffer[Path::TEXT_BUFFER_SIZE];

        /**
         * Applies a token to the current buffer.
         * @param start is the start of the token to apply.
         * @param n     is the length of the token to apply.
         */
        void applyToken(char const *start, int length);
};

#endif
