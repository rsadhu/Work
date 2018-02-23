#include "ChatServerPriv.h"
#include<qdebug.h>
#include<QString>
#include<qjsonvalue.h>
#include<qjsonobject.h>
#include<QJsonDocument>




ChatServerPriv::ChatServerPriv()
{	
	if (listen(QHostAddress::Any, 2704))
	{
		qDebug() << "System Health Server Listening..";
	}
	else
	{
		qDebug() << "System Health Server Couldn't start";
	}
}


ChatServerPriv::~ChatServerPriv()
{
}


void ChatServerPriv::incomingConnection(qintptr  socketDescriptor)
{
	ChatClientConnection * newConnection = new ChatClientConnection(socketDescriptor);
	connect(newConnection, SIGNAL(finished()), newConnection, SLOT(deleteLater()));
	newConnection->start();
}

ChatClientConnection::ChatClientConnection(int sdesc):m_SocketDescriptor(sdesc)
{

}




void ChatClientConnection::run()
{
	m_Socket = new QTcpSocket();
	if (m_Socket->setSocketDescriptor(m_SocketDescriptor))
	{
		connect(m_Socket, &QTcpSocket::readyRead, [=]()
		{
			auto data = m_Socket->readAll();	
			QJsonDocument jsD;
			jsD = QJsonDocument::fromJson(data);
			QJsonObject jsonVal = jsD.object();

			if (jsonVal["key"].toString().compare("Login") == 0)
			{			
				auto username = jsonVal["username"].toString();
				auto password = jsonVal["password"].toString();
				qDebug() << " username :: " << username;
				qDebug() << " password :: " << password;			
			}
			else
			{				
				auto n = jsonVal["name"];
				qDebug() << " name:: " << jsonVal["name"].toString();
				qDebug() << " age:: " << jsonVal["age"].toInt();
				qDebug() << " address:: " << jsonVal["address"].toString();		

			}
			
			m_Socket->write(QByteArray("socketId:: ")+QByteArray(QString::number(m_SocketDescriptor).toStdString().c_str()) + "  " + m_Socket->readAll());
			m_Socket->flush();
			m_Socket->waitForBytesWritten(300);
		});

		connect(m_Socket, &QTcpSocket::disconnected, [=]()
		{
			m_Socket->deleteLater();
			exit(0);
		});
	}
	exec();

}