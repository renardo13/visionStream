// main.cpp - VisionStream CPU-only, micro-movement detection
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    std::string source = "";
    if (argc > 1) source = argv[1]; // video path

    cv::VideoCapture cap;
    if (source.empty()) {
        std::cout << "Trying to open webcam...\n";
        cap.open(0); // webcam
    } else {
        std::cout << "Trying to open video: " << source << "\n";
        cap.open(source);
    }

    if (!cap.isOpened()) {
        std::cerr << "Cannot open video source: " 
                  << (source.empty() ? "webcam" : source) << "\n";
        return -1;
    } else {
        std::cout << "Video source opened successfully.\n";
    }

    // ----------------------------
    // Background subtractor (MOG2)
    // ----------------------------
    cv::Ptr<cv::BackgroundSubtractorMOG2> bgSubtractor = cv::createBackgroundSubtractorMOG2();
    bgSubtractor->setDetectShadows(false); // disable shadows for micro-movement detection

    cv::Mat frame, fgMask, displayFrame;
    cv::Mat acc; // accumulator for stabilizing small movements

    cv::namedWindow("VisionStream - Contours", cv::WINDOW_NORMAL);
    cv::namedWindow("Foreground Mask", cv::WINDOW_NORMAL);

    // Make windows bigger at start
    cv::resizeWindow("VisionStream - Contours", 1280, 720);
    cv::resizeWindow("Foreground Mask", 640, 480);

    // Optional ROI for eyes or face (adjust as needed)
    cv::Rect roi; 
    bool useROI = false; // set true if you want to focus on a region

    while (true) {
        if (!cap.read(frame) || frame.empty()) break;

        cv::Mat procFrame = frame;
        if (useROI) procFrame = frame(roi);

        // Apply background subtraction
        bgSubtractor->apply(procFrame, fgMask);

        // ----------------------------
        // Post-processing for micro-movements
        // ----------------------------
        if (acc.empty()) acc = cv::Mat::zeros(fgMask.size(), CV_32F);
        cv::Mat fgFloat;
        fgMask.convertTo(fgFloat, CV_32F);
        cv::accumulateWeighted(fgFloat, acc, 0.5); // alpha=0.5
        cv::Mat stableMask;
        acc.convertTo(stableMask, CV_8U);
        cv::threshold(stableMask, stableMask, 15, 255, cv::THRESH_BINARY); // low threshold

        // Morphology to reduce noise
        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2,2));
        cv::morphologyEx(stableMask, stableMask, cv::MORPH_OPEN, kernel);
        cv::morphologyEx(stableMask, stableMask, cv::MORPH_CLOSE, kernel);

        // Find contours
        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::findContours(stableMask, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        displayFrame = frame.clone();

        // Draw contours, filter by area and ROI
        const double minArea = 10.0; // small movements like eyelids
        for (size_t i = 0; i < contours.size(); ++i) {
            double area = cv::contourArea(contours[i]);
            if (area < minArea) continue;

            // ROI filter
            if (useROI && (cv::boundingRect(contours[i]) & roi).area() == 0) continue;

            cv::drawContours(displayFrame, contours, static_cast<int>(i), cv::Scalar(0,255,0), 1);
            cv::Rect bbox = cv::boundingRect(contours[i]);
            cv::rectangle(displayFrame, bbox, cv::Scalar(255,0,0), 1);
            cv::putText(displayFrame, std::to_string(static_cast<int>(area)), bbox.tl() - cv::Point(0,4),
                        cv::FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar(0,255,255), 1);
        }

        // Display
        cv::imshow("Foreground Mask", stableMask);
        cv::imshow("VisionStream - Contours", displayFrame);

        char c = static_cast<char>(cv::waitKey(1));
        if (c == 27 || c == 'q') break;
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
