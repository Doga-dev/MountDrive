
#include "factory_default_config.h"
#include "processes_manager.h"

#include <QQmlEngine>
#include <QStorageInfo>
#include "syst.h"

ProcessesManager::ProcessesManager(const QString & mountPoint, QObject *parent) : QObject(parent)
  , m_mountPoint(mountPoint)
  , m_mountProcess(nullptr)
  , m_umountProcess(nullptr)
  , m_mounted(false)
{
	TRACE_CLASS_CONSTRUCTOR;
	if (m_mountPoint.isEmpty()) {
		setMountPoint(g_defaultMountPoint);
	}
	TRACE_DEBUG << m_mountPoint << (isMounted() ? "mounted" : "unmounted");
}

ProcessesManager::~ProcessesManager()
{
	clearMountProcess();
	clearUmountProcess();
	TRACE_CLASS_DESTRUCTOR;
}

void ProcessesManager::RegisterClasses()
{
	qmlRegisterType<ProcessesManager>(QML_LIBRARY_NAME, QML_LIBRARY_MAJ_VERSION, QML_LIBRARY_MIN_VERSION, "ProcessesManager");
}

void ProcessesManager::startMountProcess(const QString & server, const QString & domain, const QString & login, const QString & password, const QString & folder, const QString & mountPoint)
{
	if (! mountPoint.isEmpty()) {
		setMountPoint(mountPoint);
	}
	// Cas ou l'execution est en cours: interruption
	if (m_mountProcess && (m_mountProcess->isRunning())) {
		m_mountProcess->stopProcess();
		TRACE_DEBUG << "Termine" << "Execution interrompue";
		return;
	}
	clearMountProcess();
	if (! m_mountPoint.isEmpty()) {
		QString networkFolder = QString("//") + server + QString("/") + folder;
		m_mountProcess = new ProcessManager(this);
		QObject::connect(m_mountProcess, & ProcessManager::processReturn, this, & ProcessesManager::mountProcessReturn);
		QObject::connect(m_mountProcess, & ProcessManager::processEnded, this, & ProcessesManager::mountProcessEnded);
		m_mountProcess->runProcess(Syst::mountCmd(networkFolder, domain, login, password, m_mountPoint));
	}
}

void ProcessesManager::startUmountProcess(const QString & mountPoint)
{
	if (! mountPoint.isEmpty()) {
		setMountPoint(mountPoint);
	}
	// Cas ou l'execution est en cours: interruption
	if (m_umountProcess && (m_umountProcess->isRunning())) {
		m_umountProcess->stopProcess();
		TRACE_DEBUG << "Termine" << "Execution interrompue";
		return;
	}
	clearUmountProcess();
	if (! m_mountPoint.isEmpty()) {
		m_umountProcess = new ProcessManager(this);
		QObject::connect(m_umountProcess, & ProcessManager::processReturn, this, & ProcessesManager::mountProcessReturn);
		QObject::connect(m_umountProcess, & ProcessManager::processEnded, this, & ProcessesManager::mountProcessEnded);
		m_umountProcess->runProcess(Syst::umountCmd(m_mountPoint));
	}
}

bool ProcessesManager::isMounted()
{
	setMounted(Syst::isMounted(m_mountPoint));
	return m_mounted;
}

void ProcessesManager::logMountedDriveInfo(const QString & mountPoint)
{
	QStorageInfo storage(mountPoint);

	if (! mountPoint.isEmpty()) {
		setMountPoint(mountPoint);
	}
	TRACE_DEBUG << storage.rootPath() << ((storage.rootPath() == mountPoint) ? "mounted" : "unmounted");
	if (storage.isReadOnly())
		TRACE_DEBUG << "isReadOnly:" << storage.isReadOnly();

	TRACE_DEBUG << "name:" << storage.name();
	TRACE_DEBUG << "fileSystemType:" << storage.fileSystemType();
	TRACE_DEBUG << "size:" << storage.bytesTotal() / 1000 / 1000 << "MB";
	TRACE_DEBUG << "availableSize:" << storage.bytesAvailable() / 1000 / 1000 << "MB";
}

void ProcessesManager::mountProcessReturn(QString output)
{
	TRACE_FUNCTION_CALL << output;
}

void ProcessesManager::mountProcessEnded(int exitCode)
{
	TRACE_FUNCTION_CALL << exitCode << (isMounted() ? "mounted" : "unmounted");
	clearMountProcess();
}

void ProcessesManager::umountProcessReturn(QString output)
{
	TRACE_FUNCTION_CALL << output;
}

void ProcessesManager::umountProcessEnded(int exitCode)
{
	TRACE_FUNCTION_CALL << exitCode << (isMounted() ? "mounted" : "unmounted");
	clearUmountProcess();
}

void ProcessesManager::setMounted(bool mounted)
{
	if (m_mounted != mounted) {
		m_mounted = mounted;
		emit isMountedChanged();
	}
}

void ProcessesManager::clearMountProcess()
{
	if (m_mountProcess) {
		delete m_mountProcess;
		m_mountProcess = nullptr;
	}
}

void ProcessesManager::clearUmountProcess()
{
	if (m_umountProcess) {
		delete m_umountProcess;
		m_umountProcess = nullptr;
	}
}

QString ProcessesManager::mountPoint() const
{
	QString mntDir = QDir(m_mountPoint).absolutePath();
	if (mntDir.right(1) == "/") {
		return mntDir;
	} else {
		return mntDir + "/";
	}
}

void ProcessesManager::setMountPoint(const QString & mountPoint)
{
	if (m_mountPoint != mountPoint) {
		m_mountPoint = mountPoint;
		Syst::initMountPoint(m_mountPoint);
		emit mountPointChanged();
	}
}
