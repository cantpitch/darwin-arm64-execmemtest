#include <errno.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

void *heap = (void *)0x300000000000;
int page_size_16k = 0x4000;

typedef int (*fnptr)(void);

int main(int argc, const char * argv[]) {
    uint64_t *addr = mmap(heap, page_size_16k,
                          PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE | MAP_JIT, -1, 0);
    
    if (MAP_FAILED == addr)
    {
        printf("mmap failed. %d\n", errno);
        printf("%s\n", strerror(errno));
    }
    
    printf("mmap'd %p\n", (void *)addr);
    
    pthread_jit_write_protect_np(0);
    addr[0] = 0xd65f03c0d28000e0; // mov     x0, #7; ret
    pthread_jit_write_protect_np(1);
    
    printf("value: 0x%08llx\n", addr[0]);

    fnptr fn = (fnptr)addr;
    int ret = (*fn)();
    
    printf("retvalue: %d\n", ret);
    
    return 0;
}
