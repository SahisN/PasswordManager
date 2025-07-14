#ifndef PASSWORDGENERATORPAGE_H
#define PASSWORDGENERATORPAGE_H

#include <QWidget>

namespace Ui {
class PasswordGeneratorPage;
}

class PasswordGeneratorPage : public QWidget
{
    Q_OBJECT

public:
    explicit PasswordGeneratorPage(QWidget *parent = nullptr);
    ~PasswordGeneratorPage();

private:
    Ui::PasswordGeneratorPage *ui;
};

#endif // PASSWORDGENERATORPAGE_H
