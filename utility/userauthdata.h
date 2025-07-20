#ifndef USERAUTHDATA_H
#define USERAUTHDATA_H
#include <QString>
struct UserAuthData {
    QString masterKey;
    QString filePath;
    QString salt;
};

#endif // USERAUTHDATA_H
