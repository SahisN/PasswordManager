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
    ui->stackedWidget->setCurrentIndex(1);

    connect(loginPage, &LoginPage::switch_to_create_account, this, &PasswordManager::go_to_create_account_page);
    connect(createAccountPage, &CreateAccount::switch_to_login, this, &PasswordManager::go_to_login_page);
}

PasswordManager::~PasswordManager()
{
    delete ui;
}

void PasswordManager::go_to_create_account_page()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void PasswordManager::go_to_login_page() {
    ui->stackedWidget->setCurrentIndex(0);
}
