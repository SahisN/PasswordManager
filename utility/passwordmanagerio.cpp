#include "passwordmanagerio.h"
#include <QString>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>
#include <QDir>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QStandardPaths>
#include <QMessageBox>
#include <QDebug>


PasswordManagerIO::PasswordManagerIO(const QString &filePath)
{
    // QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
    basePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/PasswordManagerData/" + filePath;

    qDebug() << this->basePath;
}

void PasswordManagerIO::ensure_directory_existance() {
    // filters file name from directory. "test/user1/user.json" -> test/user1
    const QFileInfo filePathInfo{basePath};

    qDebug() << filePathInfo.path() << "\n";

    QDir dir;
    // if directory doesn't exist, create directory
    if(!dir.exists(filePathInfo.path())) {

        // create parent directory & sub-directories
        if(dir.mkpath(filePathInfo.path())) {
            QMessageBox::information(nullptr, "Directory created", "new directory was created!");
        }

        // notify user if dir creation failed
        else {
           QMessageBox::information(nullptr, "Unable to create directory", "Failed to create directory for app data");

        }
    }
}

QString PasswordManagerIO::secure_hash(const QString& plainString) {
    // convert the string to utf-8 byte array
    QByteArray utfByteArray = plainString.toUtf8();

    // hash the array using Sha256
    QByteArray hashedArray = QCryptographicHash::hash(utfByteArray, QCryptographicHash::Sha256);

    // convert the array into hex array then convert the hex array to string
    return QString(hashedArray.toHex());
}

QJsonArray PasswordManagerIO::read_json() {
    QFile file(basePath);
    QJsonArray data;

    // checks whether file exists or not.
    if(!file.open(QIODevice::ReadOnly)) {

        // returns empty data if file doesn't exist
        return data;
    }

    // Storing the file data in ByteArray & closing the file
    QByteArray fileData = file.readAll();
    file.close();

    // Converts raw JSON data to QJSONDocument
    QJsonDocument doc = QJsonDocument::fromJson(fileData);

    // Checks the document is contained in an array json
    if(doc.isArray()) {
        // extract the data from array
        data = doc.array();
    }

    else {
        QMessageBox::information(nullptr, "Unable to read", "File doesn't exist or unreadable");
    }


    return data;
}


bool PasswordManagerIO::write_json(const QJsonArray& data) {
    // ensure directory existance prior to writing
    ensure_directory_existance();

    QFile file(basePath);

    // checks whether the file exist
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }

    // Convert the QJsonArray data to QJsonDocument & close the file
    QJsonDocument doc(data);
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();

    return true;
}
