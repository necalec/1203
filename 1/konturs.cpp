#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

RNG rng(12345);

int one = 5;
int two = 20;

void onTrackbar(int, void*) {}

string getShapeName(int sides) {
    if (sides == 3)
        return "triangle";
    else if (sides == 4)
        return "rectangle";
    else
        return "circle";
}

int main()
{
    string way = "notme.png";

    Mat img_show = imread(way, 1);

    if (img_show.empty()) {
        cout << "nothing!" << endl;
        return 0;
    }
    else {
        cout << "norm" << endl;
    }

    resize(img_show, img_show, Size(img_show.cols, img_show.rows));

    Mat gray;
    Mat new_img;
    Mat gauss;
    Mat drawing;

    cvtColor(img_show, gray, COLOR_BGR2GRAY, 0);
    GaussianBlur(gray, gauss, Size(7, 7), 0);

    namedWindow("drawing");
    createTrackbar("1", "drawing", &one, 100, onTrackbar);
    createTrackbar("2", "drawing", &two, 100, onTrackbar);

    while (true) {
        Canny(gauss, new_img, one, two, 3);

        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        findContours(new_img, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

        cvtColor(new_img, drawing, COLOR_GRAY2BGR);

        for (size_t i = 0; i < contours.size(); i++)
        {
            vector<Point> approx;
            approxPolyDP(contours[i], approx, arcLength(contours[i], true) * 0.02, true);

            Moments M = moments(approx);
            Point2f center(M.m10 / M.m00, M.m01 / M.m00);

            string shapeName = getShapeName(approx.size());

            putText(drawing, shapeName, center, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 2);
        }

        imshow("drawing", drawing);

        int key = waitKey(30);
    }

    return 0;
}

