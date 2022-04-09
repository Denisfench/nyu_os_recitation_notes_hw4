// On-disk file system format. 
// Both the kernel and user programs use this header file.


#define ROOTINO 1  // root i-number
#define BSIZE 512  // block size

// Disk layout:
// [ boot block | super block | log | inode blocks | free bit map | data blocks ]
//
// mkfs computes the super block and builds an initial file system. The super describes
// the disk layout:
struct superblock {
  uint size;         // Size of file system image (blocks)
  uint nblocks;      // Number of data blocks
  uint ninodes;      // Number of inodes.
  uint nlog;         // Number of log blocks
  uint logstart;     // Block number of first log block
  uint inodestart;   // Block number of first inode block
  uint bmapstart;    // Block number of first free map block
};

#define NDIRECT 12 // the number of direct blocks containing the data
                  // Not as simple as it seems because of block alignment
                  // misalignment will cause errors down the road
                  // (Hint: 22 would work)

#define NINDIRECT (BSIZE / sizeof(uint))
#define MAXFILE (NDIRECT + NINDIRECT)

// On-disk inode structure
// direct blocks contain (NDIRECT×BSIZE) bytes of a file
// indirect blocks contain (NINDIRECT×BSIZE) bytes
// inode types:
// T_DIR  1   // Directory
// T_FILE 2   // File
// T_DEV  3   // Device
// TODO: augment a timestamp field
struct dinode {
  short type;           // File type // 0: inode is free,
  short major;          // Major device number (T_DEV only)
  short minor;          // Minor device number (T_DEV only)
  short nlink;          // Number of links to inode in file system
  uint size;            // Size of file (bytes)
  uint addrs[NDIRECT+1]; // Data block addresses // records the block numbers
                        // of the disk blocks holding the file’s content
                        // addrs array refers to NDIRECT direct blocks and 1
                        // indirect block number
};

// Inodes per block.
#define IPB           (BSIZE / sizeof(struct dinode))

// Block containing inode i
#define IBLOCK(i, sb)     ((i) / IPB + sb.inodestart)

// Bitmap bits per block
#define BPB           (BSIZE*8)

// Block of free map containing bit for block b
#define BBLOCK(b, sb) (b/BPB + sb.bmapstart)

// Directory is a file containing a sequence of dirent structures.
#define DIRSIZ 14

struct dirent {
  ushort inum;
  char name[DIRSIZ];
};

