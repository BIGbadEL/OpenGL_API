//
// Created by grzegorz on 21.02.19.
//

#pragma once

#include <vector>
#include <functional>

namespace SandBox {

    class Callback {
    public:
        template <class F, class... Args> Callback(F&& fun, Args&&... args);

        inline bool operator==(const unsigned& other) const;

        inline unsigned getID() const { return _id; }

        virtual void run() const = 0;

        virtual ~Callback();

    protected:
        static std::vector<unsigned > _takenId;
        std::function<void()> _function;
        unsigned _id;

    };

    template <class F, class... Args>
    Callback::Callback(F&& fun, Args&&... args){
        if(_takenId.empty()){
            _takenId.push_back(0);
            _id = 0;
        } else {
            for(unsigned int i = 1; i < UINT32_MAX; ++i){
                if(std::find(_takenId.begin(), _takenId.end(), i) == _takenId.end()){
                    _takenId.push_back(i);
                    _id = i;
                    break;
                }
            }
        }

        _function = [=](){
            fun(args...);
        };
    }

    bool Callback::operator==(const unsigned& other) const {
        return _id == other;
    }

}
 //SANDBOX_TESTS_CALLBACK_H
