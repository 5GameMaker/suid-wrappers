# suid wrappers

A bunch of tiny c files that launch other applications that only work with root permissions.

## Building

To build this project you need a C compiler, shell and sudo (or alternatives).

The whole thing is powered by tinybuild aka a bash script which constitutes most of the codebase.

```
$ ./tinybuild
[sudo] password for nasa:
installed in 'build'
$
```

Resulting binaries will be owned by root and will have suid bit set.

Without a packaging environment, you may want to do `$ ./tinybuild install` to install in /usr.

## Contributing

Just submit an MR, wrappers take no time to write and as long as you don't put malware in you're probably good.

Be sure to be respectful in the comments!

## Safety

Those are written by somebody who knows not how to properly handle execve with suid, so no security is quaranteed. If you found a security bug, feel free to submit a patch.

## Licensing

This project is licensed under BSD-0, although the code is so small pretty sure it non-copyrightable anyway. But in cases it is, be sure that those 10 lines of code are free to be stolen!
