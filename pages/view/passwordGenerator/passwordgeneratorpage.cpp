#include "passwordgeneratorpage.h"
#include "ui_passwordgeneratorpage.h"
#include "utility/passwordmanagerio.h"
#include <QJsonArray>
#include <QJsonObject>

PasswordGeneratorPage::PasswordGeneratorPage(QWidget *parent, PasswordGenerator* passwordGenerator, const QString &vaultKey)
    : QWidget(parent)
    , ui(new Ui::PasswordGeneratorPage)
    , passwordGenerator(passwordGenerator)
    , vaultKey(vaultKey)
{
    ui->setupUi(this);

    // update password generator settings
    ui->passwordLengthSlider->setSliderPosition(passwordGenerator->get_password_length());
    ui->includeUpperCase->setChecked(passwordGenerator->get_include_upper_case());
    ui->includeNumbers->setChecked(passwordGenerator->get_include_number());
    ui->includeSymbols->setChecked(passwordGenerator->get_include_symbol());
    ui->passwordLengthDisplay->display(passwordGenerator->get_password_length());

    connect(ui->passwordLengthSlider, &QSlider::sliderMoved, this, &PasswordGeneratorPage::update_password_length_display);
    connect(ui->updatePasswordSettingBtn, &QPushButton::clicked, this, &PasswordGeneratorPage::update_password_settings);
    connect(ui->generatePasswordBtn, &QPushButton::clicked, this, &PasswordGeneratorPage::generate_password_button_pressed);
}

PasswordGeneratorPage::~PasswordGeneratorPage()
{
    delete ui;
}

void PasswordGeneratorPage::update_password_length_display(int password_length) {
    ui->passwordLengthDisplay->display(password_length);
}

void PasswordGeneratorPage::generate_password_button_pressed() {
    const int password_length = ui->passwordLengthSlider->value();
    const bool includeUpperCaseCharacter = ui->includeUpperCase->isChecked();
    const bool includeNumericCharacter = ui->includeNumbers->isChecked();
    const bool includeSymbols = ui->includeSymbols->isChecked();

    // update password generator settings
    passwordGenerator->set_password_length(password_length);
    passwordGenerator->set_include_upper_case(includeUpperCaseCharacter);
    passwordGenerator->set_include_number(includeNumericCharacter);
    passwordGenerator->set_include_symbol(includeSymbols);

    ui->displayPasswordGenerate->setText(passwordGenerator->generate_password());
}

void PasswordGeneratorPage::update_password_settings() {
    const int passwordLength = ui->passwordLengthSlider->value();
    const bool upperCaseIncluded = ui->includeUpperCase->isChecked();
    const bool numberIncluded = ui->includeNumbers->isChecked();
    const bool symbolIncluded = ui->includeSymbols->isChecked();
    bool edited = false;

    // get user preference data
    PasswordManagerIO passwordManagerIO{"user.json"};
    QJsonArray users = passwordManagerIO.read_json();

    for(int index = 0; index < users.size(); index++) {
        if(!users[index].isObject()) {
            continue;
        }

        QJsonObject user = users[index].toObject();

        if(user.contains("email") && user["email"].toString() == vaultKey) {
            qDebug() << user;
            // update user preference
            user["passwordLength"] = passwordLength;
            user["includeUpperCase"] = upperCaseIncluded;
            user["includeNumbers"] = numberIncluded;
            user["includeSymbols"] = symbolIncluded;

            // update the users data
            users[index] = user;
            edited = true;

            //stop the loop
            break;
        }

    }

    if(edited) {
        passwordManagerIO.write_json(users);
    }
}
