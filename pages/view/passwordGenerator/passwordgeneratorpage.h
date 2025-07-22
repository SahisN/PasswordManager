#ifndef PASSWORDGENERATORPAGE_H
#define PASSWORDGENERATORPAGE_H
#include "utility/passwordgenerator.h"
#include <QWidget>

namespace Ui {
class PasswordGeneratorPage;
}

class PasswordGeneratorPage : public QWidget
{
    Q_OBJECT

public:
    explicit PasswordGeneratorPage(QWidget *parent, PasswordGenerator* passwordGenerator, const QString &vaultKey);
    ~PasswordGeneratorPage();

private slots:
    void update_password_length_display(int password_length);
    void generate_password_button_pressed();
    void update_password_settings();

private:
    Ui::PasswordGeneratorPage *ui;
    PasswordGenerator* passwordGenerator;
    const QString &vaultKey;
};

#endif // PASSWORDGENERATORPAGE_H
