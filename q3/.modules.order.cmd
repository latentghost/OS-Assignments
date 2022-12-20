cmd_/home/latentghost/linux-5.19.8/q3/modules.order := {   echo /home/latentghost/linux-5.19.8/q3/custommod.ko; :; } | awk '!x[$$0]++' - > /home/latentghost/linux-5.19.8/q3/modules.order
