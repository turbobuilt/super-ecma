#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

# Define build directory
BUILD_DIR="build_test" # Use a separate build directory for tests if desired

# Clean the build directory first
echo "Cleaning previous build..."
rm -rf $BUILD_DIR

# Configure CMake
echo "Configuring CMake..."
cmake -S . -B $BUILD_DIR -DCMAKE_BUILD_TYPE=Debug # Add Debug flag for potentially better test debugging

# Build the tests
echo "Building tests..."
cmake --build $BUILD_DIR

# Run the tests using CTest
echo "Running tests..."
cd $BUILD_DIR
ctest --output-on-failure # Show output only if tests fail
cd ..

# Optional: Clean up the build directory
# echo "Cleaning up..."
# rm -rf $BUILD_DIR

echo "Test run complete."
