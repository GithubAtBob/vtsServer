# vtsServer

## 框架
- 基于boost::asio
- 主线程处理网络I/O
- 子线程根据需要处理数据库,定时器,其他业务等
- 网络协议基于google protobuffer
- 网络请求基于request/response,即采用pull模式,*** 该模式下服务端部建议主动发送数据给客户端 ***
- 网络请求基于vtsRequestHandler
- 数据库请求基于vtsDBHandler
- 定时器基于vtsTimerHandler

## 名词定义

### server
一般指程序主体类vtsServer

### service
一般指boost::asio::io_service类

### mainService
主线程io_service

### threadService
子线程io_service

***注意！采用线程池，所以每次通过vtsConnection::threadService返回的子线程是不一样的***

## 配置

### 数据库连接池配置项

|名称   |说明   |     |
|-------|------|------|
| testOnBorrow |取得连接时是否验证连接的有效性，如配置为true,testOnBorrowSql必须配置。| mysql会有默认超时时间：当连接上没有活动超过一定时间后，连接会被断开，因此该选项是必须的|
| testOnBorrowSql |默认 “SELECT 1;”	||
| testTime |数据库连接每隔一定时间才测试有效性，单位秒	| |
| maxConnectionCount |数据库连接池里连接的最大数|	该值一般和线程池的线程个数对应。 为确保不发生饿死，该值必须大于等于子线程数|
| maxWaitTime | 数据库获取连接时等待的最大时长，单位毫秒	| |
| waitInterval | 等待连接时，间隔一定时间查询是否有连接，单位毫秒，该值必须小于maxWaitTime | |

### 线程池配置项

|名称 | 说明 | |
|----|-----|----|
|numOfThreads|线程池中的线程个数;该值一般设置为cpu核心数*2	|

## 日志规范

### debug
指出细粒度信息事件对调试应用程序是非常有帮助的。
主要给开发人员看，而且随时可以通过开关将其关闭

### info
表明消息在粗粒度级别上突出强调应用程序的运行过程。
重要的业务逻辑处理完成。在理想情况下, INFO的日志信息要能让高级用户和系统管理员理解, 并从日志信息中能知道系统当前的运行状态. 比如对于一个机票预订系统来说, 当一个用户完成一个机票预订操作之后, 提醒应该给出"谁预订了从A到B的机票". 另一个需要输出INFO信息的地方就是一个系统操作引起系统的状态发生了重大变化(比如数据库更新, 过多的系统请求)。

### warning
表明会出现潜在错误的情形。
系统能继续运行, 但是必须引起关注. 对于存在的问题一般可以分为两类: 一种系统存在明显的问题(比如, 数据不可用), 另一种就是系统存在潜在的问题, 需要引起注意或者给出一些建议(比如, 系统运行在安全模式或者访问当前系统的账号存在安全隐患). 总之就是系统仍然可用, 但是最好进行检查和调整.

### error
指出虽然发生错误事件，但仍然不影响系统的继续运行。
系统发生了严重的错误, 必须马上进行处理, 否则系统将无法继续运行. 比如, 数据库不可用等.

### fatal
指出每个严重的错误事件将会导致应用程序的退出。

## session
session是一个map，key是std::string，value是QVariant；关于QVariant可以参考以下资料：
http://blog.163.com/danshiming@126/blog/static/10941274820155784313934/
http://blog.csdn.net/bzhxuexi/article/details/50069725

| 名称 | 获取方式 | 作用域 | 注意事项 |
|-----|---------|-------|---------|
| connection session | connection()->session() | connection断开后，session里的数据失效 | 不具备线程安全 |
| 全局session | connection()->server().session() | 全局共享;程序退出时数据失效 | 不具备线程安全 |

## preprocess

继承自vtsPreprocessHandler，在cpp中添加vtsSETUP_PREPROCESS_HANDLER宏
程序运行后，根据重载的函数，进行调用

| 名称 | 说明 | 备注 |
|-----|------|-----|
| whenConnectionConnnected | 新的连接到来 | vtsConnection已经生成 |
| whenConnectionDisconnected | 连接断开 | vtsConnection实例还没有销毁 |
| beforeServerRun | 在vtsServer运行之前 | |
| beforeServerStop | 在vtsServer停止之前 | |
| afterServerStop | 在vtsServer停止之后 | |

## request注意事项

***vtsDECLARE_REQUEST_HANDLER必须在cpp中声明***

### response
| 名称 | 同/异步 | 其他 |
|-----|--------|------|
| response | 同步 | workMode不能为Work_Delete_Auto |
| responseAsync | 异步 | |

### post
| 名称 | 同/异步 | 其他 | 线程 |
|-----|---------|-----|-----|
| post | 异步 | workMode不能为Work_Delete_Auto | 主线程调用 |
| postToThread | 异步 | workMode不能为Work_Delete_Auto | 子线程调用 |

### workMode
| 名称 | 说明 | 生命周期 | 其他 |
|------|-----|---------|-----|
| Work_Delete_Auto | 自动 | 请求到来时创建handle函数之后马上销毁 | 不能使用callLater、responseAsync、post、postToDB、postToThread等异步函数 |
| Work_Delete_Manual | 手动 | 请求到来时创建由开发人员决定何时销毁 | 无 |
| Work_Cached | 缓存 | 第一次请求到来后创建; 程序退出时销毁 | 使用该方式，注意reset函数里重置状态 |

### 组播multicast
发送消息，和给定的channel一致的所有connection
可以通过vtsConnection::setChannel设置

#### 关于AIS组播的一个例子
利用vtsPreprocessHandler，在whenConnectionConnected时，
或者根据连接服务器成功后发送的标识码，

设置好channel，比如说“normal-client”等

后续有AIS消息，便可直接使用multicast函数

### 广播broadcast
发送消息，所有的connection

## dbhandler注意事项
| 名称 | 线程 | 同/异步 |
|-----|------|--------|
| postToDB | 子线程 | 异步 |
| dispatchToDB | 主线程 | 同步 |

***注意:vtsDBHandler::handle函数获取到的数据库连接，无法确保是连接成功的。需要自己判断。即：QSqlDatabase需要判断是否有效***

## timer注意事项
定时器分为4种类型

| 名称 | 调用方式 | 生命周期 | 回调函数 | 触发次数 | 线程 | 其他要求 |
|------|--------|---------|--------|---------|------|---------|
| callLater | callLater | N/A | void func(const boost::system::error_code &e)或者使用boost::bind | 1次 | 主线程调用 | request的workMode不能Work_Delete_Auto |
| 静态Timer | vtsSETUP_TIMER | 程序启动后启用定时器,程序结束时释放内存; 或者调用cancel、clearTimer | 重载vtsTimerHandler::handle	 | 一直 | 根据Timer的workMode决定 | name唯一 |
| 动态Timer | setTimer | 调用setTimer后启用; 程序结束时释放内存或者调用cancel、clearTimer | 重载vtsTimerHandler::handle | 一直 | 根据Timer的workMode决定 | name唯一 |

***vtsSETUP_TIMER必须在cpp中声明***

vtsTimerHandler::handle需要处理boost::system::error_code，判断是因为被cancel而触发，还是超时触发：

``` C++
if (e)
{
// 被cancel触发
}
```

在timer中利用子线程执行

``` C++
_server->threadService().post
```

在timer中设置全局session值

``` C++
_server->session()
```
在timer中获取客户端连接
``` C++
_server->connectionManager()
```

cancel函数的autoDelete

### 如何取消一个timer
通过vtsRequestHandler::clearTimer函数

或者在vtsTimerHandler::handle中调用cancel函数，cancel需要指定true或者false，即是否自动释放timer

### 注意
timer一般需要new
除非明确是调用cancel(false)，否则，不要手动delete timer
建议使用cancel(true)取消定时器以及释放内存

## protobuf使用注意事项
解包时，请使用ParseFromArray，并要判断返回值。

## todo
1. 添加断线重连机制；断线重连机制需要有专门的连接和断开消息，以及恢复session机制；
2. 心跳包检测机制，防止假死连接、半连接等；
3. session的线程安全；
4. 考虑connection采用子线程，即业务代码更多的放在线程上执行；
