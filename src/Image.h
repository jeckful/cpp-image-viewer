#ifndef _IMAGE_H
#define _IMAGE_H

#include "Pixel.h"
#include <string>

class Image{
    
    private:
        Pixel* tab; // Array of pixels representing the image
        int dimx, dimy; //Dimensions of the image

    public: 

        Image(); // Default constructor

        Image(int dimensionX, int dimensionY); // Constructor with dimensions

        ~Image(); // Destructor

        Pixel getPix(int x, int y) const; // Get the pixel at (x, y) (const version)

        Pixel * getPix(int x, int y); // Get a pointer to the pixel at (x, y)
        
        void setPix(int x, int y, Pixel couleur); // Set the pixel at (x, y) to a given color

        void dessinerRectangle(int Xmin, int Xmax, int Ymin, int Ymax, Pixel couleur); // Draw a rectangle with the given color

        void effacer(Pixel couleur); // Clear the image with the given color

        static void testRegression(); // Regression test for the Image class

        void sauver(const std::string &filename) const; // Save the image to a file (PPM format)

        void ouvrir(const std::string &filename); // Open an image from a file (PPM format)

        void afficherConsole(); // Display the image in the console

        const Pixel* getTab() const { return tab; } // Get the pixel array (const)

        int getDimX() const { return dimx; } // Get the width of the image

        int getDimY() const { return dimy; } // Get the height of the image
};

#endif
