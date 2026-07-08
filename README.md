# hexbin

## TL;DR

Read one or more files in the Intel HEX format and produce a binary image.

## Background

Intel's HEX text file format that allowed object code to be represented
in a simple ASCII file. It's often used by the software accompanying in-
system programmers for microcontrollers, and historically was used for
loading programs into memory on computers from tape or punched cards.

Some programming tools favor binary image (.bin) files, and that is the
motivation for **hexbin**. The **hexbin** utility accepts multiple HEX
files as input as arguments to the program and produces a single binary
object file as output.

By default, the program performs full integrity checking, and will fail
to produce a binary if any violations are found. For example:

* Since each line of a HEX file contains a checksum, the program will
  validate those checksums by default. Any checksum failure will cause
  the binary generation to fail unless otherwise disabled.

* As the HEX format allows lines to cover sparse ranges (there is no
  requirement that a HEX file represent a contiguous series of bytes
  across an address range) it is possible for there to be overlapping
  ranges across multiple HEX files. The **hexbin** utility will detect
  this by default and refuse to build a binary.




