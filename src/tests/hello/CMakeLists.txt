configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/in.txt" "${CMAKE_CURRENT_BINARY_DIR}/in.txt" COPYONLY)
configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/out.txt" "${CMAKE_CURRENT_BINARY_DIR}/out.txt" COPYONLY)
add_executable (hello hello.c)
