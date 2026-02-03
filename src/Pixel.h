#ifndef _PIXEL_H
#define _PIXEL_H

struct Pixel {
    unsigned char r, g, b; // Red, green, blue components

    Pixel() : r(0), g(0), b(0) {} // Default constructor: black pixel

    Pixel(unsigned char nr, unsigned char ng, unsigned char nb) : r(nr), g(ng), b(nb) {} // Constructor with color values
};

#endif // _PIXEL_H

