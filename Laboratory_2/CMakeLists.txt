# CMakeList.txt: проект CMake для Lesson_2a; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Lesson_2a "Lesson_2a.cpp" "Lesson_2a.h" "circ_buf.h" "circ_buf.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Lesson_2a PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
