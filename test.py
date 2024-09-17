import os
import sys


if __name__ == "__main__":
    ret = os.fork()
    if ret == 0:
        # 子プロセス
        print("PID: %s, PPID: %d" % (os.getpid(), os.getppid()))
        os.pipe2()
        os.execv('/bin/echo', ['/bin/echo', '子プロセス echo'])
        raise BaseException("Error")
        exit()
    else:
        # 親プロセス
        print("PPID: %s, PID: %d" % (os.getpid(), ret))
        exit()
    sys.exit(1)