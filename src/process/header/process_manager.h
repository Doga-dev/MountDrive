#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QObject>
#include <QProcess>

class ProcessManager : public QObject
{
	Q_OBJECT
public:
	explicit ProcessManager(QObject * parent = nullptr);
	~ProcessManager();

	bool isRunning() const;

signals:
	void processEnded(int exitCode);
	void processReturn(QString output);

public slots:
	void runProcess(QString command);
	void writeInProcess(QString input);
	void stopProcess();

private:
	void processStarted();
	void endProcess(int exitCode, QProcess::ExitStatus exitStatus);
	void readProcessReturn();
	void clearProcess();

	QProcess	* m_process;            // Process de lancement de mon programme externe 1
};

#endif // PROCESSMANAGER_H
