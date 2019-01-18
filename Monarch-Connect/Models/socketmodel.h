#ifndef SOCKETMODEL_H
#define SOCKETMODEL_H

#include <QObject>
#include "QDebug"
#include "Models/monarchmodel.h"
#include "Common/config.h"
#include <nodes/NodeDataModel>
#include "Common/project.h"
#include <QDataStream>
#include <QtNetwork>
#include <QTcpSocket>
#include <QPushButton>
#include <QLineEdit>

class Worker:public QObject{
    Q_OBJECT
private:
    QTcpSocket &_socket;
    Payload _data;
public:
    explicit Worker(QTcpSocket &socket):_socket(socket), _data(Payload()){
        _socket.connectToHost(HOST, PORT);
        qDebug() << "Connecting to " + QString(HOST);
        if(_socket.waitForConnected()){
            qDebug() << "Connected!";
        }else{
            qDebug() << "Failed to connect";
            qDebug() << _socket.errorString();
        }
        //read data when ready to read
        connect(&_socket, &QIODevice::readyRead, this, &Worker::readData);
    }
    ~Worker() override{
        if(_socket.state() != QAbstractSocket::ConnectedState) return;
        _socket.disconnectFromHost();
    }
signals:
    void dataArrived(QByteArray data);
public slots:
    void readData(){
        QByteArray buffer = QByteArray();
        while(_socket.bytesAvailable() > 0){
            qDebug() << "Reading in data from host";
            buffer.append(_socket.readAll());
        }
        emit(dataArrived(buffer));
    }
    void sendData(QByteArray data){
        if(_socket.state() == QAbstractSocket::ConnectedState &&
                data.length() < 256){
            _socket.write(data);
            qDebug() << "Waiting for payload to write";
            if(_socket.waitForBytesWritten()){
                qDebug() << "Bytes written!";
            }
            else{
                qDebug() << "Failed to write";
            }
        }
    }
};


class SocketModel:public MonarchModel
{
    Q_OBJECT
private:
    QTcpSocket *_socket;
    QPushButton *_button;
    enum InPortTypes{
        STREAMPORTIN = 0,
        _NUMPORTSIN
     };
    enum OutPortTypes{
        STREAMPORTOUT = 0,
        _NUMPORTSOUT
     };
    enum ConnectionStatus{
        CONNECTED = 0,
        DISCONNECTED
    };
    ConnectionStatus _status;

public:
    explicit SocketModel():MonarchModel(),_status(DISCONNECTED),
    _socket(nullptr), _button(new QPushButton("Disconnected")){
        setup();
        _socket = new QTcpSocket(this);
        connect(_socket, &QIODevice::readyRead, this, &SocketModel::readData);
        connect(_button, &QPushButton::pressed, this, &SocketModel::changeButton);
        connect(_socket, &QTcpSocket::connected, this, &SocketModel::connected);
        connect(_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
        this, &SocketModel::error);
        connect(_socket, &QTcpSocket::disconnected, this, &SocketModel::disconnected);
    }

    ~SocketModel() override{
    }

    void readData(){
        if(_status == DISCONNECTED) return;
        QByteArray buffer = QByteArray();
        while(_socket->bytesAvailable() > 0){
            qDebug() << "Reading in data from host";
            buffer.append(_socket->readAll());
        }
        sendOnStream(STREAMPORTOUT, Payload(buffer));
    }
    void sendData(Payload data){
        if(_status == DISCONNECTED) return;
        if(_socket->state() == QAbstractSocket::ConnectedState &&
                data.encode().length() < 256){
            _socket->write(data.encode());
            qDebug() << "Waiting for payload to write";
            if(_socket->waitForBytesWritten()){
                qDebug() << "Bytes written!";
            }
            else{
                qDebug() << "Failed to write";
            }
        }
    }

    QString caption() const override{
        return "TCP socket node";
    }

    QString name() const override{
        return "TCP socket node";
    }

    QWidget *embeddedWidget() override{
        return _button;
    }

    QWidget *configWidget() override{
        return nullptr;
    }

    ////WHAT TO INSERT HERE?????
    QJsonObject saveData() const override{
        QJsonObject data;
        data["test"] = "test data";
        return data;
    }

    void loadData(QJsonObject const& modelJson) const override{
        qDebug() << modelJson["test"].toString();
    }

    void inputDataReady(Payload data, int index) override{
        sendData(data.encode());
    }

    Payload getOutputData(int) override{
        return Payload();
    }

    //get arrays for input and output ports
    QVector<MonarchInputPort> getInputPortArray()  const override{
        QVector<MonarchInputPort> ports(_NUMPORTSIN);
        ports[STREAMPORTIN] = {PortType::STREAM, QString("input stream"), -1};
        return ports;
    }

    //get arrays for input and output ports
    QVector<MonarchOutputPort> getOutputPortArray()  const override{
        QVector<MonarchOutputPort> ports(_NUMPORTSOUT);
        ports[STREAMPORTOUT] = {PortType::STREAM, QString("output stream"), -1};
        return ports;
    }
public slots:
    void connected(){
        qDebug() << "Connected!";
        _button->setText("Connected");
        _status = CONNECTED;
    }
    void error(QAbstractSocket::SocketError socketError){
        qDebug() << "Error connecting";
    }
    void disconnected(){
        _button->setText("Disconnected");
        _status = DISCONNECTED;
    }
    void changeButton(){
        switch(_status){
        case CONNECTED:{
            qDebug() << "Pressed disconnect!";
            _socket->disconnectFromHost();
            break;
        }
        case DISCONNECTED:{
            QString host = HOST;
            quint16 port = PORT;
            qDebug() << "Pressed connect!";
            _socket->connectToHost(host, port);
            qDebug() << "Connecting to " + QString(HOST);
            break;
        }
        }
    }
signals:
};

#endif // SOCKETMODEL_H
