yfs
===

a multi-server file system called Yet Another File System (yfs) in the spirit of Frangipani.

![file server architecture](/include/yfs.png)

Each client host will run a copy of yfs. Each yfs will create a file system visible to applications on the same machine, and FUSE will forward application file system operations to yfs. All the yfs instances will store file system data in a single shared "extent" server, so that all client machines will see a single shared file system.

This architecture is appealing because (in principle) it shouldn't slow down very much as you add client hosts. Most of the complexity is in the per-client yfs program, so new clients make use of their own CPUs. The extent server is shared, but hopefully it's simple and fast enough to handle a large number of clients. In contrast, a conventional NFS server is pretty complex (it has a complete file system implementation) so it's more likely to be a bottleneck when shared by many NFS clients.
