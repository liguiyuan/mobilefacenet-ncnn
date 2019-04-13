

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

**人脸检测mtcnn算法性能**

最小人脸=40，数据宽=816，高=612,，通道=4，在APP上实测数据：

| threads | Min     | Max      | Avg      |
| ------- | ------- | -------- | -------- |
| 4       | 92.76ms | 195.52ms | 103.72ms |



**人脸识别mobilefacenet模型**

利用benchncnn测试几个轻量化模型，在手机ARM处理器下的结果：

| models        | 4线程 | 8线程 |
| ------------- | ----- | ----- |
| squeezenet    | 36.50 | 43.35 |
| mobilenet_v2  | 44.94 | 68.02 |
| mobilefacenet | 22.16 | 31.60 |

可以看到经过优化（去除最好的fc7层）的mobilefacenet 人脸识别模型相对比于其他模型，速度还是比较快的，优化空间不大。



**CPU和GPU的对比**

PC端，在 i7-7700HQ CPU @ 2.80GHz，4线程下性能对比：

| models        | cpu    | gpu(vulkan) |
| ------------- | ------ | ----------- |
| vgg16         | 390.36 | 58.80       |
| mobilenet_v2  | 15.65  | 5.93        |
| mobilefacenet | 26.00  | 4.44        |

受到显卡Mali 驱动版本的限制，手机端对vulkan支持并不是很好，所以没能成功测试。



## 4.性能分析

TODO