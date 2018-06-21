# Sample init scripts and service configuration for hempcoind

Sample scripts and configuration files for systemd, Upstart and OpenRC
can be found in the contrib/init folder.

    contrib/init/hempcoind.service:    systemd service unit configuration
    contrib/init/hempcoind.openrc:     OpenRC compatible SysV style init script
    contrib/init/hempcoind.openrcconf: OpenRC conf.d file
    contrib/init/hempcoind.conf:       Upstart service configuration file
    contrib/init/hempcoind.init:       CentOS compatible SysV style init script

# Service User

All three startup configurations assume the existence of a "hempcoin" user
and group.  They must be created before attempting to use these scripts.

# Configuration

At a bare minimum, hempcoind requires that the rpcpassword setting be set
when running as a daemon.  If the configuration file does not exist or this
setting is not set, hempcoind will shutdown promptly after startup.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that hempcoind and client programs read from the configuration
file, however it is recommended that a strong and secure password be used
as this password is security critical to securing the wallet should the
wallet be enabled.

If hempcoind is run with `-daemon` flag, and no rpcpassword is set, it will
print a randomly generated suitable password to stderr.  You can also
generate one from the shell yourself like this:

```bash
bash -c 'tr -dc a-zA-Z0-9 < /dev/urandom | head -c32 && echo'
```

Once you have a password in hand, set `rpcpassword=` in `/etc/hempcoin/hempcoin.conf`

For an example configuration file that describes the configuration settings,
see `contrib/debian/examples/hempcoin.conf`.

# Paths

All three configurations assume several paths that might need to be adjusted.
```
Binary:              /usr/bin/hempcoind
Configuration file:  /etc/hempcoin/hempcoin.conf
Data directory:      /var/lib/hempcoind
PID file:            /var/run/hempcoind/hempcoind.pid (OpenRC and Upstart)
                     /var/lib/hempcoind/hempcoind.pid (systemd)
```
The configuration file, PID directory (if applicable) and data directory
should all be owned by the hempcoin user and group.  It is advised for security
reasons to make the configuration file and data directory only readable by the
hempcoin user and group.  Access to hempcoin-cli and other hempcoind rpc clients
can then be controlled by group membership.

# Installing Service Configuration

## systemd

Installing this .service file consists on just copying it to
`/usr/lib/systemd/system` directory, followed by the command
`systemctl daemon-reload` in order to update running systemd configuration.

To test, run "systemctl start hempcoind" and to enable for system startup run
`systemctl enable hempcoind`

## OpenRC

Rename hempcoind.openrc to hempcoind and drop it in `/etc/init.d`.  Double
check ownership and permissions and make it executable.  Test it with
`/etc/init.d/hempcoind start` and configure it to run on startup with
`rc-update add hempcoind`

## Upstart (for Debian/Ubuntu based distributions)

Drop hempcoind.conf in `/etc/init`.  Test by running "service hempcoind start"
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the start-stop-daemon uitility.

## CentOS

Copy hempcoind.init to `/etc/init.d/hempcoind`. Test by running "service hempcoind start".

Using this script, you can adjust the path and flags to the hempcoind program by
setting the hempcoind and FLAGS environment variables in the file
`/etc/sysconfig/hempcoind`. You can also use the DAEMONOPTS environment variable here.

# Auto-respawn

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.
