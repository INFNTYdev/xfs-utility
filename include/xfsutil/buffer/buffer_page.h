
#ifndef XFS_BUFFER_FILE_PAGE_H_
#define XFS_BUFFER_FILE_PAGE_H_



#include<cstdint>
#include<ostream>
#include<string_view>
#include<cstdlib>
#include<fstream>


// (ASCII, ANSI, E-ASCII, UTF-8) 8-bit character buffer page
class BufferPage {

public:
	explicit BufferPage(const uint32_t& page_size, const size_t& page_index, const size_t& i_start);
	//explicit BufferPage(const size_t& page_index, const size_t& i_start, const size_t& i_stop);
	BufferPage(const BufferPage&) = delete;
	BufferPage(BufferPage&&) = delete;
	~BufferPage();

	static const uint8_t MIN_ALLOC_SIZE{ 2 };// Minimum character memory allocation in bytes
	static const uint32_t SIZE_DEV{ 10 };// 10 characters = 10 Bytes
	static const uint32_t SIZE_2KB{ 2'048 };// 2048 characters = 2KB
	static const uint32_t SIZE_4KB{ 4'096 };// 4096 characters = 4KB
	static const uint32_t SIZE_8KB{ 8'192 };// 8192 characters = 8KB
	static const uint32_t SIZE_16KB{ 16'384 };// 16,384 characters = 16KB
	static const uint32_t SIZE_32KB{ 32'768 };// 32,768 characters = 32KB
	static const uint32_t SIZE_64KB{ 65'536 };// 65,536 characters = 64KB
	static const uint32_t SIZE_128KB{ 131'072 };// 131,072 characters = 128KB
	static const uint32_t SIZE_256KB{ 262'144 };// 262,144 characters = 256KB
	static const uint32_t SIZE_512KB{ 524'288 };// 524,288 characters = 512KB
	static const uint32_t SIZE_1MB{ 1'048'576 };// 1,048,576 characters = 1MB
	static const uint32_t SIZE_2MB{ 2'097'152 };// 2,097,152 characters = 2MB
	static const uint32_t SIZE_MAX_1GB{ 1'073'741'824 };// 1,073,741,824 characters = 1GB

	BufferPage& operator=(const BufferPage&) = delete;
	BufferPage& operator=(BufferPage&&) = delete;

	friend std::ostream& operator<<(std::ostream& os, const BufferPage& page);

	const size_t pageIndex;// Buffer page sequence index
	const size_t start;// Page starting character position

	// Returns length of buffer page contents
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
