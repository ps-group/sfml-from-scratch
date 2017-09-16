add_executable(06 main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype)
find_package(JPEG)
find_package(SFML 2 COMPONENTS window graphics system)

target_compile_features(06 PUBLIC cxx_std_17)
add_compile_options(06 PRIVATE "-pthread")
target_compile_definitions(06 PRIVATE SFML_STATIC)
target_link_libraries(06 PRIVATE pthread ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

