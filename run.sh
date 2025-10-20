#!/bin/bash
# run.sh - Download dependencies, compile and run VisionStream CPU-only

set -e  # Exit on error

# Default video source: empty = webcam
VIDEO_SOURCE="$1"

# -------------------------------
# Step 0: Install dependencies
# -------------------------------
echo "📦 Checking and installing dependencies..."
sudo apt update
sudo apt install -y build-essential cmake git pkg-config \
    libgtk-3-dev libavcodec-dev libavformat-dev libswscale-dev \
    libv4l-dev libxvidcore-dev libx264-dev libjpeg-dev libpng-dev libtiff-dev \
    gfortran openexr libatlas-base-dev python3-dev python3-numpy \
    libtbb-dev libdc1394-22-dev

# Optional: install OpenCV via apt if you don't want to build from source
# sudo apt install -y libopencv-dev python3-opencv

# -------------------------------
# Step 1: Download OpenCV if not already
# -------------------------------
if [ ! -d "../opencv" ]; then
    echo "🌟 Cloning OpenCV 4.9.0..."
    git clone -b 4.9.0 https://github.com/opencv/opencv.git ../opencv
fi

if [ ! -d "../opencv_contrib" ]; then
    echo "🌟 Cloning OpenCV contrib modules..."
    git clone -b 4.9.0 https://github.com/opencv/opencv_contrib.git ../opencv_contrib
fi

# -------------------------------
# Step 2: Create build directory
# -------------------------------
echo "🌟 Creating build directory..."
mkdir -p build
cd build

# -------------------------------
# Step 3: Run CMake with contrib modules
# -------------------------------
echo "⚙️ Running CMake..."
cmake ../opencv \
    -D CMAKE_BUILD_TYPE=Release \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D OPENCV_EXTRA_MODULES_PATH=../opencv_contrib/modules \
    -D BUILD_EXAMPLES=OFF \
    -D WITH_CUDA=OFF

# -------------------------------
# Step 4: Build
# -------------------------------
echo "🛠 Building project..."
make -j$(nproc)

# -------------------------------
# Step 5: Run
# -------------------------------
echo "🚀 Running VisionStream..."
if [ -z "$VIDEO_SOURCE" ]; then
    ./app
else
    ./app "$VIDEO_SOURCE"
fi
