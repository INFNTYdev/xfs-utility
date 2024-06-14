
#include"xfsutil/path/util/path_tool.h"


// PathT::Constants

const char PathT::BLANK_CHARACTER{ ' ' };
const std::string PathT::BLANK_STRING{ PathT::BLANK_CHARACTER };
const std::string PathT::EMPTY_STRING{ "" };
const size_t PathT::NO_POSITION{ std::string::npos };
const uint16_t PathT::WIN32_PATH_BYTE_MAX{ 260 };
const uint16_t PathT::WIN32_PATH_BYTE_MAX_E{ 32'767 };
const uint16_t PathT::LINUX_PATH_BYTE_MAX{ 4'096 };
const uint16_t PathT::MACOS_PATH_BYTE_MAX{ 1'024 };
const std::string PathT::WIN32_PATH_DELIMITERS{ "/\\" };
const std::string WIN32_LONG_PATH_DENOTE{ "\\\\?\\" };
const char PathT::UNIX_PATH_DELIMITER{ '/' };
const char PathT::FILE_TYPE_DENOTE{ '.' };
const char PathT::WIN32_DRIVE_DENOTE{ ':' };
const std::string PathT::WIN32_PATH_INVALIDS{
	(PathT::WIN32_PATH_DELIMITERS + PathT::WIN32_DRIVE_DENOTE + "<>\"?*\n\t")
};
const std::string PathT::WIN32_ROOT{ "C:\\" };
const std::string PathT::UNIX_ROOT{ PathT::UNIX_PATH_DELIMITER };



// PathT::Methods

constexpr bool PathT::isUnixBasedFileSystem(FileSys file_sys) noexcept
{
	switch (file_sys) {
	case PathT::FileSys::MACOS:
	case PathT::FileSys::LINUX:
		return true;
	default:
		return false;
	}
}

constexpr uint16_t PathT::getFileSystemMaxPathBytes(FileSys file_sys) noexcept
{
	switch (file_sys) {
	case FileSys::WINDOWS:
		return WIN32_PATH_BYTE_MAX;
	case FileSys::LINUX:
		return LINUX_PATH_BYTE_MAX;
	case FileSys::MACOS:
		return MACOS_PATH_BYTE_MAX;
	default:
		return uint16_t(0);
	}
}

bool PathT::hasLeadingBlankSpace(const std::string& str) noexcept
{
	if (str.empty())
		return false;

	return (str[0] == BLANK_CHARACTER || str[0] == '\n' || str[0] == '\t');
}

bool PathT::hasTrailingBlankSpace(const std::string& str) noexcept
{
	if (str.empty())
		return false;

	size_t last{ (str.size() - 1) };

	return (str[last] == BLANK_CHARACTER || str[last] == '\n' || str[last] == '\t');
}

bool PathT::isAllBlankSpace(const std::string& str) noexcept
{
	if (str.empty())
		return false;

	for (const char& c : str) {
		
		if (c != BLANK_CHARACTER && c != '\n' && c != '\t')
			return false;

	}

	return true;
}

char PathT::getPathDelimiter(const std::string& path) noexcept
{
	if (path.empty())
		return BLANK_CHARACTER;

	// Windows path delimiters contain all possible delimiters
	for (const char& delimiter : WIN32_PATH_DELIMITERS) {
		
		if (path.find(delimiter) != NO_POSITION)
			return delimiter;

	}

	return BLANK_CHARACTER;
}

size_t PathT::findPathLastDelimiter(const std::string& path, const size_t& r_from) noexcept
{
	if (path.empty())
		return NO_POSITION;

	// Allows null terminator as reverse start
	if (r_from > path.size())
		return NO_POSITION;

	char delimiter{ getPathDelimiter(path) };

	if (delimiter == BLANK_CHARACTER)
		return NO_POSITION;

	for (size_t r{ r_from }; r > 0; --r) {
		
		if (path[r] == delimiter)
			return r;

	}

	return NO_POSITION;
}

size_t PathT::findPathLastDelimiter(const std::string& path) noexcept
{
	if (path.empty())
		return NO_POSITION;

	return findPathLastDelimiter(path, (path.size() - 1));
}

size_t PathT::findPathTargetDelimiter(const std::string& path) noexcept
{
	if (path.empty())
		return NO_POSITION;

	char delimiter{ getPathDelimiter(path) };
	
	if (delimiter == BLANK_CHARACTER)
		return NO_POSITION;

	// Delimiter is the only char in string
	if (path.size() < 2)
		return size_t(0);

	size_t position{ findPathLastDelimiter(path) };

	// Pray 'path' string has no more than one delimiter at the end
	// Check for unnecessary path delimiter at end of string
	if (position == (path.size() - 1))
		position = findPathLastDelimiter(path, (position - 1));

	// Ending delimiter found but no others in string
	if (position == NO_POSITION)
		return NO_POSITION;

	return position;
}

size_t PathT::getPathNodeCount(const std::string& path) noexcept
{
	if (path.empty())
		return size_t(0);

	char delimiter{ getPathDelimiter(path) };

	// Path contains no delimiter (could be relative)
	if (delimiter == BLANK_CHARACTER)
		return size_t(1);

	// Delimiter is the only character in string
	if (path.size() < 2)
		return size_t(0);

	size_t startPos{ findPathTargetDelimiter(path) };
	size_t targetCount{ 0 };

	// Standalone target name with ending delimiter
	if (startPos == NO_POSITION)
		return size_t(1);

	// Account for passed target name
	++targetCount;
	--startPos;

	for (size_t r{ startPos }; r > 0; --r) {

		// Successfully passed another target name
		if (path[r] == delimiter && path[(r + 1)] != delimiter) {
			++targetCount;
			continue;
		}

		// Account for root target
		if (r == 1)
			++targetCount;

	}

	return targetCount;
}

std::string_view PathT::getPathEndingName(const std::string& path) noexcept
{
	if (path.empty())
		return EMPTY_STRING;

	if (path.size() < 2)
		return path;

	char delimiter{ getPathDelimiter(path) };

	// No delimiter (could be relative path)
	if (delimiter == BLANK_CHARACTER)
		return path;

	size_t startPos{ findPathTargetDelimiter(path) };

	if (startPos == NO_POSITION)
		return EMPTY_STRING;

	size_t stopPos{ path.size() };

	// Ignore target delimiter
	++startPos;

	// Check for unnecessary ending delimiter
	if (path[(stopPos - 1)] == delimiter)
		--stopPos;

	return std::string_view{
		(path.data() + startPos),
		(stopPos - startPos)
	};
}

std::string_view PathT::getPathEndingExtension(const std::string& file_path) noexcept
{
	if (file_path.empty())
		return EMPTY_STRING;

	if (file_path.size() < 2)
		return EMPTY_STRING;

	std::string_view targetName{ getPathEndingName(file_path) };

	if (targetName == EMPTY_STRING)
		return EMPTY_STRING;

	size_t startPos{ targetName.find(FILE_TYPE_DENOTE) };

	// No file extension delimiter in file name
	if (startPos == NO_POSITION)
		return EMPTY_STRING;

	// Ignore file extension denote
	++startPos;

	return std::string_view{
		(targetName.data() + startPos),
		(targetName.size() - startPos)
	};
}

bool PathT::hasIllegalPathCharacters(FileSys path_type, const std::string& path) noexcept
{
	if (path.empty())
		return false;

	if (hasLeadingBlankSpace(path) || hasTrailingBlankSpace(path))
		return true;

	const char delimiter{ getPathDelimiter(path) };

	size_t illegalFound;

	for (size_t i{ 0 }; i < path.size(); ++i) {
		
		switch (delimiter) {
		// 1. Path contains no delimiter (could be relative)
		case BLANK_CHARACTER:
			switch (path_type) {
			// Look for illegal Unix path characters
			// No real need for this but keeping just in case
			case FileSys::LINUX:
			case FileSys::MACOS:
				switch (path[i]) {
				case UNIX_PATH_DELIMITER:
					return true;
				default:
					continue;
				}

			// Look for illegal Windows path characters
			default:
				switch (WIN32_PATH_INVALIDS.find(path[i])) {
				case NO_POSITION:
					continue;
				default:
					return true;
				}
			}

		// 2. Path contains at least one delimiter
		default:
			// General guard against double delimiter use
			if (path[i] == delimiter && i > 0 && path[(i - 1)] == delimiter) {
				// Guards Windows UNC paths
				if (i == 1 && path_type == WINDOWS)
					continue;

				return true;
			}

			// General guard for legal delimiter use
			if (path[i] == delimiter)
				continue;

			// Guard for Unix type paths
			// Unix paths have no illegals chars except path delimiter
			if (path_type == LINUX || path_type == MACOS)
				continue;

			illegalFound = WIN32_PATH_INVALIDS.find(path[i]);

			// Check for illegal Windows path character
			if (illegalFound != NO_POSITION) {
				// Guards Windows root drive denote
				if (i == 1 && path[i] == WIN32_DRIVE_DENOTE)
					continue;

				// Guards Windows long path prefix
				if (i == 2 && path[i] == '?' && path[(i + 1)] == delimiter)
					continue;

				return true;
			}
			continue;
		}

	}

	return false;
}

bool PathT::isPathString(FileSys path_type, const std::string& path) noexcept
{
	if (path.empty())
		return false;

	// If file system type is unknown the path must satisfy all
	// Avoid this where possible!
	if (path_type == UNKNOWN) {
		return (
			isPathString(WINDOWS, path) &&
			isPathString(LINUX, path) &&
			isPathString(MACOS, path)
		);
	}

	size_t strByteSize{
		(sizeof(std::string::value_type) * (path.size() + 1))
	};// +1 for null terminator

	// Check if string exceeds max path byte size
	if (strByteSize > size_t(getFileSystemMaxPathBytes(path_type)))
		return false;

	if (hasIllegalPathCharacters(path_type, path))
		return false;

	return true;
}

bool PathT::isFilePathString(FileSys path_type, const std::string& file_path) noexcept
{
	if (file_path.empty())
		return false;

	if (!isPathString(path_type, file_path))
		return false;

	// Check if path has an ending extension
	if (getPathEndingExtension(file_path) == EMPTY_STRING)
		return false;

	return true;
}

void PathT::getPathVector(std::vector<std::string_view>& path_vec, const std::string& path)
{
	if (path.empty())
		return;

	char delimiter{ getPathDelimiter(path) };

	// Path contains no delimiter (could be relative)
	if (delimiter == BLANK_CHARACTER) {
		path_vec.emplace_back(path);
		return;
	}

	size_t last{ 0 };
	size_t targetLength{ 0 };

	for (size_t i{ 0 }; i < path.size(); ++i) {

		// Guard file and directory name characters
		if (path[i] != delimiter && i != (path.size() - 1)) {
			++targetLength;
			continue;
		}

		// Guard against delimiter in front of target name
		if (i == last && path[i] == delimiter) {
			last += size_t(1);
			continue;
		}

		// Catch the last character in last loop
		if (i == (path.size() - 1) && path[i] != delimiter)
			++targetLength;

		path_vec.emplace_back((path.data() + last), targetLength);

		targetLength = size_t(0);
		last = size_t(i + 1);

	}
}

std::string PathT::concatPaths(const std::string& front, const std::string& rear)
{
	if (front.empty() && rear.empty())
		return EMPTY_STRING;
	else if (front.empty() && !rear.empty())
		return rear;
	else if (!front.empty() && rear.empty())
		return front;

	// Front path delimiter takes precedence
	char delimiter{ getPathDelimiter(front) };

	// If front contains no delimiter use rear path delimiter
	if (delimiter == BLANK_CHARACTER) {
		delimiter = getPathDelimiter(rear);

		// If neither path contains a delimiter use Unix path delimiter
		if (delimiter == BLANK_CHARACTER)
			delimiter = UNIX_PATH_DELIMITER;
	}
	
	std::vector<std::string_view> rearNav{};
	getPathVector(rearNav, rear);

	std::ostringstream concatStream{};

	concatStream << front;

	// Check if front path already ends with delimiter
	if (front[(front.size() - 1)] != delimiter)
		concatStream << delimiter;

	bool isFinalLoop{ true };

	for (size_t i{ 0 }; i < rearNav.size(); ++i) {

		isFinalLoop = (i == (rearNav.size() - 1));

		switch (isFinalLoop) {
		case true:
			concatStream << rearNav[i];
			break;

		default:
			concatStream << rearNav[i] << delimiter;
			continue;
		}

	}

	return concatStream.str();
}

void PathT::appendToPath(std::string& front, const std::string& rear)
{
	if (rear.empty())
		return;

	// Front path delimiter takes precedence
	char delimiter{ getPathDelimiter(front) };

	// If front contains no delimiter use rear path delimiter
	if (delimiter == BLANK_CHARACTER) {
		delimiter = getPathDelimiter(rear);

		// If neither path contains a delimiter use Unix path delimiter
		if (delimiter == BLANK_CHARACTER)
			delimiter = UNIX_PATH_DELIMITER;
	}

	std::vector<std::string_view> rearNav{};
	getPathVector(rearNav, rear);

	std::ostringstream concatStream{};

	// Check if front path already ends with delimiter
	if (front[(front.size() - 1)] != delimiter)
		concatStream << delimiter;

	bool isFinalLoop{ true };

	for (size_t i{ 0 }; i < rearNav.size(); ++i) {

		isFinalLoop = (i == (rearNav.size() - 1));

		switch (isFinalLoop) {
		case true:
			concatStream << rearNav[i];
			break;

		default:
			concatStream << rearNav[i] << delimiter;
			continue;
		}

	}

	front = std::move(std::string{ front + concatStream.str() });
}

void PathT::buildPath(std::string& path_out, const std::vector<std::string_view>& path_vec,
	char delimiter)
{
	if (path_vec.empty())
		return;

	std::ostringstream concatStream{};

	bool isFinalLoop{ true };

	for (size_t i{ 0 }; i < path_vec.size(); ++i) {

		isFinalLoop = (i == (path_vec.size() - 1));

		switch (isFinalLoop) {
		case true:
			concatStream << path_vec[i];
			break;

		default:
			concatStream << path_vec[i] << delimiter;
			continue;
		}

	}

	path_out = std::move(concatStream.str());
}

void PathT::buildPath(std::string& path_out, const std::vector<std::string>& path_vec,
	char delimiter)
{
	std::vector<std::string_view> temp{};

	for (const std::string& target : path_vec)
		temp.emplace_back(target);

	buildPath(path_out, temp, delimiter);
}

std::string_view PathT::getDecayedPath(const std::string& path, uint16_t count) noexcept
{
	if (path.empty() || count == 0)
		return path;

	char delimiter{ getPathDelimiter(path) };

	// No delimiter means no path to decay
	if (delimiter == BLANK_CHARACTER)
		return path;

	size_t last{ findPathTargetDelimiter(path) };
	size_t end{ (last + 1) };

	// Ending delimiter found but no others in string
	if (last == NO_POSITION)
		return path;
	else
		--count;// Successfully passed 1 target name

	// NEW
	while (last != NO_POSITION && count != 0) {

		// Check if last delimiter is first character
		if (last == 0)
			break;

		// Find next delimiter
		last = findPathLastDelimiter(path, (last - 1));

		// Set new end position if delimiter found
		if (last != NO_POSITION)
			end = size_t(last + 1);

		--count;

	}

	return std::string_view{ path.data(), end };
}

std::string_view PathT::getPathRoot(const std::string& path) noexcept
{
	if (path.empty())
		return EMPTY_STRING;

	char delimiter{ getPathDelimiter(path) };

	// Path contains no delimiter (could be relative)
	if (delimiter == BLANK_CHARACTER)
		return path;

	// Delimiter is the only character in string
	if (path.size() < 2)
		return EMPTY_STRING;

	size_t start{ 0 };
	size_t stop{ 0 };

	for (size_t i{ 0 }; i < path.size(); ++i) {

		// Ignore leading delimiter
		if (i == 0 && path[i] == delimiter) {
			start = size_t(1);
			continue;
		}

		// Ignore repeating delimiter
		if (path[i] == delimiter && path[(i - 1)] == delimiter) {
			start += size_t(1);
			continue;
		}

		// Ignore root directory characters
		if (path[i] != delimiter)
			continue;

		stop = i;
		break;

	}

	return std::string_view{ path.data(), stop };
}

bool PathT::sharesRootNode(const std::string& path1, const std::string& path2)
{
	if (path1.empty() || path2.empty())
		return false;

	std::vector<std::string_view> path1_nav{};
	std::vector<std::string_view> path2_nav{};

	getPathVector(path1_nav, path1);
	getPathVector(path2_nav, path2);

	if (path1_nav.empty() || path2_nav.empty())
		return false;

	return (path1_nav[0] == path2_nav[0]);
}

std::string_view PathT::getHighestCommonNode(const std::string& path1, const std::string& path2)
{
	if (path1.empty() || path2.empty())
		return EMPTY_STRING;

	std::vector<std::string_view> path1_nav{};
	std::vector<std::string_view> path2_nav{};

	getPathVector(path1_nav, path1);
	getPathVector(path2_nav, path2);

	if (path1_nav.empty() || path2_nav.empty())
		return EMPTY_STRING;

	size_t stop{ 0 };
	size_t common{ 0 };

	// Loop using smallest paths vector size
	if (path1_nav.size() > path2_nav.size())
		stop = path2_nav.size();
	else
		stop = path1_nav.size();

	for (size_t i{ 0 }; i < stop; ++i) {

		// Root directories are different
		if (i == 0 && path1_nav[i] != path2_nav[i])
			return EMPTY_STRING;

		// Paths diverge
		if (path1_nav[i] != path2_nav[i])
			break;

		common = i;

	}

	return path1_nav[common];
}



// PathT::Wchar::Methods
