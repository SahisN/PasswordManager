#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H
#include "passwordmanagerio.h"
#include <QString>
#include <QJsonObject>


class Authentication : public PasswordManagerIO
{
public:
    Authentication(const QString& filePath);
    bool user_exist(const QString& email, const QJsonArray& users);
    bool authenticate_user(const QString& email, const QString& password);
    bool create_new_user(const QString& email, const QString& password);

private:
    QJsonObject find_user(const QString& email);
    QString secure_hash(const QString& unhashed_string);
};

#endif // AUTHENTICATION_H
