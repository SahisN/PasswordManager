#include "loginpage.h"
#include "ui_loginpage.h"
#include "qDebug"
#include "utility/authentication.h"
#include <QRegularExpression>
#include <QString>

LoginPage::LoginPage(QWidget *parent, Authentication *authPtr)
    : QWidget(parent)
    , ui(new Ui::LoginPage)
    , authPtr(authPtr)
{
    ui->setupUi(this);

    connect(ui->createAccountButton, &QPushButton::clicked, this, &LoginPage::switch_to_create_account);
    connect(ui->loginButton, &QPushButton::clicked, this, &LoginPage::handle_login);
}

LoginPage::~LoginPage()
{
    delete ui;
}


void LoginPage::handle_login() {
    const QString email = ui->emailInput->text();
    const QString password = ui->passwordInput->text();
    static const QRegularExpression emailRegex(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");

    // if it's invalid email, set error message
    if(!emailRegex.match(email).hasMatch()) {
        qDebug() << "invalid email!";
    }

    // if password is empty, set error message
    else if(password.isEmpty()) {
        qDebug() << "invalid password!";
    }

    // if password & email is valid then authenticate user
    else {
        const UserAuthData userAuthData = authPtr->authenticate_user(email, password);
        const QString fileName = authPtr->secure_hash(email);

        if(!userAuthData.filePath.isEmpty() && !userAuthData.masterKey.isEmpty() && !userAuthData.salt.isEmpty()) {
            emit LoginPage::switch_to_dashboard(userAuthData.masterKey,
                                                userAuthData.filePath,
                                                userAuthData.salt,
                                                userAuthData.passwordLength,
                                                userAuthData.includeUpperCase,
                                                userAuthData.includeNumbers,
                                                userAuthData.includeSymbols);
        }

        // if login isn't successful then notify user
        else {
            qDebug() << "Email or Password is incorrect!";
        }
    }
}

