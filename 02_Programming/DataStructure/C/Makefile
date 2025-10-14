# Makefile

# 컴파일러
CC = gcc
# 실행 파일 이름
TARGET = my_program
# 소스 파일
SRCS = C_main.c C001_Vector.c
# 오브젝트 파일
OBJS = $(SRCS:.c=.o)
OBJS := $(OBJS:.cpp=.o)

# 빌드 옵션
CFLAGS = -Wall -g

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# C 파일 컴파일
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# C++ 파일 컴파일
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
