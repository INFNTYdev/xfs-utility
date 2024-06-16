
#ifndef XFS_BUFFER_FILE_PAGE_I_H_
#define XFS_BUFFER_FILE_PAGE_I_H_



#include<cstdint>
#include<ostream>
#include<fstream>
#include<string_view>


// File buffer page interface
template <typename CharT>
class IBufferPage {

public:
	IBufferPage(const uint32_t& size, const size_t& page_index, const size_t& c_start);
	IBufferPage(const IBufferPage&) = delete;
	IBufferPage(IBufferPage&&) = delete;
	virtual ~IBufferPage();

	friend std::ostream& operator<<(std::ostream& os, const IBufferPage& page);

	IBufferPage& operator=(const IBufferPage&) = delete;
	IBufferPage& operator=(IBufferPage&&) = delete;

	const size_t pageIndex;// Page index in sequence
	const size_t start;// Page starting character position

	// Returns number of characters buffer page holds
	size_t length() const noexcept;
	// Returns size of buffer page contents in bytes
	size_t pageSize() const noexcept;
	// Returns page ending character position
	const size_t& stop() const noexcept;
	// Returns true if page contents are cached in memory
	bool isCached() const noexcept;
	/* Read page contents into memory */
	[[nodiscard]] bool cacheContents(std::basic_ifstream<CharT>& file_stream) noexcept;
	// Returns view of page contents
	std::basic_string_view<CharT> contents() const;
	// Clear page contents from memory
	void flushCache() noexcept;


protected:
	size_t m_stopPos;
	CharT* m_str_ptr;

};



#endif // XFS_BUFFER_FILE_PAGE_I_H_
