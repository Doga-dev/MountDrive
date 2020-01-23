#include "network_connection_parameters.h"
#include "tools.h"


NetworkConnectionParameters::NetworkConnectionParameters(QObject *parent) : AbstractConfigFile(parent)
  , m_ip()
  , m_port(0)
  , m_login()
  , m_password()
{
	TRACE_CLASS_CONSTRUCTOR;
	QObject::connect(this, & NetworkConnectionParameters::ipChanged			, this, & AbstractConfigFile::configChanged);
	QObject::connect(this, & NetworkConnectionParameters::portChanged		, this, & AbstractConfigFile::configChanged);
	QObject::connect(this, & NetworkConnectionParameters::loginChanged		, this, & AbstractConfigFile::configChanged);
	QObject::connect(this, & NetworkConnectionParameters::passwordChanged	, this, & AbstractConfigFile::configChanged);
}

NetworkConnectionParameters::NetworkConnectionParameters(const QString & ip, int port, const QString & login, const QString & password, QObject *parent) : AbstractConfigFile(parent)
  , m_ip(ip)
  , m_port(0)
  , m_login(login)
  , m_password(password)
{
	TRACE_CLASS_CONSTRUCTOR;
	if ((0 < port) && (port < 65536)) {
		m_port = quint16(port);
	}
}

NetworkConnectionParameters::~NetworkConnectionParameters()
{
	TRACE_CLASS_DESTRUCTOR;
}

bool NetworkConnectionParameters::init(QDomElement & element, bool status, const QString & id)
{
	bool ret = false;
	if (checkMarkupAndSetId(element, c_markupTag, id)) {
		setIp(element.attribute(c_ipTag));
		setPort(element.attribute(c_portTag, "0").toInt(& ret));
		setLogin(element.attribute(c_loginTag));
		QString pwd;
//		if (crypto()) {
//			pwd = crypto()->uncrypt(element.attribute(c_pwdTag));
//		} else {
			pwd = element.attribute(c_pwdTag);
//		}
		setPassword(pwd);
		if (! ret) {
			TRACE_DEBUG << "Error to treat markup" << element.tagName();
		}
	} else {
		// do not change the status if the element is not managed
		ret = true;
	}
	return ret && status;
}

QDomElement NetworkConnectionParameters::save(QDomDocument & doc)
{
	QDomElement element = doc.createElement(c_markupTag);
	setIdToElement(element);
	updateOrCreateAttibute(element, c_ipTag, m_ip);
	updateOrCreateAttibute(element, c_portTag, convIntToString(m_port));
	if (! m_login.isEmpty()) {
		updateOrCreateAttibute(element, c_loginTag, m_login);
	}
	if (! m_password.isEmpty()) {
		QString pwd;
		if (crypto()) {
			pwd = crypto()->crypt(m_password);
		} else {
			pwd = m_password;
		}
		updateOrCreateAttibute(element, c_pwdTag, pwd);
	}
	return element;
}

QString NetworkConnectionParameters::ip() const
{
	return m_ip;
}
void NetworkConnectionParameters::setIp(const QString & ip)
{
	if (m_ip != ip) {
		m_ip = ip;
		emit ipChanged(m_ip);
		TRACE_DEBUG << "new IP =" << m_ip;
	}
}

quint16 NetworkConnectionParameters::port() const
{
	return m_port;
}
void NetworkConnectionParameters::setPort(const quint16 & port)
{
	if (m_port != port) {
		m_port = port;
		emit portChanged(m_port);
	}
}
void NetworkConnectionParameters::setPort(const int & port)
{
	if ((0 < port) && (port < 65536) && (m_port != port)) {
		m_port = quint16(port);
		emit portChanged(m_port);
	}
}

QString NetworkConnectionParameters::login() const
{
	return m_login;
}
void NetworkConnectionParameters::setLogin(const QString & login)
{
	if (m_login != login) {
		m_login = login;
		emit loginChanged(m_login);
	}
}

QString NetworkConnectionParameters::password() const
{
	return m_password;
}
void NetworkConnectionParameters::setPassword(const QString & password)
{
	if (m_password != password) {
		m_password = password;
		emit passwordChanged(m_password);
	}
}

inline QDebug operator<<(QDebug dbg, const NetworkConnectionParameters & cls)
{
	dbg.nospace() << "NetworkConnectionParameters(" << cls.ip() << ":" << cls.port() << ", " << cls.login() << ", " << cls.password() << ")";
	return dbg.maybeSpace();
}

inline QDebug operator<<(QDebug dbg, NetworkConnectionParameters *cls)
{
	dbg.nospace() << *cls;
	return dbg.maybeSpace();
}

