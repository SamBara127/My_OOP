# CMakeList.txt: проект CMake для task_1; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (task_1 "task_1.cpp" "task_1.h" "graphic.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET task_1 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.

target_link_libraries(task_1 PUBLIC 
	matplot
)
