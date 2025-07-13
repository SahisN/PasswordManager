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
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();

private slots:
    void switch_to_valut_page();
    void switch_to_password_generator_page();
    void switch_to_settings_page();

private:
    Ui::Dashboard *ui;
};

#endif // DASHBOARD_H
