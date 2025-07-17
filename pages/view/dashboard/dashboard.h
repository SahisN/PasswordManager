#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>

namespace Ui {
class Dashboard;
}

class Dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent, const QString &email);
    ~Dashboard();

private slots:
    void switch_to_valut_page();
    void switch_to_password_generator_page();
    void switch_to_settings_page();
    void switch_to_account_creation();
    void switch_to_account_detail();

private:
    Ui::Dashboard *ui;
    const QString &email;
};

#endif // DASHBOARD_H
