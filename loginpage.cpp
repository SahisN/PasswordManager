#include "loginpage.h"
#include "ui_loginpage.h"

LoginPage::LoginPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginPage)
{
    ui->setupUi(this);

    connect(ui->button1, &QPushButton::clicked, this, &LoginPage::switchToCreateAccount);
}

LoginPage::~LoginPage()
{
    delete ui;
}


