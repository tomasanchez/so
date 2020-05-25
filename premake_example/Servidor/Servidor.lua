project "Servidor"
    kind "ConsoleApp"
    language "C"
    location "%{wks.location}/%{prj.name}"
    targetdir "%{prj.location}/bin/%{cfg.buildcfg}"
    objdir "%{prj.location}/obj/%{cfg.buildcfg}"

    includedirs{
        "%{wks.location}/Conn/include",
        "%{prj.location}/include"
    }

    files{
        "%{prj.location}/src/**.c"
    }

    links{
        "Conn"
    }

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Speed"
        optimize "Speed"

        