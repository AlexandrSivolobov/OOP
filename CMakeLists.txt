cmake_minimum_required(VERSION 3.10)
project(PhoneBook)

set(CMAKE_CXX_STANDARD 11)

# Создаем директорию для данных
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/data)

# Источники
set(SOURCES
    src/main.cpp
    src/contact.cpp
    src/phonebook.cpp
    src/validator.cpp
)

set(HEADERS
    src/contact.h
    src/phonebook.h
    src/validator.h
)

add_executable(phonebook ${SOURCES} ${HEADERS})


target_include_directories(phonebook PRIVATE src)
