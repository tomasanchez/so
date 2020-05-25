workspace "Workspace"
    configurations { "Debug", "Release" }
    architecture "x86"
    cdialect "GNU11"

    include "Conn/Conn.lua"
    include "Cliente/Cliente.lua"
    include "Servidor/Servidor.lua"
    