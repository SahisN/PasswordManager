#ifndef USERDATAHANDLER_H
#define USERDATAHANDLER_H
#include "passwordmanagerio.h"
#include "platformaccount.h"
#include "extern/qaesencryption.h"

class  UserDataHandler : public PasswordManagerIO
{
public:
    // list & vars
    QJsonArray encryptedData;
    QList<PlatformAccount> accountData;
    QList<PlatformAccount> filteredData;
    QString activeCategory = "All";

    // functions
    UserDataHandler(const QString &filePath, const QString &vaultKey, const QString &salt);
    QJsonArray fetch_account_data();
    bool sync_account_data(const QString &platformName, const QString &platformEmail, const QString &platformPassword,
                           const QString &platformCategory);
    void filter_by_category(const QString &category);
    bool editAccountDetails(const QString &platformName,
                            const QString &platformEmail,
                            const QString &platformPassword,
                            const QString &platformCategory,
                            const int index);
    bool deleteAccountDetails(const int index);

private:
    // functions
    void update_account_list(QList<PlatformAccount> &accountData);
    QList<PlatformAccount> load_account_list(const QJsonArray &encryptedData);
    QString encryptPlainText(const QString &plainText);
    QString decryptText(const QString &encryptedText);

    // const vars
    const QString vaultKey;
    const QString salt;
    const QString platformNameKey;
    const QString emailNameKey;
    const QString passwordNameKey;
    const QString categoryNameKey;

    // class var
    QAESEncryption aesEncryption;

};

#endif // USERDATAHANDLER_H
