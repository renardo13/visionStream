# VisionStream – Real-Time Micro-Movement Detection

![computerVision](https://github.com/user-attachments/assets/2298eabe-d166-4dd4-b981-424e11efae65)

<img center="yes" width="250" height="250" alt="Screenshot from 2025-10-20 15-38-52" src="https://github.com/user-attachments/assets/04e1d04a-b2e5-4d5e-b55c-bb2a01b84078" />

**VisionStream** is a lightweight C++ application that detects subtle movements in video streams or webcam feeds in real time. Using OpenCV’s background subtraction and contour analysis, it highlights micro-movements like blinking eyes, small gestures, or slight object shifts. The application stabilizes detection over multiple frames to reduce noise and clearly visualizes moving regions with contours and bounding boxes.

Designed for creative and experimental purposes, VisionStream can be used in **art installations**, **projection mapping**, or **gesture-based interaction systems**. It is fully CPU-compatible, but can optionally leverage a CUDA-enabled GPU for higher performance if compiled with OpenCV’s CUDA modules.

## Features

- Real-time detection of micro-movements
- Foreground mask and contour visualization
- Resizable display windows
- Easy-to-use webcam or video file input
- CPU-only default, optional GPU acceleration with CUDA

## Installation

### Prerequisites

- Ubuntu 20.04+ or similar Linux
- C++17 compatible compiler (GCC/Clang)
- OpenCV 4.5+ installed (CPU-only or with CUDA for GPU)
- CMake 3.10+

### Build Instructions

```bash
# Clone the repository
git clone https://github.com/renardo13/visionStream
cd VisionStream

# Create a build directory
mkdir build && cd build

# Configure the project
cmake ..

# Build the application
make -j$(nproc)
