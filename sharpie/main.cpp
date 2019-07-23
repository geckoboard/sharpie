#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <unistd.h>

using namespace std;

int main(int argc, const char * argv[]) {
    cv::VideoCapture cap;
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);

    try {
    cap.open(0);
    if (!cap.isOpened()) return -1;  // check if there is no video or no way to display it
    } catch (exception e) {
        return -1;
    }
    
    // create a window and display the video capture
    cv::namedWindow("out", cv::WINDOW_NORMAL);
    
    while(cap.grab()) {
        cv::Mat image, workingImageCopy;
        
        cap.retrieve(image);
        image.copyTo(workingImageCopy);
        
        std::vector<int> ids;
        std::vector<std::vector<cv::Point2f> > corners;
        cv::aruco::detectMarkers(image, dictionary, corners, ids);
        
        if (ids.size() > 0) {
            cv::aruco::drawDetectedMarkers(workingImageCopy, corners, ids);
            
            std::vector<cv::Point2f> allCorners;
            
            for ( std::vector<cv::Point2f> marker : corners ) {
                for (cv::Point2f corner : marker) {
                    allCorners.push_back(corner);
                }
            }
            
            cv::Rect r = cv::boundingRect(allCorners);
            
			cv::rectangle(workingImageCopy, r, (5,255,255));
        }
        
        cv::imshow("out", workingImageCopy);
        
        cv::waitKey(500);
    }
    
    return 0;
}


void writeMarker() {
    cv::Mat markerImage;
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
    cv::aruco::drawMarker(dictionary, 1, 200, markerImage, 1);
}
