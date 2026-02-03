#include "Image.h"

int main() {
    Pixel rouge (205, 9, 13); // Red pixel
    Pixel jaune (242, 248, 22); // Yellow pixel
    Pixel bleu (120, 193, 246); // Blue pixel

    // First image
    Image image1 (64,48);
    image1.effacer(bleu); // Fill the image with blue
    image1.dessinerRectangle(6, 8, 21, 26, rouge); // Draw a red rectangle
    image1.setPix(16,14,jaune); // Set a yellow pixel
    image1.setPix(46,33,jaune); // Set another yellow pixel
    image1.afficherConsole(); // Display the image in the console
    image1.sauver("./data/image1.ppm"); // Save the image to a file

    // Second image
    Image image2;
    image2.ouvrir("./data/image1.ppm"); // Load the first image
    image2.dessinerRectangle(18, 23, 28, 37, rouge); // Draw a red rectangle
    image2.dessinerRectangle(26, 34, 36, 50, jaune); // Draw a yellow rectangle
    image2.sauver("./data/image2.ppm"); // Save the image to a file

    // Third image
    Image image3;
    image3.ouvrir("./data/image2.ppm"); // Load the second image
    image3.dessinerRectangle(10, 20, 30, 40, jaune); // Draw a yellow rectangle
    image3.setPix(5, 5, rouge); // Set a red pixel
    image3.sauver("./data/image3.ppm"); // Save the image to a file

    return 0;
}
