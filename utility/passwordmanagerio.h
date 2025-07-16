#ifndef PASSWORDMANAGERIO_H
#define PASSWORDMANAGERIO_H
#include <QString>
#include <QJsonArray>

class PasswordManagerIO
{
public:
    PasswordManagerIO(QString filePath);
    QJsonArray read_json();
    bool write_json(const QJsonArray& data);

private:
    QString filePath;
    void ensure_directory_existance();
};

#endif // PASSWORDMANAGERIO_H
