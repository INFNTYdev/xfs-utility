
#ifndef XFS_BUFFER_FILE_BUFFER_DEF_
#define XFS_BUFFER_FILE_BUFFER_DEF_



#include"xfsutil/buffer/interface/page_in_i.h"
#include"xfsutil/buffer/interface/page_out_i.h"


// File Input Buffer Pages

using BufferPageIn = IBufferPageIn<char>;// ASCII, ANSI, E-ASCII (8-bit encoding)
using BufferPageIn_u8 = IBufferPageIn<char8_t>;// ASCII, ANSI, E-ASCII, UTF-8 (8-bit encoding)
using BufferPageIn_u16 = IBufferPageIn<char16_t>;// UTF-16 (16-bit encoding)
using BufferPageIn_u32 = IBufferPageIn<char32_t>;// UTF-32 (32-bit encoding)


// File Output Buffer Pages

using BufferPageOut = IBufferPageOut<char>;// ASCII, ANSI, E-ASCII (8-bit encoding)
using BufferPageOut_u8 = IBufferPageOut<char8_t>;// ASCII, ANSI, E-ASCII, UTF-8 (8-bit encoding)
using BufferPageOut_u16 = IBufferPageOut<char16_t>;// UTF-16 (16-bit encoding)
using BufferPageOut_u32 = IBufferPageOut<char32_t>;// UTF-32 (32-bit encoding)



#endif // XFS_BUFFER_FILE_BUFFER_DEF_
