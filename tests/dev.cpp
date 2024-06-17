
#include<iostream>
#include<fstream>

#include"xfsutil/buffer/interface/buffer_page_i.h"


template <typename T>
void pageStateOut(const IBufferPage<T>& page)
{
	std::cout
		<< std::boolalpha
		<< "\n- PAGE STATE -"
		<< "\nStart   : " << page.startPos
		<< "\nStop    : " << page.stop()
		<< "\nLength  : " << page.pageLength()
		<< "\nStr Len : " << page.contentLength()
		<< "\nM. size : " << page.contentSize() << " bytes"
		<< "\nCached  : " << page.isCached()
		<< std::endl;
}


int main(size_t argc, char* argv[])
{
	/*
	* 
	* char			| ASCII, ANSI, E-ASCII
	* char8_t		| ASCII, ANSI, E-ASCII, UTF-8
	* char16_t		| UTF-16
	* char32_t		| UTF-32
	* 
	*/


	// There is a lot of nonsense everywhere, kindly ignore it

	// -> The use of char16_t causes overwhelming amount of compiler warnings
	// -> The same is likely to be said for char32_t; review warnings for meaning!
	// -> If using a higher char size, std::basic_EVERYTHING_U_NAME_IT becomes the story


	//
	const std::string path{
		"F:\\InfinSys\\vc\\xfs-utility\\tests\\micro.txt"
	};

	std::ifstream file{ path };
	std::basic_ifstream<char16_t, std::char_traits<char16_t>> file16_b{ path };

	
	//
	IBufferPage<char> test8_bit{ 4, 0, 0 };
	IBufferPage<char16_t> test16_bit{ 4, 1, (test8_bit.stop() + 1) };

	bool succ_8bit = test8_bit.cacheContents(file);
	bool succ_16bit = test16_bit.cacheContents(file16_b);

	std::string regularString{ test8_bit.contents() };
	std::basic_string<char16_t> n16bitString{ test16_bit.contents() };

	std::cout << test8_bit.contents();
	std::cout << reinterpret_cast<const char*>(n16bitString.data());

	pageStateOut(test8_bit);
	pageStateOut(test16_bit);

	return 0;
}
