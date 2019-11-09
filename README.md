http://www.fpgadeveloper.com/2014/07/creating-a-base-system-for-the-zynq-in-vivado.html
 
http://www.fpgadeveloper.com/2014/08/creating-a-custom-ip-block-in-vivado.html

https://reactos.org/

http://usbip.sourceforge.net/#documentation

https://lwn.net/Articles/449509/

https://pdfs.semanticscholar.org/c7c4/cb054d75810fdb0a2affa11c288b7687267f.pdf

https://bootlin.com/docs/

https://docs.microsoft.com/en-us/windows/win32/winsock/complete-client-code

https://drive.google.com/file/d/1te6WUcKBFHNJN5ORVpYXtTPjyDfXFbp4/view?usp=sharing

#include "queue.h"
queue* CreateQueue(int32_t capacity) {
    queue* ret_queue = (queue*)malloc(1*sizeof(queue));
    ret_queue->req_queue = (request**)malloc(20*sizeof(request*));
    ret_queue->capacity = capacity;
    ret_queue->front = 0;
    ret_queue->rear = -1;
    //ret_queue->rear = capacity - 1;
    return ret_queue;
}
bool IsFull(queue *str_queue) {
    return (str_queue->size == str_queue->capacity);
}

bool IsEmpty(queue *str_queue) {
    return (str_queue->size == 0);
}

void EnQueue(queue *str_queue, request *add_request) {
    if (IsFull(str_queue)) {
        return;
    }
    str_queue->rear++;
    if (str_queue->rear >= str_queue->capacity) {
        str_queue->rear = -1;
    }
    str_queue->req_queue[str_queue->rear] = add_request;
    str_queue->size++;
}

request* DeQueue(queue *str_queue) {
    request *element_get;
    if (IsEmpty(str_queue)) {
        return NULL;
    }
    element_get = str_queue->req_queue[str_queue->front];
    str_queue->front++;
    if (str_queue->front >= str_queue->capacity) {
        str_queue->front = 0;
    }
    str_queue->size--;
    return element_get;
}

request* GetFrontQueue(queue *str_queue) {
    if (IsEmpty(str_queue)) {
         return NULL;
    }
    return str_queue->req_queue[str_queue->front];
}
request* GetRearQueue(queue *str_queue) {
    if (IsFull(str_queue)) {
        return NULL;
    }
    return str_queue->req_queue[str_queue->rear];
}
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct request {
    void *buff;
    int32_t size;
}request;

typedef struct queue {
    int front, rear, size;
    int32_t capacity;
    request **req_queue;
}queue;

queue* CreateQueue(int32_t capacity);
bool IsFull(queue *str_queue);
bool IsEmpty(queue *str_queue);
void EnQueue(queue *str_queue, request *add_request);
request* DeQueue(queue *str_queue);
request* GetFrontQueue(queue *str_queue);
request* GetRearQueue(queue *str_queue);

