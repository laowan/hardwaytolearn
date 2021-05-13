-- premake5.lua
workspace "games101"
   configurations { "Debug", "Release" }
   platforms { "x86_64" }
   
-- assigment0
project "assignment0"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    
    files {
        "../assignment0/*.cpp"
    }
    
    includedirs {
        "../../../3rd/eigen-3.4-rc1",
    }
    
    libdirs {
        "bin/%{cfg.buildcfg}"
    }

-- assigment1    
project "assignment1"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    
    files {
        "../assignment1/*.cpp"
    }
    
    includedirs {
        "../../../3rd/eigen-3.4-rc1",
        "../../../3rd/opencv-4.5.2/include",
    }
    
    libdirs {
        "bin/%{cfg.buildcfg}",
        "../../../3rd/opencv-4.5.2/x64/vc15/lib",
    }
    
    links {
        "opencv_world452.lib"
    }
    
    configuration "windows"        
      postbuildcommands {
         string.format("copy /Y %s %s", "..\\..\\..\\3rd\\opencv-4.5.2\\x64\\vc15\\bin\\opencv_world452.dll", ".\\bin\\Debug\\opencv_world452.dll"),
      }
