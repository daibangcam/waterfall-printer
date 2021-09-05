#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\opencv.hpp>
#include "HanO.h"

using namespace cv;
using namespace std;

// number of valves on 1m length
#define valve_per_length 64
// size of water curtain
#define water_width 2000
#define water_height 2000
// size of display panel
#define disp_width 700
#define disp_height 500
// input scale
#define scale_input 10

//	function
void water_curtain(Mat src, int num);

// declare
unsigned char img[disp_height][disp_width];
unsigned char tmp[disp_height][disp_width];

void main()
{
	// init array
	for (int i = 0; i < disp_height; i++)
	{
		for (int j = 0; j < disp_width; j++)
		{
			img[i][j] = tmp[i][j] = 255;
		}
	}
	//	intro
	intro(300);
	//	load image
	Mat end_img = imread("0.png");
	Mat src_1 = imread("1.png");
	Mat src_2 = imread("2.png");	
	//
	water_curtain(src_1, 1);
	water_curtain(src_2, 2);
	water_curtain(end_img, 1);
	//
	waitKey();
}

void water_curtain(Mat src, int num)
{
	//
	//	=== INIT SETUP ===
	//
	int num_line = 0;

	//
	//	=== DISPLAY INPUT IMAGE ===
	//
	Mat src1;
	cvtColor(src, src1, CV_BGR2GRAY);
	Mat src_temp;
	Size src_temp_size(src.cols / scale_input, src.rows / scale_input);
	resize(src, src_temp, src_temp_size);
	imshow("Input Image", src_temp);

	//
	//	=== SCALE TO VALVE RESOLUTION ===
	//
	Mat src2;
	src2.cols = round(water_width / 1000 * valve_per_length);
	src2.rows = round(water_height / 1000 * valve_per_length);
	//src2.rows = round(src1.rows * src2.cols / src1.cols);
	resize(src1, src2, src2.size());
	//imshow("Valve Image", src2);
	//cout << "src2_size = " << src2.cols << " x " << src2.rows << endl; 
	//waitKey();
	//
	//	=== CONVERT TO REAL VALVE RESOLUTION ===
	//
	Mat src3_temp;
	Size src3_temp_size(src2.cols, 2 * src2.rows);
	resize(src2, src3_temp, src3_temp_size);
	//imshow("real", src3_temp);
	//waikey();
	Mat src3;
	Size src3_size(2 * src3_temp.cols, src3_temp.rows);
	src3 = Mat::zeros(src3_size, CV_8UC1);
	//
	for (int i = 0; i < src3_temp.rows; i++)
	{
		for (int j = 0; j < src3_temp.cols; j++)
		{
			src3.at<uchar>(i, 2 * j + 1) = 255;
			src3.at<uchar>(i, 2 * j) = src3_temp.at<uchar>(i, j);
		}
	}
	//imshow("Real Image", src3);
	//cout << "src3_size = " << src3.cols << " x " << src3.rows << endl; 
	//waitKey();
	//	
	//	=== SCALE TO DIGITAL WATER CURTAIN RESOLUTION ===
	//	
	Mat src4;
	Size src4_size(disp_width, disp_height);
	resize(src3, src4, src4_size);
	//imshow("Water Image", src4);
	//cout << "src4_size = " << src4.cols << " x " << src4.rows << endl; 
	//waitKey();
	//	
	//	=== STORE IMAGE TO ARRAY ===
	//	
	for (int i = 0; i < disp_height; i++)
	{
		for (int j = 0; j < disp_width; j++)
		{
			img[i][j] = src4.at<uchar>(i, j);
		}
	}
	//
	//	=== MAIN PROCESS ===
	//	
	for (int l = 0; l < num; l++)
	{
		for (int h = disp_height - 1; h >= 0; h--)
		{
			for (int i = disp_height - 1; i > 0; i--)
			{
				for (int j = 0; j < disp_width; j++)
				{
					tmp[i][j] = tmp[i - 1][j];
				}
			}
			for (int k = 0; k < disp_width; k++)
			{
				tmp[0][k] = img[h][k];
			}
			//cout << "Line:\t" << num_line << endl;
			//num_line++;
			Mat dst(disp_height, disp_width, CV_8UC1, tmp);
			imshow("Digital Waterfall Curtain", dst);
			waitKey(1);
		}
	}
}

