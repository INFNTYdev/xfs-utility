
#ifndef XFS_BUFFER_FILE_PAGE_IN_I_H_
#define XFS_BUFFER_FILE_PAGE_IN_I_H_



#include"xfsutil/buffer/interface/buffer_page_i.h"


// Templated input buffer page interface
template <typename CharT>
class IBufferPageIn : public IBufferPage<CharT> {

public:
	IBufferPageIn(const uint32_t& bytes, const size_t& page_index, const size_t& c_start)
		: IBufferPage<CharT>{ bytes, page_index, c_start }
	{
		//
	}

	virtual ~IBufferPageIn() = default;


	/* Returns number of characters in contents */
	size_t contentLength() const noexcept
	{
		return ((this->m_stopPos + 1) - this->startPos);// +1 for zero index
	}

	/* Read page contents into memory */
	[[nodiscard]] bool cacheContents(std::basic_ifstream<CharT>& file_stream) noexcept
	{
		if (file_stream.fail() || !file_stream.is_open())
			return false;

		file_stream.seekg(this->startPos, std::ios::beg);

		if (file_stream.fail()) {
			file_stream.clear();

			return false;
		}

		if (this->isCached())
			this->clear();

		// Failed to allocate character array
		if (!this->allocateContentsArray(this->pageLength())) {
			file_stream.clear();

			return false;
		}

		CharT character;
		size_t position{ 0 };

		while (position != this->contentLength() && file_stream.get(character)) {

			this->m_str_ptr[position] = character;
			++position;

		}

		// Oversized page needs to be resized
		if (position != this->contentLength()) {
			size_t remainder{ (this->pageLength() - position) };
			size_t newSize{ ((this->pageLength() + 1) - remainder) };

			this->m_stopPos = (this->startPos + (position - 1));// -1 for zero index

			if (!this->reallocateContentsArray(newSize)) {
				this->clear();

				return false;
			}
		}

		this->m_str_ptr[position] = '\0';

		return true;
	}

	/* Returns view of cached page contents */
	std::basic_string_view<CharT> contents() const
	{
		if (!this->isCached())
			return std::basic_string_view<CharT>{};

		return this->m_str_ptr;
	}


protected:
	//

};



#endif // XFS_BUFFER_FILE_PAGE_IN_I_H_
