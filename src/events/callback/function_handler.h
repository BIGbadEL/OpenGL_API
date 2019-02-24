//
// Created by grzegorz on 21.02.19.
//

#pragma once

#include "callback.h"

namespace SandBox {

    class FunctionHandler : public Callback {
    public:
        template <class F, class... Args>
        FunctionHandler(F&& fun, Args&&... args): Callback(fun, args...) {}
        inline void run() const override { _function(); }
    };

}

//SANDBOX_TESTS_FUNCTION_HANDLER_H
