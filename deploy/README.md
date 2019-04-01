## 1. 训练模型

参考insightface的训练方法，github地址：https://github.com/deepinsight/insightface

数据集：MS1M



## 2. MXNet2ncnn

### 2.1 模型修改

去除模型fc7层，在**insightface/deploy** 目录下执行：

```bash
python model_slim.py --model ../models/model-y1-test2/model,0
```

会生成 ../models/model-y1-test2/models-  两个文件。



### 2.2 生成ncnn模型

- 下载ncnn并且编译，参考官网教程：[https://github.com/Tencent/ncnn/wiki/how-to-build#build-for-android](https://github.com/Tencent/ncnn/wiki/how-to-build#build-for-android)

```
cmake -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK/build/cmake/android.toolchain.cmake -DANDROID_ABI="armeabi-v7a" -DANDROID_ARM_NEON=ON -DANDROID_PLATFORM=android-14 ..
```

- 使用mxnet2ncnn工具来转化模型：

```bash
cd ncnn/build/tools/mxnet
./mxnet2ncnn models-symbol.json models-0000.params mobilefacenet.param mobilefacenet.bin
```

生成两个新的文件mobilefacenet.param ，mobilefacenet.bin，这就是我们部署ncnn需要用到的文件。









------

编译Android版本ncnn报了一个错：

```
cmake -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK/build/cmake/android.toolchain.cmake -DANDROID_ABI="armeabi-v7a" -DANDROID_ARM_NEON=ON -DANDROID_PLATFORM=android-14 ..
```

> Could not find a package configuration file provided by "OpenCV" with any
> of the following names:
>
> OpenCVConfig.cmake
> opencv-config.cmake
>
> Add the installation prefix of "OpenCV" to CMAKE_PREFIX_PATH or set
> "OpenCV_DIR" to a directory containing one of the above files.  If "OpenCV"
> provides a separate development package or SDK, be sure it has been
> installed.
>
> -- Configuring incomplete, errors occurred!
> See also "/home/liguiyuan/deep_learning/ncnn/build-android-armv7/CMakeFiles/CMakeOutput.log".

解决办法：把ncnn目录下的 CMakeLists.txt里的add_subdirectory(examples) 屏蔽掉。

