#ifndef SYST_H
#define SYST_H

//#include <QObject>
#include <QString>

extern const char * g_defaultMountPoint;

class Syst /*: public QObject*/
{
//	Q_OBJECT
public:

	static void initMountPoint(const QString & mountPoint = g_defaultMountPoint);
	static QString mountCmd(const QString & networkFolder, const QString & domain, const QString & login, const QString & password, const QString & mountPoint = g_defaultMountPoint);
	static QString umountCmd(const QString & mountPoint = g_defaultMountPoint);
	static bool isMounted(const QString & mountPoint = g_defaultMountPoint);

//signals:

//public slots:

//private:
//	explicit Syst(QObject * parent = nullptr);
};

#endif // SYST_H
