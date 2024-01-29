# Linux Rootkit

the linux rootkit supports the following:
* file hiding
* process hiding
* network connections and port (tcp) hiding
* hide itself
* give root level credentials

in addition, a remote process can connect to the rootkit and control it:
* backdoor for executing shell comamnds
* backdoor for compiling and executing C and C++ programs.

## rootkit structure
the rootkit is composed out of a regular process and a kernel module that communicate with each other through netlink.

the process related files are found under `linux/`. the kernel module parts are under` linux/kernel_access/`.

## remote controller structure

the controller is a regular process that connects remotely to the rootkit through TCP socket.

its files are found under `/linux/remote_control/`.

## building
to build the entire rootkit pack, there is a bash file `linux/build.sh` which would build under the directory `linux/build/` 3 files:
* Rootkit: the rootkit executable
* my_km: the kernel module file
* Remote_controller: the remote controller executable

when building the Rootkit file, you can change the port number in which it would listen on for the remote controller.
(in `linux/rootkit_main.cpp` source file)

when building the remote controller, you can change the port number and IP address in which it would try to connect to.
(in `linux/remote_controller_main.cpp` source file)

## running
to run the rootkit, just execute the Rootkit file. it would automatically load its kernel module and unload it when done.

to run the remote controller, just execute the Remote_controller file. it would connect to the rootkit.
