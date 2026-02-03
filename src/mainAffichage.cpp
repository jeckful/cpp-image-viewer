#include "Image.h"
#include "ImageViewer.h"

int main (int argc, char** argv) {
    Image image(1000, 1000); // Create an image of size 1000x1000
    image.ouvrir("./data/image3.ppm"); // Open and load the image from a file

    ImageViewer imview; // Create an image viewer
    imview.afficher(image); // Display the image in the viewer
    return 0;
}
