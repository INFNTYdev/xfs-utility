
# \src\ DIRECTORY CMAKE SCRIPT


add_library(
	xfs_path
	"path/util/path_tool.cpp"
	"path/system_path.cpp"
)

add_library(
	xfs_buffer
	"buffer/util/constants.cpp"
	
)

target_compile_features(xfs_buffer PUBLIC cxx_std_20)

target_link_libraries(xfs_buffer PUBLIC xfs_path)
