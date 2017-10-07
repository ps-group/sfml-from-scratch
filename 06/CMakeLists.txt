add_executable(06 main.cpp)

target_compile_features(06 PUBLIC cxx_std_17)
target_compile_definitions(06 PRIVATE SFML_STATIC)
target_link_libraries(06 PRIVATE ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

