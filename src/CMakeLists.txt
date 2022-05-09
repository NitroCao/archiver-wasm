find_package(LibArchive REQUIRED)

file(GLOB SOURCES *.cc)

add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS 
    "-sEXPORTED_RUNTIME_METHODS=ccall,cwrap,FS \
    -sENVIRONMENT='web' \
    -sMODULARIZE=1 \
    -sEXPORT_ES6=1 \
    -lembind \
    -sFORCE_FILESYSTEM=1"
)
target_include_directories(${PROJECT_NAME} PRIVATE ${EMSCRIPTEN_SYSROOT}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${LibArchive_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LibArchive_LIBRARIES})
