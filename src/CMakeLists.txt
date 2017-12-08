find_package(Doxygen REQUIRED dot OPTIONAL_COMPONENTS mscgen dia)
if (${DOXYGEN_FOUND}) 
  doxygen_add_docs(doxygen ${CMAKE_CURRENT_SOURCE_DIR})
endif()

add_library(fd_algos STATIC fd_ht.c fd_bounded_q.c)
