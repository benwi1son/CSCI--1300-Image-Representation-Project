//Part 3
#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <string.h>
#include "cs1300bmp.h"
#include "cs1300bmp.cc"
#define CHANNELS 3

/*
	Do the following operations on each of the bmp's
	placed in the images/part3/ folder.
	1.	invert ( this operation makes the images look like
		a negative that we used to have in the 90's.).
	2.	horizontal flip.
	3.	vertical flip.
*/

/*

	*************************************************************
							TODO SWAP
	*************************************************************

	Implement the swap function.
	It takes 2 integers by reference and
	exchanges the values with each other.
	For example:
	a = 12, b = 34
	after swap:
	a = 34, b = 12.

	Pay attention to the pointers.
*/
void
swap(int &a, int &b) {
    int c=a;
    a=b;
    b=c;
}

/*
	*************************************************************
							TODO SWAP ENDS
	*************************************************************
*/


/*

	*************************************************************
							TODO INVERT
	*************************************************************

	Manipulate the _image->color array such that the image
	is inverted.

	HINT: to invert an image, just subtract the image
	intensity from the maximum possible intensity possible
	i.e. 255.
*/
void
invert(cs1300bmp *_image) {
	int rows = _image->height; //Each pixel takes up one row/col cell in the 2D array
	int cols = _image->width;  //Each pixel takes up one row/col cell in the 2D array

	for (int i = 0; i <= rows; ++i) {     //Looping through every row
		for (int j = 0; j <= cols; ++j) { //Looping through every col
                for (int c=0;c<3;c++)
                    _image->color[c][i][j] = 255-_image->color[c][i][j]; //color to be inverted
		}
	}

}
/*
	*************************************************************
						TODO INVERT ENDS
	*************************************************************
*/

/*
	The function below, h_flip flips the _inimage across the
	horizontal axis. You can run the script and see how the image
	looks.
*/
void
h_flip(cs1300bmp *_inImage) {
	for (int row = 0; row < _inImage->height; ++row) {
		for (int col = 0; col < _inImage->width/2; ++col) {
			for (int channel = 0; channel < CHANNELS; ++channel) {
				swap(_inImage->color[channel][row][col], _inImage->color[channel][row][_inImage->width - col]);
			}
		}
	}
}


/*

	*************************************************************
							TODO V_FLIP
	*************************************************************

	Implement the v_flip function so that the
	_inImage is flipped by the vertical axis.

	You can take inspiration from the h_flip function above.

	HINT: You'll have to use the swap function that
	you implemented above.
*/
void
v_flip(cs1300bmp *_inImage) {
	for (int row = 0; row < _inImage->height/2; ++row) {
		for (int col = 0; col < _inImage->width; ++col) {
			for (int channel = 0; channel < CHANNELS; ++channel) {
				swap(_inImage->color[channel][row][col], _inImage->color[channel][_inImage->height - row][col]);
			}
		}
	}

}
/*
	*************************************************************
							TODO V_FLIP ENDS
	*************************************************************
*/

int
main(int argc, char *argv[]) {

	string image_file_name = "images/bmp/1.bmp";
	string invert_file_name = "images/part_3/1_inverted.bmp";
	string h_flip_file_name = "images/part_3/1_h_flipped.bmp";
	string v_flip_file_name = "images/part_3/1_v_flipped.bmp";

	cs1300bmp *inImage = new cs1300bmp;

	cs1300bmp_readfile(image_file_name, inImage);
	invert(inImage);
	cs1300bmp_writefile(invert_file_name, inImage);

	h_flip(inImage);
	cs1300bmp_writefile(h_flip_file_name, inImage);

	v_flip(inImage);
	cs1300bmp_writefile(v_flip_file_name, inImage);

	return 0;
}

