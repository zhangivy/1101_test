#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "make_log.h"


/*
 * 获取 fdfs_uplord_file返回的值
 */
int main(int argc, char *argv[]){
	
//	LOG("test", "test", "逗比了吧");
	if(argc < 2){
		printf("./app filepath\n");
		return -1;
	}

	pid_t			pid = 0;
	int 			fds[2];
	int				ret = 0;
	char 			buf[1024] = { 0 };
	ssize_t			len = 0;

	char			errbuf[1024] = { 0 };

	ret = pipe(0);
	if( ret != 0 ){
		printf("errno  %d\n", errno);
		perror("pipe");
//		read(STDERR_FILENO, errbuf, sizeof(errbuf));
		strerror_r(errno, errbuf, sizeof(buf));
		printf("%s\n", errbuf);
		sprintf(errbuf, "pipe err : %s", strerror(errno));
		LOG("utils", "upload", errbuf);
		return -1;
	}

	pid = fork();
	if(pid < 0){
		perror("fork:");
		return -1;
	}
	if(pid > 0){
		//父进程 读 关闭写端
		close(fds[1]);

		len = read(fds[0], buf, sizeof(buf));
		if(len < 0){
			perror("read");
			return -2;
		}
		printf("%s", buf);

	}else{
		//子进程
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);   //
		execlp("fdfs_upload_file", "", "/etc/fdfs/client.conf", argv[1] , NULL);
	}




	return 0;
}
