

#include "mytcpclient.h"

MyTCPClient::MyTCPClient(QObject *parent) : QTcpSocket(parent)
{
    tcpSocket = new QTcpSocket();
}

void MyTCPClient::connectTo(QHostAddress addr, quint16 port)
{
    tcpSocket->connectToHost(addr, port);
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onStateChanged(QAbstractSocket::SocketState)));
}

void MyTCPClient::onConnected()
{
    disconnect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onStateChanged(QAbstractSocket::SocketState)));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(messageReady()));
    emit myClientConnected(tcpSocket->peerAddress().toString(), tcpSocket->peerPort());
}

void MyTCPClient::onStateChanged(QAbstractSocket::SocketState state)
{
    disconnect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onStateChanged(QAbstractSocket::SocketState)));
    switch (state)
    {
    case QAbstractSocket::UnconnectedState:
        emit connectionFailed();
        //qDebug()<<"connecting timeout";
        break;
    case QAbstractSocket::HostLookupState:
        //qDebug()<<"HostLookupState";
        break;
    case QAbstractSocket::ConnectingState:
        //qDebug()<<"ConnectingState";
        break;
    case QAbstractSocket::ConnectedState:
        //qDebug()<<"ConnectedState";
        break;
    case QAbstractSocket::BoundState:
        //qDebug()<<"BoundState";
        break;
    case QAbstractSocket::ListeningState:
        //qDebug()<<"ListeningState";
        break;
    case QAbstractSocket::ClosingState:
        //qDebug()<<"ClosingState";
        break;
    }
}

void MyTCPClient::onDisconnected()
{
    disconnect(tcpSocket, SIGNAL(disconnected()));
    disconnect(tcpSocket, SIGNAL(readyRead()));
    tcpSocket->close();
    emit myClientDisconnected();
}

void MyTCPClient::closeClient()
{
    tcpSocket->close();
}

void MyTCPClient::abortConnection()
{
    tcpSocket->abort();
}

void MyTCPClient::messageReady()
{
    array = tcpSocket->readAll();
    emit newMessage(tcpSocket->peerAddress().toString(), array);
}

void MyTCPClient::sendMessage(QString string)
{
    QByteArray Data;
    Data.append(string);
    if (tcpSocket->state() == QTcpSocket::ConnectedState)
    {
        tcpSocket->write(Data);
        tcpSocket->flush();
    }
}

void MyTCPClient::disconnectCurrentConnection()
{
    tcpSocket->disconnectFromHost();
}
