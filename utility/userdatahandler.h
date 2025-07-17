#ifndef USERDATAHANDLER_H
#define USERDATAHANDLER_H
#include "passwordmanagerio.h"
#include "platformaccount.h"

class UserDataHandler : public PasswordManagerIO
{
public:
    UserDataHandler(const QString &filePath);
    QList<PlatformAccount> fetchAccountData(const QString &vaultKey);
    bool updateAccountData();

private:
    void updateAccountDataList();
};

#endif // USERDATAHANDLER_H
