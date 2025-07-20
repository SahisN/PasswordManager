#include "userdatahandler.h"
#include "platformaccount.h"
#include "extern/qaesencryption.h"
#include <QJsonObject>
#include <QCryptographicHash>

UserDataHandler::UserDataHandler(const QString &filePath, const QString &vaultKey, const QString &salt)
    : PasswordManagerIO(filePath),
    vaultKey(vaultKey),
    salt(salt),
    platformNameKey("platformName"),
    emailNameKey("email"),
    passwordNameKey("password"),
    categoryNameKey("category"),
    aesEncryption(QAESEncryption::AES_256, QAESEncryption::CBC)
{
    encryptedData = fetch_account_data();
    accountData = load_account_list(encryptedData);
    filteredData = {};
}

// encrypt few strings
QString UserDataHandler::encryptPlainText(const QString &plainText) {
    QByteArray hashKey = QCryptographicHash::hash(vaultKey.toLocal8Bit(), QCryptographicHash::Sha256);
    QByteArray hashIV = QCryptographicHash::hash(salt.toLocal8Bit(), QCryptographicHash::Md5);

    QByteArray encryptedText = aesEncryption.encode(plainText.toLocal8Bit(), hashKey, hashIV);

    return QString(encryptedText.toBase64());
}

// decode list of strings
QString UserDataHandler::decryptText(const QString &encryptedText) {
    QByteArray hashKey = QCryptographicHash::hash(vaultKey.toLocal8Bit(), QCryptographicHash::Sha256);
    QByteArray hashIV = QCryptographicHash::hash(salt.toLocal8Bit(), QCryptographicHash::Md5);

    QByteArray decodeText = aesEncryption.decode(QByteArray::fromBase64(encryptedText.toUtf8()), hashKey, hashIV);

    return QString::fromUtf8(aesEncryption.removePadding(decodeText));
}

QList<PlatformAccount> UserDataHandler::load_account_list(const QJsonArray &encryptedData) {
    QList<PlatformAccount> platformAccountList;
    // if accountJson is not empty, convert into QList<PlatformAccount>
    for(const QJsonValue &account : encryptedData) {
        if(!account.isObject()) continue;

        const QJsonObject accountObject = account.toObject();
        PlatformAccount platform;

        platform.platformName = accountObject[platformNameKey].toString();
        platform.email = decryptText(accountObject[emailNameKey].toString());
        platform.password = decryptText(accountObject[passwordNameKey].toString());
        platform.category = accountObject[categoryNameKey].toString();

        platformAccountList.append(platform);
    }

    return platformAccountList;

}

bool UserDataHandler::sync_account_data(const QString &platformName, const QString &platformEmail, const QString &platformPassword, const QString &platformCategory)
{
    // create a object representing the new account data
    QJsonObject newAccount;
    newAccount[platformNameKey] = platformName;
    newAccount[emailNameKey] = encryptPlainText(platformEmail);
    newAccount[passwordNameKey] = encryptPlainText(platformPassword);
    newAccount[categoryNameKey] = platformCategory;

    // add the object to existing QJsonArray
    encryptedData.append(newAccount);

    // write the data
    const bool isSaved = write_json(encryptedData);

    // update the QList if successful
    if(isSaved) {
        const PlatformAccount newPlatformAccount = {platformName, platformEmail, platformPassword, platformCategory};
        accountData.append(newPlatformAccount);

        // if user adds an account while they are in the matching category filter
        // then also add it to filterData list
        if(activeCategory == platformCategory) {
            filteredData.append(newPlatformAccount);
        }
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

void UserDataHandler::filter_by_category(const QString &targetCategory) {
    // clear filtered data
    filteredData.clear();

    // populate filteredData with data that has matching category
    for(int index = 0; index < accountData.size(); index++) {
        if(accountData[index].category == targetCategory) {
            filteredData.append(accountData[index]);
        }
    }
}



