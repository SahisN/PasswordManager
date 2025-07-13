#include "passwordmanager.h"
#include "ui_passwordmanager.h"
#include "loginpage.h"
#include "createaccount.h"

PasswordManager::PasswordManager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PasswordManager)
{
    ui->setupUi(this);

    // application pages
    LoginPage* loginPage = new LoginPage(this);
    CreateAccount* createAccountPage = new CreateAccount(this);

    // setting index to pages
    ui->stackedWidget->insertWidget(0, loginPage);
    ui->stackedWidget->insertWidget(1, createAccountPage);


    // starting page index
    ui->stackedWidget->setCurrentIndex(0);


    connect(loginPage, &LoginPage::switchToCreateAccount, this, &PasswordManager::showCreatedAccountPage);
}

PasswordManager::~PasswordManager()
{
    delete ui;
}

void PasswordManager::showCreatedAccountPage()
{
    ui->stackedWidget->setCurrentIndex(1);
}
