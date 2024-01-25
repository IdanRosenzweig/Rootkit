# Linux Rootkit

the linux rootkit supports the following:
* file hiding
* process hiding
* network connections and port (tcp) hiding
* hide itself
* give root level credentials

in addition, a remote process can connect to the rootkit and control it.

## rootkit structure
the rootkit is composed out of a regular process and a kernel module that communicate with each other through netlink.

the process related files are found under `linux/`. the kernel module parts are under` linux/kernel_access/`.

## remote controller structure

the controller is a regular process that connects remotely to the rootkit through TCP socket.

its files are found under `/linux/remote_control/`.

## usage
to build the entire rootkit pack, there is a bash file `linux/build.sh` which would build under the directory `linux/build/` 3 files:
* Rootkit: the rootkit executable
* my_km: the kernel module file
* Remote_controller: the remote controller executable

to run the rootkit, just execute the Rootkit file. it would automatically load its kernel module and unload it when done.
when the rootkit runs, execute the Remote_controller to connect to it.