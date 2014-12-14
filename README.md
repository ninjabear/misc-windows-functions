MiscWindowsFunctions
====================

Collection of C functions that may or not be useful (kill process/delete service/change system volume/open CD tray)

# dmode.c

Some code necessary to activate the debug mode privilege for the current process. This is required for some actions, like 
enumerating all handles in the system.

# kill.c

Kills a running process using WINAPI. 

# service_delete.c

Removes a windows service. I created this because there wasn't any functionality I could find from the windows UI to do this.

# volfunc.c

Provides functions to programatically change the volume (on channel 0) for windows. Also provides a way to toggle the mute for the same output.

# tray_open.c

A very old joke to play on people indeed. Repeatedly opens the users CD drive (if they still have one).
