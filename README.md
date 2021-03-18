# Ctrl_OS
一个精简的嵌入式操作系统

---
## 时间片轮询调度(TimeSchedule)
TimeSchedule 是基于时间片运行的一个简单调度器实现。
支持单次任务，周期任务的创建和删除。

* 详细设计见文档:
  1. [基于时间片的任务调度(一)](./doc/基于时间片的任务调度(一).md)
  2. [基于时间片的任务调度(二)](./doc/基于时间片的任务调度(二).md)

## 通用轮询架构
1. PollSchedule 针对通用轮询结构（DAS），进行任务注册和调度

## 协程生产者消费者实现
1. 基于x86 汇编进行上下文切换，实现协程
2. 基于协程实现生产者消费者，无需考虑同步问题

## 版本日志
1.  V0.0.1 2021/02/28
    添加时间片轮询[(TimeSchedule)]()
2.  V0.0.2 2021/03/02
  添加通用轮询处理架构[(PollSchedule)](./PollSchedlue/main.c)
2.  V0.0.3 2021/03/18
  协程，生产者消费者模型[(coroutine)](./coroutine/main.c)

---
我开通微信公众号啦，可在公众号查看更多文章更新哟~
排版也更好看😎，欢迎大家关注
CSDN博客：[非典型技术宅](https://blog.csdn.net/mirco_mcu)  
个人公众号：  
![非典型技术宅](https://raw.githubusercontent.com/Gary-Hobson/Blog-Attachment/master/picture/%E9%9D%9E%E5%85%B8%E5%9E%8B%E6%8A%80%E6%9C%AF%E5%AE%85.jpg)
