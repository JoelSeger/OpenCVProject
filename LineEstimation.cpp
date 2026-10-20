// Writen by Joel Seger 30/09
// Stage 5 and 6

#include "LineEstimation.h"
#include <algorithm>

LineEstimation::LineEstimation() {}

std::vector<cv::Point> LineEstimation::findCorners(const std::vector<cv::Point>& contour) {
    if (contour.size() < 4) return {};

    // Approximate the boundary itself; diagonal extrema can select the same corner.
    std::vector<cv::Point> corners;
    cv::approxPolyDP(contour, corners, 0.02 * cv::arcLength(contour, true), true);
    if (corners.size() != 4) return {};

    // Clockwise in image coordinates, starting nearest the image top-left.
    if (cv::contourArea(corners, true) < 0)
        std::reverse(corners.begin(), corners.end());
    auto first = std::min_element(corners.begin(), corners.end(),
        [](const cv::Point& a, const cv::Point& b) {
            return a.x + a.y < b.x + b.y;
        });
    std::rotate(corners.begin(), first, corners.end());

    return corners;
}

int findClosestIndex(const std::vector<cv::Point>& contour, const cv::Point& corner) {
    int bestIdx = 0;
    double minDist = 1e9;
    
    for (size_t i = 0; i < contour.size(); ++i) {
        double dist = cv::norm(contour[i] - corner);
        if (dist < minDist) {
            minDist = dist;
            bestIdx = i;
        }
    }
    return bestIdx;
}


std::vector<std::vector<cv::Point>> LineEstimation::makeSegments(std::vector<cv::Point>& corners, const std::vector<cv::Point>& contour) {
    std::vector<std::vector<cv::Point>> segments(4); // 0: Top, 1: Right, 2: Bottom, 3: Left
    if (corners.size() != 4 || contour.empty()) return segments;

    // center of quad
    cv::Point center(0, 0);
    for (const auto& c : corners) {
        center += c;
    }
    center.x /= 4;
    center.y /= 4;

    for (const auto& pt : contour) { 
        int bestEdge = 0;
        double minDistance = 1e9;

        for (int i = 0; i < 4; ++i) {
            cv::Point p1 = corners[i];
            cv::Point p2 = corners[(i + 1) % 4];
 
            double num = std::abs((p2.y - p1.y) * pt.x - (p2.x - p1.x) * pt.y + p2.x * p1.y - p2.y * p1.x);
            double den = std::sqrt(std::pow(p2.y - p1.y, 2) + std::pow(p2.x - p1.x, 2));
            double dist = (den == 0) ? cv::norm(pt - p1) : num / den;

            if (dist < minDistance) {
                minDistance = dist;
                bestEdge = i;
            }
        }

        segments[bestEdge].push_back(pt);
    }

    return segments;
}

std::vector<Line> LineEstimation::findLine(const std::vector<std::vector<cv::Point>>& segments) {
    std::vector<Line> lines;

    for (const auto& segment : segments) {
        if (segment.size() < 2) {
            lines.push_back({0.0, 0.0}); // if segment is too small
            continue;
        }

        double N = segment.size();
        double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

        for (const auto& pt : segment) {
            sumX += pt.x;
            sumY += pt.y;
            sumXY += (double)pt.x * pt.y;
            sumX2 += (double)pt.x * pt.x;
        }

        double denominator = (N * sumX2) - (sumX * sumX);

        // denominator = 0, line is vertical
        if (std::abs(denominator) < 1e-5) {

            double avgX = sumX / N;
            lines.push_back({1e9, avgX});

        } else {

            double m = ((N * sumXY) - (sumX * sumY)) / denominator;
            double b = (sumY - (m * sumX)) / N;
            lines.push_back({m, b});
        }
    }
    return lines;
}
