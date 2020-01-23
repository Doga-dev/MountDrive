
#include "factory_default_config.h"
#include "process_manager.h"


ProcessManager::ProcessManager(QObject *parent) : QObject(parent)
  , m_process(nullptr)
{
	TRACE_CLASS_CONSTRUCTOR;
}

ProcessManager::~ProcessManager()
{
	clearProcess();
	TRACE_CLASS_DESTRUCTOR;
}

bool ProcessManager::isRunning() const
{
	return (m_process && (m_process->state() == QProcess::Running));
}

void ProcessManager::runProcess(QString command)
{
	if (command.isEmpty()) return;

	m_process = new QProcess(this);
	// A chaque fois que des donnees sortent en console, lireSortieProcess1() sera appele
	QObject::connect(m_process, & QProcess::readyReadStandardOutput, this, & ProcessManager::readProcessReturn);
	// Quand le processus sera fini, executerProcess2() sera appele
	QObject::connect(m_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, & ProcessManager::endProcess);

	// Demarrage de process1
	TRACE_DEBUG << command;
	m_process->start(command);
}

void ProcessManager::writeInProcess(QString input)
{
	if (m_process) {
		m_process->write(input.toLatin1());
	}
}

void ProcessManager::stopProcess()
{
	if (isRunning()) {
		m_process->kill();
	}
}

//void QProcess::finished(int exitCode, QProcess::ExitStatus exitStatus)
void ProcessManager::endProcess(int exitCode, QProcess::ExitStatus exitStatus)
{
	if (exitCode != 0) {
		if (exitStatus == QProcess::NormalExit) {
			TRACE_DEBUG << "Erreur" << "process ended normally with exit code" << exitCode;
		} else {
			TRACE_DEBUG << "Erreur" << "process crashed with exit code" << exitCode;
		}
	}
	emit processEnded(exitCode);
//	m_process = nullptr;
	clearProcess();
}

void ProcessManager::readProcessReturn()
{
	if (m_process) {
		QByteArray output = m_process->readAllStandardOutput();
		TRACE_DEBUG << "Mount process output START :" << output;
		emit processReturn(output);
		TRACE_DEBUG << "Mount process output END.";
	}
}

void ProcessManager::clearProcess()
{
	TRACE_FUNCTION_CALL << m_process;
	if (m_process) {
		if (m_process->state() != QProcess::NotRunning) {
			m_process->close();
			QObject::disconnect(m_process, & QProcess::readyReadStandardOutput, this, & ProcessManager::readProcessReturn);
			QObject::disconnect(m_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, & ProcessManager::endProcess);
		}
		delete m_process;
		m_process = nullptr;
	}
}
