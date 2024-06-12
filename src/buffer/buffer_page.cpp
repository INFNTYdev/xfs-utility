
#include"xfsutil/buffer/buffer_page.h"


//	BufferPage::CONSTRUCTORS

BufferPage::BufferPage(const uint32_t& page_size, const size_t& page_index,
	const size_t& i_start)
	: pageIndex{ page_index },
	start{ i_start },
	m_stopPos{ calcStopPosition(page_size, i_start) },
	m_str_ptr{ nullptr }
{
	// Page size exceeds maximum size
	if (page_size > SIZE_MAX_1GB)
		this->m_stopPos = calcStopPosition(SIZE_MAX_1GB, i_start);

	// Invalid start/stop attributes
	if (this->hasInvalidIndecies())
		this->m_stopPos = this->start;
}


//	BufferPage::DESTRUCTOR

BufferPage::~BufferPage()
{
	if (this->isCached())
		this->flushCache();
}


//	BufferPage::FREE



//	BufferPage::OPERATOR

std::ostream& operator<<(std::ostream& os, const BufferPage& page)
{
	if (page.isCached())
		os << page.contents();

	return os;
}
//	BufferPage::OPERATOR END!



//	BufferPage::PUBLIC

size_t BufferPage::length() const
{
	return ((this->m_stopPos + 1) - this->start);// +1 for 0-based index conversion
}

size_t BufferPage::size() const
{
	if (!this->isCached())
		return size_t(0);

	return (sizeof(char) * (this->length() + 1));// +1 for null terminator
}

const size_t& BufferPage::stop() const
{
	return this->m_stopPos;
}

bool BufferPage::isCached() const
{
	return (this->m_str_ptr != nullptr);
}

bool BufferPage::cachePageContents(std::ifstream& file_stream)
{
	if (file_stream.fail() || !file_stream.is_open())
		return false;

	file_stream.seekg(this->start, std::ios::beg);

	if (file_stream.fail()) {
		file_stream.clear();

		return false;
	}

	if (this->isCached())
		this->flushCache();

	size_t length{ this->size() };
	this->m_str_ptr = new char[length];

	char character;
	size_t position{ 0 };

	while (position != (length - 1) && file_stream.get(character)) {
		this->m_str_ptr[position] = character;
		++position;
	}

	if (position != (length - 1)) {
		this->m_stopPos = (this->start + position);

		size_t remainder{ (this->size() - position) };
		size_t newSize{ (this->size() - (remainder - 1)) };

		if (!this->reallocateContentsString(newSize)) {
			this->flushCache();

			return false;
		}
	}

	this->m_str_ptr[position] = '\0';

	return true;
}

std::string_view BufferPage::contents() const
{
	if (!this->isCached())
		return std::string_view{};

	return this->m_str_ptr;
}

void BufferPage::flushCache()
{
	if (!this->isCached())
		return;

	delete[] this->m_str_ptr;
	this->m_str_ptr = nullptr;
}
//	BufferPage::PUBLIC END!



//	BufferPage::PRIVATE

size_t BufferPage::calcStopPosition(const uint32_t& page_size, const size_t& i_start)
{
	if (page_size < MIN_ALLOC_SIZE)
		return i_start;

	if (page_size > SIZE_MAX_1GB)
		return (i_start + (SIZE_MAX_1GB - 2));

	return (i_start + (page_size - 2));
}

bool BufferPage::hasInvalidIndecies() const
{
	return (this->start > this->m_stopPos);
}

bool BufferPage::reallocateContentsString(const size_t& new_size)
{
	if (this->m_str_ptr == nullptr)
		return false;

	if (new_size < MIN_ALLOC_SIZE || new_size > SIZE_MAX_1GB)
		return false;

	char* temp = (char*)realloc(this->m_str_ptr, (new_size * sizeof(char)));

	if (temp == nullptr)
		return false;

	this->m_str_ptr = temp;

	return true;
}
//	BufferPage::PRIVATE END!



//	BufferPage::PROTECTED
//	BufferPage::PROTECTED END!
