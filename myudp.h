

#ifndef MYUDP_H
#define MYUDP_H

#include <QUdpSocket>

class MyUDP : public QUdpSocket
{
    Q_OBJECT

  public:
    explicit MyUDP(QObject *parent = nullptr);
    bool bindPort(QHostAddress addr, qint16 port);
    void unbindPort();

  signals:
    void newMessage(const QString &from, const QString &message);

  public slots:
    void readyRead();
    void sendMessage(QHostAddress sender, quint16 senderPort, QString string);

  private:
    QUdpSocket *socket;
};

#endif // MYUDP_H
