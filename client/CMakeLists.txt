INCLUDE_DIRECTORIES(include)
FILE(GLOB SOURCES src/*.cpp)
ADD_EXECUTABLE(client client.cpp ${SOURCES})
TARGET_LINK_LIBRARIES(client network graphics)