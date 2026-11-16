#ifndef CLICKABLELINEEDIT_H
#define CLICKABLELINEEDIT_H

#include <QLineEdit>
#include <QMetaMethod>
#include <QDir>
#include <QMouseEvent>
#include <qfiledialog.h>

class ClickableLineEdit : public QLineEdit {
    Q_OBJECT
public:
    explicit ClickableLineEdit() {};
    using QLineEdit::QLineEdit;

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override {
        emit clicked();

        if (!isSignalConnected(QMetaMethod::fromSignal(&ClickableLineEdit::clicked))) {
            QString dir = QFileDialog::getExistingDirectory(
                this,
                tr("Choose Directory"),
                QDir::homePath(),
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
                );

            if (!dir.isEmpty()) {
                this->setText(dir);
            }
        }

        QLineEdit::mousePressEvent(event);
    }
};

#endif // CLICKABLELINEEDIT_H
