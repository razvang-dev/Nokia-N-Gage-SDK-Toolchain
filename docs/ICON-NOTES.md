# MBM and AIF Icon Notes

The historical bitmap tools are sensitive to modern BMP variants. Prefer uncompressed classic Windows BMP/DIB files with conventional headers.

The reference application demonstrates the common N-Gage application AIF layout using a small list/menu image and a larger application image, each paired with a monochrome mask. `bmconv` creates the MBM and `genaif` packages it with the application UID.

When replacing icon artwork, keep the pixel dimensions and bit depths expected by the build script unless you intentionally update the AIF layout.
