#!/bin/bash
SRC1=1.avi
SRC2=2.avi
SRC3=3.avi
SRC4=4.avi

gst-launch-1.0 filesrc location="$SRC1" ! decodebin ! autovideosink


gst-launch-1.0 -vv -e videomixer name=mix background=2 \
        sink_0::alpha=1.0 \
        sink_0::ypos=0 \
        sink_0::xpos=0 \
	! videoconvert ! autovideosink \
        filesrc location="$SRC1" \
            ! decodebin ! videoconvert ! videoscale \
            ! video/x-raw,width=1024,height=768 \
            ! mix.sink_0 

gst-launch-1.0 -vv -e videomixer name=mix background=2 \
        sink_0::alpha=1.0 \
        sink_0::ypos=0 \
        sink_0::xpos=0 \
        sink_1::alpha=1.0 \
        sink_1::ypos=0 \
        sink_1::xpos=512 \
	! videoconvert ! autovideosink \
        filesrc location="$SRC1" \
            ! decodebin ! videoconvert ! videoscale \
	    ! videocrop top=0 left=256 right=256 bottom=0 \
            ! video/x-raw,width=512,height=720 \
            ! mix.sink_0 \
        filesrc location="$SRC2" \
            ! decodebin ! videoconvert ! videoscale \
	    ! videocrop top=0 left=256 right=256 bottom=0 \
            ! video/x-raw,width=512,height=720 \
            ! mix.sink_1 \

gst-launch-1.0 -vv -e videomixer name=mix background=2 \
        sink_0::alpha=1.0 \
        sink_0::ypos=0 \
        sink_0::xpos=0 \
        sink_1::alpha=1.0 \
        sink_1::ypos=100 \
        sink_1::xpos=600 \
	! videoconvert ! autovideosink \
        filesrc location="$SRC1" \
            ! decodebin ! videoconvert ! videoscale \
            ! video/x-raw,width=1024,height=720 \
            ! mix.sink_0 \
        filesrc location="$SRC2" \
            ! decodebin ! videoconvert ! videoscale \
            ! video/x-raw,width=360,height=240 \
            ! mix.sink_1 \


gst-launch-1.0 -vv -e videomixer name=mix background=2 \
        sink_0::alpha=1.0 \
        sink_0::ypos=0 \
        sink_0::xpos=0 \
        sink_1::alpha=1.0 \
        sink_1::ypos=0 \
        sink_1::xpos=512 \
        sink_2::alpha=1.0 \
        sink_2::ypos=360 \
        sink_2::xpos=0 \
        sink_3::alpha=1.0 \
        sink_3::ypos=360 \
        sink_3::xpos=512 \
	! videoconvert ! autovideosink \
        filesrc location="$SRC1" \
            ! decodebin ! videoconvert ! videoscale \
            ! video/x-raw,width=512,height=360 \
            ! mix.sink_0 \
        filesrc location="$SRC2" \
            ! decodebin ! videoconvert ! videoscale \
            ! video/x-raw,width=512,height=360 \
            ! mix.sink_1 \
        filesrc location="$SRC3" \
            ! decodebin ! videoconvert ! videoscale \
            ! video/x-raw,width=512,height=360 \
            ! mix.sink_2 \
        filesrc location="$SRC4" \
            ! decodebin ! videoconvert ! videoscale \
            ! video/x-raw,width=512,height=360 \
            ! mix.sink_3 

gst-launch-1.0 -vv -e videomixer name=mix background=2 \
        sink_0::alpha=1.0 \
        sink_0::ypos=0 \
        sink_0::xpos=0 \
        sink_1::alpha=1.0 \
        sink_1::ypos=0 \
        sink_1::xpos=664 \
        sink_2::alpha=1.0 \
        sink_2::ypos=240 \
        sink_2::xpos=664 \
        sink_3::alpha=1.0 \
        sink_3::ypos=480 \
        sink_3::xpos=664 \
	! videoconvert ! autovideosink \
        filesrc location="$SRC1" \
            ! decodebin ! videoconvert ! videoscale \
            ! video/x-raw,width=1024,height=720 \
            ! mix.sink_0 \
        filesrc location="$SRC2" \
            ! decodebin ! videoconvert ! videoscale \
            ! video/x-raw,width=360,height=240 \
            ! mix.sink_1 \
        filesrc location="$SRC3" \
            ! decodebin ! videoconvert ! videoscale \
            ! video/x-raw,width=360,height=240 \
            ! mix.sink_2 \
        filesrc location="$SRC4" \
            ! decodebin ! videoconvert ! videoscale \
            ! video/x-raw,width=360,height=240 \
            ! mix.sink_3 

