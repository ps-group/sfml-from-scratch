add_executable(04 main.cpp)

target_compile_features(04 PUBLIC cxx_std_17)
target_compile_definitions(04 PRIVATE SFML_STATIC)

target_link_libraries(04 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
