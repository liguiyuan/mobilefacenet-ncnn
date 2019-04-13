# mobilefacenet-ncnn

## 1. 模型的制作与训练

本项目使用insightface的mobilefacenet网络进行人脸检测与识别。首先我们要做的就是模型的训练，然后再把训练好的模型转化为ncnn的模型，方法请看[https://github.com/liguiyuan/mobilefacenet-ncnn/tree/master/deploy](https://github.com/liguiyuan/mobilefacenet-ncnn/tree/master/deploy)，最后输出`mobilefacenet.param` ，`mobilefacenet.bin`这两个文件，这就是我们部署所需的两个文件。



## 2. 编译ncnn

这个步骤可以参考官方的教程：[https://github.com/Tencent/ncnn/wiki/how-to-build#build-for-linux-x86](https://github.com/Tencent/ncnn/wiki/how-to-build#build-for-linux-x86)

根据自己所需部署的环境（linux-x86，Android）进行选择编译方法，其实大同小异。编译成功之后在ncnn/build/install/ 就会生成`include`, `lib` 文件夹，里面包含自己所需的头文件和ncnn 库文件。



## 3. 验证模型

在本项目的examples这里提供了一个ncnn最小化模型部署的例子，里面包含人脸检测和人脸相似度对比。

使用方法：

```bash
$ cd examples/arcface/
$ make		# 编译程序
$ ./main	# 运行程序
```



## 4. 性能分析

我们可以通过ncnn的benchmark工具进行分析，可以在pc或Android设备进行分析。分析方法：[https://github.com/Tencent/ncnn/tree/master/benchmark](https://github.com/Tencent/ncnn/tree/master/benchmark)。

在安卓设备华为P9 Kirin 950 (4x2.3GHz A72+4x1.8GHz A53)上自己性能表现如下:

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



## 5.手机端人脸检测识别

安卓端的代码是在官网提供的mtcnn人脸检测的工程上进行修改，使用华为P9 Kirin 950，在多人脸检测上平均时间 在90～110ms 之间，第一次检测的时间比较长（可能第一次要加载到内存吧？），人脸检测效果还不错吧。

|              | Min     | Max      | Avg      |
| ------------ | ------- | -------- | -------- |
| 多人脸检测   | 90.65ms | 212.35ms | 106.73ms |
| 最大人脸检测 | 31ms    | 194ms    | 69ms     |
| 人脸识别     | 135ms   | 278ms    | 159ms    |

编译好的apk 文件在tools文件夹，可以在自己是手机上进行测试。

