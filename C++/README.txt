C++实现
1、采用json格式配置文件，配置顺序就是列处理顺序
2、配置的功能是可插入的
3、定制csv格式输入，可以处理的格式参见csv项目
4、csv和配置文件要求是utf8格式

函数注册是通过各动态链接库so运行时查询，接入
不是编译时链接

使用示例
cat  t.csv| ./dataTransfer dataTransfer.cfg > t.txt

dataTransfer       主程序
dataTransfer.cpp   主程序源码
dataTransfer.cfg   配置文件 
t.csv              测试样本数据
t.txt              转换后结果

已提供的注册函数
1、前后添加字符串appStr
appendStr.cpp    
appendStr.hpp
2、转换成md5码md5Str
md5Str.cpp
md5Str.hpp
md5.cpp   
md5.hpp
3、正则表达式regexStr
regexStr.cpp
regexStr.hpp
4、数据掩蔽maskStr
maskStr.cpp
maskStr.hpp
5、map表列整体替换
mapStr.cpp
mapStr.hpp

使用的C++技术
1、xxx.so动态载入，而非静态链接。
2、用map纪录xxx.so保证只载入一次
3、用xxx.so和createName唯一表征函数，多个fn可以共存于一个so文件，用createName区分
4、用stringMap统一参数传递初始化仿函数
5、用umique_ptr控so和funbase实例只有一份
6、用string和wstring统一输入和输出只使用string
7、定制csvReader转换csv为stringVector，处理多种格式
8、退出前用clear释放资源
   so要在so中对象释放完后才能卸载
9、使用nlohmann::json处理配置文件



