# Компилятор
CC := gcc

# Флаги компиляции
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -Iinc -Wfloat-equal -Wfloat-conversion -Wfloat-conversion -O0 -fprofile-arcs -ftest-coverage

# Флаги линковки
LDFLAGS := -lcheck -fprofile-arcs -lpthread -lrt -Wfloat-conversion -ftest-coverage -lm
# -fprofile-arcs

# Флаги для Valgrind
VAL_FLAGS := --leak-check=full --quiet  --show-leak-kinds=all --track-origins=yes

# Каталоги
OUT := out/
SRC := src/
INC := inc/
UNI_T := unit_tests/

# Дополнительные флаги для Ubuntu
ifeq ($(shell grep -o "^ID=.*" /etc/os-release | cut -d'=' -f2), Ubuntu)
	LDFLAGS += -lsubunit
endif

# Список исходных файлов в каталоге SRC
SRC_FILES := $(wildcard $(SRC)*.c)

# Список объектных файлов из исходных файлов
OBJ_SRC_FILES := $(SRC_FILES:$(SRC)%.c=$(OUT)%.o)

# Список исходных файлов для юнит-тестов
UNI_FILES := $(wildcard $(UNI_T)*.c)

# Список объектных файлов для юнит-тестов
OBJ_UNI_FILES := $(UNI_FILES:$(UNI_T)%.c=$(OUT)%.o)

# Общий список объектных файлов
OBJ_FILES := $(OBJ_SRC_FILES) $(OBJ_UNI_FILES)

# Исключаем main.o из списка объектных файлов для вашего приложения
OBJ_FILES := $(filter-out $(OUT)main.o, $(OBJ_FILES))

# Каталог с файлами *_args.txt
ARGS_DIR := func_tests/data

# Список файлов *_args.txt в этом каталоге
ARGS_FILES := $(wildcard $(ARGS_DIR)/*_args.txt)

# Компиляция приложения
app.exe : $(OBJ_SRC_FILES)
	$(CC) $(CFLAGS) -g -o $@ $^
	
# Создание каталога out
.PHONY: out
out :
	mkdir out

# Запуск функциональных тестов
.PHONY: func
func : app.exe
	./func_tests/scripts/func_tests.sh
	
# Запуск юнит-тестов
.PHONY: unit
unit : unit_tests.exe
	./unit_tests.exe

# Компиляция релизной версии приложения
.PHONY: release
release : $(OBJ_SRC_FILES)
	$(CC) $(CFLAGS) -o app.exe $^

# Компиляция исполняемого файла для юнит-тестов
unit_tests.exe :  $(OBJ_FILES)
	$(CC) -o $@ $^ $(LDFLAGS)

# Правило компиляции объектных файлов из исходных файлов для юнит-тестов
$(OUT)%.o: $(UNI_T)%.c
	$(CC) $(CFLAGS) -g -o $@ -c $<

# Правило компиляции объектных файлов из исходных файлов
$(OUT)%.o: $(SRC)%.c
	$(CC) $(CFLAGS) -g -o $@ -c $<

# Правило компиляции объектных файлов из исходных файлов для юнит-тестов
$(OUT)%.o: $(UNI_T)%.c
	$(CC) $(CFLAGS) -o $@ -c $<

# Запуск Valgrind для проверки утечек памяти
count := 0
.PHONY: check
check : app.exe unit_tests.exe
	touch file.txt
	for args_file in $(ARGS_FILES); do \
		count=$$((count + 1)); \
		echo "Iteration $$count: Running valgrind for $$args_file"; \
		valgrind $(VAL_FLAGS) ./app.exe $$(cat "$$args_file") > file.txt; \
	done
	valgrind $(VAL_FLAGS) ./unit_tests.exe

# Очистка файлов сборки
.PHONY: clean
clean :
	find . -type f ! -name "*.sh" ! -name "*.c" ! -name "*.h" ! -name "*.txt" ! -name "*.md" ! -name "makefile*" ! -name ".gitkeep" ! -name ".gitignore" -exec rm {} \;
	rm file.txt

# Закомментированная строка для генерации зависимостей
# $(CC) -MM -Iinc $(SRC)*.c

