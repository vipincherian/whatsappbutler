cmake_minimum_required(VERSION 3.10)

# set the project name
project(WhatsButler)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add the executable
add_library(whatsbutler SHARED whatsbutler.c)

target_include_directories(whatsbutler PUBLIC
  /usr/include/libpurple
  /usr/include/glib-2.0
  /usr/lib/x86_64-linux-gnu/glib-2.0/include
)

target_link_libraries(whatsbutler LINK_PUBLIC purple glib-2.0)