#!/bin/bash

# Installer script for stdsplit

dialog --keep-tite --yesno "Install sdtsplit?" 0 0
if [ $? -ne 0 ]; then
    dialog --keep-tite --msgbox "Installation aborted." 0 0
    exit 1
fi

Destination=$(dialog --keep-tite --title "Choose a destination for the binary:" --dselect $PWD 24 80 3>&1 1>&2 2>&3 3>&-)
if [ $? -ne 0 ]; then
    dialog --keep-tite --msgbox "Installation aborted." 0 0
    exit 1
fi

touch $Destination/stdsplit && chmod +x $Destination/stdsplit
if [ ! $? -eq 0 ]; then
    dialog --keep-tite --msgbox "Installation aborted. $Destination is not writable" 0 0
    exit 1
fi

cat $0 | grep "^#bin" | sed -e 's/^#bin//' | base64 -d > $Destination/stdsplit
