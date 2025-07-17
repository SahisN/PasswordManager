#include "dashboard.h"
#include "ui_dashboard.h"
#include "../passwordGenerator/passwordgeneratorpage.h"
#include "../settings/settingspage.h"
#include "utility/platformaccount.h"
#include <QStringList>
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

        ui->dashboardPages->insertWidget(1, passwordGeneratorPage);
        ui->dashboardPages->insertWidget(2, settingPage);

        // QIcon icon = QApplication::style()->standardIcon(QStyle::SP_DriveNetIcon);
        // QListWidgetItem* item = new QListWidgetItem(icon, "Github\njohndoe@gmail.com");
        // ui->listWidget->addItem(item);

        // QListWidgetItem* item = new QListWidgetItem("Custom Text");
        // item->setToolTip("This is a tooltip");
        // ui->listWidget->addItem(item);
        qDebug() << vaultKey << "\n";

        QList<PlatformAccount> accountData = { {"Google", "test@gmail.com", "test1234"} };
        qDebug() << accountData[0].platformName;


        connect(ui->VaultButton, &QPushButton::clicked, this, &Dashboard::switch_to_valut_page);
        connect(ui->passwordGeneratorButton, &QPushButton::clicked, this, &Dashboard::switch_to_password_generator_page);
        connect(ui->SettingsButton, &QPushButton::clicked, this, &Dashboard::switch_to_settings_page);
        connect(ui->addAccountButton, &QPushButton::clicked, this, &Dashboard::switch_to_account_creation);
        connect(ui->listWidget, &QListWidget::itemClicked, this, &Dashboard::switch_to_account_detail);
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

