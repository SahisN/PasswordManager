#ifndef PLATFORMACCOUNT_H
#define PLATFORMACCOUNT_H
#include <QString>

struct PlatformAccount {
    QString platformName;
    QString email;
    QString password;
    QString category;
    int index;
};
#endif // PLATFORMACCOUNT_H
