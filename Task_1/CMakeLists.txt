# CMakeList.txt: проект CMake для hometask_env; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (hometask_env "hometask_env.cpp" "hometask_env.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET hometask_env PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
