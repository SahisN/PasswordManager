#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H
#include <QString>

class PasswordGenerator
{
public:
    PasswordGenerator(int passwordLength,  bool includeUpperCaseAlpha, bool includeNumbers, bool includeSymbols);
    QString generate_password();

private:
    int passwordLength;
    bool includeUpperCaseAlpha;
    bool includeNumericCharacter;
    bool includeSymbols;

    QString generate_character_pool();
};


#endif // PASSWORDGENERATOR_H
