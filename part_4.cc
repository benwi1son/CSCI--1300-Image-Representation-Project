//Part 4
#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <string.h>
#include "cs1300bmp.h"
#include "cs1300bmp.cc"
#include "csvdata.h"
#define ROWS 128
#define COLUMNS 128
#define CHANNELS 3

using namespace std;

/*
	TODO
	Now we will put everything that we have learned together.
	Implement this script to do the following functions:
	1.	Read A CSV file from the image_csv folder.
	2.	Convert the read data to a bmp image by copying the
		data from the csv_data structure to the cs1300bmp
		structure.
	3.	Write the bmp to the disk.
	4.	Apply transformations such as:
		1. Invert
		2. Hflip
		3. VFlip
	5.	Save each of the above transformed images to the disk.


	You can reuse the functions from the parts 1, 2, 3.

*/

int readData(csvdata* _csv_data, string&  _file_name) {
	ifstream input_file_stream;
	input_file_stream.open(_file_name);

	int result = 0;
	int row_idx = 0, col_idx = 0;
	int value = 0;
	stringstream sstream;
	string line;
	char c;
	string color_value;
	while (!input_file_stream.eof()) {
		sstream.clear();
		getline(input_file_stream, line);
		sstream.str(line);
		col_idx = 0;

		while (sstream) {
			getline(sstream, color_value, ',');
			value = stoi(color_value);
			if (col_idx<COLUMNS)
                _csv_data->data[row_idx][col_idx] = value;
			col_idx += 1;
		}
		row_idx += 1;
		if (row_idx==ROWS*CHANNELS)
            break;
	}
	return result;
}

int
copy(csvdata *_csv_data, cs1300bmp *_image) {
    /*	Make sure you initialize the height and width of the
	cs1300bmp structure using the ROWS and COLUMNS defined above
	(just like the red_filter does it in part_1).
	*/
	_image->width = COLUMNS;
	_image->height = ROWS;

    for (int rc=0;rc<ROWS*CHANNELS;rc++) {
        for (int col=0;col<COLUMNS;col++) {
            int row=(int)(rc/3);   //Integer division gives the row
            int chan=(int) (rc%3); //Residual gives the channel
            _image->color[chan][row][col] = _csv_data->data[rc][col];
        }
    }

	return 0;
}

void
swap(int &a, int &b) {
    int c=a;
    a=b;
    b=c;
}

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

int
main(int argc, char *argv[]) {
	//1.	Read A CSV file from the image_csv folder.
	string file_name = "image_csv/2.csv";
	string image_file_name = "images/part_4/2.bmp";
	csvdata *csv_data = new csvdata;
	int result = readData(csv_data, file_name);

	//2.	Convert the read data to a bmp image by copying the
	//	data from the csv_data structure to the cs1300bmp
	//	structure.


	cout<<"Read "<<file_name <<endl;
	cs1300bmp *inImage = new cs1300bmp;
	copy(csv_data, inImage);

	//3.	Write the bmp to the disk.
	cs1300bmp_writefile(image_file_name, inImage);
	cout<<"Write "<<image_file_name <<endl;

	/*
	4.	Apply transformations such as:
		1. Invert
		2. Hflip
		3. VFlip
    */
	//5.	Save each of the above transformed images to the disk.
	string invert_file_name = "images/part_4/2_inverted.bmp";
	string h_flip_file_name = "images/part_4/2_h_flipped.bmp";
	string v_flip_file_name = "images/part_4/2_v_flipped.bmp";

	invert(inImage);
	cs1300bmp_writefile(invert_file_name, inImage);

	h_flip(inImage);
	cs1300bmp_writefile(h_flip_file_name, inImage);

	v_flip(inImage);
	cs1300bmp_writefile(v_flip_file_name, inImage);



    delete csv_data;
	delete inImage;


}

