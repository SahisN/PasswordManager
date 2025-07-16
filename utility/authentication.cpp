#include "authentication.h"
#include "passwordmanagerio.h"
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QJsonValue>

Authentication::Authentication(const QString& filePath)
    : PasswordManagerIO(filePath)
{

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
    // gather existing data from target file
    QJsonArray users = read_json();

    // check if user exist in the file
    if(user_exist(email, users)) return false;

    // create a new user data
    QJsonObject newUser;
    newUser["email"] = email;
    newUser["password"] = password;

    // add the new user data to existing data
    users.append(newUser);

    // update the target file with new users data
    return write_json(users);
}

bool Authentication::authenticate_user(const QString& email, const QString& password) {
    // find the user
    const QJsonObject user = find_user(email);

    // verify user data is not null
    if(user.isEmpty()) return false;


    // check if the password matches
    if(user.contains("password") && user["password"] == password) {
        return true;
    }

    return false;

}

