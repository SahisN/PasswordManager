#include "createaccount.h"
#include "ui_createaccount.h"

CreateAccount::CreateAccount(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CreateAccount)
{
    ui->setupUi(this);
}

CreateAccount::~CreateAccount()
{
    delete ui;
}
