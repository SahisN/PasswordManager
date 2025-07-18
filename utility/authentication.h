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
    QString authenticate_user(const QString& email, const QString& password);
    bool create_new_user(const QString& email, const QString& password);
    QString generate_file_path(const QString& email);

private:
    QJsonObject find_user(const QString& email);
    QString generate_vault_key(const QString& hashed_email, const QString& hashed_password);
    QString generate_random_salt();
};

#endif // AUTHENTICATION_H
