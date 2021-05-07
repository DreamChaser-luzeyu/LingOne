#ifndef TEXTPROCESS_H
#define TEXTPROCESS_H

#include <QObject>
#include <QTextCodec>

class TextProcess : public QObject
{
    Q_OBJECT
public:
    explicit TextProcess(QObject *parent = nullptr);
    static QString qByteArrayToQString(QByteArray);

signals:

};

#endif // TEXTPROCESS_H
