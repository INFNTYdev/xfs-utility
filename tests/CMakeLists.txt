
# \tests\ DIRECTORY CMAKE SCRIPT


add_executable(devexe "dev.cpp")

target_link_libraries(devexe PUBLIC xfs_buffer xfs_path)
