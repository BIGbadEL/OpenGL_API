//
// Created by grzegorz on 17.02.19.
//

#pragma once

class GLFWwindow;

namespace SandBox {

    class Window {

        friend void cursor_position_callback(GLFWwindow* window, double xPos, double yPos);
        friend void window_size_callback(GLFWwindow* window, int width, int height);


    public:
        Window(int width, int height, const char* name);
        ~Window();

        void EnableDepthTest();

        void Update() const;

        void Clear() const;

        bool ShouldClose() const;

        void Close() const;

        inline int getWidth() const { return _width; }
        inline int getHeight() const { return _height; }
        inline const char* getName() const { return _name; }
        inline void getMousePos(double& x, double& y) const { x = _x; y = _y; }
        inline float getAspectRatio() const { return static_cast<float>(_width) / static_cast<float>(_height); }

    private:
        void Init();
    private:
        //Window stuff
        int _width;
        int _height;
        const char* _name;
        GLFWwindow* _window;

        //input Mouse
        double _x;
        double _y;
    };
}

 //SANDBOX_TESTS_WINDOW_H
