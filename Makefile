all:
	g++ -g -pthread -I/usr/include/gstreamer-1.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include main.cpp -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0