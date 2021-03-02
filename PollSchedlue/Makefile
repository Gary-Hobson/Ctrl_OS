target = main
BUILD_DIR = build

CFLAG = -g3 -O0  -std=gnu99 #-fsanitize=address 
LD_FLAG= -lasan 


IGNORE_FILE= TimeSchedule.c 
SRC = $(filter-out $(IGNORE_FILE),$(wildcard *.c))  
OBJ =  $(addprefix $(BUILD_DIR)/,$(notdir $(SRC:.c=.o)))

$(target): $(OBJ) $(BUILD_DIR) Makefile env
	gcc $(LD_FLAG) $(OBJ)  -o $@ 

$(BUILD_DIR)/%.o:%.c $(BUILD_DIR)
	gcc -c $(CFLAG) $< -o $@

env:
	@echo SRC: $(SRC)
#@echo $(filter-out $(IGNORE_FILE),$(SRC))

#$(shell export LSAN_OPTIONS=exitcode=0:use_unaligned=4)


$(BUILD_DIR):
	mkdir $@

clean:
	rm -rf *.o $(target) $(BUILD_DIR)
