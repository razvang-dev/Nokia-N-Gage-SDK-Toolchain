# Included Tools

The environment includes the GCC 539 ARM EPOC PE compiler family, matching binutils, and the historical Symbian/N-Gage development utilities required by the supplied build workflow.

Important commands include `arm-epoc-pe-g++`, `arm-epoc-pe-ar`, `arm-epoc-pe-ld`, `arm-epoc-pe-dlltool`, `petran`, `rcomp`, `bmconv`, `genaif`, `aiftool`, `uidcrc`, and `makesis`.

Run `scripts/verify-env.sh` to confirm that the essential host executables, SDK headers and ARMI libraries are present.
