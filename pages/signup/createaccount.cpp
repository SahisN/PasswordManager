#include "createaccount.h"
#include "ui_createaccount.h"
#include "utility/authentication.h"
#include <QRegularExpression>
#include "QDebug"

CreateAccount::CreateAccount(QWidget *parent, Authentication *authPtr)
    : QWidget(parent)
    , ui(new Ui::CreateAccount)
    , authPtr(authPtr)
{
    ui->setupUi(this);


    connect(ui->loginButton, &QPushButton::clicked, this, &CreateAccount::switch_to_login);
    connect(ui->submitButton, &QPushButton::clicked, this, &CreateAccount::create_user_account);

    connect(ui->emailInput, &QLineEdit::editingFinished, this, [this]() {
        ui->emailErrorText->clear();
        ui->emailErrorText->setMargin(3);
    });

    connect(ui->passwordInput, &QLineEdit::editingFinished, this, [this]() {
        ui->passwordErrorText->clear();
        ui->passwordErrorText->setMargin(3);
    });

    connect(ui->confirmPasswordInput, &QLineEdit::editingFinished, this, [this]() {
        ui->confirmPasswordErrorText->clear();
        ui->confirmPasswordErrorText->setMargin(3);
    });
}

CreateAccount::~CreateAccount()
{
    delete ui;
}

void CreateAccount::create_user_account() {
    const QString email = ui->emailInput->text();
    const QString password = ui->passwordInput->text();
    const QString confirmPassword = ui->confirmPasswordInput->text();
    const int requiredPasswordSize = 5;
    static const QRegularExpression emailRegex(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
    bool accountCreated = false;

    // vadiate input fields here
    if((emailRegex.match(email).hasMatch()) && password.size() >= requiredPasswordSize && password == confirmPassword) {
        // create user data here
        accountCreated = authPtr->create_new_user(ui->emailInput->text(), ui->passwordInput->text());
        qDebug() << accountCreated;

        // if account is created successfully, switch to login page
        if(accountCreated) {
            ui->emailInput->clear();
            ui->passwordInput->clear();
            ui->confirmPasswordInput->clear();

            emit CreateAccount::switch_to_login();
        }

        // else, notify user
        else {
            ui->emailErrorText->setText("Email Already Used");
        }
    }

    // update visuals to show user that form is incomplete or incorrect
    else {
        if(!emailRegex.match(email).hasMatch()) {
            ui->emailErrorText->setText("Invalid Email");
            ui->emailErrorText->setMargin(10);
        }

        if(password.size() < requiredPasswordSize) {
            ui->passwordErrorText->setText("password must be 5 characters or more");
            ui->passwordErrorText->setMargin(10);
        }

        else if(password != confirmPassword) {
            ui->confirmPasswordErrorText->setText("confirm password doesn't match password");
            ui->confirmPasswordErrorText->setMargin(10);
        }

    }

}


