
#ifndef _XFS_PATH_SYSTEM_PATH_ATTR_H_
#define _XFS_PATH_SYSTEM_PATH_ATTR_H_

typedef struct _SYSTEM_PATH_ATTRIBUTES {
	bool isLegalStr{ false };// Legal path string flag
	bool isDirPath{ false };// Directory path flag
	size_t nodeQ{ 0 };// Path node quantity
} SysPathAttr;

#endif // _XFS_PATH_SYSTEM_PATH_ATTR_H_
