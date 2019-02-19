//
// Created by grzegorz on 19.02.19.
//

#pragma once

#include "event.h"

namespace SandBox {

    class WindowResize : public Event{
        friend class EventManager;
    protected:
        WindowResize() = default;
    public:
        std::type_index Type() const override { return typeid(typeof(*this)); }
    };

}
//SANDBOX_TESTS_EVENTS_H
