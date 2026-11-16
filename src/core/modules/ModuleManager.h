#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H

#include <algorithm>
#include <any>
#include <functional>
#include <tuple>
#include <unordered_map>

#include <QHash>
#include <QList>
#include <QString>
#include <QVector>

struct ModuleContext;

template<typename T>
struct ModuleDescription {
    std::function<T*(const ModuleContext&)> creator;
    std::function<QString()> name;
    int position = 0;
};

template<typename T>
using ModuleStorage = QHash<QString, QVector<ModuleDescription<T>>>;

/// Registry of pluggable modules (tabs, windows, references), grouped per
/// module base type T. Owned by AppContext and populated explicitly by
/// registerBuiltinModules().
class ModuleManager {

public:
    template<typename T>
    void registerModule(std::function<QString()> name, const QString &group, std::function<T*(const ModuleContext&)> creator, int position = 0) {
        ModuleDescription<T> desc{
            std::move(creator),
            std::move(name),
            position
        };
        getStorage<T>()[group.trimmed()].push_back(std::move(desc));
    }

    template <typename T>
    T* create(const QString& group, const int& index, const ModuleContext& context) const {
        const auto& storage = getStorageConst<T>();
        auto it = storage.find(group.trimmed());
        if (it == storage.end()) return nullptr;

        const auto& vec = it.value();
        if (index < 0 || index >= vec.size()) return nullptr;

        return vec[index].creator(context);
    }

    template<typename T>
    const QVector<ModuleDescription<T>> & getByGroup(const QString &group) const { return getByGroup(group, getStorageConst<T>()); }

    template<typename T>
    QList<QString> getGroups() const { return getSortedKeys<T>(getStorageConst<T>()); }

private:
    template<typename T>
    ModuleStorage<T>& getStorage() {
        auto it = m_storages.find(storageKey<T>());
        if (it == m_storages.end())
            it = m_storages.emplace(storageKey<T>(), ModuleStorage<T>{}).first;
        return *std::any_cast<ModuleStorage<T>>(&it->second);
    }

    template<typename T>
    const ModuleStorage<T>& getStorageConst() const {
        static const ModuleStorage<T> empty;
        auto it = m_storages.find(storageKey<T>());
        if (it == m_storages.end())
            return empty;
        return *std::any_cast<ModuleStorage<T>>(&it->second);
    }

    template<typename T>
    const QVector<ModuleDescription<T>>& getByGroup(
        const QString& group,
        const QHash<QString, QVector<ModuleDescription<T>>>& hash) const
    {
        static const QVector<ModuleDescription<T>> empty;
        auto it = hash.find(group.trimmed());
        if (it == hash.end()) return empty;
        return it.value();
    }

    template<typename T>
    QList<QString> getSortedKeys(const QHash<QString, QVector<ModuleDescription<T>>>& map) const {
        QList<QString> keys = map.keys();
        std::sort(keys.begin(), keys.end(), [](const QString& a, const QString& b) {
            return std::tuple{!a.isEmpty(), a} < std::tuple{!b.isEmpty(), b};
        });
        return keys;
    }

    // typeid(T) would require T to be complete; a per-type static address does not.
    template<typename T>
    static const void* storageKey() {
        static const char key = 0;
        return &key;
    }

    std::unordered_map<const void*, std::any> m_storages;
};

#endif // MODULEMANAGER_H
