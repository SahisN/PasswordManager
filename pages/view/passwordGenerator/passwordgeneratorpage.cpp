#include "passwordgeneratorpage.h"
#include "ui_passwordgeneratorpage.h"
#include "utility/passwordgenerator.h"

PasswordGeneratorPage::PasswordGeneratorPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PasswordGeneratorPage)
{
    ui->setupUi(this);

    connect(ui->passwordLengthSelector, SIGNAL(valueChanged(int)), this, SLOT(update_password_length_display(int)));
    connect(ui->passwordGenerateButton, SIGNAL(clicked()), this, SLOT(generate_password_button_pressed()));
}

PasswordGeneratorPage::~PasswordGeneratorPage()
{
    delete ui;
}

void PasswordGeneratorPage::update_password_length_display(int password_length) {
    ui->passwordLengthDisplay->display(password_length);
}

void PasswordGeneratorPage::generate_password_button_pressed() {
    const int password_length = ui->passwordLengthSelector->value();
    const bool includeUpperCaseCharacter = ui->upperCaseCheckBox->isChecked();
    const bool includeNumericCharacter = ui->numberCheckBox->isChecked();
    const bool includeSymbols = ui->symbolCheckBox->isChecked();

    PasswordGenerator passwordGenerator{password_length, includeUpperCaseCharacter, includeNumericCharacter, includeSymbols};

    QString password = passwordGenerator.generate_password();

    ui->showPassword->setText(password);
}
