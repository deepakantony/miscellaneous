CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (combination)

ADD_LIBRARY (CombinationLib Combination.cpp)
ADD_EXECUTABLE (combination CombinationMain.cpp)
TARGET_LINK_LIBRARIES (combination CombinationLib)
