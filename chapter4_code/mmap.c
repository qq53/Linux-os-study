/// \file mmap.c
/*
  ------------------------------------
  Create date : 2015-04-09 19:28
  Modified date: 2015-04-09 19:41
  Author : Sen1993
  Email : gsen1993@gmail.com
  ------------------------------------
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/mman.h>

int main(int argc, char *argv[]){
	int source;
	int dest;
	struct stat statbuf;
	void *pDest, *pSource;
	if(argc < 3){
		printf("Usage: ./a.out source dest\n");
		return 0;
	}
	source = open(argv[1], O_RDONLY);
	dest = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if(source < 0 || dest < 0){
		printf("open file fail\n");
		goto fail;
	}
	if( fstat(source, &statbuf) < 0 ){
		printf("fstat fail\n");
		goto fail;
	}
	if( ftruncate(dest, statbuf.st_size) == -1){
		printf("ftruncate fail\n");
		goto fail;
	}
	pSource = mmap(0, (size_t)statbuf.st_size, PROT_READ, MAP_PRIVATE | MAP_NORESERVE, source, 0);
	if(pSource == MAP_FAILED){
		printf("mmap source file fail\n");
		goto fail;	
	}
	pDest = mmap(0, (size_t)statbuf.st_size, PROT_WRITE, MAP_SHARED, dest, 0);
	if(pDest == MAP_FAILED){
		printf("mmap dest file fail\n");
		goto fail;
	}
	memcpy(pDest, pSource, (size_t)statbuf.st_size);

fail:
	close(source);
	close(dest);
	return 0;
}
