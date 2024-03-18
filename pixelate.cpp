// /*
// Author: Zuhayer Tashin
// Course: CSCI-135
// Instructor: Tong Yi

// 
// */



#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>
using namespace std;

const int MAX_H = 512;
const int MAX_W = 512;

// Function to read an image from a file
void readImage(int image[MAX_H][MAX_W], int &height, int &width) {
    char c;
    int x;
    ifstream instr;
    instr.open("inImage.pgm"); // Open input file

    instr >> c;
    assert(c == 'P'); // Ensure magic number is 'P'
    instr >> c;
    assert(c == '2'); // Ensure format is '2'

    // Skip comments
    while ((instr >> ws).peek() == '#') {
        instr.ignore(4096, '\n');
    }

    // Read width, height, and maximum value
    instr >> width;
    instr >> height;

    assert(width <= MAX_W); // Ensure width is within bounds
    assert(height <= MAX_H); // Ensure height is within bounds
    int max;
    instr >> max;
    assert(max == 255); // Ensure maximum value is 255

    // Read pixel values into the image array
    for (int row = 0; row < height; row++)
        for (int col = 0; col < width; col++)
            instr >> image[row][col];
    instr.close();
    return;
}

// Function to write an image to a file
void writeImage(int image[MAX_H][MAX_W], int height, int width) {
    ofstream ostr;
    ostr.open("outImage.pgm"); // Open output file
    if (ostr.fail()) {
        cout << "Unable to write file\n";
        exit(1);
    };

    ostr << "P2" << endl; // Write magic number
    ostr << width << ' '; // Write width
    ostr << height << endl; // Write height
    ostr << 255 << endl; // Write maximum value

    // Write pixel values
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            assert(image[row][col] < 256); // Ensure pixel value is within bounds
            assert(image[row][col] >= 0); // Ensure pixel value is non-negative
            ostr << image[row][col] << ' '; // Write pixel value
            ostr << endl; // New line after each pixel value
        }
    }
    ostr.close();
    return;
}

int main() {
    int img[MAX_H][MAX_W];
    int h, w;

    readImage(img, h, w); // Read input image from file

    int out[MAX_H][MAX_W];

    // Perform interpolation on the input image
    for(int row = 0; row < h; row++) {
        for(int col = 0; col < w; col++) {
            if(row % 2 == 0) {
                if(col % 2 == 0) {
                    out[row][col] = (img[row][col] + img[row + 1][col] + img[row][col + 1] + img[row + 1][col + 1]) / 4;
                } else {
                    out[row][col] = (img[row][col] + img[row + 1][col] + img[row][col - 1] + img[row + 1][col - 1]) / 4;
                }
            } else {
                if (col % 2 == 0) {
                    out[row][col] = (img[row][col] + img[row - 1][col] + img[row - 1][col + 1] + img[row][col + 1]) / 4;
                } else {
                    out[row][col] = (img[row][col] + img[row - 1][col] + img[row][col - 1] + img[row - 1][col - 1]) / 4;
                }
            }
        }
    }

    writeImage(out, h, w); // Write output image to file
}
