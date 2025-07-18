#include "dashboard.h"
#include "ui_dashboard.h"
#include "../passwordGenerator/passwordgeneratorpage.h"
#include "../settings/settingspage.h"
#include "utility/userdatahandler.h"
#include <QJsonArray>
#include <QStringList>
#include <QJsonObject>
#include <QDebug>

Dashboard::Dashboard(QWidget *parent, const QString &vaultKey)
    : QWidget(parent)
    , ui(new Ui::Dashboard)
    , vaultKey(vaultKey)
{
    ui->setupUi(this);


    ui->listWidget->setStyleSheet(R"(
        QListWidget {
            spacing: 12px; /* spacing between items */
            outline: 0;
        }

        QListWidget::item {
            padding: 10px;
            font-size: 16px;
            font-weight: bold;
            color: white;
            margin: 8px;
        }

        QListWidget::item:hover {
            border: 1px solid #0078D7;
        }

        QListWidget::item:selected {
            border: 1px solid #005a9e;
            background: transparent;
        }

        )");

        PasswordGeneratorPage* passwordGeneratorPage = new PasswordGeneratorPage(this);
        SettingsPage* settingPage = new SettingsPage(this);
        userDataHandler = new UserDataHandler("PasswordManagerData/users/pass.json", vaultKey);

        ui->dashboardPages->insertWidget(1, passwordGeneratorPage);
        ui->dashboardPages->insertWidget(2, settingPage);

        // QIcon icon = QApplication::style()->standardIcon(QStyle::SP_DriveNetIcon);
        // QListWidgetItem* item = new QListWidgetItem(icon, "Github\njohndoe@gmail.com");
        // ui->listWidget->addItem(item);

        qDebug() << vaultKey << "\n";
        qDebug() << userDataHandler->accountData.size();
        qDebug() << userDataHandler->encryptedData.size();
        load_list_view();

        // navigation
        connect(ui->passwordGeneratorButton, &QPushButton::clicked, this, &Dashboard::switch_to_password_generator_page);
        connect(ui->SettingsButton, &QPushButton::clicked, this, &Dashboard::switch_to_settings_page);
        connect(ui->addAccountButton, &QPushButton::clicked, this, &Dashboard::switch_to_account_creation);
        connect(ui->VaultButton, &QPushButton::clicked, this, &Dashboard::switch_to_valut_page);

        // list widget detection
        connect(ui->listWidget, &QListWidget::itemClicked, this, &Dashboard::switch_to_account_detail);

        // new accout submission
        connect(ui->addNewAccountBtn, &QPushButton::clicked, this, &Dashboard::add_new_account);
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::switch_to_valut_page() {
    ui->dashboardPages->setCurrentIndex(0);
}

void Dashboard::switch_to_password_generator_page() {
    ui->dashboardPages->setCurrentIndex(1);
}

void Dashboard::switch_to_settings_page() {
    ui->dashboardPages->setCurrentIndex(2);
}

void Dashboard::switch_to_account_creation() {
    ui->accountPanel->setCurrentIndex(2);
}

void Dashboard::switch_to_account_detail() {
    ui->accountPanel->setCurrentIndex(1);
    qDebug() << ui->listWidget->currentRow();
}

void Dashboard::load_list_view() {
    QList<PlatformAccount> &accountData =  userDataHandler->accountData;
    for(int index = 0; index < accountData.size(); index++) {
        ui->listWidget->addItem(accountData[index].platformName);
    }
}

void Dashboard::add_new_account() {
    const QString platformName = ui->platformNameInput->text();
    const QString platformEmail = ui->platformEmailInput->text();
    const QString platformPassword = ui->platformPasswordInput->text();


    const bool isSuccessful = userDataHandler->sync_account_data(platformName, platformEmail, platformPassword);
    if(isSuccessful) {
        const QString data = userDataHandler->accountData.last().platformName;
        ui->listWidget->addItem(data);
    }

    // reset input fields
    ui->platformEmailInput->clear();
    ui->platformNameInput->clear();
    ui->platformPasswordInput->clear();
}


