@echo off
setlocal enabledelayedexpansion

::项目目录
set project=E:\project\HgProject
::exe目录
set soft=F:\ftp_root\software


svn update %project%\trunk --username HongWuHan --password 05140631 --trust-server-cert --non-interactive --no-auth-cache


for /f "delims=" %%i in ('svn info %project%\trunk\vtsServer') do (
set b=%%i
if "!b:~0,17!"=="Last Changed Rev:" (
echo 版本号!b:~18,30!
set a=!b:~18,22!)
)
if exist "%soft%\vtsServer\1.0.0.0.%a%" goto END

call "E:\sofware\VS2010\VC\vcvarsall.bat"
copy %project%\trunk\vtsServer\win32_QMake\vtsServer.pro  %project%\trunk\vtsServer\vtsServer
cd %project%\trunk\vtsServer\vtsServer

echo 生成makefile文件
E:\sofware\Qt\5.5\msvc2010\bin\qmake -o makefile vtsServer.pro
echo makefile文件生成结束

::pause

echo 开始编译
E:\sofware\Qt\Tools\QtCreator\bin\jom -f makefile.Release
if errorlevel 1 goto END
echo 编译结束

::pause

echo 移动exe
mkdir %soft%\vtsServer\1.0.0.0.%a%
copy %project%\trunk\vtsServer\bin\vtsServer.exe %soft%\vtsServer\1.0.0.0.%a%
if errorlevel 1 (
echo 复制exe失败，未找到拷贝文件
goto END)
echo 移动exe结束

copy %project%\trunk\vtsServer\bin\vtsServer.pdb %soft%\vtsServer\1.0.0.0.%a%

mkdir %soft%\vtsServer\1.0.0.0.%a%\data
Xcopy %project%\trunk\vtsServer\bin\data %soft%\vtsServer\1.0.0.0.%a%\data /s/e/y

echo 导出日志
svn log %project%\trunk\vtsServer --username HongWuHan --password 05140631 --trust-server-cert --non-interactive --no-auth-cache > %soft%\vtsServer\1.0.0.0.%a%\log.txt
echo 导出日志结束



:END
echo 删除makefile文件
if exist "%project%\trunk\vtsServer\vtsServer\makefile" del %project%\trunk\vtsServer\vtsServer\makefile
if exist "%project%\trunk\vtsServer\vtsServer\makefile.Debug" del %project%\trunk\vtsServer\vtsServer\makefile.Debug
if exist "%project%\trunk\vtsServer\vtsServer\makefile.Release" del %project%\trunk\vtsServer\vtsServer\makefile.Release
echo 删除makefile文件成功

echo 删除pro文件
if exist "%project%\trunk\vtsServer\vtsServer\vtsServer.pro" del %project%\trunk\vtsServer\vtsServer\vtsServer.pro
echo 删除pro文件成功

echo 删除文件夹文件
if exist "%project%\trunk\vtsServer\Win32" rd /s/q %project%\trunk\vtsServer\Win32
if exist "%project%\trunk\vtsServer\vtsServer\debug" rd /s/q %project%\trunk\vtsServer\vtsServer\debug
if exist "%project%\trunk\vtsServer\vtsServer\GeneratedFiles" rd /s/q %project%\trunk\vtsServer\vtsServer\GeneratedFiles
if exist "%project%\trunk\vtsServer\vtsServer\release" rd /s/q %project%\trunk\vtsServer\vtsServer\release
if exist "%soft%\vtsServer\Release" rd /s/q %soft%\vtsServer\Release
echo 删除文件夹文件成功

if exist "%project%\trunk\vtsServer\bin\vtsServer.exe" del /s/q %project%\trunk\vtsServer\bin\vtsServer.exe
if exist "%project%\trunk\vtsServer\bin\vtsServer.exe.embed.manifest" del /s/q %project%\trunk\vtsServer.exe.embed.manifest

if not exist %soft%\vtsServer\1.0.0.0.%a% (
svn update %soft%\vtsServer\1.0.0.0.%a%
echo 编译失败
) else (
echo 编译成功
)


pause



