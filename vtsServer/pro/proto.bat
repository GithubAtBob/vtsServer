@echo off

::消息文件路径
set SOURCE_FOLDER=.

::protoc编译器路径
set CPP_COMPILER_PATH=.\protoc.exe

::文件生成路径
set CPP_TARGET_PATH=..\message

::删除之前创建的文件
del %CPP_TARGET_PATH%\*.pb.cc /f /s /q
del %CPP_TARGET_PATH%\*.pb.h /f /s /q

::遍历所有文件
for /f "delims=" %%i in ('dir /b "%SOURCE_FOLDER%\*.proto"') do (

	echo %CPP_COMPILER_PATH% --cpp_out=%CPP_TARGET_PATH% %%i

	%CPP_COMPILER_PATH% --cpp_out=%CPP_TARGET_PATH% %%i

)

echo 协议编译结束

pause