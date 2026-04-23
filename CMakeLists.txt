cmake_minimum_required(VERSION 3.10)
project(str_problem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the main executable (assuming there's a main.cpp for testing)
# The OJ system expects an executable named "code"
add_executable(code main.cpp)
