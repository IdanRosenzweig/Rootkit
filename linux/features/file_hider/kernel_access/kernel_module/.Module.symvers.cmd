cmd_/home/idan/CLionProjects/Rootkit/linux/features/file_hider/kernel_access/kernel_module/Module.symvers :=  sed 's/ko$$/o/'  /home/idan/CLionProjects/Rootkit/linux/features/file_hider/kernel_access/kernel_module/modules.order | scripts/mod/modpost -m     -o /home/idan/CLionProjects/Rootkit/linux/features/file_hider/kernel_access/kernel_module/Module.symvers -e -i Module.symvers -T - 
