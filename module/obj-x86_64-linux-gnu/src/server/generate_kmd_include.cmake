  execute_process (COMMAND /usr/bin/kurento-module-creator -r /home/andrey/mnscmodule/mnscmodule/src/server/interface ;-dr;/usr/share/kurento/modules -o /home/andrey/mnscmodule/mnscmodule/obj-x86_64-linux-gnu/src/server/)

  file (READ /home/andrey/mnscmodule/mnscmodule/obj-x86_64-linux-gnu/src/server/mnscmodule.kmd.json KMD_DATA)

  string (REGEX REPLACE "\n *" "" KMD_DATA ${KMD_DATA})
  string (REPLACE "\"" "\\\"" KMD_DATA ${KMD_DATA})
  string (REPLACE "\\n" "\\\\n" KMD_DATA ${KMD_DATA})
  set (KMD_DATA "\"${KMD_DATA}\"")

  file (WRITE /home/andrey/mnscmodule/mnscmodule/obj-x86_64-linux-gnu/src/server/mnscmodule.kmd.json ${KMD_DATA})
