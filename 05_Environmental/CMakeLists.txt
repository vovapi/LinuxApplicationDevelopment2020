cmake_minimum_required(VERSION 2.8.12.2)

project(05-Environmental)

add_executable(Window Window.c)

find_package(Curses REQUIRED)
find_library(PCRE2_LIBRARY pcre2-8)

find_path(PCRE2_INCLUDE_DIRS pcre2.h)
find_path(LOCALE_INCLUDE_DIRS locale.h)

include_directories(${CURSES_INCLUDE_DIR} ${PCRE2_INCLUDE_DIRS} ${LOCALE_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(Window ${CURSES_LIBRARY} ${PCRE2_LIBRARY})

option(WITHOUT_UTF "without-UTF" OFF)

set(GENERATES CMakeCache.txt CMakeFiles cmake_install.cmake config.h Makefile)
add_custom_target(allclean)
add_custom_command(
	TARGET    allclean
	COMMAND   rm -rf ${GENERATES}
)

configure_file(config.h.in config.h)