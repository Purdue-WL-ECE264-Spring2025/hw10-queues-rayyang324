CFLAGS = -std=c99 -g -Wall -Wshadow -Wvla -Werror -Wunreachable-code
OBJS = main.o linked_list.o tile_game.o queue.o
HEADERS = linked_list.h tile_game.h
APP = hw10

.PHONY: clean

$(APP): $(OBJS)
	$(CC) $(CFLAGS) *.o -o $(APP)

clean:
	/bin/rm -rf *.o
	/bin/rm -rf $(APP)

%.o: %.c $(HEADERS)
	$(CC) -c $< -o $@ $(CFLAGS)

testall: test1 test2 test3 
	@echo "All tests passed"
test1: hw10
	./hw10 testcases/1.txt
	@echo "test1 passed"
test2: hw10
	./hw10 testcases/2.txt
	@echo "test2 passed"
test3: hw10
	./hw10 testcases/3.txt
	@echo "test3 passed"

timeAmt1: $(APP)
	@echo "test1: "
	time ./hw10 testcases/1.txt 
	
timeAmt2: $(APP)
	@echo "test2: "
	time ./hw10 testcases/2.txt 
	
timeAmt3: $(APP)
	@echo "test3: "
	time ./hw10 testcases/3.txt 