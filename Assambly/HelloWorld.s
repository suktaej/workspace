section .data
  ; .data는 읽기,쓰기가 가능한 일반 데이터를 위한 section

  msg db "Hello World"   
  ; 문자열 데이터를 선언
  ; msg는 "Hello World"의 시작 주소

section .text
  ; .text는 실행파일의 소스가 들어있는 section

  global _start
  ; 링커에게 entry point로 _start 사용하도록 선언

_start:
  ; main함수보다 먼저 실행되는 함수

  mov rax, 1             ; syscall 번호 1 = write
  mov rdi, 1             ; 첫 번째 인자: 1 = STDOUT
  mov rsi, msg           ; 두 번째 인자: 출력할 문자열 주소
  mov rdx, 12            ; 세 번째 인자: 출력할 바이트 수 (Hello World\0 → 12)
  syscall                ; 커널 호출 = write(STDOUT, msg, 12)

  mov rax, 60            ; syscall 번호 60 = exit
  mov rdi, 0             ; 첫 번째 인자: exit 코드 = 0
  syscall                ; 커널 호출 = exit(0)
