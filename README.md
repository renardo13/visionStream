# VisionStream – Real-Time Micro-Movement Detection

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
git clone https://github.com/<your-username>/VisionStream.git
cd VisionStream

# Create a build directory
mkdir build && cd build

# Configure the project
cmake ..

# Build the application
make -j$(nproc)
