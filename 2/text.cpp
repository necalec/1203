#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
    string way = "image.jpg";

    Mat img = imread(way, IMREAD_COLOR);

    if (img.empty())
    {
        cerr << "no!" << endl;
        return -1;
    }

    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    Mat binary;
    threshold(gray, binary, 60, 255, THRESH_BINARY);

    Mat inverted_binary;
    bitwise_not(binary, inverted_binary);

    Mat white_bg(img.size(), img.type(), Scalar(255, 255, 255));

    Mat gray_objects;
    addWeighted(img, 0.5, Scalar(200, 200, 200), 0.5, 0, gray_objects);

    gray_objects.copyTo(white_bg, inverted_binary);

    namedWindow("Original Image", WINDOW_AUTOSIZE);
    imshow("Original Image", img);

    namedWindow("Result Image", WINDOW_AUTOSIZE);
    imshow("Result Image", white_bg);

    waitKey(0);

    return 0;
}
//серый цвет чтобы делать расскраски