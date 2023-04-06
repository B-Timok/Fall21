/// @file pa09b.cpp
/// @author Brandon Timok
/// @date 11/29/2021
/// @brief Program that takes in a ppm file and gives the user
/// a choice of how to modify the picture and write to an output.ppm file.

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <iomanip>

using namespace std;
using Kernel = float[3][3];

static const Kernel SHARPEN = {
    {  0, -1,  0 },
    { -1,  5, -1 },
    {  0, -1,  0 }
};

static const Kernel EMBOSS = {
    { -2, -1,  0 },
    { -1,  1,  1 },
    {  0,  1,  2 }
};

static const Kernel BLUR = {
    { 1.0F / 9, 1.0F / 9, 1.0F / 9 },
    { 1.0F / 9, 1.0F / 9, 1.0F / 9 },
    { 1.0F / 9, 1.0F / 9, 1.0F / 9 }
};

static const Kernel EDGE = {
    { -1,  0,  1 },
    { -1,  0,  1 },
    { -1,  0,  1 }
};

const int MAX_SIZE = 1024;

struct Pixel {
    unsigned char red;    // red   intensity [0,256)
    unsigned char green;  // green intensity [0,256)
    unsigned char blue;   // blue  intensity [0,256)
};

struct Image {
    unsigned int width;
    unsigned int height;
    unsigned int max_colors;
    Pixel data[MAX_SIZE][MAX_SIZE];
};

void read_pixel(std::ifstream& infile, Pixel& pixel);
void write_pixel(std::ofstream& outfile, const Pixel& pixel);
bool read_image(std::ifstream& infile, Image& image);
void write_image(std::ofstream& outfile, const Image& image);
void grayscale(Image& image);
void negative(Image& image);
void flop(Image& image);
void flip(Image& image);
void convolute(Image& image, const Kernel& kernel);
void print_usermsg();

int main(int argc, const char* argv[]) {
    ifstream infile;
    ofstream outfile;
    string options;
    string file_name;

    if (argc == 1) {
       print_usermsg();
    } else if (argc == 2) {
       print_usermsg();
    } else if (argc == 3) {
        if (argv[1][0] == '-') {
            options = argv[1];
            file_name = argv[2];
        } else {
            file_name = argv[1];
            options = argv[2];
        }
        Image image;
        image = {0, 0, 0, {{{0,0,0}}}};

        infile.open(file_name);

        read_image(infile, image);
        for (unsigned int i = 0; i < options.length(); ++i) {
            if (options[i] == 'g') {
                grayscale(image);
            } else if (options[i] == 'n') {
                negative(image);
            } else if (options[i] == 'f') {
                flop(image);
            } else if (options[i] == 'v') {
                flip(image);
            } else if (options[i] == 'm') {
                convolute(image, EMBOSS);
            } else if (options[i] == 's') {
                convolute(image, SHARPEN);
            } else if (options[i] == 'b') {
                convolute(image, BLUR);
            } else if (options[i] == 'e') {
                convolute(image, EDGE);
            }
        }

        outfile.open("output.ppm");
        write_image(outfile, image);

        infile.close();
        outfile.close();
    }
    return 0;
}



/// (Image Effects) used to modify an image by bluring, sharpening, embossing,
/// or edge detection.
/// @param image is the struct that contains the image data.
/// @param kernel is the matrix used to modify the pixels in the image.
void convolute(Image& image, const Kernel& kernel) {
    Pixel image_cpy[3][MAX_SIZE];
    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int j = 0; j < image.width; ++j) {
            image_cpy[i][j] = image.data[i][j];
        }
    }
    for (unsigned int i = 1; i < image.height - 1; ++i) {
        for (unsigned int j = 0; j < image.width; ++j) {
            image_cpy[0][j] = image_cpy[1][j];
        }
        for (unsigned int j = 0; j < image.width; ++j) {
            image_cpy[1][j] = image_cpy[2][j];
        }
        for (unsigned int j = 0; j < image.width; ++j) {
            image_cpy[2][j] = image.data[i + 1][j];
        }
        for(unsigned int j = 1; j < image.width - 1; ++j) {
            int sum_red = 0;
            int sum_green = 0;
            int sum_blue = 0;
            for (int k = -1; k <= 1; ++k) {
                for (int l = -1; l <= 1; ++l) {
                    sum_red += kernel[l+1][k+1] * image_cpy[l + 1][j-k].red;
                    sum_green += kernel[l+1][k+1] * image_cpy[l + 1][j-k].green;
                    sum_blue += kernel[l+1][k+1] * image_cpy[l + 1][j-k].blue;
                }
            }
            image.data[i][j].red = min(max(0, sum_red), 255); 
            image.data[i][j].green = min(max(0, sum_green), 255); 
            image.data[i][j].blue = min(max(0, sum_blue), 255); 
        }
    }
}

/// (Image Transformation: Flip) function inverts the image vertically.
/// @param image is the struct that contains the image data.
void flip(Image& image) {
    for (unsigned int j = 0; j < image.width; ++j) {
        Pixel col_cpy[MAX_SIZE];
        for(unsigned int i = 0; i < image.height; ++i) {
            col_cpy[i] = image.data[i][j]; 
        }
        for(unsigned int i = 0; i < image.height; ++i) {
            image.data[i][j] = col_cpy[image.height - 1 - i]; 
        }
    }
}

/// (Image Transformation: Flop) function inverts the image horizontally.
/// @param image is the struct that contains the image data.
void flop(Image& image) {
    for (unsigned int i = 0; i < image.height; ++i) {
        Pixel row_cpy[MAX_SIZE];
        for(unsigned int j = 0; j < image.width; ++j) {
            row_cpy[j] = image.data[i][j]; 
        }
        for(unsigned int j = 0; j < image.width; ++j) {
            image.data[i][j] = row_cpy[image.width - 1 - j]; 
        }
    }
}

/// (Image Enhancement: Negative) modifies image by replacing every pixel with
/// its complimentary value.
/// @param image is the struct that contains the image data.
void negative(Image& image) {  
     for (unsigned int i = 0; i < image.height; ++i) {
        for(unsigned int j = 0; j < image.width; ++j) {
            image.data[i][j].red = image.max_colors - image.data[i][j].red;
            image.data[i][j].green = image.max_colors - image.data[i][j].green;
            image.data[i][j].blue = image.max_colors - image.data[i][j].blue;
        }
    }
}

/// (Image Enhancement: Grayscale) modifies the color values of each pixel
/// to grayscale (black & white).
/// @param image is the struct that contains the image data.
void grayscale(Image& image) {
    int avg_pixel;

    for (unsigned int i = 0; i < image.height; ++i) {
        for(unsigned int j = 0; j < image.width; ++j) {
            avg_pixel = (image.data[i][j].red + image.data[i][j].green +
                        image.data[i][j].blue) / 3;
            image.data[i][j].red = avg_pixel;
            image.data[i][j].green = avg_pixel;
            image.data[i][j].blue = avg_pixel;
        }
    }
}

 /// Reads an RGB color triplet into a Pixel from an input file.
 /// @param infile is the input of the file.
 /// @param pixel is the struct used for the pixel data.
void read_pixel(std::ifstream& infile, Pixel& pixel) {
    int red_value;
    int green_value;
    int blue_value;

    infile >> red_value >> green_value >> blue_value;

    pixel.red = static_cast<unsigned char>(red_value);
    pixel.green = static_cast<unsigned char>(green_value);
    pixel.blue = static_cast<unsigned char>(blue_value);
}

 /// Writes a Pixel's RGB components to an output file stream.
 /// Each value is followed by whitespace.
 /// @param outfile is used for the output.
 /// @param pixel is the struct used for the pixel data.
void write_pixel(std::ofstream& outfile, const Pixel& pixel) {
    outfile << '\t' << static_cast<int>(pixel.red) << '\t' 
            << static_cast<int>(pixel.green) 
            << '\t' << static_cast<int>(pixel.blue);
}
 /// Reads a P3 PPM image from the input file stream.
 /// @returns true if image is read successfully and is of correct size.
 /// @param infile is the input of the file.
 /// @param image is the struct used for the image data.
bool read_image(std::ifstream& infile, Image& image) {
    bool valid = false;
    string magic_num;

    if (infile.get() == 'P' && infile.get() == '3' && infile.get() == '\n') {

        while (infile.peek() == '#') {
            infile.ignore(numeric_limits <streamsize>::max(), '\n');
        }

        infile >> image.width >> image.height >> image.max_colors;

        if (image.width < 0 || image.width > MAX_SIZE || image.height < 0 || 
            image.height > MAX_SIZE || image.max_colors < 0 || 
            image.max_colors > 255) {
            valid = false;
        } else {
            for (unsigned int i = 0; i < image.height; ++i) {
                for(unsigned int j = 0; j < image.width; ++j) {
                   read_pixel(infile, image.data[i][j]);
                }
            }
            valid = true;
        }
    } else {
        valid = false;
    }
    return valid;
}

 /// Writes a P3 PPM image to the output file stream.
 /// The header is formatted as specified, and the author's name is
 /// inserted as a comment after the magic number.
 /// @param outfile is used for the output.
 /// @param image is the struct used for the image data.
void write_image(std::ofstream& outfile, const Image& image) {
    outfile << "P3" << '\n';
    outfile << "# Brandon Timok" << '\n';
    outfile << image.width << ' ' << image.height << '\n';
    outfile << image.max_colors << '\n';

    for (unsigned int i = 0; i < image.height; ++i) {
        for(unsigned int j = 0; j < image.width; ++j) {
            write_pixel(outfile, image.data[i][j]);
        } outfile << '\n';
    }
}

/// prints usage message.
/// no parameters needed.
void print_usermsg() {
    cout << "Modifies an image and writes the result to output.ppm\n"
         << "Usage: ./a.out -options source.ppm" << endl
         << "\nwhere -options can be one or more of the following:" << endl;
    cout << left;
    cout << "\nEnhancements:" << '\n'
         << setw(17) << "g - grayscale";
    cout << " -- convert image to grayscale (b&w)\n";
    cout << setw(17) << "n - negate"
         << " -- replace each pixel with its"
         << " complementary color" << endl;
    cout << "\nTransformations:\n"
         << setw(17) << "f - flop";
    cout << " -- flip image in the horizontal direction"   
         << endl;
    cout << setw(17) << "v - flip"
         << " -- flip image in the vertical direction" 
         << endl;
    cout << "\nEffects:\n"
         << setw(17) << "m - emboss"
         << " -- apply embossing effect to image" << endl;
    cout << setw(17) << "s - sharpen"
         << " -- sharpen the image"  << endl;
    cout << setw(17) << "b - blur"
         << " -- blur (soften) the image\n"
         << setw(17) << "e - edge detect"
         << " -- detect edges in the image" << endl;
    cout << "\nExample:" << endl
         << "$ ./pa09b -smns source.ppm" << endl
         << "\nApplies in order: sharpen, emboss, negate, and sharpen"
         << "(again)\n" << "to the 'source.ppm' image." 
         << endl;
    cout << "\nOutput written to 'output.ppm'\n" << endl;
}
