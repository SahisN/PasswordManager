#include "createaccount.h"
#include "ui_createaccount.h"
#include "utility/authentication.h"
#include "QDebug"

CreateAccount::CreateAccount(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CreateAccount)
{
    ui->setupUi(this);

    connect(ui->loginButton, &QPushButton::clicked, this, &CreateAccount::switch_to_login);
    connect(ui->submitButton, SIGNAL(clicked()), this, SLOT(create_user_account()));
}

CreateAccount::~CreateAccount()
{
    delete ui;
}

void CreateAccount::create_user_account() {
    const QString email = ui->emailInput->text();
    const QString password = ui->passwordInput->text();
    const QString confirmPassword = ui->confirmPasswordInput->text();

    // vadiate input fields here
    if(!email.isEmpty() && !password.isEmpty() && password == confirmPassword) {
        // create user data here
        Authentication authentication{"PasswordManagerData/user.json"};
        bool exist = authentication.authenticate_user(ui->emailInput->text(), ui->passwordInput->text());
        qDebug() << exist;
    }

    else {

    }




}


