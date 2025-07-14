#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H
#include <QString>

class PasswordGenerator
{
public:
    PasswordGenerator(int passwordLength,  bool includeUpperCaseAlpha, bool includeNumbers, bool includeSymbols);
    QString generatePassword();

private:
    int passwordLength;
    bool includeUpperCaseAlpha;
    bool includeNumericCharacter;
    bool includeSymbols;

    QString generateCharacterPool();
};


#endif // PASSWORDGENERATOR_H
