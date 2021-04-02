#ifndef STRFUNC_H
#define STRFUNC_H

#include <QObject>
#include <QString>

class StrFunc : public QObject
{
    Q_OBJECT
public:
    explicit StrFunc(QObject *parent = nullptr);

    static QStringList splitBySpace(QString);

signals:

};

#endif // STRFUNC_H
