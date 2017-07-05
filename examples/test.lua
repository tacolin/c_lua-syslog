#!/usr/bin/lua

require "syslog"

syslog.openlog("TEST_EXAMPLE", syslog.LOG_CONS + syslog.LOG_PID, syslog.LOG_USER)

syslog.syslog(syslog.LOG_DEBUG,   "This is Debug Message\n")
syslog.syslog(syslog.LOG_INFO,    "This is Info Message\n")
syslog.syslog(syslog.LOG_WARNING, "This is Warning Message\n")
syslog.syslog(syslog.LOG_ERR,     "This is Error Message\n")

syslog.closelog()
