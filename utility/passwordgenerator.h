#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H
#include <QString>

class PasswordGenerator
{
public:
    PasswordGenerator(int passwordLength,  bool includeUpperCaseAlpha, bool includeNumbers, bool includeSymbols);
    QString generate_password();

    // getters
    int get_password_length();
    bool get_include_upper_case();
    bool get_include_number();
    bool get_include_symbol();

    // setters
    void set_password_length(int length);
    void set_include_upper_case(bool includeUpperCase);
    void set_include_number(bool includeNumbers);
    void set_include_symbol(bool includeSymbol);


private:
    QString generate_character_pool();
    int passwordLength;
    bool includeUpperCaseAlpha;
    bool includeNumericCharacter;
    bool includeSymbols;
};


#endif // PASSWORDGENERATOR_H
