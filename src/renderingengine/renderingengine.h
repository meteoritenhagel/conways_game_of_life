#ifndef RENDERINGENGINE_H_
#define RENDERINGENGINE_H_

#include <SDL.h>

#include <string>

/*
 * This class is a simple wrapper for a single SDL window and renderer.
 */
class RenderingEngine {
public:
    /*
     * Constructor
     * @param[in] width window width
     * @param[in] height window height
     * @param[in] title window title
     */
    RenderingEngine(const int width, const int height, const std::string title);
    ~RenderingEngine();

    /*
     * Returns window width.
     * @return width
     */
    int get_width();

    /*
     * Returns window height.
     * @return height
     */
    int get_height();

    /*
     * Returns window.
     * @return window
     */
    SDL_Window* get_window();

    /*
     * Returns renderer.
     * @return renderer.
     */
    SDL_Renderer* get_renderer();

private:
    int _width; ///< window width
    int _height; ///< window height
    SDL_Window* _window; ///< SDL window
    SDL_Renderer* _renderer; ///< SDL renderer
};

#endif /* RENDERINGENGINE_H_ */
