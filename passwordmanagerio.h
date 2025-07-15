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
};

#endif // PASSWORDMANAGERIO_H
