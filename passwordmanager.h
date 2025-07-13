#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class PasswordManager;
}
QT_END_NAMESPACE

class PasswordManager : public QMainWindow
{
    Q_OBJECT

public:
    PasswordManager(QWidget *parent = nullptr);
    ~PasswordManager();

private slots:
    void showCreatedAccountPage();

private:
    Ui::PasswordManager *ui;
};
#endif // PASSWORDMANAGER_H
