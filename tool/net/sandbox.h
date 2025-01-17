#ifndef COSMOPOLITAN_TOOL_NET_SANDBOX_H_
#define COSMOPOLITAN_TOOL_NET_SANDBOX_H_
#include "libc/calls/struct/bpf.h"
#include "libc/calls/struct/filter.h"
#include "libc/calls/struct/seccomp.h"
#include "libc/sysv/consts/audit.h"
// clang-format off

#define _SECCOMP_MACHINE(MAGNUM)                                             \
    BPF_STMT(BPF_LD | BPF_W | BPF_ABS, offsetof(struct seccomp_data, arch)), \
    BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, AUDIT_ARCH_X86_64, 1, 0),            \
    BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_KILL_PROCESS)

#define _SECCOMP_LOAD_SYSCALL_NR()                                           \
    BPF_STMT(BPF_LD | BPF_W | BPF_ABS, offsetof(struct seccomp_data, nr))

#define _SECCOMP_ALLOW_SYSCALL(MAGNUM)                                       \
    BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, MAGNUM, 0, 1),                       \
    BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ALLOW)

#define _SECCOMP_TRAP_SYSCALL(MAGNUM, DATA)                                  \
    BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, MAGNUM, 0, 1),                       \
    BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_TRAP | ((DATA) & SECCOMP_RET_DATA))

#define _SECCOMP_TRACE_SYSCALL(MAGNUM, DATA)                                 \
    BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, MAGNUM, 0, 1),                       \
    BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_TRACE | ((DATA) & SECCOMP_RET_DATA))

#define _SECCOMP_LOG_AND_RETURN_ERRNO(MAGNUM)                                \
    BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ERRNO | ((MAGNUM) & SECCOMP_RET_DATA))

#endif /* COSMOPOLITAN_TOOL_NET_SANDBOX_H_ */
