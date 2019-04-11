

#include "myudp.h"

MyUDP::MyUDP(QObject *parent) : QUdpSocket(parent)
{
    socket = new QUdpSocket();
}

bool MyUDP::bindPort(QHostAddress addr, qint16 port)
{
    socket->abort();
    bool isBinded = socket->bind(addr, port);
    if (isBinded)
    {
        connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    }
    return isBinded;
}

void MyUDP::sendMessage(QHostAddress sender, quint16 senderPort, QString string)
{
    QByteArray Data;
    Data.append(string);

    // Sends the datagram datagram
    // to the host address and at port.
    socket->writeDatagram(Data, sender, senderPort);
}

void MyUDP::readyRead()
{
    // when data comes in
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;


    socket->readDatagram(buffer.data(), buffer.size(),
                         &sender, &senderPort);

    emit newMessage(sender.toString(), buffer);
}

void MyUDP::unbindPort()
{
    disconnect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    socket->close();
}
