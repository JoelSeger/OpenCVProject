// Written by Joel 30/09
// Stage 4

#include "ContourDetection.h"

// OpenCV 5 moved contourArea/approxPolyDP/getPerspectiveTransform/solvePnP into
// the geometry module, which <opencv2/opencv.hpp> no longer includes.
#if CV_VERSION_MAJOR >= 5
#include <opencv2/geometry.hpp>
#endif

ContourDetection::ContourDetection() {}

std::vector<cv::Point> ContourDetection::extractContour(const cv::Mat& binary, const cv::Rect& rect) {
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(binary(rect), contours, cv::RETR_EXTERNAL,
                     cv::CHAIN_APPROX_NONE, rect.tl());

    // Follow one connected boundary, excluding separate objects inside the box.
    std::vector<cv::Point> contour;
    double largestArea = 0.0;
    for (const auto& candidate : contours) {
        const double area = cv::contourArea(candidate);
        if (area > largestArea) {
            largestArea = area;
            contour = candidate;
        }
    }
    return contour;
}
