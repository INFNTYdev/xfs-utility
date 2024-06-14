
#ifndef XFS_PATH_STRING_TOOL_H_
#define XFS_PATH_STRING_TOOL_H_



#include<string>
#include<string_view>
#include<vector>
#include<sstream>


// XFS system path utility
namespace PathT {

	extern const char BLANK_CHARACTER;// Space character
	extern const std::string BLANK_STRING;// Single space string
	extern const std::string EMPTY_STRING;// Empty string
	extern const size_t NO_POSITION;// No position index
	extern const uint16_t WIN32_PATH_BYTE_MAX;// Max number of bytes allowed in Windows path
	extern const uint16_t WIN32_PATH_BYTE_MAX_E;// Max number of bytes allowed in long Windows path
	extern const uint16_t LINUX_PATH_BYTE_MAX;// Max number of bytes allowed in Linux path
	extern const uint16_t MACOS_PATH_BYTE_MAX;// Max number of bytes allowed in MacOS path
	extern const std::string WIN32_PATH_DELIMITERS;// Windows system path delimiters
	extern const std::string WIN32_LONG_PATH_DENOTE;// Windows long path prefix
	extern const char UNIX_PATH_DELIMITER;// Unix system path delimiter
	extern const char FILE_TYPE_DENOTE;// File extension denote character
	extern const char WIN32_DRIVE_DENOTE;// Windows system root drive denote
	extern const std::string WIN32_PATH_INVALIDS;// Windows system illegal path characters
	extern const std::string WIN32_ROOT;// Windows system root directory
	extern const std::string UNIX_ROOT;// Unix system root directory

	
	// Supported file systems
	enum FileSys {
		UNKNOWN,// Unspecified file system
		WINDOWS,// Windows based file system
		LINUX,// Linux based file system
		MACOS,// MacOS file system
	};


	// Returns true if provided file system is Unix based
	constexpr bool isUnixBasedFileSystem(FileSys file_sys) noexcept;
	// Returns the maximum number of bytes allowed for file system path
	constexpr uint16_t getFileSystemMaxPathBytes(FileSys file_sys) noexcept;
	// Returns true if provided string begins with whitespace
	bool hasLeadingBlankSpace(const std::string& str) noexcept;
	// Returns true if provided string ends with whitespace
	bool hasTrailingBlankSpace(const std::string& str) noexcept;
	// Returns true if provided string contains all whitespace
	bool isAllBlankSpace(const std::string& str) noexcept;
	// Returns provided path delimiter if any
	char getPathDelimiter(const std::string& path) noexcept;
	// Returns index of provided paths last delimiter if any
	size_t findPathLastDelimiter(const std::string& path, const size_t& r_from) noexcept;
	// Returns index of provided paths last delimiter if any
	size_t findPathLastDelimiter(const std::string& path) noexcept;
	// Returns index of provided paths target directory/file delimiter if any
	size_t findPathTargetDelimiter(const std::string& path) noexcept;
	// Returns total number of navigation points in path
	size_t getPathNodeCount(const std::string& path) noexcept;
	// Returns provided paths file/directory name pointed to
	std::string_view getPathEndingName(const std::string& path) noexcept;
	// Returns provided paths ending extension if any
	std::string_view getPathEndingExtension(const std::string& file_path) noexcept;
	// Returns true if provided path contains an illegal character
	bool hasIllegalPathCharacters(FileSys path_type, const std::string& path) noexcept;
	// Returns true if provided string follows file system path rules
	bool isPathString(FileSys path_type, const std::string& path) noexcept;
	// Returns true if provided string follows file system file path rules
	bool isFilePathString(FileSys path_type, const std::string& file_path) noexcept;
	// Returns vector of provided paths nodes to target
	void getPathVector(std::vector<std::string_view>& path_vec, const std::string& path);
	// Returns concatenated path
	std::string concatPaths(const std::string& front, const std::string& rear);
	// Concatenate rear element to provided path string
	void appendToPath(std::string& front, const std::string& rear);
	// Construct path string from path vector
	void buildPath(std::string& path_out, const std::vector<std::string_view>& path_vec,
		char delimiter);
	// Construct path string from path vector
	void buildPath(std::string& path_out, const std::vector<std::string>& path_vec,
		char delimiter);
	// Returns provided path with specified number of navigation points removed
	std::string_view getDecayedPath(const std::string& path, uint16_t count = 1) noexcept;
	// Returns root directory of provided path
	std::string_view getPathRoot(const std::string& path) noexcept;
	// Returns true if provided paths share the same root node
	bool sharesRootNode(const std::string& path1, const std::string& path2);
	// Returns highest shared node between provided paths if any
	std::string_view getHighestCommonNode(const std::string& path1, const std::string& path2);


	// Extended byte character path tools
	namespace Wchar {

		// 16-bit character path methods

	}

}



#endif // XFS_PATH_STRING_TOOL_H_
