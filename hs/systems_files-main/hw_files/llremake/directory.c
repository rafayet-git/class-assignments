#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

char* compactSize(long bytes, char* bytestr){
	int xbyte = 0;
	long newbyte = bytes;
	while (newbyte > 1024){
		newbyte = newbyte / 1024;
		xbyte++;
	}
	if (xbyte==0){	
		sprintf(bytestr, "%ldB", newbyte);
	}else if (xbyte==1){
		sprintf(bytestr, "%ldKB", newbyte);	
	}else if (xbyte==2){
		sprintf(bytestr, "%ldMB", newbyte);	
	
	}else if (xbyte==3){
		sprintf(bytestr, "%ldGB", newbyte);	
	
	}else if (xbyte==4){
		sprintf(bytestr, "%ldTB", newbyte);	
	} else{
		bytestr = "1PB+";
	}return bytestr;


}

int main(int argc, char *argv[]){
	if (argc >2) return -1;
	DIR *d;
	if (argc == 2){
		d = opendir(argv[1]);
	} else {
		d = opendir(".");
	}
	struct dirent *entry = readdir(d);
	int filecount = 0;
	long dirsize = 0;
	int type;
	char *typename;
	struct stat filestats;
	char strsiz[7];
	printf("\e[1;33mSIZE\tTYPE\t\tNAME\n\e[m");
	while (entry){
		type = entry->d_type;
		filecount++;
		switch(type){
			case DT_UNKNOWN:
				typename = "unknown ";
				break;
			case DT_REG:
				typename = "regularfile";
				break;
			case DT_DIR:
				typename = "directory ";
				break;
			case DT_FIFO:
				typename = "pipe/FIFO ";
				break;
			case DT_SOCK:
				typename = "socket ";
				break;
		}
		stat(entry->d_name,&filestats);
		compactSize(filestats.st_size, strsiz);
		printf("%s", strsiz);
		dirsize = dirsize + filestats.st_size;
		printf("\t%s", typename);
		printf("\t%s",entry->d_name);
		printf("\n");
		entry = readdir(d);
	}
	compactSize(dirsize, strsiz);
	printf("total files:%d size:%s\n", filecount, strsiz);
	closedir(d);

}
