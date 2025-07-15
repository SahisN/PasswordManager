#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H
#include "passwordmanagerio.h"
#include <QString>
#include <QJsonObject>


class Authentication : public PasswordManagerIO
{
public:
    Authentication(const QString& filePath);
    bool user_exists(const QString& email);
    bool authenticate_user(const QString& email, const QString& password);
    bool create_new_user(const QString& email, const QString& password);

private:
    QJsonObject find_user(const QString& email);
};

#endif // AUTHENTICATION_H
