#include <errno.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

void *heap = (void *)0x300000000000;
int page_size_16k = 0x4000;

typedef int (*fnptr)(void);

uint64_t *test_mmap(const char *header, void *want, size_t nbytes, int permissions, int flags, int fd, off_t off)
{
    uint64_t *addr = mmap(want, nbytes, permissions,  flags, fd, off);

    if (MAP_FAILED == addr)
    {
        printf("%s mmap failed.    want: %p, flags: 0x%04x, fd: %2d, errno: %d %s\n", 
            header, want, flags, fd, errno, strerror(errno));
    } 
    else 
    {
        printf("%s mmap succeeded. want: %p, flags: 0x%04x, fd: %2d,  addr: %p\n", 
            header, want, flags, fd, addr);
    }

    return addr;
}

int main(int argc, const char * argv[]) {
    int fd = open("main.o", O_RDONLY, 0);
    if (fd == -1) {
        printf("%d %s\n", errno, strerror(errno));
        exit(-1);
    }

    
    uint64_t *addr;

    printf("---------------- Fixed Address (0x300000000000) (Y=F)?\n");
    printf("|  ------------- PROT_READ/WRITE/EXEC\n");
    printf("|  |   --------- MAP_PRIVATE/ANON/JIT\n");
    printf("|  |   |  ------ File Descriptor Passed (Y/N)?\n");
    printf("|  |   |  |\n");
    printf("V  V   V  V\n");
 
    // addr = test_mmap("  R   P   Y:", NULL, page_size_16k, PROT_READ, MAP_PRIVATE, fd, 0);
    // addr = test_mmap("  RW  P   Y:", NULL, page_size_16k, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    // addr = test_mmap("  R X P   Y:", NULL, page_size_16k, PROT_READ | PROT_EXEC, MAP_PRIVATE, fd, 0);
    // addr = test_mmap("  RWX P   Y:", NULL, page_size_16k, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE, fd, 0);
    // addr = test_mmap("  R   PA  Y:", NULL, page_size_16k, PROT_READ, MAP_PRIVATE | MAP_ANON, fd, 0);
    // addr = test_mmap("  RW  PA  Y:", NULL, page_size_16k, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, fd, 0);
    // addr = test_mmap("  R X PA  Y:", NULL, page_size_16k, PROT_READ | PROT_EXEC, MAP_PRIVATE | MAP_ANON, fd, 0);
    // addr = test_mmap("  RWX PA  Y:", NULL, page_size_16k, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANON, fd, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("  R   P J Y:", NULL, page_size_16k, PROT_READ, MAP_PRIVATE | MAP_JIT, fd, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("  RW  P J Y:", NULL, page_size_16k, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_JIT, fd, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("  R X P J Y:", NULL, page_size_16k, PROT_READ | PROT_EXEC, MAP_PRIVATE | MAP_JIT, fd, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("  RWX P J Y:", NULL, page_size_16k, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_JIT, fd, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("  R   PAJ Y:", NULL, page_size_16k, PROT_READ, MAP_PRIVATE | MAP_ANON | MAP_JIT, fd, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("  RW  PAJ Y:", NULL, page_size_16k, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_JIT, fd, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("  R X PAJ Y:", NULL, page_size_16k, PROT_READ | PROT_EXEC, MAP_PRIVATE | MAP_ANON | MAP_JIT, fd, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("  RWX PAJ Y:", NULL, page_size_16k, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANON | MAP_JIT, fd, 0);

    // addr = test_mmap("  R   P   N:", NULL, page_size_16k, PROT_READ, MAP_PRIVATE, -1, 0);
    // addr = test_mmap("  RW  P   N:", NULL, page_size_16k, PROT_READ | PROT_WRITE, MAP_PRIVATE, -1, 0);
    // addr = test_mmap("  R X P   N:", NULL, page_size_16k, PROT_READ | PROT_EXEC, MAP_PRIVATE, -1, 0);
    // addr = test_mmap("  RWX P   N:", NULL, page_size_16k, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE, -1, 0);
    // addr = test_mmap("  R   PA  N:", NULL, page_size_16k, PROT_READ, MAP_PRIVATE | MAP_ANON, -1, 0);
    // addr = test_mmap("  RW  PA  N:", NULL, page_size_16k, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    // addr = test_mmap("  R X PA  N:", NULL, page_size_16k, PROT_READ | PROT_EXEC, MAP_PRIVATE | MAP_ANON, -1, 0);
    // addr = test_mmap("  RWX PA  N:", NULL, page_size_16k, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANON, -1, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("  R   P J N:", NULL, page_size_16k, PROT_READ, MAP_PRIVATE | MAP_JIT, -1, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("  RW  P J N:", NULL, page_size_16k, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_JIT, -1, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("  R X P J N:", NULL, page_size_16k, PROT_READ | PROT_EXEC, MAP_PRIVATE | MAP_JIT, -1, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("  RWX P J N:", NULL, page_size_16k, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_JIT, -1, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("  R   PAJ N:", NULL, page_size_16k, PROT_READ, MAP_PRIVATE | MAP_ANON | MAP_JIT, -1, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("  RW  PAJ N:", NULL, page_size_16k, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_JIT, -1, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("  R X PAJ N:", NULL, page_size_16k, PROT_READ | PROT_EXEC, MAP_PRIVATE | MAP_ANON | MAP_JIT, -1, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("  RWX PAJ N:", NULL, page_size_16k, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANON | MAP_JIT, -1, 0);
    // munmap(addr, page_size_16k);

    void *want = (void *)0x300000000000;
    uint64_t size = 128L<<30; /* 128 GiB */

    // addr = test_mmap("F R   P   Y:", want, page_size_16k, PROT_READ, MAP_PRIVATE, fd, 0);
    // addr = test_mmap("F RW  P   Y:", want, page_size_16k, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    // addr = test_mmap("F R X P   Y:", want, page_size_16k, PROT_READ | PROT_EXEC, MAP_PRIVATE, fd, 0);
    // addr = test_mmap("F RWX P   Y:", want, page_size_16k, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE, fd, 0);
    // addr = test_mmap("F R   PA  Y:", want, page_size_16k, PROT_READ, MAP_PRIVATE | MAP_ANON, fd, 0);
    // addr = test_mmap("F RW  PA  Y:", want, page_size_16k, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, fd, 0);
    // addr = test_mmap("F R X PA  Y:", want, page_size_16k, PROT_READ | PROT_EXEC, MAP_PRIVATE | MAP_ANON, fd, 0);
    // addr = test_mmap("F RWX PA  Y:", want, page_size_16k, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANON, fd, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("F R   P J Y:", want, page_size_16k, PROT_READ, MAP_PRIVATE | MAP_JIT, fd, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("F RW  P J Y:", want, page_size_16k, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_JIT, fd, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("F R X P J Y:", want, page_size_16k, PROT_READ | PROT_EXEC, MAP_PRIVATE | MAP_JIT, fd, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("F RWX P J Y:", want, page_size_16k, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_JIT, fd, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("F R   PAJ Y:", want, page_size_16k, PROT_READ, MAP_PRIVATE | MAP_ANON | MAP_JIT, fd, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("F RW  PAJ Y:", want, page_size_16k, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_JIT, fd, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("F R X PAJ Y:", want, page_size_16k, PROT_READ | PROT_EXEC, MAP_PRIVATE | MAP_ANON | MAP_JIT, fd, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("F RWX PAJ Y:", want, page_size_16k, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANON | MAP_JIT, fd, 0);
    // munmap(addr, page_size_16k);
    
    // addr = test_mmap("F R   P   N:", want, page_size_16k, PROT_READ, MAP_FIXED | MAP_PRIVATE, -1, 0);
    // addr = test_mmap("F RW  P   N:", want, page_size_16k, PROT_READ | PROT_WRITE, MAP_FIXED | MAP_PRIVATE, -1, 0);
    // addr = test_mmap("F R X P   N:", want, page_size_16k, PROT_READ | PROT_EXEC, MAP_FIXED | MAP_PRIVATE, -1, 0);
    // addr = test_mmap("F RWX P   N:", want, page_size_16k, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_FIXED | MAP_PRIVATE, -1, 0);
    // addr = test_mmap("F R   PA  N:", want, page_size_16k, PROT_READ, MAP_FIXED | MAP_PRIVATE | MAP_ANON, -1, 0);
    // addr = test_mmap("F RW  PA  N:", want, page_size_16k, PROT_READ | PROT_WRITE, MAP_FIXED | MAP_PRIVATE | MAP_ANON, -1, 0);
    // addr = test_mmap("F R X PA  N:", want, page_size_16k, PROT_READ | PROT_EXEC, MAP_FIXED | MAP_PRIVATE | MAP_ANON, -1, 0);
    // addr = test_mmap("F RWX PA  N:", want, page_size_16k, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_FIXED | MAP_PRIVATE | MAP_ANON, -1, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("F R   P J N:", want, page_size_16k, PROT_READ, MAP_FIXED | MAP_PRIVATE | MAP_JIT, -1, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("F RW  P J N:", want, page_size_16k, PROT_READ | PROT_WRITE, MAP_FIXED | MAP_PRIVATE | MAP_JIT, -1, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("F R X P J N:", want, page_size_16k, PROT_READ | PROT_EXEC, MAP_FIXED | MAP_PRIVATE | MAP_JIT, -1, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("F RWX P J N:", want, page_size_16k, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_FIXED | MAP_PRIVATE | MAP_JIT, -1, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("F R   PAJ N:", want, page_size_16k, PROT_READ, MAP_FIXED | MAP_PRIVATE | MAP_ANON | MAP_JIT, -1, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("F RW  PAJ N:", want, page_size_16k, PROT_READ | PROT_WRITE, MAP_FIXED | MAP_PRIVATE | MAP_ANON | MAP_JIT, -1, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("F R X PAJ N:", want, page_size_16k, PROT_READ | PROT_EXEC, MAP_FIXED | MAP_PRIVATE | MAP_ANON | MAP_JIT, -1, 0);
    // munmap(addr, page_size_16k);
    // addr = test_mmap("F RWX PAJ N:", want, page_size_16k, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_FIXED | MAP_PRIVATE | MAP_ANON | MAP_JIT, -1, 0);
    // munmap(addr, page_size_16k);

    addr = test_mmap("  RWX PAJ N:", NULL, size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANON | MAP_JIT, -1, 0);

    pthread_jit_write_protect_np(0);
    // write 8GiB of simple JIT code
    for (uint64_t i = 0; i < 1L<<30; i++) 
    {
        addr[i] = 0xd65f03c0d28000e0; // mov     x0, #7; ret
    }
    pthread_jit_write_protect_np(1);

    printf("value: 0x%08llx\n", addr[1L<<20]); // Check the value at 1MiB (it should be the same everywhere.)

    fnptr fn = (fnptr)addr;
    int ret = (*fn)();
    
    printf("retvalue: %d\n", ret);

    return 0;
}
