#include "udpclient.h"
#include <QDebug>


UDPClient::UDPClient(QObject *parent) :QObject(parent), clientSocket(this)
{
    qDebug()<<"I am your client";
    connect(&clientSocket,SIGNAL(readyRead()),this,SLOT(readReady()));
}

void UDPClient::WriteData(const QString& data)
{
    QByteArray clientData;
    clientData.append(data);

    clientSocket.writeDatagram(clientData, QHostAddress::LocalHost, 9999 );
}

void UDPClient::readReady()
{
    // got response from server, so clientSoclet port number can get.
    //qDebug()<< "Reacieved response from server through my port(Client port No):" << clientSocket.localPort();

    QByteArray buffer;
    buffer.resize(clientSocket.pendingDatagramSize());

    QHostAddress sender;
    quint16 port;
    clientSocket.readDatagram(buffer.data(),buffer.size(),&sender,&port);
    // To read server IP
//    qDebug()<< "Server IP Responded" << sender.toString();
//    qDebug()<< "Server Port Number" << port;
    QString message = QString::fromStdString(buffer.toStdString());
    if (message.startsWith("COLOR")) {
        QStringList list = message.split(' ');
        emit sendColor(list.at(1));
    }
    else if (message == QString("CONNECTED")) {
        emit sendConnectedState();
    }
    else {
        //parse turns
        QStringList list = message.split(' ');
        if (list.size() == 5)
            emit sendTurn(list.at(0), list.at(1)[0], list.at(2).toInt(), list.at(3)[0], list.at(4).toInt());
    }
}
