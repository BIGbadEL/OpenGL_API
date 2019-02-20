//
// Created by grzegorz on 19.02.19.
//

#pragma once

#include "event.h"

#define NEW_EVENT_TYPE(name) class name : public ::SandBox::Event {                                              \
                                friend class EventManager;                                                     \
                             protected:                                                                        \
                                name() = default;                                                              \
                             public:                                                                           \
                                inline std::type_index Type() const override { return typeid(typeof(*this)); } \
                             }

namespace SandBox {


    NEW_EVENT_TYPE(WindowResize);
    NEW_EVENT_TYPE(CursorMove);
    NEW_EVENT_TYPE(KeyPressed);
    NEW_EVENT_TYPE(ButtonPressed);

}
//SANDBOX_TESTS_EVENTS_H
