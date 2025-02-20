cmake_minimum_required(VERSION 3.16)

# Название проекта
project(server)

set(CMAKE_AUTOMOC ON)       # Включает автоматическую генерацию .moc-файлов
set(CMAKE_AUTORCC ON)       # Включает автоматическую обработку .qrc-файлов
set(CMAKE_AUTOUIC ON)       # Включает автоматическую обработку .ui-файлов

# Указание на использование C++ стандарта
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск пакета Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

add_executable(server
                main.cpp
                server.h server.cpp
                user.h user.cpp

                factory/acceptname.h )


# Подключение библиотек Qt
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Network)
