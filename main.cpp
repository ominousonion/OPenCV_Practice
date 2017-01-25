#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char** argv)
{
	Mat frame;
	VideoCapture video("../data/ted.mp4");

	if (!video.isOpened()) {
		cout << "Cannot open the video" << endl;
		return -1;
	}
	
	VideoCapture camera(0);

	if (!camera.isOpened()) {
		cout << "Cannot open the camera" << endl;
		return -1;
	}

	for (;;) {
		Mat frame_camsrc;
		Mat frame_camdst;
		Mat frame_ROI;
		video.read(frame);
		camera >> frame_camsrc;

		if (frame.rows > 0) {
			resize(frame_camsrc, frame_camdst, Size(frame.cols / 4, frame.rows / 3));
			frame_ROI = frame(Rect(0, 0, frame_camdst.cols, frame_camdst.rows));
			addWeighted(frame_ROI, 0, frame_camdst, 1, 0, frame_ROI);
			imshow("Video Frame", frame);
		}
		else {
			break;
		}

		if (waitKey(30) == 27) {
			break;
		}
	}
	return 0;
}