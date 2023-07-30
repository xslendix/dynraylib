# dynraylib
Public domain (or MIT licensed) toolkit for developing games in a hot-reloaded
manner.

# FAQ (that no one asked)

> Is it really public domain? Really?

Yes. Go make cool stuff now, the code is not that complicated enough for me to
consider it deserving of a license.

> How do I use this thing?

First, clone the repository

```
git clone --depth 1 https://github.com/xslendix/dynraylib.git <my_project>
```

Then to build the loader (and game library)

```
./build.sh
```

From here you can run the game with `./run.sh`. The loader should start up and you should see a basic demo up and running. You can then in another terminal start up `./recompile.sh` which will listen to changes of the dyn.c file and execute `./build_dyn.sh`.

When it recompiles, you should see changes being applied in real time. Trying to overwrite the executable with `build.sh` WILL result in a `Bus error` and the program will crash.

