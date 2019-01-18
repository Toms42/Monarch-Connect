#ifndef SOCKETVIEW_H
#define SOCKETVIEW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QFormLayout>

class SocketView : public QWidget
{
    Q_OBJECT
private:
    QPushButton *_confirm;
    QLineEdit *_host;
    QLineEdit *_port;
    QLineEdit *_status;
    QGroupBox *_horizontalGroupBox;
public:
    explicit SocketView(QWidget *parent = nullptr);
    QString getHost(){
        return _host->text();
    }
    QString getPort(){
        return _port->text();
    }
signals:
    void pressed();

public slots:
    void setStatus(QString status);
};

#endif // SOCKETVIEW_H
