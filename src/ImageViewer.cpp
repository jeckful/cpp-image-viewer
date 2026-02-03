#include "ImageViewer.h"
#include <iostream>
#include <SDL2/SDL.h>

ImageViewer::ImageViewer() {
    SDL_Init(SDL_INIT_VIDEO); // Initialize SDL
    window = SDL_CreateWindow("Image Viewer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_SHOWN); // Create SDL window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // Create SDL renderer
}

ImageViewer::~ImageViewer() {
    SDL_DestroyTexture(texture); // Free SDL texture
    SDL_DestroyRenderer(renderer); // Free SDL renderer
    SDL_DestroyWindow(window); // Free SDL window
    SDL_Quit(); // Quit SDL
}

void ImageViewer::afficher(const Image& im) {
    // Convert the image to an SDL surface
    surface = SDL_CreateRGBSurfaceFrom((void*)im.getTab(), im.getDimX(), im.getDimY(), 24, im.getDimX() * 3, 255, 255, 255, 0);

    // Initialize the displayed area with the full image size
    zoneAffichee.x = 0;
    zoneAffichee.y = 0;
    zoneAffichee.w = im.getDimX(); // Image width
    zoneAffichee.h = im.getDimY(); // Image height

    // Check surface
    if (surface == nullptr) {
        // Error handling
        return;
    }

    // Create SDL texture from the surface
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    // Check texture
    if (texture == nullptr) {
        // Error handling
        SDL_FreeSurface(surface);
        return;
    }

    // Clear the renderer
    SDL_RenderClear(renderer);

    // Copy the texture to the renderer
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Present the renderer
    SDL_RenderPresent(renderer);

    // Event loop
    bool running = true;
    SDL_Event event;
    bool sizeChanged = false; // Indicates if the displayed area size has changed

    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                // Keyboard events
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                    case SDLK_t:
                        // Zoom in: increase displayed area size
                        zoneAffichee.w += 10;
                        zoneAffichee.h += 10;
                        sizeChanged = true;
                        break;
                    case SDLK_g:
                        // Zoom out: decrease displayed area size
                        zoneAffichee.w -= 10;
                        zoneAffichee.h -= 10;
                        sizeChanged = true;
                        break;
                    default:
                        break;
                }
            }
        }
    
        if (sizeChanged) {
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, &zoneAffichee, NULL);
            SDL_RenderPresent(renderer);
            sizeChanged = false; // Reset after rendering
        }

        SDL_Delay(10); // Pause for 10 milliseconds to reduce CPU usage
    }

    SDL_FreeSurface(surface);
}
