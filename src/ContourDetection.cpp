// Written by Joel 30/09
// Stage 4

#include "ContourDetection.h"

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
