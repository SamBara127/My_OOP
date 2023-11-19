# CMakeList.txt: проект CMake для Laboratory_2; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Laboratory_2 "Laboratory_2.cpp" "Laboratory_2.h" "circ_buf.cpp" "circ_buf.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Laboratory_2 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
