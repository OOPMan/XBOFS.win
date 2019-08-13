ECHO OFF
ECHO Ensuring sub-modules are available
git submodule init
git submodule update
ECHO Patching VigEmClient
CD VigEmClient
git apply ..\VigEmClient.patch 2>nul & exit 0
CD ..