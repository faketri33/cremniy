//
// Created by Dmitriy on 4/3/26.
//

#ifndef CREMNIY_LANGUAGE_MANAGER_H
#define CREMNIY_LANGUAGE_MANAGER_H

#include <memory>

#include <QTranslator>

#include "config.h"


class AppSettings;

class LanguageManager {
private:
    AppSettings& m_settings;
    std::unique_ptr<QTranslator> _m_base_translator;
    std::unique_ptr<QTranslator> _m_translator;

public:
    explicit LanguageManager(AppSettings& settings) : m_settings(settings) {}
    ~LanguageManager();
    LanguageManager(const LanguageManager&) = delete;
    LanguageManager& operator=(const LanguageManager&) = delete;

    void loadUserDefaultLocale();

    void setLocale(const QString& locale);

    static QString translationsPath();

    static QStringList supportedLanguages() {
        return QStringLiteral(APP_LANGUAGES).split(';', Qt::SkipEmptyParts);
    }
};



#endif //CREMNIY_LANGUAGE_MANAGER_H
