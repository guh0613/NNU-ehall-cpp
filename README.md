[南京师范大学一站式服务平台](http://ehall.nnu.edu.cn/)的C++实现。

# 安装依赖
为进行https通信，你需要安装openssl以及zlib库，然后在构建时链接ssl、crypto、z库。

对于Macos用户，你可以使用homebrew安装。

对于Windows用户，可前往[这里](https://slproweb.com/products/Win32OpenSSL.html)下载预构建的openssl库，zlib库需自行下载[源码](https://github.com/madler/zlib/releases/tag/v1.3)构建。

# 构建
若要手动构建，确保你已经安装并正确链接上述库，然后参照`compile_flags.txt`中的内容构建。

推荐使用`CMake`直接构建，请确保你的计算机中已经安装上述依赖。