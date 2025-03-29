# 🎯 PoseEstimator – Camera Pose Estimation Utility in C++ with OpenCV

**PoseEstimator** is a reusable C++ class built on OpenCV for estimating the 3D pose of planar or rigid objects from 2D-3D point correspondences using `cv::solvePnP`.  

It provides a clean, modular interface for:
- Setting camera intrinsics and distortion
- Assigning 3D model points and 2D image projections
- Solving for the object's rotation and translation vectors
- Projecting any 3D point into image space
- Integrating into industrial or real-time CV pipelines

---

## ✅ Features

- 🔁 Easy to integrate in threaded or modular CV pipelines
- 📸 Supports camera matrix + distortion coefficients
- 📐 Uses OpenCV's `solvePnP` for pose estimation
- 🧮 Projects 3D world points into 2D with `projectPoints`
- 🧩 Lightweight and header-based API
- 🧪 Ideal for object alignment, robot vision, pose debugging

---

## 📁 File Structure

```txt
/PoseEstimator
  ├── PoseEstimator.h # Class interface
  ├── PoseEstimator.cpp # Implementation
  └── main.cpp # Example usage
```


---

## 🧠 Use Case Examples

- Estimate the pose of a part using 4-6 corner points
- Project 3D axes or CAD points over a live camera image
- Align real-world objects with a robot manipulator
- Debug calibration and camera alignment
- Replace ArUco detection when markers are not available

---

## 🔧 Dependencies

- OpenCV 4.x
- C++17 standard or newer
- No external dependencies

---

## 🛠️ Build

```bash
g++ main.cpp PoseEstimator.cpp -o pose_estimator `pkg-config --cflags --libs opencv4` -std=c++17
```

## 📌 Example Usage

```cpp
PoseEstimator pose;
pose.setCameraParameters(cameraMatrix, distortion);
pose.setCorrespondences(objectPoints3D, imagePoints2D);

if (pose.computePose()) {
    std::cout << "Rotation Vector: " << pose.getRvec() << "\n";
    std::cout << "Translation Vector: " << pose.getTvec() << "\n";

    std::vector<cv::Point3f> axes = { {30,0,0}, {0,30,0}, {0,0,-30} };
    std::vector<cv::Point2f> projected;
    pose.projectPoints(axes, projected);
}
```

## 🔄 Future Extensions

- Visualizer: PoseVisualizer for drawing axes and overlays
- Multiple object pose management
- Time-series logging and CSV/JSON export
- Integration with OpenCV ArUco or feature trackers
