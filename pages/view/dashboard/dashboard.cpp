#include "dashboard.h"
#include "ui_dashboard.h"
#include "../passwordGenerator/passwordgeneratorpage.h"
#include "../settings/settingspage.h"
#include "utility/userdatahandler.h"
#include <QJsonArray>
#include <QStringList>
#include <QJsonObject>
#include <QDebug>

Dashboard::Dashboard(QWidget *parent,
                     const QString &vaultKey,
                     const QString &fileName,
                     const QString &salt,
                     const int passwordLength,
                     const bool includeUpperCase,
                     const bool includeNumbers,
                     const bool includeSymbols)
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

        passwordGenerator = new PasswordGenerator(passwordLength, includeUpperCase, includeNumbers, includeSymbols);
        userDataHandler = new UserDataHandler("users/" + fileName + ".json", vaultKey, salt);

        // sub pages for dashboard
        PasswordGeneratorPage* passwordGeneratorPage = new PasswordGeneratorPage(this, passwordGenerator, fileName);
        SettingsPage* settingPage = new SettingsPage(this);

        ui->dashboardPages->insertWidget(1, passwordGeneratorPage);
        ui->dashboardPages->insertWidget(2, settingPage);

        // temp
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
            uncheck_all_filter_buttons();
            ui->developmentCategoryBtn->setChecked(true);

        });
        connect(ui->gamingCategoryBtn, &QPushButton::clicked, this, [=]() {
            filter_by_category("Gaming");
            uncheck_all_filter_buttons();
            ui->gamingCategoryBtn->setChecked(true);
        });
        connect(ui->socialCategoryBtn, &QPushButton::clicked, this, [=]() {
            filter_by_category("Social");
            uncheck_all_filter_buttons();
            ui->socialCategoryBtn->setChecked(true);
        });
        connect(ui->EmailCategoryBtn, &QPushButton::clicked, this, [=]() {
            filter_by_category("Email");
            uncheck_all_filter_buttons();
            ui->EmailCategoryBtn->setChecked(true);
        });
        connect(ui->otherCategoryBtn, &QPushButton::clicked, this, [=]() {
            filter_by_category("Other");
            uncheck_all_filter_buttons();
            ui->otherCategoryBtn->setChecked(true);
        });

        connect(ui->allCategoryBtn, &QPushButton::clicked, this, &Dashboard::reset_filter);

        // account edit & delete operation
        connect(ui->editAccountDetails, &QPushButton::clicked, this, &Dashboard::go_to_edit_page);
        connect(ui->saveEditBtn, &QPushButton::clicked, this, &Dashboard::edit_account_detail);
        connect(ui->cancelEditBtn, &QPushButton::clicked, this, [=]() {
            ui->accountPanel->setCurrentIndex(1);
        });
        connect(ui->deleteAccountBtn, &QPushButton::clicked, this, &Dashboard::handle_deletion);
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::switch_to_valut_page() {
    ui->dashboardPages->setCurrentIndex(0);
    ui->VaultButton->setChecked(true);
    ui->passwordGeneratorButton->setChecked(false);
    ui->SettingsButton->setChecked(false);
}

void Dashboard::switch_to_password_generator_page() {
    ui->dashboardPages->setCurrentIndex(1);
    ui->VaultButton->setChecked(false);
    ui->passwordGeneratorButton->setChecked(true);
    ui->SettingsButton->setChecked(false);
}

void Dashboard::switch_to_settings_page() {
    ui->dashboardPages->setCurrentIndex(2);
    ui->SettingsButton->setChecked(true);
    ui->passwordGeneratorButton->setChecked(false);
    ui->VaultButton->setChecked(false);
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
    // button visuals update
    uncheck_all_filter_buttons();
    ui->allCategoryBtn->setChecked(true);

    // reset activeCategory to All
    userDataHandler->activeCategory = "All";
    ui->accountPanel->setCurrentIndex(0);

    // reload the list to show all accounts
    load_list_view(userDataHandler->accountData);

}

// sets all category buttons checked to false
void Dashboard::uncheck_all_filter_buttons() {
    ui->allCategoryBtn->setChecked(false);
    ui->developmentCategoryBtn->setChecked(false);
    ui->gamingCategoryBtn->setChecked(false);
    ui->EmailCategoryBtn->setChecked(false);
    ui->otherCategoryBtn->setChecked(false);
    ui->socialCategoryBtn->setChecked(false);
}

void Dashboard::go_to_edit_page() {
    const QString currentPlatformName = ui->platformNameText->text();
    const QString currentEmail = ui->platformEmailText->text();
    const QString currentPassword = ui->platformPasswordText->text();
    const QString currentCategory = ui->platformCategoryText->text();
    const int currentCategoryIndex = ui->editCategoryCombo->findText(currentCategory);

    // switch to edit page
    ui->accountPanel->setCurrentIndex(3);

    // set default input
    ui->editPlatformName->setText(currentPlatformName);
    ui->editEmailInput->setText(currentEmail);
    ui->editPasswordInput->setText(currentPassword);
    ui->editCategoryCombo->setCurrentIndex(currentCategoryIndex);
}

void Dashboard::update_list_view() {
    // update the list view
    if(userDataHandler->activeCategory == "All") {
        load_list_view(userDataHandler->accountData);
    }

    else {
        load_list_view(userDataHandler->filteredData);
    }

    // switch to account detail page
    ui->accountPanel->setCurrentIndex(0);
}

void Dashboard::edit_account_detail() {
    const QString editPlatformName = ui->editPlatformName->text();
    const QString editEmail = ui->editEmailInput->text();
    const QString editPassword = ui->editPasswordInput->text();
    const QString editCategory = ui->editCategoryCombo->currentText();

    int itemIndex;
    if(userDataHandler->activeCategory == "All") {
        itemIndex = userDataHandler->accountData[ui->listWidget->currentRow()].index;
    }

    else {
        itemIndex = userDataHandler->filteredData[ui->listWidget->currentRow()].index;
    }

    qDebug() << itemIndex;

    // edit account data list
    userDataHandler->editAccountDetails(editPlatformName, editEmail, editPassword, editCategory, itemIndex);

    // update list view
    update_list_view();
}

void Dashboard::handle_deletion() {
    // get the index for account data
    int itemIndex;

    if(userDataHandler->activeCategory == "All") {
        itemIndex = userDataHandler->accountData[ui->listWidget->currentRow()].index;
    }

    else {
        itemIndex = userDataHandler->filteredData[ui->listWidget->currentRow()].index;
    }

    // delete the account detail from user data
    userDataHandler->deleteAccountDetails(itemIndex);

    // update the list view
    update_list_view();
}

