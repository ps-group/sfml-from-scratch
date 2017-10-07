add_executable(05 main.cpp)

target_compile_features(05 PUBLIC cxx_std_17)
target_compile_definitions(05 PRIVATE SFML_STATIC)

target_link_libraries(05 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
