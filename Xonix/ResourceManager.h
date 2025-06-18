#pragma once

#include <map>
#include <memory>
#include <stdexcept>
#include <string>

template <typename Resource>
class ResourceManager {
public:
    void load(const std::string& id, const std::string& filename)
    {
        auto resource = std::make_unique<Resource>();
        if (!resource->loadFromFile(filename))
        {
            throw std::runtime_error("ResourceManager::load - Failed to load " + filename);
        }
        m_resources.emplace(id, std::move(resource));
    }

    Resource& get(const std::string& id)
    {
        auto found = m_resources.find(id);
        if (found == m_resources.end())
        {
            throw std::runtime_error("ResourceManager::get - Resource not found with ID: " + id);
        }
        return *found->second;
    }

    const Resource& get(const std::string& id) const
    {
        auto found = m_resources.find(id);
        if (found == m_resources.end())
        {
            throw std::runtime_error("ResourceManager::get - Resource not found with ID: " + id);
        }
        return *found->second;
    }

private:
    std::map<std::string, std::unique_ptr<Resource>> m_resources;
};