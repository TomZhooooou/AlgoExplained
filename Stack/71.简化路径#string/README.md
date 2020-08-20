### [71. 简化路径](https://leetcode-cn.com/problems/simplify-path/)

以 Unix 风格给出一个文件的**绝对路径**，你需要简化它。或者换句话说，将其转换为规范路径。

在 Unix 风格的文件系统中，一个点（.）表示当前目录本身；此外，两个点 （..） 表示将目录切换到上一级（指向父目录）；两者都可以是复杂相对路径的组成部分。更多信息请参阅：Linux / Unix中的绝对路径 vs 相对路径

请注意，返回的规范路径必须始终以斜杠 / 开头，并且两个目录名之间必须只有一个斜杠 /。最后一个目录名（如果存在）不能以 / 结尾。此外，规范路径必须是表示绝对路径的最短字符串。

##### 示例1:

```
输入："/home/"
输出："/home"
解释：注意，最后一个目录名后面没有斜杠。
```

##### 示例2:

```
输入："/../"
输出："/"
解释：从根目录向上一级是不可行的，因为根是你可以到达的最高级。
```

##### 示例3:

```
输入："/home//foo/"
输出："/home/foo"
解释：在规范路径中，多个连续斜杠需要用一个斜杠替换。
```

##### 示例4:

```
输入："/a/./b/../../c/"
输出："/c"
```

##### 示例5:

```
输入："/a/../../b/../c//.//"
输出："/c"
```

1.此题，与字节跳动校招提前批的一道题很像，是其基础版。

2.很容易想到的是对于c++可以用标准库中的getline函数，使用stringstream作为输入流，用‘/’分割所有的数据。

3.使用stack对每个文件名依次进行处理，当遇见'.'时，跳过，当遇见‘..'时，将stack顶端(最近加入的那个路径弹出)

最后再按照路径格式，将stack元素依次拿出即可。

```c++
    string simplifyPath(string path) {
        stringstream ss(path);
        string tmp;
        vector<string> file;//这里使用vector模拟栈操作
       // stack<string> f;
        while(getline(ss, tmp, '/'))
        {
            if(!tmp.empty() && tmp!= "." && tmp != "..")
            { 
                file.push_back(tmp);
            }
            else if(!file.empty() && tmp == "..")//弹出上一个路径文件，回到上一级
            {
                file.pop_back();
            }
        }
        if(file.empty()) return "/";
        tmp.clear();
        for(string&s : file)
        {
            tmp+= "/";
            tmp+= s;
        }
        return tmp;
    }
```



