add_executable(09 main.cpp AnimatedSprite.h AnimatedSprite.cpp HeroPuppeteer.h HeroPuppeteer.cpp)

target_compile_features(09 PUBLIC cxx_std_17)
add_compile_options(09 PRIVATE)
target_compile_definitions(09 PRIVATE SFML_STATIC)
target_link_libraries(09 PRIVATE ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

# Выполняем копирование ресурсов в выходную директорию
file(COPY ../res/09 DESTINATION ${CMAKE_BINARY_DIR})
