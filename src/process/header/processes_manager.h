#ifndef PROCESSESMANAGER_H
#define PROCESSESMANAGER_H

#include <QObject>
#include "process_manager.h"

class ProcessesManager : public QObject
{
	Q_OBJECT
public:
	Q_PROPERTY(QString mountPoint READ mountPoint WRITE setMountPoint NOTIFY mountPointChanged)
	Q_PROPERTY(bool isMounted READ isMounted NOTIFY isMountedChanged)

	explicit ProcessesManager(const QString & mountPoint = QString(), QObject * parent = nullptr);
	~ProcessesManager();

	static void RegisterClasses();

	Q_INVOKABLE void startMountProcess(const QString & server, const QString & domain, const QString & login, const QString & password, const QString & networkFolder, const QString & mountPoint = QString());
	Q_INVOKABLE void startUmountProcess(const QString & mountPoint = QString());

	Q_INVOKABLE bool isMounted();
	Q_INVOKABLE void logMountedDriveInfo(const QString & mountPoint = QString());

	QString mountPoint() const;
	void setMountPoint(const QString & mountPoint);

signals:
	void mountPointChanged();
	void isMountedChanged();

public slots:
	void mountProcessReturn(QString output);
	void mountProcessEnded(int exitCode);
	void umountProcessReturn(QString output);
	void umountProcessEnded(int exitCode);

private:
	void setMounted(bool mounted);
	void clearMountProcess();
	void clearUmountProcess();

	QString			m_mountPoint;
	ProcessManager	* m_mountProcess;
	ProcessManager	* m_umountProcess;
	bool			m_mounted;
};

#endif // PROCESSESMANAGER_H
