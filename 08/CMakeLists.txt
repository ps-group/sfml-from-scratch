add_executable(08 main.cpp RussianFlag.h RussianFlag.cpp)

target_compile_features(08 PUBLIC cxx_std_17)
add_compile_options(08 PRIVATE)
target_compile_definitions(08 PRIVATE SFML_STATIC)
target_link_libraries(08 PRIVATE ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
