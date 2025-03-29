#include <opencv2/opencv.hpp>
#include <iostream>

// Global vector to store 2D points clicked by the user
std::vector<cv::Point2f> clickedPoints;

// Mouse callback: stores up to 4 clicked points
void mouseCallback(int event, int x, int y, int flags, void*) {
    if (event == cv::EVENT_LBUTTONDOWN && clickedPoints.size() < 4) {
        clickedPoints.emplace_back(x, y);
        std::cout << "Clicked: " << x << ", " << y << std::endl;
    }
}

int main() {
    // Open webcam
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Cannot open webcam.\n";
        return -1;
    }

    cv::namedWindow("Camera");
    cv::setMouseCallback("Camera", mouseCallback);

    // Define known 3D object points (e.g., square 50x50 mm on a flat surface)
    std::vector<cv::Point3f> objectPoints = {
        {0, 0, 0},
        {50, 0, 0},
        {50, 50, 0},
        {0, 50, 0}
    };

    // Hypothetical camera intrinsic parameters (from calibration or approximation)
    cv::Mat cameraMatrix = (cv::Mat_<double>(3,3) <<
        800, 0, 320,
        0, 800, 240,
        0, 0, 1
    );
    cv::Mat distCoeffs = cv::Mat::zeros(5, 1, CV_64F);

    cv::Mat frame;

    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        // Draw the clicked points on the image
        for (const auto& pt : clickedPoints) {
            cv::circle(frame, pt, 5, cv::Scalar(0, 255, 255), -1);
        }

        // If exactly 4 points were clicked, estimate pose and draw 3D axes
        if (clickedPoints.size() == 4) {
            cv::Mat rvec, tvec;

            bool ok = cv::solvePnP(objectPoints, clickedPoints, cameraMatrix, distCoeffs, rvec, tvec);
            if (ok) {
                std::vector<cv::Point3f> axes = {
                    {30, 0, 0},    // X axis → red
                    {0, 30, 0},    // Y axis → green
                    {0, 0, -30}    // Z axis → blue (into the scene)
                };
                std::vector<cv::Point2f> imagePoints;
                cv::projectPoints(axes, rvec, tvec, cameraMatrix, distCoeffs, imagePoints);

                // Origin: first clicked point
                cv::Point2f origin = clickedPoints[0];
                cv::arrowedLine(frame, origin, imagePoints[0], cv::Scalar(0, 0, 255), 2);   // X = red
                cv::arrowedLine(frame, origin, imagePoints[1], cv::Scalar(0, 255, 0), 2);   // Y = green
                cv::arrowedLine(frame, origin, imagePoints[2], cv::Scalar(255, 0, 0), 2);   // Z = blue
            }
        }

        cv::imshow("Camera", frame);
        char key = (char)cv::waitKey(10);
        if (key == 27) break;                  // ESC = quit
        if (key == 'r') clickedPoints.clear(); // R = reset
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
