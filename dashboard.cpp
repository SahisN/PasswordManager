#include "dashboard.h"
#include "ui_dashboard.h"

Dashboard::Dashboard(QWidget *parent)
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
            border: 1px solid #0078D7; /* blue border on hover */
        }

        QListWidget::item:selected {
            border: 1px solid #005a9e;
            background: transparent;
        }

        )");

    // QIcon icon = QApplication::style()->standardIcon(QStyle::SP_DriveNetIcon);
    // QListWidgetItem* item = new QListWidgetItem(icon, "Github\njohndoe@gmail.com");
    // ui->listWidget->addItem(item);
    //  connect(ui->btn_zero, SIGNAL(released()), this, SLOT(digit_btn_released()));
    connect(ui->VaultButton, SIGNAL(clicked()), this, SLOT(switch_to_valut_page()));
    connect(ui->passwordGeneratorButton, SIGNAL(clicked()), this, SLOT(switch_to_password_generator_page()));
    connect(ui->SettingsButton, SIGNAL(clicked()), this, SLOT(switch_to_settings_page()));
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



