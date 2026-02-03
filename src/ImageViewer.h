#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include "Image.h"
#include <SDL2/SDL.h>

class ImageViewer {
    private:
        SDL_Window* window;      // SDL window for displaying the image
        SDL_Renderer* renderer;  // SDL renderer for drawing
        SDL_Texture* texture;    // SDL texture for the image
        SDL_Surface* surface;    // SDL surface for the image
        SDL_Rect zoneAffichee;   // Rectangle representing the displayed area

    public:
        ImageViewer();           // Constructor: initializes SDL and creates window/renderer
        ~ImageViewer();          // Destructor: frees SDL resources

        void afficher(const Image& im); // Display the given image in the SDL window
};

#endif
