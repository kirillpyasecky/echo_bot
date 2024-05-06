cmake_minimum_required(VERSION 3.10)
project(echo_bot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/config.json
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include(FetchContent)
FetchContent_Declare(tgbotxx
        GIT_REPOSITORY "https://github.com/baderouaich/tgbotxx"
        GIT_TAG         main
)

FetchContent_Declare(json 
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)

FetchContent_Declare(spdlog
		GIT_REPOSITORY https://github.com/gabime/spdlog.git
		GIT_TAG v1.3.1
)

FetchContent_MakeAvailable(tgbotxx json spdlog)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC tgbotxx)
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)
