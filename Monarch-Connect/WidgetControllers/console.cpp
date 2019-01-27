#include "console.h"

Console::Console(QPlainTextEdit *textEdit, QObject *parent):
    QObject(parent), _textEdit(textEdit)
{
    _textEdit->setReadOnly(true);
}

void Console::changeOutput(QString text){
    _textEdit->setPlainText(text);
    //_textEdit->appendPlainText("\n");
}
