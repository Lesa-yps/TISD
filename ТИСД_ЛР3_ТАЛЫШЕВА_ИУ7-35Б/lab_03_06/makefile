# Компилятор
CC := gcc

# Флаги компиляции
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -Iinc -Wfloat-equal -Wfloat-conversion -Wfloat-conversion -O0 -fprofile-arcs -ftest-coverage -g

# Флаги линковки
LDFLAGS := -lcheck -fprofile-arcs -lpthread -lrt -Wfloat-conversion -ftest-coverage -lm
# -fprofile-arcs

# Флаги для Valgrind
VAL_FLAGS := --leak-check=full --quiet  --show-leak-kinds=all --track-origins=yes

# Каталоги
OUT := out/
SRC := src/
INC := inc/

# Дополнительные флаги для Ubuntu
ifeq ($(shell grep -o "^ID=.*" /etc/os-release | cut -d'=' -f2), ubuntu)
	LDFLAGS += -lsubunit
endif

# Список исходных файлов в каталоге SRC
SRC_FILES := $(wildcard $(SRC)*.c)

# Список объектных файлов из исходных файлов
OBJ_SRC_FILES := $(SRC_FILES:$(SRC)%.c=$(OUT)%.o)

# Каталог с файлами *_in.txt
IN_DIR := func_tests/data

# Список файлов *_in.txt в этом каталоге
IN_FILES := $(wildcard $(IN_DIR)/*_in.txt)

# Компиляция приложения
app.exe : $(OBJ_SRC_FILES)
	$(CC) $(CFLAGS) -g -o $@ $^ -lm
	
# Создание каталога out
.PHONY: out
out :
	mkdir out

# Запуск функциональных тестов
.PHONY: func
func : app.exe
	./func_tests/scripts/func_tests.sh

# Компиляция релизной версии приложения
.PHONY: release
release : $(OBJ_SRC_FILES)
	$(CC) $(CFLAGS) -o app.exe $^

# Правило компиляции объектных файлов из исходных файлов
$(OUT)%.o: $(SRC)%.c
	$(CC) $(CFLAGS) -g -o $@ -c $<

# Запуск Valgrind для проверки утечек памяти
count := 0
.PHONY: check
check : app.exe
	for in_file in $(IN_FILES); do \
		count=$$((count + 1)); \
		echo "Iteration $$count: Running valgrind for $$in_file"; \
		valgrind $(VAL_FLAGS) ./app.exe < "$$in_file"; \
	done

# Очистка файлов сборки
.PHONY: clean
clean :
	find . -type f ! -name "*.sh" ! -name "*.c" ! -name "*.h" ! -name "*.txt" ! -name "*.md" ! -name "makefile*" ! -name ".gitkeep" ! -name ".gitignore" -exec rm {} \;
	rm file.txt

# Закомментированная строка для генерации зависимостей
# $(CC) -MM -Iinc $(SRC)*.c

