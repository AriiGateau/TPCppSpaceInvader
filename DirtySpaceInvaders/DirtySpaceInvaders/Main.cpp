#include "ConsoleRenderer.h"
#include <random>
#include <thread>
#include <memory>
#include <string>
#include "RndInput.h"
//#include "GameObject.h"
#include "PlayField.h"
#include "Alien.h"
#include "PlayerShip.h"

std::default_random_engine rGen;
typedef std::uniform_int_distribution<int> intRand;
typedef std::uniform_real_distribution<float> floatRand;

int main()
{
	rGen.seed(1);

	Vector2D size(80, 28);
	Renderer consoleRenderer(size);
	PlayField world(size);

	// Add Input
	RndInput* Input = new RndInput();
	world.controllerInput = Input;
	
	intRand xCoord(0, (int)size.x- 1);
	intRand yCoord(0, (int)size.y - 1);

	// Populate aliens
	for (int k = 0; k < 20; k++)
	{
		Alien* a = new Alien();
		a->pos.x = (float)xCoord(rGen);
		a->pos.y = (float)yCoord(rGen);
		world.AddObject(a);
	}

	// Add player
	PlayerShip* p = new PlayerShip;
	p->pos = Vector2D(40, 27);
	world.AddObject(p);

	
	for (int i = 0; i < 100; i++)
	{
		world.Update();

		RenderItemList rl;
		for (auto it : world.GameObjects())
		{
			RenderItem a = RenderItem(Vector2D(it->pos), it->sprite);
			rl.push_back(a);
		}
		
		consoleRenderer.Update(rl);

		// Sleep a bit so updates don't run too fast
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}