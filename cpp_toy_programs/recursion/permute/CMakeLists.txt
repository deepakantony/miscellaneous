CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (permute)

ADD_LIBRARY (PermuteLib Permute.cpp)
ADD_EXECUTABLE (Permute PermuteMain.cpp)
TARGET_LINK_LIBRARIES (Permute PermuteLib)
