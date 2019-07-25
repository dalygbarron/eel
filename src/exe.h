#ifndef EXE_H
#define EXE_H

/**
 * Initialises a script runner.
 * @param scriptRunner is the script runner to initialise.
 * @return true on success and false on failure.
 */
int exe_initScriptRunner(struct ScriptRunner *scriptRunner);

/**
 * Initialises a script runner and gives it a script to run.
 * @param scriptRunner is the script runner to initialise.
 * @param script       is the script for it to run.
 * @return true on success and false on failure.
 */
int exe_initScript(struct ScriptRunner *scriptRunner, char const *script);

/**
 * Adds a script to a script runner.
 * @param scriptRunner is the script runner to add the script to.
 * @param script       is the lua name of the script to laod.
 * @return -1 on failure, or the id of the new script inside the runner.
 */
int exe_addScript(struct ScriptRunner *scriptRunner, char const *script);

/**
 * Runs everything that the script runner has loaded.
 * @param script is the script runner in question.
 */
void exe_run(struct ScriptRunner *script);

/**
 * Makes a script listen to an event.
 * @param scriptRunner is the script runner that contains the listening script.
 * @param script       is the number of the script to give the event to.
 * @param value        is the event that has been sent to the script.
 */
void exe_listen(struct ScriptRunner *scriptRunner, int script, int value);

#endif
