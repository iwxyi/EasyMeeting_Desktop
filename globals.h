#ifndef GLOBALS_H
#define GLOBALS_H

#include <QString>
#include "user.h"

extern QString APPLICATION_PATH;
extern QString NETWORK_PATH;
extern bool DEBUG_MODE;

extern User user;

extern qint64 getTimestamp();

#endif // GLOBALS_H
