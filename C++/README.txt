C++实现
1、订阅顺序只支持线性
2、不通过阻塞队列订阅实现
   通过仿函数顺序注册，对输入的每一行顺序调用注册的函数
3、正则表达式支持中文
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
appendStr.so*
2、转换成md5码md5Str
md5Str.cpp
md5Str.hpp
md5Str.so*
md5.cpp    md5 C实现
md5.hpp
3、正则表达式(w)regexStr
regexStr.cpp
regexStr.hpp
regexStr.so*
wregexStr.cpp  支持中文
wregexStr.hpp
wregexStr.so*  
4、数据掩蔽maskStr
maskStr.cpp
maskStr.hpp
maskStr.so*

使用的C++技术
1、xxx.so动态载入，而非静态链接。
2、用map纪录xxx.so保证只载入一次
3、用xxx.so和createName唯一表征函数，多个fn可以共存于一个so文件，用createName区分
4、用stringMap统一参数传递初始化仿函数
5、用umique_ptr控so和funbase实例只有一份
6、用string和wstring统一输入和输出只使用string（wregexStr实现）
7、用getline转换csv为stringVector，不能处理引号中分割符
8、退出前用clear释放资源
   so要在so中对象释放完后才能卸载

改进
1、config文件应使用xml或json格式，不使用分割符，避免实际数据中有分割符
2、csv格式要处理"中的分割符，最好能处理引号中\n



