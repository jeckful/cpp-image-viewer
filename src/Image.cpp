#include <iostream>
#include <cassert>
#include "Image.h"
#include "Pixel.h"
#include <fstream>

// Default constructor
Image::Image(){
    tab = nullptr;
    dimx = 0; // Initialize dimx to 0
    dimy = 0; // Initialize dimy to 0
}

// Constructor with dimensions
Image::Image(int dimensionX, int dimensionY){
    dimx = dimensionX; // Assign dimensionX to dimx
    dimy = dimensionY; // Assign dimensionY to dimy
    tab = new Pixel[dimx * dimy]; // Dynamically allocate a pixel array
    effacer(Pixel()); // Clear the array with the default color
}

// Destructor
Image::~Image(){
    if(tab != nullptr) delete[] tab; // Deallocate the pixel array
    dimx = 0; // Reset dimx to 0
    dimy = 0; // Reset dimy to 0
}

// Get a pixel at (x, y) (const version)
Pixel Image::getPix(int x, int y)const{
    if(x >= 0 && x < dimx && y >= 0 && y < dimy) return tab[y*dimx+x]; // Check bounds and return the corresponding pixel
    return Pixel(); // Return a default Pixel if parameters are invalid
}

// Get a pointer to the pixel at (x, y)
Pixel * Image::getPix(int x, int y){
    assert(x >= 0 && x < dimx && y >= 0 && y < dimy); // Check bounds
    return &tab[y*dimx+x]; // Return a pointer to the corresponding pixel
}

// Set the pixel at (x, y) to a given color
void Image::setPix(int x, int y, Pixel couleur){
    if(x >= 0 && x < dimx && y >= 0 && y < dimy) tab[y*dimx+x] = couleur; // Check bounds and assign the color to the specified pixel
}

// Draw a rectangle with the given color
void Image::dessinerRectangle(int Xmin, int Xmax, int Ymin, int Ymax, Pixel couleur){
    for(int i = Xmin; i <= Xmax; i++ ){
        for(int j = Ymin; j <= Ymax; j++ ){
            setPix(i, j, couleur); // Draw a rectangle by applying the specified color to all pixels between the given coordinates
        }
    }
}

// Clear the image with the given color
void Image::effacer(Pixel couleur){
    dessinerRectangle(0, dimx-1, 0, dimy-1, couleur); // Clear the image by drawing a rectangle of the image size with the specified color
}

// Regression test for the Image class
void Image::testRegression() {
    using namespace std;

    Image testImageDefault; // Create a default image
    assert(testImageDefault.dimx == 0 && testImageDefault.dimy == 0); // Check dimensions of the default image
    cout << "Default constructor OK!" << endl;

    Image imageTest(3, 4); // Create a new image with specified dimensions
    assert(imageTest.dimx == 3 && imageTest.dimy == 4); // Check dimensions of the new image
    cout << "Constructor with dimensions OK!" << endl;

    Pixel* PixelPtr; // Declare a Pixel pointer

    imageTest.effacer(Pixel(255, 0, 0)); // Clear the image with a specified color
    for (int i = 0; i < imageTest.dimx; ++i) {
        for (int j = 0; j < imageTest.dimy; ++j) {
            PixelPtr = imageTest.getPix(i, j); // Get the pixel at (i, j)
            assert(PixelPtr != nullptr); // Check that the pixel is not null
            Pixel Pixel = *PixelPtr; // Get the value of the pixel
            assert(Pixel.r == 255 && Pixel.g == 0 && Pixel.b == 0); // Check the color of the pixel
        }
    }
    cout << "Clear OK!" << endl;

    imageTest.dessinerRectangle(1, 2, 1, 2, Pixel(0, 255, 0)); // Draw a rectangle on the image with a specified color
    Pixel* pixel1 = imageTest.getPix(1, 1); // Get the pixel at (1, 1)
    assert(pixel1 != nullptr); // Check that the pixel is not null
    assert(pixel1->r == 0 && pixel1->g == 255 && pixel1->b == 0); // Check the color of the pixel
    Pixel* pixel2 = imageTest.getPix(2, 2); // Get the pixel at (2, 2)
    assert(pixel2 != nullptr); // Check that the pixel is not null
    assert(pixel2->r == 0 && pixel2->g == 255 && pixel2->b == 0); // Check the color of the pixel
    cout << "DrawRectangle OK!" << endl;

    imageTest.setPix(1, 1, Pixel(0, 0, 255)); // Modify the pixel at (1, 1) with a new color
    Pixel* modifiedPixelPtr = imageTest.getPix(1, 1); // Get the modified pixel
    assert(modifiedPixelPtr != nullptr); // Check that the pixel is not null
    Pixel modifiedPixel = *modifiedPixelPtr; // Get the value of the modified pixel
    assert(modifiedPixel.r == 0 && modifiedPixel.g == 0 && modifiedPixel.b == 255); // Check the color of the pixel
    cout << "GetPix and SetPix OK!" << endl;
}

// Save the image to a file (PPM format)
void Image::sauver(const std::string &filename) const
{
    using namespace std;

    ofstream fichier(filename.c_str()); // Open the file for writing
    assert(fichier.is_open()); // Check that the file opened successfully
    fichier << "P3" << endl; // Write the PPM header
    fichier << dimx << " " << dimy << endl; // Write the image dimensions
    fichier << "255" << endl; // Write the max color value
    for (unsigned int y = 0; y < dimy; ++y) // Loop through image rows
        for (unsigned int x = 0; x < dimx; ++x) // Loop through image columns
        {
            Pixel pix = getPix(x, y); // Get the pixel at (x, y)
            fichier << +pix.r << " " << +pix.g << " " << +pix.b << " "; // Write the R, G, B values of the pixel to the file
        }
    cout << "Image saved to " << filename << " ... OK\n";
    fichier.close(); // Close the file
}

// Open an image from a file (PPM format)
void Image::ouvrir(const std::string &filename)
{
    using namespace std;

    ifstream fichier(filename.c_str()); // Open the file for reading
    if (!fichier.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        assert(false);
    }
    int r, g, b; // Temporary variables for RGB components
    std::string mot; // Temporary variable for reading words from the file
    dimx = dimy = 0; // Reset image dimensions
    fichier >> mot >> dimx >> dimy >> mot; // Read the PPM header and image dimensions
    assert(dimx >= 0 && dimy >= 0); // Check that dimensions are valid
    if (tab != nullptr)
        delete[] tab; // Free memory if the array already exists
    tab = new Pixel[dimx * dimy]; // Allocate a new pixel array
    for (unsigned int y = 0; y < dimy; ++y) // Loop through image rows
        for (unsigned int x = 0; x < dimx; ++x) // Loop through image columns
        {
            fichier >> r >> g >> b; // Read the RGB components of the pixel
            getPix(x, y)->r = r; // Assign the R component
            getPix(x, y)->g = g; // Assign the G component
            getPix(x, y)->b = b; // Assign the B component
        }
    fichier.close(); // Close the file
    cout << "Image loaded from " << filename << " ... OK\n";
}

// Display the image in the console
void Image::afficherConsole()
{
    using namespace std;
    cout << dimx << " " << dimy << endl; // Display the image dimensions
    for (unsigned int y = 0; y < dimy; ++y) // Loop through image rows
    {
        for (unsigned int x = 0; x < dimx; ++x) // Loop through image columns
        {
            Pixel* pix = getPix(x, y); // Get the pixel at (x, y)
            cout << +pix->r << " " << +pix->g << " " << +pix->b << " "; // Display the R, G, B values of the pixel
        }
        cout << endl; // New line at the end of each row
    }
}
