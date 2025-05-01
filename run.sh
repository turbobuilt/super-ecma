#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

# Build the project
mkdir -p build
cd build
cmake ..
make

# Run the executable with the provided script or the default testprogram.ses
SCRIPT_FILE="../testprogram.ses"
if [ "$#" -gt 0 ]; then
    SCRIPT_FILE="$1"
fi

./superecma "$SCRIPT_FILE"

echo "Execution finished."
