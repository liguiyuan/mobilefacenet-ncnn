安卓设备华为P9:

Kirin 950 (4x2.3GHz A72+4x1.8GHz A53)



编译好之后就可以性能分析了，直接跑模型的前向传播。

安卓设备跑模型：

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



相关参数说明：

| param       | options                                            | default       |
| ----------- | -------------------------------------------------- | ------------- |
| loop count  | 1~N                                                | 4             |
| num threads | 1~N                                                | max_cpu_count |
| powersave   | 0=all cores, 1=little cores only, 2=big cores only | 0             |
| gpu device  | -1=cpu-only, 0=gpu0, 1=gpu1 ...                    | -1            |



使用cpu 4线程跑模型：

```
HWEVA:/data/local/tmp $ ./benchncnn 8 4 0                                      
loop_count = 8
num_threads = 4
powersave = 0
gpu_device = -1
          squeezenet  min =   33.94  max =   36.40  avg =   34.71
     squeezenet-int8  min =   32.52  max =   57.28  avg =   36.01
           mobilenet  min =   42.30  max =   42.96  avg =   42.59
      mobilenet-int8  min =   40.45  max =   40.85  avg =   40.61
        mobilenet_v2  min =   44.09  max =   44.81  avg =   44.53
          shufflenet  min =   19.27  max =   36.23  avg =   23.72
             mnasnet  min =   32.30  max =   51.19  avg =   34.80
     proxylessnasnet  min =   44.36  max =  131.77  avg =   57.84
           googlenet  min =  109.54  max =  112.24  avg =  110.99
      googlenet-int8  min =   92.82  max =   96.92  avg =   94.07
            resnet18  min =  205.80  max =  210.33  avg =  208.28
       resnet18-int8  min =  177.37  max =  179.99  avg =  178.55
             alexnet  min =  338.49  max =  342.61  avg =  339.72
               vgg16  min =  586.38  max =  627.77  avg =  602.71
            resnet50  min =  612.11  max =  759.51  avg =  671.89
       resnet50-int8  min =  343.69  max =  404.23  avg =  352.05
      squeezenet-ssd  min =  134.22  max =  136.10  avg =  135.02
 squeezenet-ssd-int8  min =  149.85  max =  180.08  avg =  157.29
       mobilenet-ssd  min =  149.49  max =  151.00  avg =  149.90
  mobilenet-ssd-int8  min =  118.85  max =  190.51  avg =  137.94
      mobilenet-yolo  min =  267.74  max =  369.75  avg =  297.94
    mobilenet-yolov3  min =  243.21  max =  297.45  avg =  250.67
```



当使用8线程时发现速度更慢，所以后面的测试主要是使用4线程来测试。

```
HWEVA:/data/local/tmp $ ./benchncnn 8 8 0                                      
loop_count = 8
num_threads = 8
powersave = 0
gpu_device = -1
          squeezenet  min =   41.09  max =   43.77  avg =   42.44
     squeezenet-int8  min =   35.82  max =   37.27  avg =   36.52
           mobilenet  min =   45.68  max =   53.77  avg =   47.44
      mobilenet-int8  min =   38.88  max =   47.40  avg =   41.73
        mobilenet_v2  min =   50.35  max =   52.44  avg =   51.69
          shufflenet  min =   37.67  max =   91.03  avg =   60.20
             mnasnet  min =   40.28  max =   87.04  avg =   47.07
     proxylessnasnet  min =   47.12  max =   50.85  avg =   48.01
           googlenet  min =  117.77  max =  209.51  avg =  134.21
      googlenet-int8  min =  137.14  max =  160.22  avg =  144.60
            resnet18  min =  141.48  max =  160.63  avg =  145.57
       resnet18-int8  min =  148.97  max =  150.56  avg =  149.89
             alexnet  min =  177.87  max =  183.37  avg =  179.71
               vgg16  min =  674.49  max =  730.66  avg =  705.37
            resnet50  min =  446.08  max =  618.48  avg =  500.55
       resnet50-int8  min =  188.28  max =  349.39  avg =  262.98
      squeezenet-ssd  min =  108.25  max =  120.28  avg =  111.71
 squeezenet-ssd-int8  min =  158.13  max =  163.96  avg =  160.54
       mobilenet-ssd  min =  106.06  max =  114.85  avg =  108.79
  mobilenet-ssd-int8  min =   76.16  max =   83.08  avg =   78.14
      mobilenet-yolo  min =  267.70  max =  305.16  avg =  277.59
    mobilenet-yolov3  min =  246.50  max =  329.38  avg =  268.13
```





在安卓工程里面的测试(mtcnn+mobilenet)

这是在ncnn提供的example project（https://github.com/moli232777144/mtcnn_ncnn ）直接测试的两次结果如下。

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





















