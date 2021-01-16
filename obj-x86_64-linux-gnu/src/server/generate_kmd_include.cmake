  execute_process (COMMAND /usr/bin/kurento-module-creator -r /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/src/server/interface ;-dr;/usr/share/kurento/modules -o /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/src/server/)

  file (READ /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/src/server/mnscmixer.kmd.json KMD_DATA)

  string (REGEX REPLACE "\n *" "" KMD_DATA ${KMD_DATA})
  string (REPLACE "\"" "\\\"" KMD_DATA ${KMD_DATA})
  string (REPLACE "\\n" "\\\\n" KMD_DATA ${KMD_DATA})
  set (KMD_DATA "\"${KMD_DATA}\"")

  file (WRITE /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/src/server/mnscmixer.kmd.json ${KMD_DATA})
