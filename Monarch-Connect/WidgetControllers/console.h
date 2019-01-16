#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QPlainTextEdit>

class Console:public QObject{
    Q_OBJECT
private:
    QPlainTextEdit *_textEdit;
public:
    explicit Console(QPlainTextEdit *textEdit, QObject *parent = nullptr);
public slots:
    void changeOutput(QString text);
};

#endif // CONSOLE_H
