@echo off
echo Cleaning all build artifacts recursively...

REM 삭제할 파일 확장자 목록
set EXT_LIST=*.exe *.obj *.o *.pdb *.ilk *.out

REM 현재 폴더부터 모든 하위 폴더까지
for /r %%f in (%EXT_LIST%) do (
    echo Deleting %%f
    del /q "%%f"
)

echo Done.
pause