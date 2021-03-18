target = main
BUILD_DIR = build

CFLAG = -g3 -O0  -std=gnu99 -fsanitize=address 
LD_FLAG= -lasan 


IGNORE_FILE=
SRC = $(filter-out $(IGNORE_FILE),$(wildcard *.c) )  
ASM = $(filter-out $(IGNORE_FILE),$(wildcard *.S) )  
OBJ =  $(addprefix $(BUILD_DIR)/,$(notdir $(SRC:.c=.o) $(ASM:.S=.o) )) 

$(target):Makefile env $(OBJ) $(BUILD_DIR)  $(SRC)
	gcc $(LD_FLAG) $(OBJ)  -o $@ 

$(BUILD_DIR)/%.o:%.c $(BUILD_DIR)
	gcc -c $(CFLAG) $< -o $@

$(BUILD_DIR)/%.o:%.S $(BUILD_DIR)
	gcc -c $(CFLAG) $< -o $@

env:
	@echo SRC: $(SRC) OBJ :$(OBJ) ASM :$(ASM)
	$(shell export LSAN_OPTIONS=exitcode=0:use_unaligned=4)

$(BUILD_DIR):
	mkdir $@

clean:
	rm -rf *.o $(target) $(BUILD_DIR) 
