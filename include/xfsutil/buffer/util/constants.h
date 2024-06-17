
#ifndef XFS_BUFFER_CONSTANTS_H_
#define XFS_BUFFER_CONSTANTS_H_



#include<cstdint>


// Dynamic file buffer constants
namespace DBuff
{

	// File buffer limit constants
	namespace Limit
	{

		extern const uint8_t MIN_CHAR_SPACE;// Minimum page character space required
		extern const uint8_t MIN_ALLOC_BYTES;// Minimum character memory allocation 2 bytes
		extern const uint32_t MAX_ALLOC_BYTES;// Maximum character memory allocation 1,073,741,824 bytes = 1GB
		extern const uint32_t MAX_PAGE_BYTES;// Maximum character memory allocation for page 536,870,912 bytes = 512MB

	}

	// 8-bit character constants (1 byte)
	namespace Char
	{

		const uint32_t SIZE_DEV{ 10 };// 10 1 byte characters = 10 Bytes
		extern const uint32_t SIZE_2KB;// 2,048 1 byte characters = 2KB
		extern const uint32_t SIZE_4KB;// 4,096 1 byte characters = 4KB
		extern const uint32_t SIZE_8KB;// 8,192 1 byte characters = 8KB
		extern const uint32_t SIZE_16KB;// 16,384 1 byte characters = 16KB
		extern const uint32_t SIZE_32KB;// 32,768 1 byte characters = 32KB
		extern const uint32_t SIZE_64KB;// 65,536 1 byte characters = 64KB
		extern const uint32_t SIZE_128KB;// 131,072 1 byte characters = 128KB
		extern const uint32_t SIZE_256KB;// 262,144 1 byte characters = 256KB
		extern const uint32_t SIZE_512KB;// 524,288 1 byte characters = 512KB
		extern const uint32_t SIZE_1MB;// 1,048,576 1 byte characters = 1MB
		extern const uint32_t SIZE_2MB;// 2,097,152 1 byte characters = 2MB
		extern const uint32_t SIZE_4MB;// 4,194,304 1 byte characters = 4MB
		extern const uint32_t SIZE_8MB;// 8,388,608 1 byte characters = 8MB
		extern const uint32_t SIZE_16MB;// 16,777,216 1 byte characters = 16MB
		extern const uint32_t SIZE_32MB;// 33,554,432 1 byte characters = 32MB

	}

	// 16-bit character constants (2 bytes)
	namespace Wchar
	{

		extern const uint32_t SIZE_2KB;// 1,024 2 byte characters = 2KB
		extern const uint32_t SIZE_4KB;// 2,048 2 byte characters = 4KB
		extern const uint32_t SIZE_8KB;// 4,096 2 byte characters = 8KB
		extern const uint32_t SIZE_16KB;// 8,192 2 byte characters = 16KB
		extern const uint32_t SIZE_32KB;// 16,384 2 byte characters = 32KB
		extern const uint32_t SIZE_64KB;// 32,768 2 byte characters = 64KB
		extern const uint32_t SIZE_128KB;// 65,536 2 byte characters = 128KB
		extern const uint32_t SIZE_256KB;// 131,072 2 byte characters = 256KB
		extern const uint32_t SIZE_512KB;// 262,144 2 byte characters = 512KB
		extern const uint32_t SIZE_1MB;// 524,288 2 byte characters = 1MB
		extern const uint32_t SIZE_2MB;// 1,048,576 2 byte characters = 2MB
		extern const uint32_t SIZE_4MB;// 2,097,152 2 byte characters = 4MB
		extern const uint32_t SIZE_8MB;// 4,194,304 2 byte characters = 8MB
		extern const uint32_t SIZE_16MB;// 8,388,608 2 byte characters = 16MB
		extern const uint32_t SIZE_32MB;// 16,777,216 2 byte characters = 32MB

	}

	// 32-bit character constants (4 bytes)
	namespace UWchar {

		extern const uint32_t SIZE_2KB;// 512 4 byte characters = 2KB
		extern const uint32_t SIZE_4KB;// 1,024 4 byte characters = 4KB
		extern const uint32_t SIZE_8KB;// 2,048 4 byte characters = 8KB
		extern const uint32_t SIZE_16KB;// 4,096 4 byte characters = 16KB
		extern const uint32_t SIZE_32KB;// 8,192 4 byte characters = 32KB
		extern const uint32_t SIZE_64KB;// 16,384 4 byte characters = 64KB
		extern const uint32_t SIZE_128KB;// 32,768 4 byte characters = 128KB
		extern const uint32_t SIZE_256KB;// 65,536 4 byte characters = 256KB
		extern const uint32_t SIZE_512KB;// 131,072 4 byte characters = 512KB
		extern const uint32_t SIZE_1MB;// 262,144 4 byte characters = 1MB
		extern const uint32_t SIZE_2MB;// 524,288 4 byte characters = 2MB
		extern const uint32_t SIZE_4MB;// 1,048,576 4 byte characters = 4MB
		extern const uint32_t SIZE_8MB;// 2,097,152 4 byte characters = 8MB
		extern const uint32_t SIZE_16MB;// 4,194,304 4 byte characters = 16MB
		extern const uint32_t SIZE_32MB;// 8,388,608 4 byte characters = 32MB

	}

}



#endif // XFS_BUFFER_CONSTANTS_H_
