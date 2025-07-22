#ifndef DASHBOARD_H
#define DASHBOARD_H
#include "utility/userdatahandler.h"
#include "utility/passwordgenerator.h"
#include <QWidget>


namespace Ui {
class Dashboard;
}

class Dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent,
                       const QString &vaultKey,
                       const QString &fileName,
                       const QString &salt,
                       const int passwordLength,
                       const bool includeUpperCase,
                       const bool includeNumbers,
                       const bool includeSymbols
                    );
    ~Dashboard();

private slots:
    void switch_to_valut_page();
    void switch_to_password_generator_page();
    void switch_to_settings_page();
    void switch_to_account_creation();
    void switch_to_account_detail();
    void load_list_view(const QList<PlatformAccount> accountData);
    void add_new_account();
    void filter_by_category(const QString &category);
    void reset_filter();
    void uncheck_all_filter_buttons();

private:
    Ui::Dashboard *ui;
    UserDataHandler* userDataHandler = nullptr;
    PasswordGenerator* passwordGenerator = nullptr;
};

#endif // DASHBOARD_H
