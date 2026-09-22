# Native N-Gage Build Pipeline

The included reference build follows the EKA1 / Series 60 1.x native application process:

1. Compile ARM C++ objects with GCC 539 (`2.9-psion-98r2`).
2. Archive project objects.
3. Generate the `NewApplication()` export.
4. Perform the first EKA1 DLL/application link to obtain the base file.
5. Regenerate exports from the base file and perform the final link.
6. Run PETRAN with UID1 `0x10000079`, UID2 `0x100039CE`, and the application's own UID3.
7. Preprocess and compile application resources with `rcomp -6 -u`.
8. Build MBM graphics and the AIF application file.
9. Assemble the `System/Apps/<Application>/` deployment directory.

See `scripts/build-example.sh` for an executable reference implementation.
