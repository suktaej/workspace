# Makefile

# 컴파일러
CC = g++

# 실행 파일 이름
TARGET = as

# 소스 파일 (헤더 파일은 제외)
SRCS = main.cpp CPPGraph.cpp

# 오브젝트 파일 (.cpp 파일을 .o로 변환)
OBJS = $(SRCS:.cpp=.o)

# 빌드 옵션
CFLAGS = -Wall -g

# 기본 타겟 (실행 파일)
all: $(TARGET)

# 실행 파일을 빌드
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# .cpp 파일을 .o 파일로 컴파일
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# 빌드된 파일 삭제
clean:
	rm -f $(OBJS) $(TARGET)