#ifndef SOCKETMODEL_H
#define SOCKETMODEL_H

#include <QObject>
#include "QDebug"
#include "Models/monarchmodel.h"
#include <nodes/NodeDataModel>
#include "Common/project.h"
#include <QDataStream>
#include <QtNetwork>
#include <QTcpSocket>
#include <QPushButton>

class SocketModel : public MonarchModel
{
    Q_OBJECT
private:
    QTcpSocket *_socket;
    enum InPortTypes{
        STREAMPORTIN = 0,
        _NUMPORTSIN
    };

    enum OutPortTypes{
        STREAMPORTOUT = 0,
        _NUMPORTSOUT
     };
public:
    explicit SocketModel():MonarchModel(),_socket(new QTcpSocket(this)){
        connectToHost("172.20.10.2", 80);

    }

    ~SocketModel() override{
        disconnectFromHost();
    }

    QString caption() const override{
        return "TCP socket node";
    }

    QString name() const override{
        return "TCP socket node";
    }

    QWidget *embeddedWidget() override{
        return nullptr;
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
        writeData(data);
    }

    Payload getOutputData(int) override{
        return Payload();
    }

    //get arrays for input and output ports
    QVector<MonarchInputPort> getInputPortArray()  const override{
        QVector<MonarchInputPort> ports(_NUMPORTSIN);
        ports[STREAMPORTIN] = {PortType::STREAM, QString("input"), -1};
        return ports;
    }

    //get arrays for input and output ports
    QVector<MonarchOutputPort> getOutputPortArray()  const override{
        QVector<MonarchOutputPort> ports(_NUMPORTSOUT);
        ports[STREAMPORTOUT] = {PortType::STREAM, QString("output stream"), -1};
        return ports;
    }

    //returns whether the socket connected to host successfully
    bool connectToHost(QString host, quint16 port){
        _socket->connectToHost(host, port);
        return _socket->waitForConnected();
    }

    void disconnectFromHost(){
        if(_socket->state() != QAbstractSocket::ConnectedState) return;
        return _socket->disconnectFromHost();
    }

    //returns whether the data wrote successfully
    bool writeData(Payload payload){
        if(_socket->state() == QAbstractSocket::ConnectedState){
            _socket->write(payload.encode());
            return _socket->waitForBytesWritten();
        }
        else return false;
    }

    QByteArray readData(){
        QByteArray buffer = QByteArray();
        while(_socket->bytesAvailable() > 0){
            buffer.append(_socket->readAll());
        }
        return buffer;
    }

signals:

public slots:
};

#endif // SOCKETMODEL_H
