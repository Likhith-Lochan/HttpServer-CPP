# 🧠 C++ Multithreaded HTTP Server

This is a low-level multithreaded HTTP server built in **C++** using **POSIX sockets** and **standard libraries**. It handles HTTP requests manually without using external frameworks or libraries — offering an in-depth understanding of how web servers work under the hood.

Each client connection is handled in a **separate thread**, allowing the server to respond to multiple concurrent HTTP requests. The project is fully **Dockerized** and can be built and run using a one-command shell script.

---

## 🏗️ Project Structure

- 📂 cpp-http-server/
- ├── include/
- │ └── HttpServer.hpp # Header file for the HttpServer class
- │ ├── HttpServer.cpp # Main server logic with threading and socket handling
- │ └── main.cpp # Program entry point
- ├── Dockerfile # Docker container setup
- ├── run_server.sh # Shell script to build and run the server
- ├── CMakeLists.txt # CMake configuration
- └── README.md # You're here!

---


---

## 🚀 How to Run Locally

### ✅ Requirements

- [Docker](https://www.docker.com/) installed and running
- Bash shell (Linux, macOS, or Git Bash on Windows)

---

### 🔧 Step 1: Clone the Repository

```bash
git clone https://github.com/Likhith-Lochan/HttpServer-CPP
cd http_server

./run_server.sh

