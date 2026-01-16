cd ..
SolutionGenerator.exe -make ./
cd ide/ShootEmUp/
mkdir x64
cd x64
mkdir Debug Release
cd ../../..
robocopy SDL2\lib\x64 ide\ShootEmUp\x64\Debug SDL2.dll SDL2_image.dll
robocopy SDL2\lib\x64 ide\ShootEmUp\x64\Release SDL2.dll SDL2_image.dll