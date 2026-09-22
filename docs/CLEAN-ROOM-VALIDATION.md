# Clean-Room Validation

To validate a release, extract it into a new directory on a supported Linux x86_64 or WSL2 installation and run:

```bash
source ./env.sh
./scripts/verify-env.sh
./scripts/build-example.sh
```

The validation is successful when environment checks report the required compiler/tools/SDK files as available and the reference build finishes with `SUCCESS` while producing a populated `System/Apps/HelloNgage/` directory.
