#include "syst.h"
#include <QDir>
#include <QStorageInfo>

#ifdef __linux__
	const char * g_defaultMountPoint = "/mount/client";
#elif _WIN32
	const char * g_defaultMountPoint = "M:";
#endif

//Syst::Syst(QObject *parent) : QObject(parent)
//{
//}

void Syst::initMountPoint(const QString & mountPoint)
{
#ifdef __linux__
	QDir dir(mountPoint);
	if (! dir.exists()) {
		dir.mkpath(".");
	}
#else
	Q_UNUSED(mountPoint)
#endif
}

QString Syst::mountCmd(const QString & networkFolder, const QString & domain, const QString & login, const QString & password, const QString & mountPoint)
{
	QString ret, dmnPrm, lgnPrm, pwdPrm, mntDir;
	QString netDir = QDir::toNativeSeparators(networkFolder);
#ifdef __linux__
	ret = "mount -t cifs -o vers=2.0,%1%2%3uid=1000,gid=1000 %4 %5";
	dmnPrm = (domain.isEmpty()) ? "" : QString("domain=%1,").arg(domain);
	lgnPrm = (login.isEmpty()) ? "" : QString("username=%1,").arg(login);
	pwdPrm = (password.isEmpty()) ? "" : QString("password=%1,").arg(password);
	mntDir = QDir::toNativeSeparators(mountPoint);
	ret = ret.arg(dmnPrm, lgnPrm, pwdPrm, netDir, mntDir);
#elif _WIN32
	ret = "net use %4 %3%2%1 /PERSISTENT:NO";
	dmnPrm = (domain.isEmpty()) ? "" : QString("%1\\").arg(domain);
	lgnPrm = (login.isEmpty()) ? "" : QString(" /USER:%1%2").arg(dmnPrm, login);
	pwdPrm = (password.isEmpty()) ? "" : QString(" %1").arg(password);
	// in Windows mount point is only a drive letter
	mntDir = QString(mountPoint.left(1).toUpper()).append(":");
	ret = ret.arg(lgnPrm, pwdPrm, netDir, mntDir);
#endif
	return ret;
}

QString Syst::umountCmd(const QString & mountPoint)
{
	QString ret;
#ifdef __linux__
	ret = QString("umount %1").arg(QDir::toNativeSeparators(mountPoint));
#elif _WIN32
	QString mntDir = QString(mountPoint.left(1).toUpper()).append(":");
	QDir dir(mntDir + "/");
	if (dir.exists()) {
		ret = QString("net use %1 /DELETE").arg(mntDir);
	}
#endif

	return ret;
}

bool Syst::isMounted(const QString & mountPoint)
{
	bool ret = false;
#ifdef __linux__
	if (! mountPoint.isEmpty()) {
		QDir			dir(mountPoint);
		QStorageInfo	storage(mountPoint);
		ret = (dir.absolutePath() == storage.rootPath());
//		TRACE_DEBUG << "dir =" << dir.absolutePath() << "; stor =" << storage.rootPath() << "; ret =" << ret;
	}
#elif _WIN32
	QDir dir(mountPoint);
	ret = dir.exists();
#endif

	return ret;
}
