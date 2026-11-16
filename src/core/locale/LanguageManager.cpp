//
// Created by Dmitriy on 4/3/26.
//

#include "LanguageManager.h"

#include <QApplication>
#include <qlocale.h>
#include <QTranslator>

#include "appsettings.h"

LanguageManager::~LanguageManager() {
    // Uninstall explicitly while the application object is still alive.
    QCoreApplication::removeTranslator(_m_base_translator.get());
    QCoreApplication::removeTranslator(_m_translator.get());
}

void LanguageManager::loadUserDefaultLocale() {
    setLocale(m_settings.language());
}

void LanguageManager::setLocale(const QString& locale) {
    auto base_qt = std::make_unique<QTranslator>();
    auto newTranslator = std::make_unique<QTranslator>();

    QApplication::removeTranslator(_m_base_translator.get());
    QApplication::removeTranslator(_m_translator.get());

    if (base_qt->load(QLocale(locale), "qtbase", "_", translationsPath())){
        _m_base_translator = std::move(base_qt);
        QApplication::installTranslator(_m_base_translator.get());
    }
    if (newTranslator->load(QLocale(locale), "app", "_", translationsPath())){
        _m_translator = std::move(newTranslator);
        QApplication::installTranslator(_m_translator.get());
    }

    m_settings.setLanguage(locale);
}

QString LanguageManager::translationsPath() {
    QString translationsPath = QApplication::applicationDirPath();

#if defined(Q_OS_APPLE) || defined(Q_OS_MAC)
    return translationsPath.append("/../Resources/translations/");
#else
    return translationsPath.append("/Resources/translations/");
#endif
}
