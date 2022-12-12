UF2 tools
=========

A toolbox for working with the UF2 format.
This can be used for:

- converting the binary file with the bitstream to send to the FPGA flash,
- loading custom data at a chosen address in the flash,
- converting the current content of the flash back to a binary file,
- debugging and inspecting UF2 files of various kinds

In firmware using the pico-ice-sdk,
an USB disk named ``pico-ice`` provides a file named ``CURRENT.UF2`` with the content of the flash,
and permits to load new UF2 files that will program the flash chip.


.. program:: bin2uf2

   Produce an UF2 formatted file as a result of one or multiple binary input files.

.. option:: -f familyID

   Set the ``familyID`` field of UF2 to something else than the default ``0x792e7263`` used for the pico-ice.

.. option:: -o file.uf2

   Output file to which UF2 data is written.
   If ommited, stdout is used.

.. option:: [ 0x01230000 file.bin ]...

   Input files are specified as pairs of arguments:

   * the address at which to write the data, i.e. here ``0x01230000``,
   * the path to the file which contains the data, i.e. here ``file.bin``, use ``-`` for stdin.


.. program:: uf22bin

   Decode a single UF2 input file and write the output as a plain binary.
   An optional offset permits to avoid large files composed of only NUL bytes (0x00).

.. option:: -o file.bin

   Output file to which the decoded binary data is written.
   If ommited, the stdout is used.
   This file must be seekable like normal files are.
   If stdout is used, it need to be redirected to a file (``... >file.bin``).

.. option:: -a 0x01230000

   Offset address in the input file.
   Blocks with addresses from 0x00000000 up to the specified address will be skipped,
   and the first byte of the output file will contain the data at that specified address.

.. option:: file.uf2

    Input file from which the data is read.


.. program:: uf2dump

   Dump the content of an UF2 file as human-readable text for inspection and debugging purposes.

.. option:: file.uf2

   Input file containing the UF2 data.
   If ommited, stdin is used.
