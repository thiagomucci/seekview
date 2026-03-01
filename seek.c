#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define MAXBUF 4096

int
main(int argc, char *argv[])
{
	ssize_t n;
	char buf[MAXBUF];
	int whence;

	if(argc != 4)
	{
		write(STDERR_FILENO,
				"try: ./prog <file> <offset <whence>\n",
					sizeof("try: ./prog <file> <offset> <whence>\n") -1);
		exit(1);
	}

	int fd = open(argv[1], O_RDONLY);
	if(fd < 0)
	{
		perror("open");
		exit(1);
	}
	off_t offset = strtoll(argv[2], NULL, 10);
	if(strcmp(argv[3], "set") == 0)
	{
		whence = SEEK_SET;
	}
	else if(strcmp(argv[3], "cur") == 0)
	{
		whence = SEEK_CUR;
	}
	else if(strcmp(argv[3], "end") == 0)
	{
		whence = SEEK_END;
	}
	else{
		write(STDERR_FILENO,
				"whence: <set> || <cur> || <end>\n",
					sizeof("whence: <set> || <cur> || <end>\n") -1);
		exit(1);
	}
	off_t new_offset = lseek(fd, offset, whence);
	if(new_offset == -1)
	{
		perror("lseek");
		exit(1);
	}
	while((n = read(fd, buf, MAXBUF)) > 0)
	{
		ssize_t count = 0;
		while(count < n)
		{
			ssize_t w = write(STDOUT_FILENO, buf + count, n - count);
			if(w < 0)
			{
				perror("write");
				exit(1);
			}
			count += w;
		}
	}
	if(n < 0)
	{
		perror("read");
		exit(1);
	}

	if(close(fd) < 0)
	{
		perror("close");
		exit(1);
	}
	return 0;
}

