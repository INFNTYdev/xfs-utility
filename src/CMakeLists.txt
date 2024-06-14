
# \src\ DIRECTORY CMAKE SCRIPT


add_library(
	xfs_path
	"path/util/path_tool.cpp"
)

add_library(
	xfs_buffer
	"buffer/buffer_page.cpp"
)

target_link_libraries(xfs_buffer PUBLIC xfs_path)
