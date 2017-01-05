#
# 
#

.PHONY : macos ios macc++11 android

system	:= $(shell uname -s)
ifeq ($(system), Darwin)
	TARGET ?= macos
else
ifeq ($(system), MINGW32_NT-6.1)
	TARGET ?= windows
else
ifeq ($(system), MINGW32_NT-6.2)
	TARGET ?= windows
else
ifeq ($(system), Linux)
	TARGET ?= linux
endif
endif
endif
endif


OUT  := libmusicxml2.framework libmusicxml2.a
MACX ?= macos
IOS  := ios
ANDROID := android
LINUX := linux

# try to detect Visual Studio version used
ifeq ($(TARGET), windows)
 MSVC ?= C:\Program Files (x86)\Microsoft Visual Studio 12.0
 ifneq ($(wildcard "$(MSVC)"), "") 
  WIN32VS ?= Visual Studio 12 2013
  WIN64VS ?= $(WIN32VS) Win64
  endif
 else
 MSVC := C:\Program Files (x86)\Microsoft Visual Studio 10.0
 ifneq ($(wildcard "$(MSVC)"), "") 
  WIN32VS ?= Visual Studio 10
  WIN64VS ?= $(WIN32VS) Win64
 endif
endif

C++11 ?= no
CMAKEOPT ?= -DC++11=$(C++11)

all :
	make $(TARGET)

help :
	@echo libmusicxml makefile - Targets are :
	@echo "   all (default): build the libmusicxml library for the current platform,"	
	@echo "                        the libmusicxml tools,"	
	@echo 
	@echo "Platform targets to build the GUIDOEngine library are:"	
	@echo "   macos     build the library for macos"	
	@echo "   macc++11  build the library for macos, linked to libc"	
	@echo "   windows   build 32 and 64 bits library"
	@echo "   linux"	
	@echo "   android      : build the libmusicxml static library for Android"	
	@echo "the platform targets is automatically evaluated by the default target."	
	@echo "NOTE: windows targets are based on $(WIN32VS)"	

#===============================================================
# building the library on Mac OS X
#===============================================================
.PHONY : $(MACX)/Release/libmusicxml2.framework $(IOS)/Release-iphoneos/libmusicxml2.a

macos : $(MACX)/libmusicxml2.xcodeproj libmusicxml2.framework libmusicxml2.tgz

libmusicxml2.framework :  macos/libmusicxml2.xcodeproj macos/Release/libmusicxml2.framework
	rm -rf libmusicxml2.framework
	cp -R macos/Release/libmusicxml2.framework .

$(MACX)/Release/libmusicxml2.framework :
	xcodebuild -jobs 8 -project $(MACX)/libmusicxml2.xcodeproj -target ALL_BUILD -configuration Release

$(MACX)/libmusicxml2.xcodeproj : CMakeLists.txt
	[ -d $(MACX) ] || mkdir $(MACX)
	cd $(MACX) && cmake .. -G Xcode $(CMAKEOPT)  -Wno-dev

libmusicxml2.tgz : libmusicxml2.framework
	tar czf libmusicxml2.tgz libmusicxml2.framework

macc++11:
	[ -d macc++11 ] || mkdir macc++11
	cd macc++11 && cmake .. -G Xcode -DC++11=yes  -Wno-dev
	xcodebuild -jobs 8 -project macc++11/libmusicxml2.xcodeproj -target ALL_BUILD -configuration Release
	cp macc++11/Release/libmusicxml2.*.dylib macc++11

macc++11/Release/libmusicxml2.dylib:
	xcodebuild -jobs 8 -project macc++11/libmusicxml2.xcodeproj -target ALL_BUILD -configuration Release

#===============================================================
# building the library for iOS
#===============================================================
$(IOS) : $(IOS)/libmusicxml2.xcodeproj libmusicxml2.a

libmusicxml2.a : $(IOS)/libmusicxml2.xcodeproj $(IOS)/Release-iphoneos/libmusicxml2.a
	cp $(IOS)/Release-iphoneos/libmusicxml2.a .

$(IOS)/Release-iphoneos/libmusicxml2.a :
	xcodebuild -jobs 8 -project $(IOS)/libmusicxml2.xcodeproj -target ALL_BUILD -configuration Release
 
$(IOS)/libmusicxml2.xcodeproj : CMakeLists.txt
	[ -d $(IOS) ] || mkdir $(IOS)
	cd $(IOS) && cmake .. -G Xcode -DMIDIEXPORT=no -DC++11=yes -DIOS=yes


#===============================================================
# building the library on windows
#===============================================================
.PHONY : win32 win64 win32/Release/libmusicxml2.dll win64/Release/libmusicxml264.dll

windows :
	make win32
	make win64

win32 : win32/libmusicxml2.sln libmusicxml2.dll libmusicxml2.lib 

libmusicxml2.lib : libmusicxml2.dll

libmusicxml2.dll : win32/Release/libmusicxml2.dll
	cp win32/Release/libmusicxml2.dll .
	cp win32/Release/libmusicxml2.lib .

win32/Release/libmusicxml2.dll : win32/libmusicxml2.sln
	cmd /c "\"$(MSVC)\VC\vcvarsall.bat\" && msbuild win32/libmusicxml2.sln /maxcpucount:4 /p:Configuration=Release"

win32/libmusicxml2.sln : CMakeLists.txt
	[ -d win32 ] || mkdir win32
	cd win32 && cmake .. -G "$(WIN32VS)" $(CMAKEOPT)


win64 : win64/libmusicxml2.sln libmusicxml264.dll libmusicxml264.lib 

libmusicxml264.lib : libmusicxml264.dll

libmusicxml264.dll : win64/Release/libmusicxml264.dll
	cp win64/Release/libmusicxml264.dll .
	cp win64/Release/libmusicxml264.lib .

win64/Release/libmusicxml264.dll : win64/libmusicxml2.sln
	cmd /c "\"$(MSVC)\VC\vcvarsall.bat\" && msbuild win64/libmusicxml2.sln /maxcpucount:4 /p:Configuration=Release"

win64/libmusicxml2.sln : CMakeLists.txt
	[ -d win64 ] || mkdir win64
	cd win64 && cmake .. -G "$(WIN64VS)" $(CMAKEOPT) -DMIDIEXPORT=yes

#===============================================================
# building the library on linux
#===============================================================
.PHONY : $(LINUX) libmusicxml2.so

linux : $(LINUX)/Makefile libmusicxml2.so

libmusicxml2.so :  $(LINUX)/Makefile  $(LINUX)/libmusicxml2.so
	rm -rf libmusicxml2*.so*
	make -C $(LINUX)
	cp -R $(LINUX)/libmusicxml2*.so* .

$(LINUX)/libmusicxml2.so : 
	make -C $(LINUX)
	
$(LINUX)/Makefile : CMakeLists.txt
	[ -d $(LINUX) ] || mkdir $(LINUX)
	cd $(LINUX) && cmake .. -G "Unix Makefiles" -DMIDIEXPORT=yes

#===============================================================
# building the library for Android
#===============================================================
android :
	ndk-build -C android -j 4
	cp -f android/libs/armeabi/libmusicxml2.so android/