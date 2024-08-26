default:
	g++ -o audioActorTest main.cpp -Iraylib/include -Isteamaudio/include -Lraylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm -Lsteamaudio/lib -lphonon