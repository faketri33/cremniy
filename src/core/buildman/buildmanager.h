#ifndef BUILDMANAGER_H
#define BUILDMANAGER_H

#include <qprocess.h>

class logView;

class BuildManager : public QObject {
    Q_OBJECT

    private:
        QProcess* m_buildProcess;
        QString m_workPath;
        QString m_command;

    public:
        BuildManager(const QString &workPath, const QString &command, logView* logViewWidg);
        ~BuildManager();

        void build();
        void stop();

};

#endif// BUILDMANAGER_H
