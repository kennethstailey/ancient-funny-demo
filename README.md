# ancient-funny-demo
The funny.c demo from 1BSD ported to FreeBSD and Linux

1BSD was the first release of BSD UNIX but it was only a collection of add-on programs for Bell Labs 6th Edtion UNIX. One of the programs on the 1BSD tape was a demo, `funny.c`. It relied on the fact that video terminals which where were relativly new back then could erase text by printing over it.  It also relied on the video terminals being slow, so I had to modify it for FreeBSD and Linux by adding delays.  This is an example of primitive C language source code, not an example of modern C language source code so you should not try to code like this today.

To compile it try `make funny` on a FreeBSD or Linux system with developer tools (`gcc` and `make`, and so on) installed.

This repo includes a bunch of funny license stuff too. Have fun poking around and seeing what the old UNIX world was like, if you want to.
