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


    connect(ui->passwordLengthSlider, &QSlider::sliderMoved, this, &PasswordGeneratorPage::update_password_length_display);
    connect(ui->updatePasswordSettingBtn, &QPushButton::clicked, this, &PasswordGeneratorPage::update_password_settings);
    // connect(ui->passwordGenerateButton, SIGNAL(clicked()), this, SLOT(generate_password_button_pressed()));

}

PasswordGeneratorPage::~PasswordGeneratorPage()
{
    delete ui;
}

void PasswordGeneratorPage::update_password_length_display(int password_length) {
    ui->passwordLengthDisplay->display(password_length);
}

void PasswordGeneratorPage::generate_password_button_pressed() {
    // const int password_length = ui->passwordLengthSelector->value();
    // const bool includeUpperCaseCharacter = ui->upperCaseCheckBox->isChecked();
    // const bool includeNumericCharacter = ui->numberCheckBox->isChecked();
    // const bool includeSymbols = ui->symbolCheckBox->isChecked();

    // PasswordGenerator passwordGenerator{password_length, includeUpperCaseCharacter, includeNumericCharacter, includeSymbols};

    // QString password = passwordGenerator.generate_password();

    // ui->showPassword->setText(password);
}

void PasswordGeneratorPage::update_password_settings() {
    const int passwordLength = ui->passwordLengthSlider->value();
    const bool upperCaseIncluded = ui->includeUpperCase->isChecked();
    const bool numberIncluded = ui->includeNumbers->isChecked();
    const bool symbolIncluded = ui->includeSymbols->isChecked();

    // get user preference data
    PasswordManagerIO passwordManagerIO{"users.json"};
    QJsonArray users = passwordManagerIO.read_json();

    for(int index = 0; index < users.size(); index++) {
        if(!users[index].isObject()) {
            continue;
        }

        QJsonObject user = users[index].toObject();
        if(user.contains("email") && user["email"].toString() == vaultKey) {
            // update user preference
            user["passwordLength"] = passwordLength;
            user["includeUpperCase"] = upperCaseIncluded;
            user["includeNumbers"] = numberIncluded;
            user["includeSymbols"] = symbolIncluded;

            // update the users data
            users[index] = user;

            // stop the loop
            break;
        }

    }

    passwordManagerIO.write_json(users);
}
