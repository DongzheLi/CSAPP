FROM ubuntu:22.04

# Install only what's needed for CSAPP labs
RUN apt-get update && apt-get install -y \
    clang \
    clang-format \
    make \
    python3 \
    perl \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /labs

# Default command
CMD ["/bin/bash"]
