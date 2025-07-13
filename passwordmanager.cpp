#include "passwordmanager.h"
#include "ui_passwordmanager.h"
#include "loginpage.h"
#include "createaccount.h"
#include "dashboard.h"

PasswordManager::PasswordManager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PasswordManager)
{
    ui->setupUi(this);

    // application pages
    LoginPage* loginPage = new LoginPage(this);
    CreateAccount* createAccountPage = new CreateAccount(this);
    Dashboard* dashboardPage = new Dashboard(this);

    // setting index to pages
    ui->stackedWidget->insertWidget(0, loginPage);
    ui->stackedWidget->insertWidget(1, createAccountPage);
    ui->stackedWidget->insertWidget(2, dashboardPage);


    // starting page index
    ui->stackedWidget->setCurrentIndex(2);


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
