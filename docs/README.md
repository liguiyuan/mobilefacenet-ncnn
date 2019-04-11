

# 性能分析



## 1. 分析环境

> 安卓设备：华为P9 
>
> CPU: Kirin 950 (4x2.3GHz A72+4x1.8GHz A53)



## 2. 分析步骤

编译好之后就可以性能分析了，直接跑模型的前向传播，方法如下：

```bash
# for running on android device, upload to /data/local/tmp/ folder
$ adb push benchncnn /data/local/tmp/
$ adb push <ncnn-root-dir>/benchmark/*.param /data/local/tmp/
# adb push benchmark/. /data/local/tmp/ # 这个命令是push benchmark整个文件夹的内容
$ adb shell

# executed in android adb shell
$ cd /data/local/tmp/
$ ./benchncnn [loop count] [num threads] [powersave] [gpu device]
```

exit 命令退出adb调试。



- 相关参数说明：

| param       | options                                            | default       |
| ----------- | -------------------------------------------------- | ------------- |
| loop count  | 1~N                                                | 4             |
| num threads | 1~N                                                | max_cpu_count |
| powersave   | 0=all cores, 1=little cores only, 2=big cores only | 0             |
| gpu device  | -1=cpu-only, 0=gpu0, 1=gpu1 ...                    | -1            |





## 3. 测试参数

人脸识别



**测试1：**

> armv7
> 4线程
> 大核小核
> DNCNN_VULKAN=OFF
> ARM_NEON=ON

情况下跑模型：

```
HWEVA:/data/local/tmp $ ./benchncnn 8 4 0                                      
loop_count = 8
num_threads = 4
powersave = 0
gpu_device = -1
          squeezenet  min =   34.52  max =   45.66  avg =   36.50
     squeezenet-int8  min =   32.57  max =   45.46  avg =   34.81
           mobilenet  min =   42.87  max =   67.39  avg =   53.37
      mobilenet-int8  min =   40.73  max =   41.25  avg =   40.95
        mobilenet_v2  min =   44.68  max =   45.42  avg =   44.94
          shufflenet  min =   19.58  max =   43.51  avg =   27.65
             mnasnet  min =   32.29  max =   40.78  avg =   33.51
     proxylessnasnet  min =   44.43  max =   44.75  avg =   44.56
           googlenet  min =  110.20  max =  161.82  avg =  124.23
      googlenet-int8  min =   93.00  max =   95.14  avg =   93.86
            resnet18  min =  143.92  max =  145.31  avg =  144.34
       resnet18-int8  min =   84.11  max =  118.15  avg =   88.80
             alexnet  min =  301.81  max =  327.68  avg =  305.20
               vgg16  min =  578.48  max =  626.68  avg =  604.68
            resnet50  min =  614.11  max =  663.31  avg =  621.09
       resnet50-int8  min =  193.42  max =  194.41  avg =  193.89
      squeezenet-ssd  min =  102.94  max =  103.96  avg =  103.40
 squeezenet-ssd-int8  min =  106.35  max =  110.12  avg =  107.56
       mobilenet-ssd  min =   95.07  max =   96.55  avg =   95.52
  mobilenet-ssd-int8  min =   83.72  max =   84.12  avg =   83.90
      mobilenet-yolo  min =  264.28  max =  270.89  avg =  266.10
    mobilenet-yolov3  min =  243.05  max =  252.33  avg =  245.20
       mobilefacenet  min =   17.05  max =   31.43  avg =   22.16
```



**测试2：**

> armv7
> 8线程
> 大核小核
> DNCNN_VULKAN=OFF
> ARM_NEON=ON

的测试结果：

```
HWEVA:/data/local/tmp $ ./benchncnn 8 8 0                                      
loop_count = 8
num_threads = 8
powersave = 0
gpu_device = -1
          squeezenet  min =   37.33  max =   57.29  avg =   43.35
     squeezenet-int8  min =   39.05  max =   52.42  avg =   42.40
           mobilenet  min =   46.90  max =   56.75  avg =   49.62
      mobilenet-int8  min =   41.14  max =  168.11  avg =   86.33
        mobilenet_v2  min =   50.40  max =  122.28  avg =   68.02
          shufflenet  min =   30.67  max =   32.68  avg =   31.72
             mnasnet  min =   36.29  max =   82.27  avg =   49.53
     proxylessnasnet  min =   45.10  max =   63.75  avg =   48.64
           googlenet  min =  128.97  max =  144.04  avg =  133.41
      googlenet-int8  min =  131.77  max =  248.31  avg =  165.83
            resnet18  min =  140.30  max =  190.91  avg =  149.01
       resnet18-int8  min =   92.90  max =  166.37  avg =  143.22
             alexnet  min =  177.92  max =  181.53  avg =  179.48
               vgg16  min =  701.67  max =  846.45  avg =  731.20
            resnet50  min =  452.15  max =  559.22  avg =  482.99
       resnet50-int8  min =  189.59  max =  219.69  avg =  200.80
      squeezenet-ssd  min =  118.33  max =  173.99  avg =  131.37
 squeezenet-ssd-int8  min =  111.08  max =  219.91  avg =  160.82
       mobilenet-ssd  min =  106.90  max =  122.22  avg =  111.38
  mobilenet-ssd-int8  min =   76.56  max =   88.29  avg =   80.13
      mobilenet-yolo  min =  267.09  max =  293.91  avg =  277.90
    mobilenet-yolov3  min =  248.22  max =  262.62  avg =  253.11
       mobilefacenet  min =   20.36  max =   60.06  avg =   31.60
```

**结论：**

①经过优化（去除最好的fc7层）的mobilefacenet 人脸识别模型相对比于其他模型，速度还是比较快的，优化空间不大。

②对比测试1和测试2，发现上面使用4线程和8线程对比，发现4线程效果反而会更好。(原因？)



**APP实测数据**

这是在ncnn提供的安卓工程example project（https://github.com/moli232777144/mtcnn_ncnn ）直接测试的两次结果如下：

```
循环测试次数：10次
线程数：4

I/ContentValues: 最小人脸：40
D/MtcnnSo: 数据宽=816,高=612,通道=4
D/MtcnnCpp: iter 1/10 cost: 212.347 ms
D/MtcnnCpp: iter 2/10 cost: 116.149 ms
D/MtcnnCpp: iter 3/10 cost: 92.372 ms
D/MtcnnCpp: iter 4/10 cost: 92.525 ms
D/MtcnnCpp: iter 5/10 cost: 91.499 ms
D/MtcnnCpp: iter 6/10 cost: 93.328 ms
D/MtcnnCpp: iter 7/10 cost: 92.209 ms
D/MtcnnCpp: iter 8/10 cost: 92.987 ms
D/MtcnnCpp: iter 9/10 cost: 93.262 ms
D/MtcnnCpp: iter 10/10 cost: 90.649 ms
    Time cost:Max 212.35ms,Min 90.65ms,Avg 106.73ms
D/MtcnnSo: 检测到的人脸数目：13
I/ContentValues: 检测所有人脸
    人脸平均检测时间：107
I/ContentValues: 图宽：816高：612 人脸数目：13
```

```
I/ContentValues: 最小人脸：40
D/MtcnnSo: 数据宽=816,高=612,通道=4
D/MtcnnCpp: iter 1/10 cost: 205.394 ms
D/MtcnnCpp: iter 2/10 cost: 96.680 ms
D/MtcnnCpp: iter 3/10 cost: 92.743 ms
D/MtcnnCpp: iter 4/10 cost: 91.915 ms
D/MtcnnCpp: iter 5/10 cost: 93.451 ms
D/MtcnnCpp: iter 6/10 cost: 93.801 ms
D/MtcnnCpp: iter 7/10 cost: 94.197 ms
D/MtcnnCpp: iter 8/10 cost: 94.869 ms
D/MtcnnCpp: iter 9/10 cost: 139.036 ms
D/MtcnnCpp: iter 10/10 cost: 107.698 ms
    Time cost:Max 205.39ms,Min 91.92ms,Avg 110.98ms
D/MtcnnSo: 检测到的人脸数目：13
I/ContentValues: 检测所有人脸
    人脸平均检测时间：112
I/ContentValues: 图宽：816高：612 人脸数目：13
```

可以看到需要的平均时间是105-110ms之间，第一次检测比较耗时。



下面的是使用新版本ncnn在该工程下的效果

更新新的ncnn库办法：替换新的include目录下的头文件和 .a库文件。（新版的改进：①添加了vulkan；②其他的一些优化）

```
I/ContentValues: 最小人脸：40
D/MtcnnSo: 数据宽=816,高=612,通道=4
I/zygote: Background concurrent copying GC freed 20165(3MB) AllocSpace objects, 5(2032KB) LOS objects, 70% free, 2MB/8MB, paused 6.130ms total 33.551ms
D/MtcnnCpp: iter 1/10 cost: 195.521 ms
D/MtcnnCpp: iter 2/10 cost: 93.847 ms
D/MtcnnCpp: iter 3/10 cost: 95.196 ms
D/MtcnnCpp: iter 4/10 cost: 93.993 ms
D/MtcnnCpp: iter 5/10 cost: 93.243 ms
D/MtcnnCpp: iter 6/10 cost: 93.134 ms
D/MtcnnCpp: iter 7/10 cost: 92.975 ms
D/MtcnnCpp: iter 8/10 cost: 92.762 ms
D/MtcnnCpp: iter 9/10 cost: 92.923 ms
D/MtcnnCpp: iter 10/10 cost: 93.609 ms
    Time cost:Max 195.52ms,Min 92.76ms,Avg 103.72ms
D/MtcnnSo: 检测到的人脸数目：13
I/ContentValues: 检测所有人脸
    人脸平均检测时间：105
I/ContentValues: 图宽：816高：612 人脸数目：13
```

发现新版本效果更好一点，主要是稳定性方面更强些吧。



## 4. 性能分析

TODO

















