@echo off

::��Ϣ�ļ�·��
set SOURCE_FOLDER=.

::protoc������·��
set CPP_COMPILER_PATH=.\protoc.exe

::�ļ�����·��
set CPP_TARGET_PATH=..\message

::ɾ��֮ǰ�������ļ�
del %CPP_TARGET_PATH%\*.pb.cc /f /s /q
del %CPP_TARGET_PATH%\*.pb.h /f /s /q

::���������ļ�
for /f "delims=" %%i in ('dir /b "%SOURCE_FOLDER%\*.proto"') do (

	echo %CPP_COMPILER_PATH% --cpp_out=%CPP_TARGET_PATH% %%i

	%CPP_COMPILER_PATH% --cpp_out=%CPP_TARGET_PATH% %%i

)

echo Э��������

pause