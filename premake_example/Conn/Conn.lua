project "Conn"
    kind "SharedLib"
    language "C"
    location "%{wks.location}/%{prj.name}"
    targetdir "%{prj.location}/bin/%{cfg.buildcfg}"
    objdir "%{prj.location}/obj/%{cfg.buildcfg}"

    includedirs{
        "%{prj.location}/include"
    }

    files{
        "%{prj.location}/src/**.c"
    }

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Speed"
        optimize "Speed"
        