#ifndef LOGINPAGE_H
#define LOGINPAGE_H
#include <QWidget>
#include "utility/authentication.h"

namespace Ui {
class LoginPage;
}

class LoginPage : public QWidget
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr, Authentication *authPtr = nullptr);
    ~LoginPage();

signals:
    void switch_to_create_account();
    void switch_to_dashboard(const QString &vaultKey,
                             const QString &fileName,
                             const QString &salt,
                             const int passwordLength,
                             const bool includeUpperCase,
                             const bool includeNumbers,
                             const bool includeSymbols);

private slots:
    void handle_login();

private:
    Ui::LoginPage *ui;
    Authentication *authPtr;
};

#endif // LOGINPAGE_H
