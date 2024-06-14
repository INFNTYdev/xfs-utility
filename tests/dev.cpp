
#include<iostream>

#include"xfsutil/buffer/buffer_page.h"
#include"xfsutil/path/util/path_tool.h"


int main(size_t argc, char* argv[])
{
	//
	const std::string path{
		"F:\\InfinSys\\vc\\xfs-utility\\tests\\buffer_dev.txt"
	};

	std::ifstream file{ path };

	BufferPage test{ BufferPage::SIZE_DEV, 6, 62 };

	if (!test.cachePageContents(file))
		std::cout << "\nCache failed" << std::endl;
	else
		std::cout << "\nSuccessful cache" << std::endl;

	if (file.is_open())
		file.close();

	std::cout << PathT::getHighestCommonTarget(path, path) << std::endl;

	return 0;
}
