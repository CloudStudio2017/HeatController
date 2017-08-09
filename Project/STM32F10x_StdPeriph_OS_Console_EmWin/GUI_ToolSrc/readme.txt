【***增加中文字的方法***】
【准备】
建立WORDs_UTF8.txt文件，在里面加上需要的中文字，可以任意添加换行，保存格式为UTF8
建立WORDs_Unicode.txt文件，将WORDs_UTF8.txt中的文字拷贝进来，保存格式为Unicode
【生成字库C文件】
打开FontCvt.exe程序
Edit->Disable all characters
Edit->Read pattern file... 选择WORDs_Unicode.txt
File->Save As... 保存
【生成打印文字对应UTF8代码】
打开U2C.exe程序
Select file... 选择WORDs_UTF8.txt
Convert 将自动生成WORDs_UTF8.c，里面有对应的UTF8代码
【使用】
程序上需要在UI中加上GUI_UC_SetEncodeUTF8();使能UTF8码
UI元素需要使用类似函数来设定字体：TEXT_SetFont(hItem, &你得到的字体C文件中描述的字体结构体);

【为什么不直接用中文？】
直接用中文需要将C文件保存为UTF8格式，该格式无法被emwin窗口设计工具识别，不利于后续修改编辑
