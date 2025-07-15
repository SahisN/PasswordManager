#include "createaccount.h"
#include "ui_createaccount.h"
#include "authentication.h"
#include "QDebug";

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
    Authentication authentication{"PasswordManagerData/user.json"};
    bool exist = authentication.user_exists("yo@gmail.com");
    qDebug() << exist << '\n';
}


