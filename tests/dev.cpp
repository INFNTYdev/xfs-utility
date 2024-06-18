
#include<iostream>
#include<fstream>

#include"xfsutil/buffer/fbuffer.h"


// Maybe? (These could go in the DBuff namespace)
// That namespace needs a better name, the file as well


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
	BufferPageIn test{ pageSize, 0, 0 };

	return 0;
}
