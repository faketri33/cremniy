#pragma once

#include "blamelineinfo.h"

#include <QHash>
#include <QObject>
#include <QString>
#include <QVector>

/**
 * @brief Application-facing interface for asynchronous Git blame requests.
 *
 * The service owns background execution and request correlation. Module state
 * and presentation are routed through TabBase by the application shell.
 */
class GitBlameService final : public QObject {
    Q_OBJECT

public:
    explicit GitBlameService(QObject* parent = nullptr);

    void requestBlame(const QString& filePath);

signals:
    void blameReady(const QString& filePath, const QVector<BlameLineInfo>& result);
    void blameFailed(const QString& filePath, const QString& error);
    void repositoryChanged();

private:
    QHash<QString, quint64> m_requestVersions;
    quint64 m_nextRequestVersion = 0;
};
