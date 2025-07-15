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

private slots:
    void update_password_length_display(int password_length);
    void generate_password_button_pressed();


private:
    Ui::PasswordGeneratorPage *ui;
};

#endif // PASSWORDGENERATORPAGE_H
