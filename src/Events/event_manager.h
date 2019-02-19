//
// Created by grzegorz on 19.02.19.
//

#pragma once


#include <unordered_map>
#include <functional>
#include <deque>
#include <vector>
#include <typeindex>
#include <typeinfo>

#include "event.h"
#include "strong_type/strong_type.h"

namespace SandBox {

    class EventManager {
    public:

        EventManager() = delete;

        template <class T, class F, class... Args> static void AddCallback(F&& callback, Args&&... args);

        template <class T> static void Emit();

        template <class T> static bool onEvent();

        static void CleanUp();

        static void Flush(int n = -1);

    private:
        static void call();

    private:
        static std::unordered_map<std::type_index, std::vector<std::function<void()>>*> _events_callbacks;
        static std::deque<Event*> _events_queue;
    };


    template <class T>
    void EventManager::Emit(){
        static_assert(std::is_base_of<Event, T>::value, "Event is not the base of T");
        _events_queue.push_back(new T);
    }

    template<class T, class F, class... Args>
    void EventManager::AddCallback(F&& callback, Args&&... args) {

        static_assert(std::is_base_of<Event, T>::value , "Event is not the base of T");

        if(_events_callbacks.find(typeid(T)) == _events_callbacks.end()){
            _events_callbacks[typeid(T)] =  new std::vector<std::function<void()>>;
        }

        _events_callbacks[typeid(T)]->push_back(
                [=](){
                    callback(args...);
                });

    }

    template<class T>
    bool EventManager::onEvent() {
        for(auto ev : _events_queue){
            if(ev->Type() == typeid(T)) return true;
        }
        return false;
    }

}

//SANDBOX_TESTS_EVENT_MANAGER_H
