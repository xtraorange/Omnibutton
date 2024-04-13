#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <functional>
#include <map>
#include <vector>
#include <string>

class EventManager {
private:
    std::map<std::string, std::vector<std::function<void(std::string)>>> listeners;

public:
    void registerListener(const std::string& eventType, std::function<void(std::string)> callback) {
        listeners[eventType].push_back(callback);
    }

    void fireEvent(const std::string& eventType, std::string data) {
        if (listeners.find(eventType) != listeners.end()) {
            for (auto& listener : listeners[eventType]) {
                listener(data);
            }
        }
    }
};

#endif