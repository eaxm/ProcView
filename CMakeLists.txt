cmake_minimum_required(VERSION 3.20)
project(ProcView)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProcView
        src/main.cpp

        src/memlib/exception/ProcessNotFound.h

        src/memlib/Process.h
        src/memlib/Process.cpp
        src/command/Command.cpp src/command/Command.h src/command/ListProcessesCommand.cpp src/command/ListProcessesCommand.h src/command/ViewProcessInfoCommand.cpp src/command/ViewProcessInfoCommand.h src/command/ReadMemoryCommand.cpp src/command/ReadMemoryCommand.h src/command/WriteMemoryCommand.cpp src/command/WriteMemoryCommand.h src/command/DumpProcessMemoryCommand.cpp src/command/DumpProcessMemoryCommand.h src/command/ListUsersWithProcessesCommand.cpp src/command/ListUsersWithProcessesCommand.h src/command/StringsCommand.cpp src/command/StringsCommand.h src/command/exception/UnknownArgumentException.h src/command/exception/MissingArgumentException.h src/memlib/MemoryRegion.cpp src/memlib/MemoryRegion.h)
