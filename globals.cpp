#include "globals.h"
#include <QDateTime>

QString APPLICATION_PATH;
QString NETWORK_PATH;
bool DEBUG_MODE;

User user;

/**
 * 毫秒级获取时间戳
 * @return 时间戳
 */
qint64 getTimestamp()
{
    return QDateTime::currentDateTime().toMSecsSinceEpoch();
}
