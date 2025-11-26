@echo off
setlocal EnableDelayedExpansion

:: 시작 번호 설정 (0부터 시작)
set "count=0"

:: 현재 폴더의 모든 파일(*.*)에 대해 반복
for %%f in (*.*) do (
    :: 이 배치 파일 자체는 이름 변경에서 제외
    if "%%f" neq "%~nx0" (
        
        :: 숫자 앞에 0을 채우는 로직 (3자리수 맞추기)
        set "number=000!count!"
        set "number=!number:~-3!"
        
        :: 파일 이름 변경 (예: 000_기존이름.확장자)
        ren "%%f" "!number!_%%f"
        
        :: 진행 상황 출력 (선택 사항)
        echo Renamed: "%%f" to "!number!_%%f"
        
        :: 카운트 1 증가
        set /a count+=1
    )
)

echo.
pause