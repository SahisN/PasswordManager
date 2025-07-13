#ifndef CREATEACCOUNT_H
#define CREATEACCOUNT_H

#include <QWidget>

namespace Ui {
class CreateAccount;
}

class CreateAccount : public QWidget
{
    Q_OBJECT

public:
    explicit CreateAccount(QWidget *parent = nullptr);
    ~CreateAccount();

private:
    Ui::CreateAccount *ui;
};

#endif // CREATEACCOUNT_H
