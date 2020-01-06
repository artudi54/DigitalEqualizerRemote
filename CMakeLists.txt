cmake_minimum_required(VERSION 3.10)
project(DigitalEqualizerRemote VERSION 1.0.0 LANGUAGES CXX)

# Dependencies
find_package(Qt5 HINTS $ENV{QTDIR} COMPONENTS Bluetooth Core Gui Qml Quick REQUIRED)
add_subdirectory(lib/player-protocol)

# Executable
set(SOURCES
    src/main.cpp
)
set(HEADERS
        src/model/PlayerModel.cpp src/model/PlayerModel.hpp src/model/PlayState.hpp src/DigitalEqualizerRemoteApplication.cpp src/DigitalEqualizerRemoteApplication.hpp src/communication/ResponseHandler.cpp src/communication/ResponseHandler.hpp src/communication/DeviceConnector.cpp src/communication/DeviceConnector.hpp src/communication/CommunicationProvider.cpp src/communication/CommunicationProvider.hpp src/communication/RequestSender.cpp src/communication/RequestSender.hpp src/model/ConnectionModel.cpp src/model/ConnectionModel.hpp)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Compile options
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
)
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Wconversion -Wsign-conversion)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(IGNORED_WARNINGS /wd4514 /wd4571 /wd4623 /wd4625 /wd4626 /wd4668 /wd4710 /wd4774 /wd4820 /wd5026 /wd5027 /wd5045)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /Wall /Za /permissive- ${IGNORED_WARNINGS})
    target_compile_definitions(${PROJECT_NAME} PRIVATE -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS -D_SCL_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS)
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    AUTORCC ON
)

# Include directories
target_include_directories(${PROJECT_NAME}
PRIVATE
    src
)

target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Bluetooth Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick player-protocol)

