#ifndef USERDATAHANDLER_H
#define USERDATAHANDLER_H
#include "passwordmanagerio.h"
#include "platformaccount.h"

class UserDataHandler : public PasswordManagerIO
{
public:
    QJsonArray encryptedData;
    QList<PlatformAccount> accountData;
    UserDataHandler(const QString &filePath, const QString &vaultKey);
    QJsonArray fetch_account_data();
    bool sync_account_data(const QString &platformName, const QString &platformEmail, const QString &platformPassword);

private:
    void update_account_list(QList<PlatformAccount> &accountData);
    QList<PlatformAccount> load_account_list(QJsonArray &encryptedData);
    const QString vaultKey;
    const QString platformNameKey;
    const QString emailNameKey;
    const QString passwordNameKey;
};

#endif // USERDATAHANDLER_H
