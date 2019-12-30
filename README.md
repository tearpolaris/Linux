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

#include "usb_func_driver.h"
#include <stdio.h>
#include <stdint.h>

void callback(uint32_t adr, uint8_t *buff, uint32_t size);
void callback(uint32_t adr, uint8_t *buff, uint32_t size) {
    uint8_t reg_val, idx;

    reg_val = idx = 0; 
  
    while (idx < size) {
       reg_val = Read8_Register(adr);
       buff[idx] = reg_val;
       idx++;
    }
    
    else if (Read_Register(REGISTER_STATE) == 2) {
        printf("Nadal beats Zerev\n");
    }
}

#include "usb_func_model.h"

void DMAWriteCallback(void (*callback)(uint32_t adr, uint8_t *buff, uint32_t size)) {
    callback();
}

#include <stdio.h>
#include <stdint.h>
void DMAWriteCallback(void (*callback)(uint32_t adr, uint8_t *buff, uint32_t size


Generating a variable-length memory pool
+ Get memory block from variable-length memory pool
+ Delete a variable-length memory pool
+ Acquiring memory blocks from variable-length memory pools


+ generate and start a task int8_t *name, int32_t priority, int32_t stacksize, FP entryptr, uint32_t arg
+ Launching a task int32_t tskid, int32_t arg
+ Terminate a task + delete a task: int32_t id

https://gist.github.com/ngryman/6482577


#include "bsakr_commu.h"


Event_t arr_event[MAX_EVENT];
int32_t evt_num = 0;

int8_t* search_evt_obj(int32_t flgid) {
    return arr_event[flgid].name;
}

bool check_timeout(int32_t timeout) {
    if (timeout < BSA_WAIT_FOREVER) {
        return false;
    }
    else {
        return true;
    }
}

bool check_mode(int32_t mode) {
    if ((mode != WAIT_EVTFLG_AND) && (mode != WAIT_EVTFLG_OR)) {
        return false;
    }
    else {
        return true;
    }
}

bool get_mode(int32_t mode) {
    return (mode == WAIT_EVTFLG_AND) ? true : false;
}

int32_t get_timeout(int32_t timeout) {
    int32_t ret_time;
    if (timeout == BSA_WAIT_FOREVER) {
        ret_time = INFINITE;
    }
    else {
        ret_time = timeout;
    }
    return ret_time;
}

int32_t bsa_create_msg(int8_t *name, int32_t msgbfsz, int32_t maxbytes)
{
    return 0;
}
int32_t bsakr_create_evtflg(int8_t *name, uint32_t flgptn)
{
#ifdef _WIN32
    HANDLE evt_obj[BIT_WIDTH];
    bool dup_flgptn;
    int32_t ret_cre;
    char *name_evt;

    name_evt = (char*)malloc(strlen((char*)name)+8);

    for (int i = 0; i < BIT_WIDTH; i++) {
        dup_flgptn = ((flgptn >> i) & (uint8_t)0x1);
        sprintf_s(name_evt, MAX_LENGTH, "%s%d", name, i);
        evt_obj[i] = CreateEventA(NULL, true, dup_flgptn, (LPCSTR)name_evt);
        if (!evt_obj) {
            dump_message_dummy("There is no spcace for creating event\n");
            return E_LIMIT;
        }
        arr_event[evt_num].hdl_obj[i] = evt_obj[i];
    }
    memcpy(arr_event[evt_num].name, name, strlen((char*)name));
    arr_event[evt_num].id = evt_num;
    ret_cre = evt_num;
    evt_num++;
    return ret_cre;
#endif
}

int32_t bsakr_wait_evtflg(int32_t flgid, uint32_t flgptn, uint32_t *p_flgptn, int32_t mode, int32_t timeout)
{
    HANDLE ptn_obj[BIT_WIDTH];
    bool bit_ptn, bwaitall;
    int32_t idx_ptn_obj, inter_time, count_bit_one, org;
    DWORD ret_wait;

    *p_flgptn = 0;
    idx_ptn_obj = 0;
    count_bit_one = -1;
    org = 0;

    if (!search_evt_obj(flgid)) {
        dump_message_dummy("Flag id is not exist\n");
        return E_NOEXS;
    }

    if ((!check_timeout(timeout)) || (!check_mode(mode))) {
        dump_message_dummy("Argument is invalid\n");
        return E_PAR;
    }

    for (int i = 0; i < BIT_WIDTH; i++) {
        bit_ptn = (flgptn >> i) & 0x1;
        if (bit_ptn) {
            ptn_obj[idx_ptn_obj++] = arr_event[flgid].hdl_obj[i];
        }
    }
    bwaitall = get_mode(mode);
    inter_time = get_timeout(timeout);
    ret_wait = WaitForMultipleObjects(idx_ptn_obj, ptn_obj, bwaitall, inter_time);

    if (ret_wait == WAIT_TIMEOUT) {
        return E_TMOUT;
    }
    else if (ret_wait == WAIT_FAILED) {
        return E_SYS;
    }

    if (bwaitall) {
        *p_flgptn = flgptn;
    }
    else {
        for (int j = 0; j < BIT_WIDTH; j++) {
            bit_ptn = (flgptn >> j) & 0x1;
            if (bit_ptn) {
                count_bit_one++;
            }
            if (count_bit_one == ret_wait) {
                *p_flgptn |= (0x1 << j);
                break;
            }
        }
    }
    return E_OK;
}

int32_t bsakr_set_evtflg(int32_t flgid, uint32_t flgptn)
{
    int32_t bit_ptn;
    if (!search_evt_obj(flgid)) {
        dump_message_dummy("Flag id is not exist\n");
        return E_NOEXS;
    }
    for (int i = 0; i < BIT_WIDTH; i++) {
        bit_ptn = (flgptn >> i) & 0x1;
        if (bit_ptn) {
            SetEvent(arr_event[flgid].hdl_obj[i]);
        }
    }
    return E_OK;
}

int32_t bsakr_clear_evtflg(int32_t flgid, uint32_t flgptn)
{
    int32_t bit_ptn;
    if (!search_evt_obj(flgid)) {
        dump_message_dummy("Flag id is not exist\n");
        return E_NOEXS;
    }
    for (int i = 0; i < BIT_WIDTH; i++) {
        bit_ptn = (flgptn >> i) & 0x1;
        if (bit_ptn) {
            ResetEvent(arr_event[flgid].hdl_obj[i]);
        }
    }
    return E_OK;
}

