
#include<iostream>
#include<fstream>

#include"xfsutil/buffer/interface/buffer_page_i.h"


template <typename T>
void pageStateOut(const IBufferPage<T>& page)
{
	std::cout
		<< std::boolalpha
		<< "\n- PAGE STATE -"
		<< "\nIndex   : " << page.pageIndex
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
	// -> The buffer pages appear to be working correctly SO FAR
	// -> Need to learn more about dealing with wider chars


	//
	const std::string path{
		"F:\\InfinSys\\vc\\xfs-utility\\tests\\micro.txt"
	};

	std::ifstream file{ path };

	
	//
	IBufferPage<char> page1{ 4, 0, 0 };
	IBufferPage<char> page2{ 4, 1, (page1.stop() + 1) };
	IBufferPage<char> page3{ 4, 2, (page2.stop() + 1) };

	bool succ = page1.cacheContents(file);
	succ = page2.cacheContents(file);
	succ = page3.cacheContents(file);

	std::cout << "\nOUTPUT: "
		<< page1.contents()
		<< page2.contents()
		<< page3.contents()
		<< std::endl;

	pageStateOut(page1);
	pageStateOut(page2);
	pageStateOut(page3);

	if (file.is_open())
		file.close();

	return 0;
}
