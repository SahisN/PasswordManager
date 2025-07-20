#include "dashboard.h"
#include "ui_dashboard.h"
#include "../passwordGenerator/passwordgeneratorpage.h"
#include "../settings/settingspage.h"
#include "utility/userdatahandler.h"
#include <QJsonArray>
#include <QStringList>
#include <QJsonObject>
#include <QDebug>

Dashboard::Dashboard(QWidget *parent, const QString &vaultKey, const QString &fileName, const QString &salt)
    : QWidget(parent)
    , ui(new Ui::Dashboard)
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
        userDataHandler = new UserDataHandler("PasswordManagerData/users/" + fileName + ".json", vaultKey, salt);

        ui->dashboardPages->insertWidget(1, passwordGeneratorPage);
        ui->dashboardPages->insertWidget(2, settingPage);

        // QIcon icon = QApplication::style()->standardIcon(QStyle::SP_DriveNetIcon);
        // QListWidgetItem* item = new QListWidgetItem(icon, "Github\njohndoe@gmail.com");
        // ui->listWidget->addItem(item);

        qDebug() << vaultKey << "\n";
        qDebug() << userDataHandler->accountData.size();
        qDebug() << userDataHandler->encryptedData.size();
        load_list_view(userDataHandler->accountData);

        // navigation
        connect(ui->passwordGeneratorButton, &QPushButton::clicked, this, &Dashboard::switch_to_password_generator_page);
        connect(ui->SettingsButton, &QPushButton::clicked, this, &Dashboard::switch_to_settings_page);
        connect(ui->addAccountButton, &QPushButton::clicked, this, &Dashboard::switch_to_account_creation);
        connect(ui->VaultButton, &QPushButton::clicked, this, &Dashboard::switch_to_valut_page);

        // list widget detection
        connect(ui->listWidget, &QListWidget::itemClicked, this, &Dashboard::switch_to_account_detail);

        // new accout submission
        connect(ui->addNewAccountBtn, &QPushButton::clicked, this, &Dashboard::add_new_account);

        // category buttons
        connect(ui->developmentCategoryBtn, &QPushButton::clicked, this, [=]() {
            filter_by_category("Development");
        });
        connect(ui->gamingCategoryBtn, &QPushButton::clicked, this, [=]() {
            filter_by_category("Gaming");
        });
        connect(ui->socialCategoryBtn, &QPushButton::clicked, this, [=]() {
            filter_by_category("Social");
        });
        connect(ui->FianceCategoryBtn, &QPushButton::clicked, this, [=]() {
            filter_by_category("Fiance");
        });
        connect(ui->otherCategoryBtn, &QPushButton::clicked, this, [=]() {
            filter_by_category("Other");
        });

        connect(ui->allCategoryBtn, &QPushButton::clicked, this, &Dashboard::reset_filter);
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

    // get the current item index from listWidget
    const int index = ui->listWidget->currentRow();

    // switches between filtered category data or all account data
    // depending on category selection
    PlatformAccount currentAccount;
    if(userDataHandler->activeCategory == "All") {
        currentAccount = userDataHandler->accountData[index];
    }

    else {
        currentAccount = userDataHandler->filteredData[index];
    }

    // display the account data that matches the item index
    ui->platformNameText->setText(currentAccount.platformName);
    ui->platformEmailText->setText(currentAccount.email);
    ui->platformPasswordText->setText(currentAccount.password);
    ui->platformCategoryText->setText(currentAccount.category);

    qDebug() << userDataHandler->activeCategory;
}

void Dashboard::load_list_view(const QList<PlatformAccount> accountData) {
    ui->listWidget->clear();
    for(int index = 0; index < accountData.size(); index++) {
        ui->listWidget->addItem(accountData[index].platformName);
    }
}

void Dashboard::add_new_account() {
    const QString platformName = ui->platformNameInput->text();
    const QString platformEmail = ui->platformEmailInput->text();
    const QString platformPassword = ui->platformPasswordInput->text();
    const QString platformCategory = ui->categorySelection->currentText();

    const bool isSuccessful = userDataHandler->sync_account_data(platformName, platformEmail, platformPassword, platformCategory);
    if(isSuccessful && (userDataHandler->activeCategory == "All" || userDataHandler->activeCategory == platformCategory)) {
        const QString data = userDataHandler->accountData.last().platformName;
        ui->listWidget->addItem(data);
    }

    // reset input fields
    ui->platformEmailInput->clear();
    ui->platformNameInput->clear();
    ui->platformPasswordInput->clear();
}

void Dashboard::filter_by_category(const QString &category) {
    ui->accountPanel->setCurrentIndex(0);

    // update active category to the category user selected
    userDataHandler->activeCategory = category;

    // filter accounts by category
    userDataHandler->filter_by_category(category);

    // reload the list with the updated filter
    load_list_view(userDataHandler->filteredData);
}

void Dashboard::reset_filter() {
    // reset activeCategory to All
    userDataHandler->activeCategory = "All";
    ui->accountPanel->setCurrentIndex(0);

    // reload the list to show all accounts
    load_list_view(userDataHandler->accountData);

}


