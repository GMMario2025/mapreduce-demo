## MapReduce Demo

我们实现了一个简易版伪分布式 mapreduce 框架，该框架基于 C++ 语言实现。

项目结构：

```
.
├── in
│   └── in.txt                              # 输入数据
|
├── src                                     # 框架源代码
│   ├── mr
│   │   ├── mapper.h                        # map 接口           
│   │   └── reducer.h                       # reduce 接口
│   ├── utils
│   │   ├── client.cc                       # 封装的 Client 源文件
│   │   ├── client.h                        # 封装的 Client 头文件
│   │   ├── server.cc                       # 封装的 Server 源文件
│   │   ├── server.h                        # 封装的 Server 头文件
│   │   ├── string.cc                       # 对 C++ std::string 的增强源文件
│   │   └── string.h                        # 对 C++ std::string 的增强头文件
│   ├── main.cc                             # 客户端进程源代码
│   ├── Makefile                            # 编译文件
│   ├── master.cc                           # JobTracker 进程源代码
│   └── worker.cc                           # TaskTracker 进程源代码
│
├── README.md
│
├── templates                               # 模板代码
│   ├── template_map.cc                     # 模板 map 代码
│   ├── template_shuffle.cc                 # 模板 shuffle 代码
│   └── template_reduce.cc                  # 模板 reduce 代码
│
└── udf                                     # WordCount 代码
    ├── WordCountMapper.cc                  # WordCountMapper 源文件
    ├── WordCountMapper.h                   # WordCountMapper 头文件
    ├── WordCountReducer.cc                 # WordCountReducer 源文件
    └── WordCountReducer.h                  # WordCountReducer 头文件
```

运行方式：

```sh
cd src
make
# 在项目根目录下新建三个终端
# 终端 1
./bin/master
# 终端 2
./bin/worker
# 终端 3
./bin/main in/in.txt out.txt udf WordCountMapper WordCountReducer
```

### TODO 优化
1. 用 RPC 协议替换传统套接字
2. 用 JSON/Protobuf 替换传统的字符串写盘
3. 拆分文件，多进程处理
4. 实现一个简易的分布式文件系统（分布式框架必需），并用其代替本地系统（伪分布式）
...
