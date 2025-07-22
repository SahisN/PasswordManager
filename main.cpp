#include "passwordmanager.h"
#include <QApplication>
#include <QStyleFactory>
#include <QIcon>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    PasswordManager w;
    w.setWindowIcon(QIcon(":/img/images/vault_logo.svg"));
    w.setIconSize(QSize(48, 48));

    w.show();
    return a.exec();
}
