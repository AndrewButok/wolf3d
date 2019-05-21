cmake_minimum_required(VERSION 3.14)
project(wolf3d C)

set(CMAKE_C_STANDARD 99)

find_library(SDL SDL2)

include_directories(includes)
include_directories(libft/includes)
include_directories(/Library/Frameworks/SDL2.framework/Headers)

AUX_SOURCE_DIRECTORY(libft LIBFT_SRC)
add_library(ft ${LIBFT_SRC})

set(SOURCE_FILES
        includes/wolf3d.h
        src/draw_surface.c
        src/main.c
        src/parse_map.c
        src/vector.c src/ray_cast.c src/map_intersection.c)

add_executable(wolf3d ${SOURCE_FILES})
target_link_libraries(wolf3d ft ${SDL})
