#ifndef USERAUTHDATA_H
#define USERAUTHDATA_H
#include <QString>
struct UserAuthData {
    QString masterKey;
    QString filePath;
    QString salt;
    int passwordLength;
    bool includeUpperCase;
    bool includeNumbers;
    bool includeSymbols;
};

#endif // USERAUTHDATA_H
