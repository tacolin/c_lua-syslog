#include <stdio.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

static int my_syslog(lua_State* L)
{
    int priority  = 0;
    char* content = NULL;

    if (!lua_isnumber(L, 1))
    {
        perror("syslog priority is not number");
        return 0;
    }

    if (!lua_isstring(L, 2))
    {
        perror("syslog content is not string");
        return 0;
    }

    priority = lua_tointeger(L, 1);
    content  = (char*)lua_tostring(L, 2);
    syslog(priority, (const char*)content);

    return 0;
}

static int my_closelog(lua_State* L)
{
    closelog();
    return 0;
}

static int my_openlog(lua_State* L)
{
    char* ident  = NULL;
    int option   = 0;
    int facility = 0;

    if (!lua_isstring(L, 1))
    {
        perror("openlog ident is not string");
        return 0;
    }

    if (!lua_isnumber(L, 2))
    {
        perror("openlog option is not number");
        return 0;
    }

    if (!lua_isnumber(L, 3))
    {
        perror("openlog facility is not number");
        return 0;
    }

    ident    = (char*)lua_tostring(L, 1);
    option   = lua_tointeger(L, 2);
    facility = lua_tointeger(L, 3);
    openlog((const char*)ident, option, facility);

    return 0;
}

static luaL_Reg _mylibs[] =
{
    {"openlog", my_openlog},
    {"closelog", my_closelog},
    {"syslog", my_syslog},
    {NULL, NULL}
};

#define ADD_CONSTANT(L, c)\
do {\
    lua_pushstring(L, #c);\
    lua_pushinteger(L, c);\
    lua_rawset(L, -3);\
} while(0)

int luaopen_syslog(lua_State* L)
{
    const char* libname = "syslog";
    luaL_openlib(L, libname, _mylibs, 0);

    // option constant
    ADD_CONSTANT(L, LOG_CONS);
    ADD_CONSTANT(L, LOG_NDELAY);
    ADD_CONSTANT(L, LOG_NOWAIT);
    ADD_CONSTANT(L, LOG_ODELAY);
    ADD_CONSTANT(L, LOG_PERROR);
    ADD_CONSTANT(L, LOG_PID);

    // facility constant
    ADD_CONSTANT(L, LOG_AUTH);
    ADD_CONSTANT(L, LOG_AUTHPRIV);
    ADD_CONSTANT(L, LOG_CRON);
    ADD_CONSTANT(L, LOG_DAEMON);
    ADD_CONSTANT(L, LOG_FTP);
    ADD_CONSTANT(L, LOG_KERN);
    ADD_CONSTANT(L, LOG_LOCAL0);
    ADD_CONSTANT(L, LOG_LOCAL1);
    ADD_CONSTANT(L, LOG_LOCAL2);
    ADD_CONSTANT(L, LOG_LOCAL3);
    ADD_CONSTANT(L, LOG_LOCAL4);
    ADD_CONSTANT(L, LOG_LOCAL5);
    ADD_CONSTANT(L, LOG_LOCAL6);
    ADD_CONSTANT(L, LOG_LOCAL7);
    ADD_CONSTANT(L, LOG_LPR);
    ADD_CONSTANT(L, LOG_MAIL);
    ADD_CONSTANT(L, LOG_NEWS);
    ADD_CONSTANT(L, LOG_SYSLOG);
    ADD_CONSTANT(L, LOG_USER);
    ADD_CONSTANT(L, LOG_UUCP);

    // level constant
    ADD_CONSTANT(L, LOG_EMERG);
    ADD_CONSTANT(L, LOG_ALERT);
    ADD_CONSTANT(L, LOG_CRIT);
    ADD_CONSTANT(L, LOG_ERR);
    ADD_CONSTANT(L, LOG_WARNING);
    ADD_CONSTANT(L, LOG_NOTICE);
    ADD_CONSTANT(L, LOG_INFO);
    ADD_CONSTANT(L, LOG_DEBUG);

    return 1;
}
