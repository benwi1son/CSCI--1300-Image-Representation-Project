//Part 2
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
	Now, in PART 1. what you did is read data from an
	image file in bmp format and then modify the image
	by applying filters to it.

	But what if you dont have a bmp file and you have a jpeg
	or a png?

	In that case, you will have to copy data from a universal
	file format such as a csv (others do exist like .txt and .md)
	and then layer the data read from the csv into the cs1300bmp data
	structure.

	So, this function below does the following:
	1.	It reads a .csv file.
	2.	The data read from the .csv file is stored in the
		csvdata structure.
	3.	It then returns the csvdata structure holding the color
		information from the csv file in the same format as described
		in the CSV file.

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

/*
	*************************************************************
								TODO
	*************************************************************
	CAUTION: Before attempting to implement this function, go through
	section 4.3 of the supplied pdf.

	Implement the utility copy() below.

	The utility takes a csvdata structure and a cs1300bmp
	structure as arguments.

	It should copy the data from csvdata structure into the
	cs1300bmp structure.

	Make sure you initialize the height and width of the
	cs1300bmp structure using the ROWS and COLUMNS defined above
	(just like the red_filter does it in part_1).


*/
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
/*
	*************************************************************
								TODO ENDS
	*************************************************************
*/


int
main(int argc, char *argv[]) {
	/*

		The lines below convert each of the csv's present in the
		image_csv folder to the corresponding bmp images.
	*/
	string file_name = "image_csv/1.csv";
	string image_file_name = "images/part_2/1.bmp";
	/*
		The lines below uses the readData function to read the data from
		file_name csv file (declared above) into the
		csv_data structure declared below.
	*/
	csvdata *csv_data = new csvdata;
	int result = readData(csv_data, file_name);
	cout<<"Read "<<file_name <<endl;
	/*

		Use the copy function that you implemented
		to copy the data from the csv_data structure to the cs1300bmp
		structure.
	*/
	cs1300bmp *inImage = new cs1300bmp;
	copy(csv_data, inImage);

	/*
		Finally write the image data onto the disk.
	*/
	cs1300bmp_writefile(image_file_name, inImage);
	cout<<"Write "<<image_file_name <<endl;
    delete csv_data;
	delete inImage;

	return 0;
}

