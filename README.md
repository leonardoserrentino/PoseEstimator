# 📌 Pose Visualization via Clicked Points (solvePnP + OpenCV)

This is a minimal OpenCV application in C++ that demonstrates pose estimation using `cv::solvePnP` and manual point selection from a webcam feed.

It lets you:
- Click 4 points in the image corresponding to known 3D coordinates
- Estimate the 3D pose of a planar object (e.g., square marker)
- Visualize the camera pose by projecting the X, Y, Z axes onto the image

---

## 📸 How It Works

1. Opens the webcam.
2. Lets you click on 4 image points (in order) corresponding to known real-world 3D points.
3. Estimates pose using OpenCV's `solvePnP`.
4. Projects 3D axes onto the image:
   - 🔴 X axis = red
   - 🟢 Y axis = green
   - 🔵 Z axis = blue (pointing outward)

---

## 🧱 Requirements

- OpenCV 4.x
- C++17
- A working webcam

---

## 🛠️ Build

```bash
g++ main.cpp -o pose_axes `pkg-config --cflags --libs opencv4` -std=c++17
```

## ▶️ Run

```bash
./pose_axes
```

Then:
1. Click on 4 image points (corners of a known square)
2. Watch the axes appear once 4 points are selected
(2b). Press R to reset
3. Press ESC to quit

## 📄 License

MIT License — free for academic and commercial use.
