# Компилятор
CC := gcc

# Флаги компиляции
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -Iinc -Wfloat-equal -Wfloat-conversion -Wfloat-conversion -O0 -fprofile-arcs -ftest-coverage

# Флаги линковки
LDFLAGS := -lcheck -fprofile-arcs -lpthread -lrt -Wfloat-conversion -ftest-coverage
# -fprofile-arcs

# Флаги для Valgrind
VAL_FLAGS := --leak-check=full --quiet  --show-leak-kinds=all --track-origins=yes

# Каталоги
OUT := out/
SRC := src/
INC := inc/

# Дополнительные флаги для ubuntu
ifeq ($(shell grep -o "^ID=.*" /etc/os-release | cut -d'=' -f2), ubuntu)
	LDFLAGS += -lsubunit
endif

# Список исходных файлов в каталоге SRC
SRC_FILES := $(wildcard $(SRC)*.c)

# Список объектных файлов из исходных файлов
OBJ_SRC_FILES := $(SRC_FILES:$(SRC)%.c=$(OUT)%.o)

# Общий список объектных файлов
OBJ_FILES := $(OBJ_SRC_FILES) $(OBJ_UNI_FILES)

# Исключаем main.o из списка объектных файлов для вашего приложения
OBJ_FILES := $(filter-out $(OUT)main.o, $(OBJ_FILES))

# Компиляция приложения
app.exe : $(OBJ_SRC_FILES)
	$(CC) $(CFLAGS) -g -o $@ $^ -lm
	
# Создание каталога out
.PHONY: out
out :
	mkdir out

# Правило компиляции объектных файлов из исходных файлов
$(OUT)%.o: $(SRC)%.c
	$(CC) $(CFLAGS) -g -o $@ -c $< -lm

# Очистка файлов сборки
.PHONY: clean
clean :
	find . -type f ! -name "*.sh" ! -name "*.c" ! -name "*.h" ! -name "*.txt" ! -name "*.md" ! -name "makefile*" ! -name ".gitkeep" ! -name ".git*" -exec rm {} \;
	rm file.txt

# визуалочка графа dot-ом
.PHONY: visual
visual : visual_graph.gv
	dot -Tpng visual_graph.gv -o visual_graph.png

.PHONY: gen_test
gen_test : generate.py
	python3 generate.py

# Закомментированная строка для генерации зависимостей
# $(CC) -MM -Iinc $(SRC)*.c

