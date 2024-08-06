compile: dircreate main.o StyleChar.o Canvas.o Preset.o Instruction.o Window.o TTTClient.o Move.o Monster.o MonsterData.o BattleData.o Player.o BattleClient.o CustomPreset.o SocketConnect.o
	gcc -o build/prog build/main.o build/TUI/StyleChar.o build/TUI/Canvas.o build/TUI/Preset.o build/TUI/Instruction.o build/TUI/Window.o build/TTT/TTTClient.o build/Battle/Move.o build/Battle/Monster.o build/Battle/MonsterData.o build/Battle/BattleData.o build/Battle/Player.o build/Battle/BattleClient.o build/Battle/CustomPreset.o build/TUI/SocketConnect.o
compile-tool: dircreate BattleTool.o Move.o Monster.o MonsterData.o
	gcc -o build/battle-tool build/Tool/BattleTool.o build/Battle/Move.o build/Battle/Monster.o build/Battle/MonsterData.o

dircreate:
	mkdir -p build/TUI/
	mkdir -p build/TTT/
	mkdir -p build/Battle/
	mkdir -p build/Tool/
main.o: main.c 
	gcc -c main.c -o build/main.o
StyleChar.o: TUI/StyleChar.c TUI/StyleChar.h
	gcc -c TUI/StyleChar.c -o build/TUI/StyleChar.o
Canvas.o: TUI/Canvas.c TUI/Canvas.h
	gcc -c TUI/Canvas.c -o build/TUI/Canvas.o
Preset.o: TUI/Preset.c TUI/Preset.h
	gcc -c TUI/Preset.c -o build/TUI/Preset.o
Instruction.o: TUI/Instruction.c TUI/Instruction.h
	gcc -c TUI/Instruction.c -o build/TUI/Instruction.o
Window.o: TUI/Window.c TUI/Window.h
	gcc -c TUI/Window.c -o build/TUI/Window.o
TTTClient.o: TTT/TTTClient.c TTT/TTTClient.h
	gcc -c TTT/TTTClient.c -o build/TTT/TTTClient.o
Monster.o: Battle/Monster.c Battle/Monster.h
	gcc -c Battle/Monster.c -o build/Battle/Monster.o
MonsterData.o: Battle/MonsterData.c Battle/MonsterData.h
	gcc -c Battle/MonsterData.c -o build/Battle/MonsterData.o
Move.o: Battle/Move.c Battle/Move.h
	gcc -c Battle/Move.c -o build/Battle/Move.o
BattleTool.o: BattleTool.c
	gcc -c BattleTool.c -o build/Tool/BattleTool.o
BattleData.o: Battle/BattleData.c Battle/BattleData.h
	gcc -c Battle/BattleData.c -o build/Battle/BattleData.o
BattleClient.o: Battle/BattleClient.c Battle/BattleClient.h
	gcc -c Battle/BattleClient.c -o build/Battle/BattleClient.o
Player.o: Battle/Player.c Battle/Player.h
	gcc -c Battle/Player.c -o build/Battle/Player.o
CustomPreset.o: Battle/CustomPreset.c Battle/CustomPreset.h
	gcc -c Battle/CustomPreset.c -o build/Battle/CustomPreset.o
SocketConnect.o: TUI/SocketConnect.c TUI/SocketConnect.h
	gcc -c TUI/SocketConnect.c -o build/TUI/SocketConnect.o

profile-compile: profile-main.o profile-StyleChar.o
	gcc -o build/profile-prog build/main.o build/TUI/StyleChar.o -pg
profile-main.o: main.c
	gcc -c main.c -o build/main.o -pg
profile-StyleChar.o: TUI/StyleChar.c TUI/StyleChar.h
	gcc -c TUI/StyleChar.c -o build/StyleChar.o -pg
profile: ./build/profile-prog
	./build/profile-prog
	gprof ./build/profile-prog > ./build/profile.stat

run: build/prog
	./build/prog
tool: build/battle-tool
	./build/battle-tool
clean:
	rm -rf build/
