#!/bin/bash
# run.sh - Compile and run VisionStream CPU-only

set -e  # Exit on error

# Default video source: empty = webcam
VIDEO_SOURCE="$1"

echo "🌟 Creating build directory..."
mkdir -p build
cd build

echo "⚙️ Running CMake..."
cmake ..

echo "🛠 Building project..."
make -j$(nproc)

echo "🚀 Running VisionStream..."
if [ -z "$VIDEO_SOURCE" ]; then
    ./app
else
    ./app "$VIDEO_SOURCE"
fi
