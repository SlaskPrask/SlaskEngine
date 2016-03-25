#pragma once
class Scene
{
private:

	int w, h;
	int** block;

public:

	void load(const char* file);
	Scene();
	~Scene();

	enum Blocks { Empty, Wall, andwhateverelsekindofblocktypesyouwant };
};

