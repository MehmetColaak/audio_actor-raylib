default:
	g++ -o audioActorTest main.cpp -Iraylib/include -Lraylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm