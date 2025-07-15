#include "loginpage.h"
#include "ui_loginpage.h"

LoginPage::LoginPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginPage)
{
    ui->setupUi(this);

    connect(ui->createAccountButton, &QPushButton::clicked, this, &LoginPage::switch_to_create_account);
    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(login()));
}

LoginPage::~LoginPage()
{
    delete ui;
}

void LoginPage::login() {
    qDebug() << "Login";
}


