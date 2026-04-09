cmake_minimum_required(VERSION 3.14)

project (cpp-course)

set(CMAKE_PREFIX_PATH "external/")

find_package(SFML REQUIRED COMPONENTS graphics system window)

add_executable(app src/main.cpp "include/Application.h" "src/Application.cpp" "src/Figure.cpp" "include/Figure.h" "src/Button.cpp" "include/Button.h" "include/Label.h" "src/Label.cpp")

target_include_directories(app PRIVATE include)
target_link_libraries(app PRIVATE sfml-graphics sfml-system sfml-window)

add_custom_command(TARGET app POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/external/SFML/bin
	$<TARGET_FILE_DIR:app>
)


add_custom_command(TARGET app POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:app>/assets"
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${CMAKE_SOURCE_DIR}/assets"
	"$<TARGET_FILE_DIR:app>/assets"
)
