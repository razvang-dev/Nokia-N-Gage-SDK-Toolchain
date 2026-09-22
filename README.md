# Nokia N-Gage SDK Toolchain

**A complete, modernized and fully working native development environment for the original Nokia N-Gage and N-Gage QD.**

**Brought to you by RazvanG.**

This project makes native Nokia N-Gage / Series 60 1.x development practical on modern computers. The original early-2000s SDK environment is increasingly difficult to install and use reliably on current operating systems; this distribution provides a relocatable, tested toolchain with the compiler, linker, SDK headers and libraries, resource compiler, MBM/AIF utilities and build workflow already integrated.

The environment has been validated by building native EKA1 applications intended for original N-Gage hardware. It preserves the period-correct ARM EPOC PE and Series 60 6.1 workflow while wrapping the awkward legacy steps in repeatable scripts.

## Highlights

- Ready-to-use native Nokia N-Gage / N-Gage QD development environment
- Runs on modern Linux x86_64 and Windows through WSL2
- GCC 539 / `2.9-psion-98r2` ARM EPOC PE cross compiler
- ARM PE binutils and the correct two-pass EKA1 application link procedure
- Series 60 6.1 headers and ARMI libraries
- `rcomp`, `bmconv`, `petran`, `uidcrc`, `genaif`, `aiftool`, and `makesis`
- Case-insensitive header compatibility layer for Linux hosts
- Resource, MBM and AIF/icon support
- Hardware-oriented package layout suitable for `System/Apps/`
- Neutral `HelloNgage` reference application
- Offline and relocatable after extraction

## Quick start

On Linux x86_64 or inside WSL2:

```bash
tar -xf Nokia_NGage_SDK_Toolchain_v1.0.0_Linux_x86_64.tar.xz
cd Nokia_NGage_SDK_Toolchain_v1.0.0_Linux_x86_64
source ./env.sh
./scripts/verify-env.sh
./scripts/build-example.sh
```

A successful build ends with `SUCCESS` and creates:

```text
examples/HelloNgage/build/package/System/Apps/HelloNgage/
    HelloNgage.app
    HelloNgage.rsc
    HelloNgage_caption.rsc
    HelloNgage.aif
```

Copy the `HelloNgage` directory to `System/Apps/` on an MMC or device filesystem to test it.

## Important build details

N-Gage / Symbian OS 6 resources must be compiled using `rcomp -6 -u`. The application linker uses the EKA1 two-pass export/base-file process before PETRAN creates the final E32 image. The supplied scripts already implement these requirements.

The old graphics tools also expect classic bitmap formats. See `docs/ICON-NOTES.md` before replacing AIF/MBM source graphics.

## Host requirements

The prebuilt host tools are Linux x86_64 ELF executables. A normal contemporary Linux distribution with Bash, glibc, libstdc++ and zlib is expected. On Windows 10/11, WSL2 is the recommended host environment.

## Repository vs. release package

The GitHub repository contains the project documentation, scripts and distributable toolchain materials. GitHub Releases should also provide the complete versioned `.tar.xz` package so users can download one ready-to-use environment while preserving Unix permissions and symlinks.

## License

Original code, scripts, examples and documentation created for this project are licensed under the MIT License. Copyright (c) 2026 RazvanG. See `LICENSE`.

Bundled or referenced third-party SDK, compiler, tool and library components remain subject to their original licenses and copyright terms. See `THIRD_PARTY.md`.
