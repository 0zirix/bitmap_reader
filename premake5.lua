workspace "bmp_reader"
	architecture "x64"
	startproject "bmp_reader"

	configurations {
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "bmp_reader"
	kind "ConsoleApp"
	location "src"
	language "C++"
	warnings "off"

    flags {
        "MultiProcessorCompile"
    }

	objdir ("build/" .. outputdir .. "/%{prj.name}")
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")

	files {
		"./src/**.h",
		"./src/**.cpp"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		flags {
            "LinkTimeOptimization" 
        }

		defines {
			"PLATFORM_WINDOWS",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "system:linux"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		buildoptions { "-fpermissive" }

		defines {
			"PLATFORM_LINUX",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		defines "DEBUG"
		staticruntime "off"

	filter "configurations:Release"
		defines "RELEASE"
		staticruntime "off"
		runtime "Release"
		optimize "On"
		symbols "On"
