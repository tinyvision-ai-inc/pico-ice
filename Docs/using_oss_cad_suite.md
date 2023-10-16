---
title: Using OSS CAD Suite
layout: default
nav_order: 3
parent: pico-ice
---

# Using OSS CAD Suite

The [OSS CAD Suite](https://github.com/YosysHQ/oss-cad-suite-build) project is a pre-compiled package of several tools.
It provides a complete solution for building, debugging, simulating, uploading Hardware Description Language (HDL).
It is based on [Yosys](https://github.com/YosysHQ/).

As explained on the [installation](https://github.com/YosysHQ/oss-cad-suite-build#installation) instructions,
you can download it and extract it to a directory of your choice.

Several pico-ice-sdk [examples](https://github.com/tinyvision-ai-inc/pico-ice-sdk/tree/main/examples) rely on a
`$OSS_CAD_SUITE` variable set to the full path where you extracted these files.

On Windows, you can run these examples from the cygwin environment,
under which you can navigate to the example repositories and try them.

If you [used `apio` to install OSS CAD Suite](/using_apio.html),
then you can use the APIO install directory as well:
`export OSS_CAD_SUITE="$HOME/.apio/packages/tools-oss-cad-suite/"`.


## F.A.Q.

### Q: Why is specifying the OSS_CAD_SUITE directory needed?

APIO installs OSS-CAD-Suite, but it is not possible to directly call the commands from the shell environment
so it is needed to provide the full path to the binaries to execute them.

With OSS-CAD-Suite, there is a script to source in the current shell environment to avoid this, but if the user forgets, then nothing works.
