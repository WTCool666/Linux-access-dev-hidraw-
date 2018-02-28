#include"HidrawManager.h"

HidrawManager::HidrawManager():fd(-1){
}

HidrawManager::~HidrawManager(){
	closeHidraw();
}
bool HidrawManager::isSelfHidraw(){
	struct hidraw_devinfo raw_info;
	struct hidraw_report_descriptor rep_des;
	int desc_size = 0;
	
	if(-1 == ioctl(fd, HIDIOCGRAWINFO, &raw_info)){
		return false;
       }
	
	if(ioctl(fd, HIDIOCGRDESCSIZE, &desc_size) < 0) {
		return false;
	}
      rep_des.size = desc_size;
	if(4096 == raw_info.product && 1546 == raw_info.vendor)//
	{
		return true;
	}
	return false;
}
int HidrawManager::openHidraw(){
	int result=-1;
	DIR *dir = NULL;
       struct dirent *hidraw = NULL;
	char path[HIDRAW_PATH_SIZE];
	dir = opendir(HIDRAW_DIR);
       if(dir == NULL) 
	{
	  return -1;
       }
	memset(path,0x00,sizeof(path));
	strcpy(path,HIDRAW_DIR);
	do{
		if(!(hidraw = readdir(dir))){
			goto EXIT;
		}
		if(hidraw!=NULL){
		   if(hidraw->d_name == NULL){
	             continue;
	         }
             }
		if(!strstr(hidraw->d_name,"hidraw"))
		{
			continue;
		}
		memset(&path[sizeof(HIDRAW_DIR)-1],0x00,sizeof(path)-sizeof(HIDRAW_DIR));
		strcpy(&path[sizeof(HIDRAW_DIR)-1],hidraw->d_name);
		fd=open(path,O_RDWR);
		if(fd<0){
			continue;
		}
		if(isSelfHidraw()){
			result=fd;
		}
	}while(hidraw != NULL);
	
	EXIT:	
	closedir(dir);

	return result;
}
int HidrawManager::writeHidraw(char* buf,unsigned int size){
	int ret = -1;
	ret = write(fd,buf,size);
	return ret;
}
int HidrawManager::readHidraw(char* buf,unsigned int size){
	int ret = -1;
	ret = read(fd,buf,size);
	return ret;
}

int HidrawManager::closeHidraw(){
	int ret = -1;
	ret = close(fd);
	return ret;
}