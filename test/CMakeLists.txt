include_directories(${fd_algos_SOURCE_DIR}/src)
link_directories(${fd_algos_SOURCE_DIR}/src)

add_executable(test_fd_ht test_fd_ht.c unity.c)
target_link_libraries(test_fd_ht fd_algos)

add_executable(test_fd_bounded_q test_fd_bounded_q.c unity.c)
target_link_libraries(test_fd_bounded_q fd_algos)
