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

bool Authentication::user_exists(const QString& email) {
    const QJsonObject userObject = find_user(email);

    if(userObject.isEmpty()) {
        return false;
    }

    return true;
}

bool Authentication::create_new_user(const QString& email, const QString& password) {
    // check if user already has account
    if(user_exists(email)) return false;

    // gather existing data from target file
    QJsonArray users = read_json();

    // create a new user data
    QJsonObject newUser;
    newUser["email"] = email;
    newUser["password"] = password;

    // add the new user data to existing data
    users.append(newUser);

    // update the target file with new users data
    const bool isSuccessful = write_json(users);

    return isSuccessful;
}

bool Authentication::authenticate_user(const QString& email, const QString& password) {
    // check if user exist
    if(!user_exists(email)) return false;

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

