#include "passwordgenerator.h"
#include <ctime>
#include <QString>
#include <QChar>

PasswordGenerator::PasswordGenerator(int passwordLength,  bool includeUpperCaseAlpha, bool includeNumbers, bool includeSymbols)
    : passwordLength(passwordLength),
    includeUpperCaseAlpha(includeUpperCaseAlpha),
    includeNumericCharacter(includeNumbers),
    includeSymbols(includeSymbols)
{

}

QString PasswordGenerator::generate_password() {
    srand(time(0));
    const QString characterPool = generate_character_pool();
    const int poolSize = characterPool.size();

    QString password;
    QChar prevChar;
    int count = 0;

    while (count < passwordLength)
    {
        // randomly picks a character from character pool
        int randomIndex = rand() % poolSize;
        QChar currentChar = characterPool[randomIndex];

        // prevents repeating same character in sequence
        if (!prevChar.isNull() && prevChar == currentChar)
        {
            continue;
        }

        // updates prevChar && adds character to password string
        prevChar = currentChar;
        password += currentChar;
        count++;
    }

    return password;
}

QString PasswordGenerator::generate_character_pool() {
    QString characterPool = "abcdefghijklmnopqrstuvwxyz";
    const QString upperCaseCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const QString numericCharacters = "0123456789";
    const QString symbolCharacters = "!@#$%^&*_-";

    if (includeUpperCaseAlpha)
    {
        characterPool += upperCaseCharacters;
    }

    if (includeNumericCharacter)
    {
        characterPool += numericCharacters;
    }

    if (includeSymbols)
    {
        characterPool += symbolCharacters;
    }

    return characterPool;
}

