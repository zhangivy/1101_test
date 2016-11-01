#ifndef _UTILS_H_
#define _UTILS_H_


/*
 * 上传文件
 * filepath		上传文件的路径
 * strIdBuf		上传后文件保存的id号
 * len			strIdBuf缓存区的大小
 */
int uploadFile(const char *filepath, char *strIdBuf, int len);


#endif
