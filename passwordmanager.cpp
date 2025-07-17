#include "passwordmanager.h"
#include "ui_passwordmanager.h"
#include "pages/login/loginpage.h"
#include "pages/signup/createaccount.h"
#include "pages/view/dashboard/dashboard.h"
#include "utility/authentication.h"

PasswordManager::PasswordManager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PasswordManager), dashboardPagePtr(nullptr)
{
    ui->setupUi(this);

    Authentication *authPtr = new Authentication("PasswordManagerData/user.json");

    // application pages
    LoginPage* loginPage = new LoginPage(this, authPtr);
    CreateAccount* createAccountPage = new CreateAccount(this, authPtr);

    // setting index to pages
    ui->stackedWidget->insertWidget(0, loginPage);
    ui->stackedWidget->insertWidget(1, createAccountPage);

    // starting page index
    ui->stackedWidget->setCurrentIndex(0);

    connect(loginPage, &LoginPage::switch_to_create_account, this, &PasswordManager::go_to_create_account_page);
    connect(loginPage, &LoginPage::switch_to_dashboard, this, &PasswordManager::go_to_dashboard);
    connect(createAccountPage, &CreateAccount::switch_to_login, this, &PasswordManager::go_to_login_page);
}

PasswordManager::~PasswordManager()
{
    delete ui;
}

void PasswordManager::go_to_login_page()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void PasswordManager::go_to_create_account_page()
{
    ui->stackedWidget->setCurrentIndex(1);
}

// only called when login is successful
void PasswordManager::go_to_dashboard(const QString &email)
{
    // only called if dashboardPagePtr is not null
    if(dashboardPagePtr) {

        // debug purpose [temp]
        qDebug() << "dashboard already exists!\n";

        // remove dashboardPagePtr from stackedWidget
        ui->stackedWidget->setCurrentIndex(0);
        ui->stackedWidget->removeWidget(dashboardPagePtr);

        // destory dashboardPagePtr from heap
        delete dashboardPagePtr;

        // set dashboardPagePtr to nullprt
        dashboardPagePtr = nullptr;
    }

    // create dashboardPagePtr when login is successful
    // add it in stackWidget and switch to that page
    dashboardPagePtr = new Dashboard(this, email);
    ui->stackedWidget->addWidget(dashboardPagePtr);
    ui->stackedWidget->setCurrentIndex(2);
}
