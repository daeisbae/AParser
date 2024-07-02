# Use an official GCC image as a parent image
FROM gcc:latest

# Set the working directory in the container
WORKDIR /usr/src/AParser

# Copy the current directory contents into the container at /usr/src/AParser
COPY . /usr/src/AParser

# Install CMake
RUN apt-get update && \
    apt-get install -y cmake && \
    rm -rf /var/lib/apt/lists/*

# Build the project
RUN cmake . && cmake --build .

# Make the AParser executable runnable
RUN chmod +x AParser

# Command to run the application
CMD ["./AParser"]