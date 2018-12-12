//Part1
#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "cs1300bmp.h"
#include "cs1300bmp.cc"

using namespace std;
/*
	In this part you'll be implementing 2 filters.
	1. green filter
	2. blue filter

	Before you can do any operation on images, you'll
	have to read the image file into the program.
	You can read and write "bmp" images using the functions
	1. cs1300bmp_readfile()
	and
	2. cs1300bmp_writefile() respectively.

	cs1300bmp_readfile(image_file_name, cs1300bmp_struct):
		1.	The data read from an image on the disk with path
			image_file_name is stored in the cs1300bmp_structure.

		2.	The structure holds 3 things:
				a.	The HEIGHT of the image (int).
				b.	The WIDTH of the image (int).
				c.	A 3D array storing the colors
					of every pixel in the image.

		3.	I suggest you to look at the declaration of the
			structure in file cs1300bmp.h @ line#18.

		4.	Most of the manipulations that you will be doing in
			this project will be on the color field of the
			cs1300bmp structure.

	cs1300bmp_writefile(output_file_name, cs1300bmp_structure):
		1.	Similar to the cs1300bmp_readfile function, except in this
			case, the function will be writing the data from the
			cs1300bmp_structure to the file defined by the
			output_file_name value onto the disk.
*/

/*
	While implementing the below functions based on the
	introduction mentioned in the attached pdf document,
	do not forget to set the width and height values of
	the new cs1300bmp structure.
	HINT: the values will be same as the dimensions of the
	inImage structure.
*/

/*
	We have implemented the red_filter for you. Go through
	it and comment your understanding below.
	HERE:

*/

void red_filter(cs1300bmp *inImage, cs1300bmp *outImage) {

	outImage->width = inImage->width; //Set the width of outImage to be the same as inImage.
	outImage->height = inImage->height; //Set the height of outImage to be the same as inImage.

	int rows = outImage->height; //Each pixel takes up one row/col cell in the 2D array
	int cols = outImage->width;  //Each pixel takes up one row/col cell in the 2D array

	for (int i = 0; i <= rows; ++i) {     //Looping through every row
		for (int j = 0; j <= cols; ++j) { //Looping through every col
			outImage->color[0][i][j] = 0; //Set index 0 in RGB, i.e. Red to zero.
			outImage->color[1][i][j] = inImage->color[1][i][j]; //Keep other colors the same as inImage
			outImage->color[2][i][j] = inImage->color[2][i][j]; //Keep other colors the same as inImage
		}
	}
}

void green_filter(cs1300bmp *inImage, cs1300bmp *outImage) {
	outImage->width = inImage->width; //Set the width of outImage to be the same as inImage.
	outImage->height = inImage->height; //Set the height of outImage to be the same as inImage.

	int rows = outImage->height; //Each pixel takes up one row/col cell in the 2D array
	int cols = outImage->width;  //Each pixel takes up one row/col cell in the 2D array

	for (int i = 0; i <= rows; ++i) {     //Looping through every row
		for (int j = 0; j <= cols; ++j) { //Looping through every col
			outImage->color[1][i][j] = 0; //Set index 1 in RGB, i.e. Green to zero.
			outImage->color[0][i][j] = inImage->color[0][i][j]; //Keep other colors the same as inImage
			outImage->color[2][i][j] = inImage->color[2][i][j]; //Keep other colors the same as inImage
		}
	}
}

void blue_filter(cs1300bmp *inImage, cs1300bmp *outImage) {
	outImage->width = inImage->width; //Set the width of outImage to be the same as inImage.
	outImage->height = inImage->height; //Set the height of outImage to be the same as inImage.

	int rows = outImage->height; //Each pixel takes up one row/col cell in the 2D array
	int cols = outImage->width;  //Each pixel takes up one row/col cell in the 2D array

	for (int i = 0; i <= rows; ++i) {     //Looping through every row
		for (int j = 0; j <= cols; ++j) { //Looping through every col
			outImage->color[2][i][j] = 0; //Set index 1 in RGB, i.e. Blue to zero.
			outImage->color[1][i][j] = inImage->color[1][i][j]; //Keep other colors the same as inImage
			outImage->color[0][i][j] = inImage->color[0][i][j]; //Keep other colors the same as inImage
		}
	}
}


int
main(int argc, char *argv[]) {
	//	This is how you mention the file name.
	//	for the images that you need to read and
	//	write as mentioned in the project PART 1.A
	//	description.
	string inputfilename = "images/bmp/1.bmp";
	//	Output file name for the red filter image.
	string outputfilename_red_filter = "images/part_1/1_red_filter.bmp";
	//	Output file name for the red filter image.
	string outputfilename_blue_filter = "images/part_1/1_blue_filter.bmp";
	//	Output file name for the red filter image.
	string outputfilename_green_filter = "images/part_1/1_green_filter.bmp";

	cout << "Read file " << inputfilename << endl;
	//	Below, we have declared
	//	the structure where you will read the
	//	file mentioned.
	cs1300bmp *inImage = new cs1300bmp;

	//	Similarly create a structure which will hold the
	//	modified image data.
	cs1300bmp *outImage = new cs1300bmp;

	// Read the file to be filtered
	int result = cs1300bmp_readfile(inputfilename, inImage);

	if ( result ) {
		cout << "Adding Red Filter" << endl;
		red_filter(inImage, outImage);
		cout << "Writing output image to " << outputfilename_red_filter << endl;
		cs1300bmp_writefile(outputfilename_red_filter, outImage);
		cout << "Writing output image to " << outputfilename_green_filter << endl;
		cs1300bmp_writefile(outputfilename_green_filter, outImage);
		cout << "Writing output image to " << outputfilename_blue_filter << endl;
		cs1300bmp_writefile(outputfilename_blue_filter, outImage);
	}
    else {
        cout << "Unable to read image" << endl;
    }
    cout << "Deleting image" << endl;
    delete inImage;
    delete outImage;

    return 0;
}
