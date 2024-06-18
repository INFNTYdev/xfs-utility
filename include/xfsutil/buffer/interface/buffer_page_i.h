
#ifndef XFS_BUFFER_FILE_PAGE_I_H_
#define XFS_BUFFER_FILE_PAGE_I_H_



#include<cstdint>
#include<ostream>
#include<fstream>
#include<string_view>
#include"xfsutil/buffer/util/constants.h"


// Templated file buffer page interface
template <typename CharT>
class IBufferPage {

public:
	IBufferPage(const uint32_t& bytes, const size_t& page_index, const size_t& c_start)
		: pageIndex{ page_index },
		startPos{ c_start },
		m_stopPos{ calcStopPosition(bytes, c_start) },
		m_str_ptr{ nullptr }
	{
		//
	}
	
	IBufferPage(const IBufferPage&) = delete;
	IBufferPage(IBufferPage&&) = delete;

	virtual ~IBufferPage()
	{
		if (this->isCached())
			this->clear();
	}

	IBufferPage& operator=(const IBufferPage&) = delete;
	IBufferPage& operator=(IBufferPage&&) = delete;

	const size_t pageIndex;// Page index in sequence
	const size_t startPos;// Page starting character position

	/* Returns number of characters buffer page holds */
	size_t pageLength() const noexcept
	{
		return ((this->m_stopPos + 2) - this->startPos);// +2 for null termintor and zero index
	}

	/* Returns size of buffer page contents in bytes */
	size_t contentSize() const noexcept
	{
		if (!this->isCached())
			return size_t(0);

		return (sizeof(CharT) * this->pageLength());
	}

	/* Returns page ending character position */
	const size_t& stop() const noexcept
	{
		return this->m_stopPos;
	}

	/* Returns true if page contents are cached in memory */
	bool isCached() const noexcept
	{
		return (this->m_str_ptr != nullptr);
	}

	/* Clear page contents from memory */
	void clear() noexcept
	{
		if (!this->isCached())
			return;

		delete[] this->m_str_ptr;
		this->m_str_ptr = nullptr;
	}


protected:
	size_t m_stopPos;// Page ending character position
	CharT* m_str_ptr;// Page contents character array

	/* Returns calculated ending character position */
	static size_t calcStopPosition(const uint32_t& page_bytes, const size_t& c_start) noexcept
	{
		size_t charSpace{ (page_bytes / sizeof(CharT)) };

		// Not enough space for characters
		if (charSpace < DBuff::Limit::MIN_CHAR_SPACE)
			return c_start;

		return (c_start + (charSpace - 2));// (-1 for null termintor) + (-1 for zero index)
	}

	/* Returns true if page character indecies are illogical */
	bool hasInvalidIndecies() const noexcept
	{
		return (this->startPos >= this->m_stopPos);
	}

	/* Allocate specified amount of bytes for new character array */
	[[nodiscard]] bool allocateContentsArray(const size_t& chars)
	{
		if (this->m_str_ptr != nullptr)
			return false;

		if ((chars * sizeof(CharT)) < DBuff::Limit::MIN_ALLOC_BYTES)
			return false;

		if ((chars * sizeof(CharT)) > DBuff::Limit::MAX_PAGE_BYTES)
			return false;

		this->m_str_ptr = new CharT[chars];

		return true;
	}

	/* Allocate new specified amount of bytes for existing page character array */
	[[nodiscard]] bool reallocateContentsArray(const size_t& new_bytes)
	{
		if (this->m_str_ptr == nullptr)
			return false;

		if (new_bytes < DBuff::Limit::MIN_ALLOC_BYTES)
			return false;

		if (new_bytes > DBuff::Limit::MAX_PAGE_BYTES)
			return false;

		CharT* temp = (CharT*)realloc(this->m_str_ptr, new_bytes);

		if (temp == nullptr)
			return false;

		this->m_str_ptr = temp;

		return true;
	}

};



#endif // XFS_BUFFER_FILE_PAGE_I_H_
