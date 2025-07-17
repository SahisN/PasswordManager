#ifndef CREATEACCOUNT_H
#define CREATEACCOUNT_H
#include <QWidget>
#include "utility/authentication.h"

namespace Ui {
class CreateAccount;
}

class CreateAccount : public QWidget
{
    Q_OBJECT

public:
    explicit CreateAccount(QWidget *parent = nullptr, Authentication *authPtr = nullptr);
    ~CreateAccount();

signals:
    void switch_to_login();

private slots:
    void create_user_account();

private:
    Ui::CreateAccount *ui;
    Authentication *authPtr;
};

#endif // CREATEACCOUNT_H
