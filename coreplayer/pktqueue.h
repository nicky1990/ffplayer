#ifndef _PKT_QUEUE_H_
#define _PKT_QUEUE_H_

// ����ͷ�ļ�
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

// avformat.h
#include "libavformat/avformat.h"

// ��������
// it must be:
// DEF_PKT_QUEUE_FSIZE == (DEF_PKT_QUEUE_ASIZE + DEF_PKT_QUEUE_VSIZE)
#define DEF_PKT_QUEUE_FSIZE   64
#define DEF_PKT_QUEUE_ASIZE   32
#define DEF_PKT_QUEUE_VSIZE   32

typedef struct {
    long       fsize;
    long       asize;
    long       vsize;
    long       fhead;
    long       ftail;
    long       ahead;
    long       atail;
    long       vhead;
    long       vtail;
    long       fpktnum;
    long       apktnum;
    long       vpktnum;
    HANDLE     fsemr;
    HANDLE     asemr;
    HANDLE     asemw;
    HANDLE     vsemr;
    HANDLE     vsemw;
    AVPacket  *bpkts; // packet buffers
    AVPacket **fpkts; // free packets
    AVPacket **apkts; // audio packets
    AVPacket **vpkts; // video packets
} PKTQUEUE;

// ��������
BOOL pktqueue_create (PKTQUEUE *ppq);
void pktqueue_destroy(PKTQUEUE *ppq);
void pktqueue_flush  (PKTQUEUE *ppq);

void pktqueue_write_request(PKTQUEUE *ppq, AVPacket **pppkt);
void pktqueue_write_release(PKTQUEUE *ppq);
void pktqueue_write_done_a(PKTQUEUE *ppq);
void pktqueue_write_done_v(PKTQUEUE *ppq);

void pktqueue_read_request_a(PKTQUEUE *ppq, AVPacket **pppkt);
void pktqueue_read_done_a  (PKTQUEUE *ppq);

void pktqueue_read_request_v(PKTQUEUE *ppq, AVPacket **pppkt);
void pktqueue_read_done_v  (PKTQUEUE *ppq);

#ifdef __cplusplus
}
#endif

#endif




