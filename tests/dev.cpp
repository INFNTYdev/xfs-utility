
#include<iostream>
#include<fstream>

#include"xfsutil/buffer/interface/buffer_page_i.h"
#include"xfsutil/buffer/interface/page_in_i.h"
#include"xfsutil/buffer/interface/page_out_i.h"


// Maybe? (These could go in the DBuff namespace)
// That namespace needs a better name, the file as well

//using BufferPage = IBufferPage<char>;// ASCII, ANSI, E-ASCII (8-bit encoding)
//using BufferPage_u8 = IBufferPage<char8_t>;// ASCII, ANSI, E-ASCII, UTF-8 (8-bit encoding)
//using BufferPage_u16 = IBufferPage<char16_t>;// UTF-16 (16-bit encoding)
//using BufferPage_u32 = IBufferPage<char32_t>;// UTF-32 (32-bit encoding)


int main(size_t argc, char* argv[])
{
	// -> The use of char16_t causes overwhelming amount of compiler warnings
	// -> The same is likely to be said for char32_t; review warnings for meaning!
	// -> If using a higher char size, std::basic_EVERYTHING_U_NAME_IT becomes the story
	// -> The buffer pages appear to be working correctly SO FAR
	// -> Need to learn more about dealing with wider chars


	//
	const std::string path{
		"F:\\InfinSys\\vc\\xfs-utility\\tests\\micro.txt"
	};

	std::ifstream file{ path };

	uint32_t pageSize{ 5 };


	//
	IBufferPageIn<char> test{ pageSize, 0, 0 };

	return 0;
}
