/*
 * colors.cpp
 *
 *  Created on: Sep 6, 2018
 *      Author: lab
 */


#include <opencv2/opencv.hpp>

using namespace cv;

struct colorNode
{
	Scalar color;
	colorNode* next;
};

class colorList {

	colorNode *colors_head;
	colorNode *curr_color;

public:
	colorList() {
		colors_head = new colorNode;
		//PINK
		colors_head->color = Scalar(255,100,255);
		curr_color = colors_head;
		//YELLOW
		colorNode* temp = new colorNode;
		temp->color = Scalar(100,255,255);
		curr_color->next = temp;
		curr_color = curr_color->next;
		//TURQUOISE
		temp = new colorNode;
		temp->color = Scalar(255,255,100);
		curr_color->next = temp;
		curr_color = curr_color->next;
		//WHITE
		temp = new colorNode;
		temp->color = Scalar(255,255,255);
		curr_color->next = temp;
		curr_color = curr_color->next;

		curr_color->next = colors_head;
		curr_color = colors_head;
	}

	Scalar next() {
		curr_color = curr_color->next;
		return curr_color->color;
	}

	Scalar getColor() {
		return curr_color->color;
	}
};

