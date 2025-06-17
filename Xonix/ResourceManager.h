#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

template <typename Resource>
class ResourceManager {
public:
    // £aduje zasób z pliku i zapisuje go pod danym ID
    void load(const std::string& id, const std::string& filename) {
        auto resource = std::make_unique<Resource>();
        if (!resource->loadFromFile(filename)) {
            // Rzucenie wyj¹tku w przypadku b³êdu ³adowania
            throw std::runtime_error("ResourceManager::load - Failed to load " + filename);
        }
        m_resources.emplace(id, std::move(resource));
    }

    // Zwraca referencjê do za³adowanego zasobu
    Resource& get(const std::string& id) {
        auto found = m_resources.find(id);
        if (found == m_resources.end()) {
            throw std::runtime_error("ResourceManager::get - Resource not found with ID: " + id);
        }
        return *found->second;
    }

    // Zwraca sta³¹ referencjê do za³adowanego zasobu
    const Resource& get(const std::string& id) const {
        auto found = m_resources.find(id);
        if (found == m_resources.end()) {
            throw std::runtime_error("ResourceManager::get - Resource not found with ID: " + id);
        }
        return *found->second;
    }

private:
    std::map<std::string, std::unique_ptr<Resource>> m_resources;
};