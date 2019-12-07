@ECHO OFF

SET CUR_DIR=%CD%
SET SRC_DIR=%CD%\src
SET DEPOT_TOOLS_PATH=%CUR_DIR%\depot_tools
SET SOLUTION_RELATIVE_DIR=out\Default
SET SOLUTION_PATH=%SRC_DIR%\%SOLUTION_RELATIVE_DIR%\all.sln
SET GN_PATH=%DEPOT_TOOLS_PATH%\gn

SET GYP_MSVS_VERSION=2019
SET DEPOT_TOOLS_WIN_TOOLCHAIN=0
SET DEPOT_TOOLS_UPDATE=0
SET GYP_GENERATORS=ninja
REM SET CHROMIUM_BUILDTOOLS_PATH=%SRC_DIR%\buildtools

REM Add depot tools to environment path
echo %PATH% | CALL findstr %DEPOT_TOOLS_PATH%; >nul && echo '' >nul || SET PATH=%DEPOT_TOOLS_PATH%;%PATH%

PUSHD %SRC_DIR%
echo %SOLUTION_PATH%

IF NOT EXIST "%GN_PATH%" (
    echo Start updating submodule
    call git submodule update
    echo Finished updating submodule
)

IF NOT EXIST "%SOLUTION_PATH%" (
    echo Start generating project files
    CALL gn gen --ide=vs2019 --filters=//examples %SOLUTION_RELATIVE_DIR% --args="is_component_build=true is_debug=true target_cpu=\"x86\""
    echo Finished generating project files
)

echo Start building files
CALL ninja -C %SOLUTION_RELATIVE_DIR% examples
echo Finished building files
POPD