#include "authentication.h"
#include "userauthdata.h"
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QJsonValue>
#include <QByteArray>
#include <QCryptographicHash>
#include <QString>
#include <QRandomGenerator>

Authentication::Authentication(const QString &filePath)
    : PasswordManagerIO(filePath)
{

}

// generates a random salt for each user
QString Authentication::generate_random_salt() {
    const QString possibleChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    // get a random salt length between 16-32
    const int length =  QRandomGenerator::global()->bounded(16, 33);

    QString randomSalt;
    for(int count = 0; count < length; count++) {
        int index = QRandomGenerator::global()->bounded(possibleChars.length());
        randomSalt.append(possibleChars.at(index));
    }

    return randomSalt;
}

// adds hashed_email & hashed_password together and creates a new hash as vault key
QString Authentication::generate_vault_key(const QString& hashed_email, const QString& hashed_password) {
    return secure_hash(hashed_email + hashed_password);
}

QJsonObject Authentication::find_user(const QString& email) {

    QJsonArray users = read_json();

    for(const QJsonValue &userData : std::as_const(users)) {

        if(!userData.isObject()) {
            continue;
        }
        // convert QJsonValue into Object
        QJsonObject user = userData.toObject();
        qDebug() << userData << '\n';

        // check if email exists and check if email matches
        if(user.contains("email") && user["email"].toString() == email) {
            qDebug() << user["email"] << '\n';
            return user;
        }
    }

    return {};
}

/**
 * @brief Authentication::user_exist
 * @param email
 * @param users
 * @return bool
 * @ Returns True if it can find user in the given QJsonArray
 * @ Return False if it can't find user in the given QJsonArray
 */
bool Authentication::user_exist(const QString& email, const QJsonArray& users) {
    for(const QJsonValue &userData : std::as_const(users)) {

        if(!userData.isObject()) {
            continue;
        }
        // convert QJsonValue into Object
        QJsonObject user = userData.toObject();
        qDebug() << userData << '\n';

        // check if email exists and check if email matches
        if(user.contains("email") && user["email"].toString() == email) {
            return true;
        }
    }

    return false;
}

bool Authentication::create_new_user(const QString& email, const QString& password) {
    const QString randomSalt = generate_random_salt();
    const QString hashed_email = secure_hash(email);
    const QString hashed_password = secure_hash(password + randomSalt);

    // gather existing data from target file
    QJsonArray users = read_json();

    // check if user exist in the file
    if(user_exist(hashed_email, users)) return false;

    // create a new hashed user data
    QJsonObject newUser;
    newUser["email"] = hashed_email;
    newUser["password"] = hashed_password;
    newUser["salt"] = randomSalt;
    newUser["passwordLength"] = 8;
    newUser["includeUpperCase"] = true;
    newUser["includeNumbers"] = true;
    newUser["includeSymbols"] = true;

    // add the new user data to existing data
    users.append(newUser);

    // update the target file with new users data
    return write_json(users);
}

UserAuthData Authentication::authenticate_user(const QString& email, const QString& password) {
    // hash the email
    const QString hashed_email = secure_hash(email);

    // find the user by searching the hash email signature
    const QJsonObject user = find_user(hashed_email);

    // verify user data is not null, exit the function is data is null
    if(user.isEmpty()) return {};

    // get salt
    const QString salt = user["salt"].toString();
    qDebug() << salt;

    // if user exist, hash the password
    const QString hashed_password = secure_hash(password + salt);

    // compare the hash password signature with another hash password that stored in file
    if(user.contains("password") && user["password"] == hashed_password) {
        return{password, hashed_email, salt,
                user["passwordLength"].toInt(),
                user["includeUpperCase"].toBool(),
                user["includeNumbers"].toBool(),
                user["includeSymbols"].toBool()};
    }

    return {};
}

