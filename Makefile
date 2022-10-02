CFLAGS=$(shell)
LIBS=$(shell)
OBJS=$(patsubst src/%.cpp, obj/%.o, $(wildcard src/*.cpp))
NAME=toidua

CC?=gcc

install: folders bin/$(NAME)
	sudo cp bin/$(NAME) /usr/bin/$(NAME)

folders:
	if [ ! -d "bin" ]; then mkdir bin; fi
	if [ ! -d "obj" ]; then mkdir obj; fi

bin/$(NAME): $(OBJS)
	$(CC) $(wildcard obj/*.o) -o $@ $(LIBS)

obj/%.o: src/%.cpp $(wildcard src/*.h)
	$(CC) -c $< -o $@ $(CFLAGS)

run: bin/$(NAME)
	chmod u+x bin/$(NAME)
	bin/$(NAME)

uninstall:
	sudo rm /usr/bin/$(NAME)

clean:
	rm bin obj -rf