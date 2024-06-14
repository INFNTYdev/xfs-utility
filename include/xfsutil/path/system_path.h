
#ifndef XFS_PATH_SYSTEM_PATH_H_
#define XFS_PATH_SYSTEM_PATH_H_



#include"xfsutil/path/util/path_tool.h"


// (ASCII, ANSI, E-ASCII, UTF-8) 8-bit character system path
class SystemPath {

public:
	explicit SystemPath(PathT::FileSys file_sys, const std::string& path_str) noexcept;
	explicit SystemPath(PathT::FileSys file_sys, const std::string_view& path_v);
	explicit SystemPath(PathT::FileSys file_sys, std::string&& path_str) noexcept;
	explicit SystemPath(const std::string_view& path_v);
	explicit SystemPath(const std::string& path_str) noexcept;
	explicit SystemPath(std::string&& path_str) noexcept;
	SystemPath(const SystemPath& path) noexcept;
	SystemPath(SystemPath&& path) noexcept;
	~SystemPath() = default;

	friend std::ostream& operator<<(std::ostream& os, const SystemPath& path);

	SystemPath& operator=(const SystemPath& rhs_path) noexcept;
	SystemPath& operator=(SystemPath&& rhs_path) noexcept;
	bool operator=(const std::string_view& rhs_str_v);
	bool operator=(const std::string& rhs_str) noexcept;
	bool operator=(std::string&& rhs_str) noexcept;
	SystemPath& operator+=(const SystemPath& rhs_path);
	SystemPath& operator+=(const std::string_view& rhs_str_v);
	SystemPath& operator+=(const std::string& rhs_str);
	SystemPath& operator--() noexcept;
	SystemPath operator--(int) noexcept;
	bool operator==(const SystemPath& rhs_path) const noexcept;
	bool operator==(const std::string_view& rhs_str_v) const;
	bool operator==(const std::string& rhs_str) const noexcept;
	std::string_view operator[](const size_t& target_index) const;

	// Returns true if path contains no characters
	bool empty() const noexcept;
	// Returns total number of characters in path
	size_t length() const noexcept;
	// Returns size of path in bytes
	size_t size() const noexcept;
	// Returns path intended file system
	constexpr PathT::FileSys& pathType() const noexcept;
	// Returns true if path obeys file system path syntax
	bool isLegalString() const noexcept;
	// Returns true if path points to a file
	bool isFilePath() const noexcept;
	// Returns true if path points to a directory
	bool isDirectoryPath() const noexcept;
	// Returns total number of navigation points in path
	size_t nodeCount() const noexcept;
	// Returns path delimiting character
	char getDelimiter() const noexcept;
	// Returns path root directory
	std::string_view getRoot() const noexcept;
	// Returns path target name
	std::string_view getTarget() const noexcept;
	// Returns path ending extension if any
	std::string_view getExtension() const noexcept;
	const std::string& str() const noexcept;
	const char* c_str() const noexcept;
	const char* data() const noexcept;
	// Returns vector of path navigation points to target
	std::vector<std::string_view> getPathVector() const;
	// Returns true if provided system path has same root directory
	bool sharesRootNode(const SystemPath& path) const noexcept;
	// Returns true if provided path has same root directory
	bool sharesRootNode(const std::string& path_str) const noexcept;
	// Returns true if provided path has same root directory
	bool sharesRootNode(const std::string_view& path_str_v) const;
	// Returns highest shared node between system paths if any
	std::string_view findHighestCommonNode(const SystemPath& path) const;
	// Returns highest shared node between system path and provided path if any
	std::string_view findHighestCommonNode(const std::string& path_str) const;
	// Returns highest shared node between system path and provided path if any
	std::string_view findHighestCommonNode(const std::string_view& path_str_v) const;
	// Remove specified number of navigation points from path
	void decay(const size_t& count = size_t(1));
	// Collapse path to root node
	void decayToRoot();


private:
	PathT::FileSys m_fileSys;
	std::string m_path;
	bool m_isLegalStr;
	bool m_isDirPath;

};



#endif // XFS_PATH_SYSTEM_PATH_H_
