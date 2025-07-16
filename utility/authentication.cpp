#include "authentication.h"
#include "passwordmanagerio.h"
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QJsonValue>
#include <QByteArray>
#include <QCryptographicHash>
#include <QString>

Authentication::Authentication(const QString& filePath)
    : PasswordManagerIO(filePath)
{

}


QString Authentication::secure_hash(const QString& unhashed_string) {
    // convert the string to utf-8 byte array
    QByteArray utfByteArray = unhashed_string.toUtf8();

    // hash the array using Sha256
    QByteArray hashedArray = QCryptographicHash::hash(utfByteArray, QCryptographicHash::Sha256);

    // convert the array into hex array then convert the hex array to string
    return QString(hashedArray.toHex());
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
    const QString hashed_email = secure_hash(email);
    const QString hashed_password = secure_hash(password);

    // gather existing data from target file
    QJsonArray users = read_json();

    // check if user exist in the file
    if(user_exist(hashed_email, users)) return false;

    // create a new hashed user data
    QJsonObject newUser;
    newUser["email"] = hashed_email;
    newUser["password"] = hashed_password;

    // add the new user data to existing data
    users.append(newUser);

    // update the target file with new users data
    return write_json(users);
}

bool Authentication::authenticate_user(const QString& email, const QString& password) {
    // hash the email
    const QString hashed_email = secure_hash(email);

    // find the user by searching the hash email signature
    const QJsonObject user = find_user(hashed_email);

    // verify user data is not null, exit the function is data is null
    if(user.isEmpty()) return false;

    // if user exist, hash the password
    const QString hashed_password = secure_hash(password);

    // compare the hash password signature with another hash password that stored in file
    if(user.contains("password") && user["password"] == hashed_password) {
        return true;
    }

    return false;

}

