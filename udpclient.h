#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>
#include <QUdpSocket>

class UDPClient : public QObject
{
    Q_OBJECT
public:
    explicit UDPClient(QObject *parent = 0);
    void WriteData( const QString& );
public slots:
    void readReady();

signals:
    void sendColor(QString color);

private:
    QUdpSocket clientSocket;

};

#endif // UDPCLIENT_H
