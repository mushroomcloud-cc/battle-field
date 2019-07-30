# 投影增强游戏: 战地 Battle Field

### 概述

儿童时期的 FC 游戏 《Battle City》 给我们带来了很多美好的回忆，现在通过模拟器也可以再去回味，体验儿童时期的美好回忆，在蘑菇云这样的环境，激发了改进这个游戏机制的想法，希望能实现物理沙盘的《Battle City》，玩家可以控制实物战车和敌军开展战斗。正好借脑洞大赛 [http://mc.dfrobot.com.cn/thread-296636-1-1.html](http://mc.dfrobot.com.cn/thread-296636-1-1.html) 的契机，把这个事情推动起来。本项目为[物联网游戏开发平台]原型验证项目。

### 游戏机制
* [游戏机制](./mechanism.md)

### 项目分布
* [cockpit](./cockpit/README.md) 手机控制端
* [game-station](./game-station/README.md) 游戏服务器
* [game](./game/README.md) 游戏程序
* [tank](./tank/README.md) 战车端程序
* [tank-detector](./tank-detector/README.md) 战车识别跟踪程序 
* [scene-controller](./scene-controller/README.md) 场景控制程序

### 技术方案

#### 物理实现部分
* 战车
    >战车使用2轮驱动，低底盘，低速度，物理上实现前进，后退，左右转弯功能即可，主控使用 ESP32，电机驱动使用TB6612，其他技术细节待补充。
* 场景
    >场景设计使用 NxM 的矩阵场景，标准的正方形单位面积，任何道具，战车，炮台等都是以单位面积为基准设计。道路/平地部分，只需图案即可，战车可以通行，悬崖/峡谷/河流部分，需要物理凸起或者隔离，战车不可通行。障碍物场景在多次攻击后，需要实现下降隐藏后，战车可以通行。
#### 投影增强部分
* 攻击炮弹弹道
    >战车/炮台的炮弹发射炮弹的弹道使用投影实现，炮弹只能直线前进，直到遇到障碍物或者边缘后爆炸。
* 攻击爆炸效果
    >炮弹爆炸效果使用投影实现，包括发射炮弹的效果。
* 道具
    >道具使用投影实现，投射到地图上。
#### 通信方案
* 网络方案
    >系统使用 WIFI 接入通讯，玩家，服务器，战车，场景在同一局域网内。
* 通讯协议
    >战车/场景等设备和服务器使用 MQTT 协议通讯。
    >投影程序（游戏引擎制作）使用 WebSocket 和服务器通讯。
#### 控制方案
* 玩家战车
    >玩家使用手机连接服务器，玩家控制发送控制指令，接收战场数据。
* 敌军
    >敌军战车，炮台等使用 ESP32 连接服务器，接收服务器下发的控制指令完成控制。
* 场景
    >目前为可破坏的障碍物，场景总控使用有线或者ESP32连接服务器，接收服务器下发的控制指令完成控制。
#### 软件方案
* 硬件部分
    >硬件部分，主要使用 ESP32 模块，使用 Arduino 兼容代码。
* 服务器逻辑部分
    >服务器部分使用 Go 或者 Java ， 运行环境为 Linux 系统。
* 投影部分
    >投影部分使用 Unity3D 或者 GodotEngine 实现游戏画面。
