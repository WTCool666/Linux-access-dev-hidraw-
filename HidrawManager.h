#ifndef HIDRAW_MANAGER_H
#define  HIDRAW_MANAGER_H
#include <linux/types.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#define HIDRAW_DIR 				"/dev/"
#define HIDRAW_PATH_SIZE 		20
class HidrawManager{
public:
	HidrawManager();
	virtual ~HidrawManager();
	int openHidraw();
	int writeHidraw(char* buf,unsigned int size);
	int readHidraw(char* buf,unsigned int size);
	int closeHidraw();
	bool isSelfHidraw();
private:
	int fd;
		
};

#endif


