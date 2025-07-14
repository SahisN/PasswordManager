#include "passwordgeneratorpage.h"
#include "ui_passwordgeneratorpage.h"

PasswordGeneratorPage::PasswordGeneratorPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PasswordGeneratorPage)
{
    ui->setupUi(this);
}

PasswordGeneratorPage::~PasswordGeneratorPage()
{
    delete ui;
}
