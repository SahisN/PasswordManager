#include "userdatahandler.h"
#include "platformaccount.h"
#include <QJsonObject>

UserDataHandler::UserDataHandler(const QString &filePath, const QString &vaultKey)
    : PasswordManagerIO(filePath),
    vaultKey(vaultKey),
    platformNameKey("platformName"),
    emailNameKey("email"),
    passwordNameKey("password")
{
    encryptedData = fetch_account_data();
    accountData = load_account_list(encryptedData);

}

QList<PlatformAccount> UserDataHandler::load_account_list(QJsonArray &encryptedData) {
    QList<PlatformAccount> platformAccountList;
    // if accountJson is not empty, convert into QList<PlatformAccount>
    for(const QJsonValue &account : encryptedData) {
        if(!account.isObject()) continue;

        const QJsonObject accountObject = account.toObject();
        PlatformAccount platform;

        platform.platformName = accountObject[platformNameKey].toString();
        platform.email = accountObject[emailNameKey].toString();
        platform.password = accountObject[passwordNameKey].toString();

        platformAccountList.append(platform);
    }

    return platformAccountList;

}

bool UserDataHandler::sync_account_data(const QString &platformName, const QString &platformEmail, const QString &platformPassword)
{
    // create a object representing the new account data
    QJsonObject newAccount;
    newAccount[platformNameKey] = platformName;
    newAccount[emailNameKey] = platformEmail;
    newAccount[passwordNameKey] = platformPassword;

    // add the object to existing QJsonArray
    encryptedData.append(newAccount);

    // write the data
    const bool isSaved = write_json(encryptedData);

    // update the QList if successful
    if(isSaved) {
        const PlatformAccount newPlatformAccount = {platformName, platformEmail, platformPassword};
        accountData.append(newPlatformAccount);
    }

    // if writing data is not successful then remove the new data from memory
    else {
        accountData.removeLast();
    }

    return isSaved;
}

QJsonArray UserDataHandler:: fetch_account_data() {
    // read user account json
    const QJsonArray accountData = read_json();

    // check if accountJson is empty, return empty list
    if(accountData.isEmpty()) return {};

    return accountData;
}



