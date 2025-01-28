#ifndef CRYPTER_H
#define CRYPTER_H

#include <QObject>
#include <QDebug>
#include <QChar>
static const QString kEncryptorString = QString("encryption key"); //here is key to crypt/decrypt QString;

class Crypter : public QObject
{
    Q_OBJECT
public:
    static QString cryptString(QString toCrypt)
    {
        QString resultString = "";
        for ( int i = 0; i < toCrypt.length(); i++)
        {
            resultString.append(QChar(toCrypt[i].unicode() ^ kEncryptorString[keyIndex(i)].unicode()));
        }
        return resultString;
    }
    static QString decryptString(QString toDecrypt)
    {
        QString resultString = "";
        for ( int i = 0; i < toDecrypt.length(); i++)
        {
            resultString.append(QChar(toDecrypt[i].unicode() ^ kEncryptorString[keyIndex(i)].unicode()));
        }
        return resultString;
    }
private:
    Crypter(QObject *parent = 0);
    static int keyIndex(int index)
    {
        int len = kEncryptorString.length();
        int multiple = index / len;
        if ( index >=  len ) {
            return index - (len * multiple);
        }
        return index;
    }
};

#endif // CRYPTER_H
