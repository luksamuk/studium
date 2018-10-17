#ifndef MACROS_H
#define MACROS_H

/* I advise you not to use these extensively.
   Those really are elegant macros, though.   */

#include <stdio.h>

// Preparation for actual important macros
#define __st_str_statement(x) #x
#define __st_str_log_lvl(lvl) " [ " __st_str_statement(lvl) " ] "
#define __st_log(lvl, thunk) puts(__st_str_log_lvl(lvl) thunk);


// The following macros should be used with string literals
// for console messages only.
#define st_log_info(msg)  __st_log(INFO,  msg);
#define st_log_debug(msg) __st_log(DEBUG, msg);
#define st_log_warn(msg)  __st_log(WARN,  msg);
#define st_log_crit(msg)  __st_log(CRIT,  msg);
#define st_log_err(msg) \
    printf(" [ ERR ] %s: %s\n", __func__, msg);

// The following macros should be used for overall
// debugging. Type in a specific thunk you wish to
// display info about, and let the magic happen on
// the console. Thunk is executed, and code line
// is printed to stdout. Less typing, more output.

// Logging will only happen on Debug target when
// using non-info log levels.

#define st_log_exec_info(thunk)			\
    __st_log(INFO,  __st_str_statement(thunk));	\
    thunk;

#ifndef STUDIUM_RELEASE

#    define st_log_exec_debug(thunk)		\
    __st_log(DEBUG, __st_str_statement(thunk));	\
    thunk;

#    define st_log_exec_warn(thunk)		\
    __st_log(WARN,  __st_str_statement(thunk));	\
    thunk;

#    define st_log_exec_crit(thunk)		\
    __st_log(CRIT,  __st_str_statement(thunk));	\
    thunk;

#else

#    define st_log_exec_debug(thunk) thunk;
#    define st_log_exec_warn(thunk)  thunk;
#    define st_log_exec_crit(thunk)  thunk;

#endif // STUDIUM_RELEASE
    

#endif // MACROS_H
