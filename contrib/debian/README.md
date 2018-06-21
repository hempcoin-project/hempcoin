
Debian
====================
This directory contains files used to package hempcoind/hempcoin-qt
for Debian-based Linux systems. If you compile hempcoind/hempcoin-qt yourself, there are some useful files here.

## hempcoin: URI support ##


hempcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install hempcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your hempcoinqt binary to `/usr/bin`
and the `../../share/pixmaps/hempcoin128.png` to `/usr/share/pixmaps`

hempcoin-qt.protocol (KDE)

