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


bool Authentication::user_exists(const QString& email) {
    QJsonArray users = read_json();

    for(const QJsonValue &userData : std::as_const(users)) {

        if(!userData.isObject()) {
            continue;
        }
        // convert QJsonValue into Object
        QJsonObject user = userData.toObject();

        // check if email exists and check if email matches
        if(user.contains("email") && user["email"].toString() == email) {
            return true;
        }

        qDebug() << user["email"] << '\n';
    }

    return false;
}

bool Authentication::create_new_user() {
    return true;
}

bool Authentication::authenticate_user() {
    return true;
}

