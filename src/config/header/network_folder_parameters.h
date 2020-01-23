#ifndef NETWORKCONNECTIONPARAMETERS_H
#define NETWORKCONNECTIONPARAMETERS_H

#include "abstract_config_file.h"
#include <QtDebug>

class NetworkConnectionParameters : public AbstractConfigFile
{
	Q_OBJECT
public:
	Q_PROPERTY(QString ip READ ip WRITE setIp NOTIFY ipChanged)
	Q_PROPERTY(quint16 port READ port WRITE setPort NOTIFY portChanged)
	Q_PROPERTY(QString login READ login WRITE setLogin NOTIFY loginChanged)
	Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)

	explicit NetworkConnectionParameters(QObject * parent = nullptr);
	NetworkConnectionParameters(const QString & ip, int port, const QString & login = "", const QString & password = "", QObject * parent = nullptr);
	~NetworkConnectionParameters();

	bool init(QDomElement & element, bool status = false, const QString & id = QString());
	QDomElement save(QDomDocument & doc);

	QString ip() const;
	void setIp(const QString & ip);

	quint16 port() const;
	void setPort(const quint16 & port);
	void setPort(const int & port);

	QString login() const;
	void setLogin(const QString & login);

	QString password() const;
	void setPassword(const QString & password);

signals:
	void ipChanged(const QString & value);
	void portChanged(const quint16 & value);
	void loginChanged(const QString & value);
	void passwordChanged(const QString & value);

public slots:

private:
	QString		m_ip;
	quint16		m_port;
	QString		m_login;
	QString		m_password;

	const char * c_markupTag	= "networkConnection";
	const char * c_ipTag		= "ip";
	const char * c_portTag		= "port";
	const char * c_loginTag		= "login";
	const char * c_pwdTag		= "pwd";
};

//Q_DECLARE_METATYPE(NetworkConnectionParameters)

QDebug operator<<(QDebug dbg, const NetworkConnectionParameters & cls);
QDebug operator<<(QDebug dbg, NetworkConnectionParameters * cls);

#endif // NETWORKCONNECTIONPARAMETERS_H
