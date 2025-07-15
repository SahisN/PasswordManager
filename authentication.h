#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H
#include <QString>
#include "passwordmanagerio.h"

class Authentication : public PasswordManagerIO
{
public:
    Authentication(const QString& filePath);
    bool user_exists(const QString& email);
    bool authenticate_user();
    bool create_new_user();
};

#endif // AUTHENTICATION_H
