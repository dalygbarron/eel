 #define unit_assert(message, test) do { if (!(test)) return message; } while (0)
 #define unit_runTest(test) do { char *message = test(); unit_testsRun++; \
                                if (message) return message; } while (0)
 extern int unit_testsRun;
