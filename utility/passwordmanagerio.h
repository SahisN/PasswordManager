#ifndef PASSWORDMANAGERIO_H
#define PASSWORDMANAGERIO_H
#include <QString>
#include <QJsonArray>

class PasswordManagerIO
{
public:
    PasswordManagerIO(const QString& filePath);
    QJsonArray read_json();
    bool write_json(const QJsonArray& data);
    QString secure_hash(const QString& plainString);

private:
    QString basePath;
    void ensure_directory_existance();
};

#endif // PASSWORDMANAGERIO_H
