cmake_minimum_required(VERSION 3.19)
project(Peyot)

set(CMAKE_CXX_STANDARD 17)
find_package (Threads)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread(-D_REENTRANT, -lpthread)")

add_executable(PeyotServer server/main.cpp server/Server.cpp server/Server.h communication/Sender.cpp communication/Sender.h communication/Receiver.cpp communication/Receiver.h server/ConnectionHandler.cpp server/ConnectionHandler.h server/database/DBManager.cpp server/database/DBManager.h server/eventLog/ELManager.h server/eventLog/ELManager.cpp)
add_executable(PeyotClient client/main.cpp client/Client.cpp client/Client.h communication/Sender.cpp communication/Sender.h communication/Receiver.cpp communication/Receiver.h)

target_link_libraries (PeyotServer ${CMAKE_THREAD_LIBS_INIT})