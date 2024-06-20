
#ifndef XFS_BUFFER_FILE_PAGE_OUT_I_H_
#define XFS_BUFFER_FILE_PAGE_OUT_I_H_



#include"xfsutil/buffer/page/interface/buffer_page_i.h"


// Templated output buffer page interface
template <typename CharT>
class IBufferPageOut : public IBufferPage<CharT> {

public:
	IBufferPageOut(const uint32_t& bytes, const size_t& page_index, const size_t& c_start)
		: IBufferPage<CharT>{ bytes, page_index, c_start }
	{
		//
	}

	virtual ~IBufferPageOut() = default;


protected:
	//

};



#endif // XFS_BUFFER_FILE_PAGE_OUT_I_H_
