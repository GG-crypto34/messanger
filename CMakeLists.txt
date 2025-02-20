cmake_minimum_required(VERSION 3.16)

# Название проекта
project(messanger)

# Указание на использование C++ стандарта
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск пакета Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets)


# Подключение библиотек Qt
#target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

add_subdirectory(client)
add_subdirectory(server)
