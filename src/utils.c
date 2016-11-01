#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "ivy_log.h"

int uploadFile(const char *filepath, char *strIdBuf, int len){
	pid_t			pid = 0;
	int 			fds[2];
	int				ret = 0;
	char 			errbuf[1024] = { 0 };
	ssize_t			len = 0;

	ret = pipe(fds);
	if( ret != 0 ){
		perror("pipe:");
		memset(errbuf, 0, sizeof(errbuf));
		sprintf(errbuf, "pipe err : %s\n", strerror(errno));
		LOG("utils", "upload", errbuf);
		return -1;
	}

	pid = fork();
	if(pid < 0){
		perror("fork:");
		memset(errbuf, 0, sizeof(errbuf));
		sprintf(errbuf, "fork err : %s\n", strerror(errno));
		LOG("utils", "upload", errbuf);
		return -1;
	}
	if(pid > 0){
		//父进程 读 关闭写端
		close(fds[1]);

		len = read(fds[0], buf, sizeof(buf));
		if(len < 0){
			perror("read");
			memset(errbuf, 0, sizeof(errbuf));
			sprintf(errbuf, "read err : %s\n", strerror(errno));
			LOG("utils", "upload", errbuf);
			return -2;
		}
//		printf("%s", buf);

	}else{
		//子进程
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);   //
		execlp("fdfs_upload_file", "", "/etc/fdfs/client.conf", filepath , NULL);
	}

}
