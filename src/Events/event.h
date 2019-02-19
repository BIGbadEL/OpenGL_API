//
// Created by grzegorz on 19.02.19.
//

#pragma once

#include <typeindex>
#include <typeinfo>

namespace SandBox {

    class Event {
    public:
        virtual std::type_index Type() const = 0;
        virtual ~Event() = default;
    protected:
        Event() = default;
    };

}
 //SANDBOX_TESTS_EVENT_H
