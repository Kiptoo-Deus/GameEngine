#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <string>

class Window {
public:
    Window(const std::string& title, int width, int height);
    ~Window();

    bool Init();
    void PollEvents();
    void SwapBuffers();

private:
    std::string title;
    int width, height;
    SDL_Window* sdlWindow;
    SDL_GLContext glContext;
};

#endif // WINDOW_H
