
#include"xfsutil/path/system_path.h"


//	SystemPath::CONSTRUCTORS

SystemPath::SystemPath(PathT::FileSys file_sys, const std::string& path_str) noexcept
	: m_fileSys{ file_sys },
	m_path{ path_str },
	m_attr{}
{
	this->parsePath();
}

SystemPath::SystemPath(PathT::FileSys file_sys, const std::string_view& path_v)
	: m_fileSys{ file_sys },
	m_path{ path_v },
	m_attr{}
{
	this->parsePath();
}

SystemPath::SystemPath(PathT::FileSys file_sys, std::string&& path_str) noexcept
	: m_fileSys{ file_sys },
	m_path{ std::move(path_str) },
	m_attr{}
{
	this->parsePath();
}

SystemPath::SystemPath(const std::string_view& path_v)
	: m_fileSys{ PathT::FileSys::UNKNOWN },
	m_path{ path_v },
	m_attr{}
{
	this->parsePath();
}

SystemPath::SystemPath(const std::string& path_str) noexcept
	: m_fileSys{ PathT::FileSys::UNKNOWN },
	m_path{ path_str },
	m_attr{}
{
	this->parsePath();
}

SystemPath::SystemPath(std::string&& path_str) noexcept
	: m_fileSys{ PathT::FileSys::UNKNOWN },
	m_path{ std::move(path_str) },
	m_attr{}
{
	this->parsePath();
}

SystemPath::SystemPath(const SystemPath& path) noexcept
	: m_fileSys{ path.m_fileSys },
	m_path{ path.m_path },
	m_attr{ path.m_attr }
{
	//
}

SystemPath::SystemPath(SystemPath&& path) noexcept
	: m_fileSys{ std::move(path.m_fileSys) },
	m_path{ std::move(path.m_path) },
	m_attr{ std::move(path.m_attr) }
{
	//
}


//	SystemPath::FREE



//	SystemPath::OPERATOR

std::ostream& operator<<(std::ostream& os, const SystemPath& path)
{
	os << path.m_path;

	return os;
}

SystemPath& SystemPath::operator=(const SystemPath& rhs_path) noexcept
{
	if (this == &rhs_path)
		return *this;

	this->m_fileSys = rhs_path.m_fileSys;
	this->m_path = rhs_path.m_path;
	this->m_attr = rhs_path.m_attr;

	return *this;
}

SystemPath& SystemPath::operator=(SystemPath&& rhs_path) noexcept
{
	if (this == &rhs_path)
		return *this;

	this->m_fileSys = std::move(rhs_path.m_fileSys);
	this->m_path = std::move(rhs_path.m_path);
	this->m_attr = std::move(rhs_path.m_attr);

	return *this;
}

SystemPath& SystemPath::operator=(const std::string_view& rhs_str_v)
{
	if (this->m_path == rhs_str_v)
		return *this;

	this->m_path = rhs_str_v;
	this->parsePath();

	return *this;
}

SystemPath& SystemPath::operator=(const std::string& rhs_str) noexcept
{
	if (this->m_path == rhs_str)
		return *this;

	this->m_path = rhs_str;
	this->parsePath();

	return *this;
}

SystemPath& SystemPath::operator=(std::string&& rhs_str) noexcept
{
	if (this->m_path == rhs_str)
		return *this;

	this->m_path = std::move(rhs_str);
	this->parsePath();

	return *this;
}

SystemPath& SystemPath::operator+=(const SystemPath& rhs_path)
{
	PathT::appendToPath(this->m_path, rhs_path.str());
	this->parsePath();

	return *this;
}

SystemPath& SystemPath::operator+=(const std::string_view& rhs_str_v)
{
	PathT::appendToPath(this->m_path, std::string{ rhs_str_v });
	this->parsePath();

	return *this;
}

SystemPath& SystemPath::operator+=(const std::string& rhs_str)
{
	PathT::appendToPath(this->m_path, rhs_str);
	this->parsePath();

	return *this;
}

SystemPath& SystemPath::operator--() noexcept
{
	this->decay(size_t(1));

	return *this;
}

SystemPath SystemPath::operator--(int) noexcept
{
	SystemPath temp{ *this };

	this->decay(size_t(1));

	return temp;
}

bool SystemPath::operator==(const SystemPath& rhs_path) const noexcept
{
	return (this->m_path == rhs_path.m_path);
}

bool SystemPath::operator==(const std::string_view& rhs_str_v) const
{
	return (this->m_path == rhs_str_v);
}

bool SystemPath::operator==(const std::string& rhs_str) const noexcept
{
	return (this->m_path == rhs_str);
}

std::string_view SystemPath::operator[](const size_t& node_index) const
{
	if (node_index >= this->nodeCount())
		return PathT::EMPTY_STRING;

	return this->getPathVector()[node_index];
}
//	SystemPath::OPERATOR END!



//	SystemPath::PUBLIC

bool SystemPath::empty() const noexcept
{
	return this->m_path.empty();
}

size_t SystemPath::length() const noexcept
{
	return this->m_path.size();
}

size_t SystemPath::size() const noexcept
{
	return (sizeof(std::string::value_type) * (this->length() + size_t(1)));
}

constexpr PathT::FileSys SystemPath::pathType() const noexcept
{
	return this->m_fileSys;
}

bool SystemPath::isLegalString() const noexcept
{
	return this->m_attr.isLegalStr;
}

bool SystemPath::isFilePath() const noexcept
{
	return (this->isLegalString() && !this->m_attr.isDirPath);
}

bool SystemPath::isDirectoryPath() const noexcept
{
	return (this->isLegalString() && this->m_attr.isDirPath);
}

const size_t& SystemPath::nodeCount() const noexcept
{
	return this->m_attr.nodeQ;
}

char SystemPath::getDelimiter() const noexcept
{
	return PathT::getPathDelimiter(this->m_path);
}

std::string_view SystemPath::getRoot() const noexcept
{
	return PathT::getPathRoot(this->m_path);
}

std::string_view SystemPath::getTarget() const noexcept
{
	return PathT::getPathEndingName(this->m_path);
}

std::string_view SystemPath::getExtension() const noexcept
{
	return PathT::getPathEndingExtension(this->m_path);
}

const std::string& SystemPath::str() const noexcept
{
	return this->m_path;
}

const char* SystemPath::c_str() const noexcept
{
	return this->m_path.c_str();
}

const char* SystemPath::data() const noexcept
{
	return this->m_path.data();
}

std::vector<std::string_view> SystemPath::getPathVector() const
{
	std::vector<std::string_view> temp{};

	PathT::getPathVector(temp, this->m_path);

	return temp;
}

bool SystemPath::sharesRootNode(const SystemPath& path) const noexcept
{
	return (this->getRoot() == path.getRoot());
}

bool SystemPath::sharesRootNode(const std::string& path_str) const noexcept
{
	return (this->getRoot() == PathT::getPathRoot(path_str));
}

bool SystemPath::sharesRootNode(const std::string_view& path_str_v) const
{
	return (this->getRoot() == PathT::getPathRoot(std::string{ path_str_v }));
}

std::string_view SystemPath::findHighestCommonNode(const SystemPath& path) const
{
	return PathT::getHighestCommonNode(this->m_path, path.m_path);
}

std::string_view SystemPath::findHighestCommonNode(const std::string& path_str) const
{
	return PathT::getHighestCommonNode(this->m_path, path_str);
}

std::string_view SystemPath::findHighestCommonNode(const std::string_view& path_str_v) const
{
	return PathT::getHighestCommonNode(this->m_path, std::string{ path_str_v });
}

void SystemPath::decay(const size_t& count)
{
	if (count >= this->nodeCount() || this->nodeCount() == size_t(0))
		return;

	this->m_path = PathT::getDecayedPath(this->m_path, count);
	this->m_attr.nodeQ = PathT::getPathNodeCount(this->m_path);
}

void SystemPath::decayToRoot()
{
	this->decay(this->nodeCount() - size_t(1));
}
//	SystemPath::PUBLIC END!



//	SystemPath::PRIVATE

void SystemPath::parsePath() noexcept
{
	this->m_attr.isLegalStr = PathT::isPathString(this->m_fileSys, this->m_path);
	this->m_attr.isDirPath = (!PathT::isFilePathString(this->m_fileSys, this->m_path));
	this->m_attr.nodeQ = PathT::getPathNodeCount(this->m_path);
}
//	SystemPath::PRIVATE END!



//	SystemPath::PROTECTED
//	SystemPath::PROTECTED END!
