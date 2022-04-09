// All the open files in the system are kept in a global file table, the ftable
struct file {
  enum { FD_NONE, FD_PIPE, FD_INODE } type;
  int ref; // reference count to a particular open file
  char readable;
  char writable;
  struct pipe *pipe;
  struct inode *ip;
  uint off;
};


// in-memory copy of an inode
// in-memory copy of a struct dinode on disk
// stored in memory only if there are C pointers referring to that inode
// * Pointers to an inode can come from file descriptors, current working
// directories, and transient kernel code such as exec.
// Why?
// 1. Synchronize access by multiple processes
// 2. Caching
// TODO: augment a timestamp field
struct inode {
  uint dev;           // Device number
  uint inum;          // Inode number
  int ref;            // * Reference count // counts the number of C pointers
                      // referring to the in-memory inode
                      // inode is discarded if the count drops to 0
  int flags;          // I_BUSY, I_VALID

  short type;         // copy of disk inode
  short major;
  short minor;
  short nlink;        // * # of directory entries that refer to a file
  uint size;
  uint addrs[NDIRECT+1];
};
#define I_BUSY 0x1
#define I_VALID 0x2

// table mapping major device number to
// device functions
struct devsw {
  int (*read)(struct inode*, char*, int);
  int (*write)(struct inode*, char*, int);
};

extern struct devsw devsw[];

#define CONSOLE 1

//PAGEBREAK!
// Blank page.
