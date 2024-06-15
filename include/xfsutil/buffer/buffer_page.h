
#ifndef XFS_BUFFER_FILE_PAGE_H_
#define XFS_BUFFER_FILE_PAGE_H_



#include<cstdint>
#include<ostream>
#include<string_view>
#include<cstdlib>
#include<fstream>


// (ASCII, ANSI, UTF-8, E-ASCII) 8-bit character buffer page
class BufferPage {

public:
	BufferPage(const uint32_t& page_size, const size_t& page_index, const size_t& i_start);
	BufferPage(const BufferPage&) = delete;
	BufferPage(BufferPage&&) = delete;
	~BufferPage();

	static const uint8_t MIN_ALLOC_SIZE{ 2 };// Minimum character memory allocation in bytes
	static const uint32_t SIZE_DEV{ 10 };// 10 1 byte characters = 10 Bytes
	static const uint32_t SIZE_2KB{ 2'048 };// 2,048 1 byte characters = 2KB
	static const uint32_t SIZE_4KB{ 4'096 };// 4,096 1 byte characters = 4KB
	static const uint32_t SIZE_8KB{ 8'192 };// 8,192 1 byte characters = 8KB
	static const uint32_t SIZE_16KB{ 16'384 };// 16,384 1 byte characters = 16KB
	static const uint32_t SIZE_32KB{ 32'768 };// 32,768 1 byte characters = 32KB
	static const uint32_t SIZE_64KB{ 65'536 };// 65,536 1 byte characters = 64KB
	static const uint32_t SIZE_128KB{ 131'072 };// 131,072 1 byte characters = 128KB
	static const uint32_t SIZE_256KB{ 262'144 };// 262,144 1 byte characters = 256KB
	static const uint32_t SIZE_512KB{ 524'288 };// 524,288 1 byte characters = 512KB
	static const uint32_t SIZE_1MB{ 1'048'576 };// 1,048,576 1 byte characters = 1MB
	static const uint32_t SIZE_2MB{ 2'097'152 };// 2,097,152 1 byte characters = 2MB
	static const uint32_t SIZE_MAX_1GB{ 1'073'741'824 };// 1,073,741,824 1 byte characters = 1GB

	BufferPage& operator=(const BufferPage&) = delete;
	BufferPage& operator=(BufferPage&&) = delete;

	friend std::ostream& operator<<(std::ostream& os, const BufferPage& page);

	const size_t pageIndex;// Buffer page sequence index
	const size_t start;// Page starting character position

	// Returns number of characters buffer page holds
	size_t length() const;
	// Returns size of buffer page contents in bytes
	size_t size() const;
	// Returns page ending character position
	const size_t& stop() const;
	// Returns true if page contents are cached in memory
	bool isCached() const;
	// Read page contents into memory
	[[nodiscard]] bool cachePageContents(std::ifstream& file_stream);
	// Returns view of page contents
	std::string_view contents() const;
	// Clear page contents from memory
	void flushCache();


private:
	size_t m_stopPos;
	char* m_str_ptr;

	static size_t calcStopPosition(const uint32_t& page_size, const size_t& i_start);

	bool hasInvalidIndecies() const;
	[[nodiscard]] bool reallocateContentsString(const size_t& new_size);

};



#endif // XFS_BUFFER_FILE_PAGE_H_
