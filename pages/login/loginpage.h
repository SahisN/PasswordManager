#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>

namespace Ui {
class LoginPage;
}

class LoginPage : public QWidget
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);
    ~LoginPage();

signals:
    void switch_to_create_account();
    void switch_to_dashboard();

private slots:
    void handle_login();

private:
    Ui::LoginPage *ui;
};

#endif // LOGINPAGE_H
