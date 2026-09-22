# Resource Notes

For the N-Gage / Symbian OS 6.1 target, compile resources using the Symbian OS 6 binary format and Unicode output:

```text
rcomp -6 -u
```

The supplied reference script preprocesses `.rss` files with the bundled C preprocessor and SDK include paths before passing the resulting `.rpp` file to `rcomp`.
