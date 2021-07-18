build:
	g++ -w -std=c++17 \
	-Iinclude \
	-Isrc/dynamics \
	./src/*.cc" \
	./src/game/*.cc \
	./src/collision/*.cpp \
	./src/common/*.cpp \
	./src/dynamics/*.cpp \
	./src/rope/*.cpp \
	./src/GUI/*.cc \
	-o ./bin/Im_old_4_this.exe \
	-lbin/Im_old_4_this.exe \
	-llib/libopenal32.a \
	-llib/libsfml-audio.a \
	-llib/libsfml-graphics.a \
	-llib/libsfml-window.a \
	-llib/libsfml-system.a \
	-llib/libsfml-main.a \
	-llib/libsfml-network.a \

clean:
	rm ./bin/Im_old_4_this

run:
	./bin/Im_old_4_this