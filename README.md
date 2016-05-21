# ConcurrentOS
A concurrent operating system kernel. 

To run seperate terminal windows:
`dd of=disk.bin if=/dev/zero count=1048576 bs=1`
`make launch-qemu`
`make launch-gdb`
`python disk.py --host=127.0.0.1 --port=1235 --file=disk.bin --block-num=65536 --block-len=16`

Ensure the line in Makefile that reads
QEMU_UART += telnet:127.0.0.1:1235,server

View file: `hexdump -C disk.bin`
# Description
The overarching goal of this assignment is to develop an initially simple but then increasingly capable operating
system kernel. It should execute and thus manage resources on a specific ARM-based target platform, namely
a RealView Platform Baseboard for Cortex-A8 emulated by QEMU1
.
Stage 1. A simple, functioning operating system kernel that supports pre-emptive multi-tasking. All similar
simplifications made there can also be made here. In particular, note that at this point you can and
should assume a) each user program is statically compiled into the kernel image, and b) there is no
need to deal with dynamic process creation or termination.

Stage 2. This stage involves the design and implementation of some standard improvements to the kernel.
(a) The kernel developed in the lab. worksheet(s) assumed two user processes exist at all times
(once executed). Supporting dynamic creation and termination of processes via fork and exit system calls. 

(however simple) that allows the user to
enter commands and thus interactively control program execution (i.e., process creation and
termination); in UNIX parlance, this interaction is often termed job control.

Stage 3. An alternative to considering one of the various real, albeit emulated devices supported by the
PB-A8 is a compromise: for certain cases we could consider a simplified device instead, and
therefore (legitimately) focus on higher-level use rather than the device itself.
Appendix A outlines the source code provided in order to support such a case. The goal is to use
a simplified disk, which offers block-based storage of data, to implement a file system: ideally
this will a) implement a UNIX-like, inode-based data structure, and b) support a suite of system
calls such as creat, unlink, open, close, read and write, with semantics of your own design,
which, in turn, demand management of file descriptors.
