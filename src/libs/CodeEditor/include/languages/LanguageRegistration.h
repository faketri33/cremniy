#ifndef LANGUAGEREGISTRATION_H
#define LANGUAGEREGISTRATION_H

class LanguageRegistry;

/**
 * @brief Регистрирует все поддерживаемые языки в переданном реестре.
 *
 * Вызывается один раз из composition root (AppContext). Функции языков
 * вызываются явно, поэтому линкер статической библиотеки не может выбросить
 * их object-файлы, а глобальных статических инициализаторов нет.
 *
 * При добавлении нового языка: добавь объявление и вызов в
 * src/languages/core/LanguageRegistration.cpp. Подробнее —
 * docs/adding_a_language.md.
 */
void registerAllLanguages(LanguageRegistry& registry);

#endif // LANGUAGEREGISTRATION_H
