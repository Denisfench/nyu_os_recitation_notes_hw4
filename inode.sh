echo "sort file listing"
ls
echo "long file listing"
ls -l
echo "inode-filename listing"
ls - i
echo "viewing the inode info for the README.md file"
stat README.md
echo "viewing the disk usage stat"
df -hi