

#include "ConsoleRenderer.h"
#include <random>
#include <thread>
#include <memory>
#include <string>
#include "RndInput.h"

std::default_random_engine rGen;
typedef std::uniform_int_distribution<int> intRand;
typedef std::uniform_real_distribution<float> floatRand;


class PlayField;

class GameObject
{
public:
	char* m_objType = nullptr;
	Vector2D pos;
	unsigned char sprite;

	virtual void Update(PlayField& world) {};
	bool DecreaseHealth() { return true; };
};

class PlayField
{
private:
	std::vector<GameObject*> gameObjects;

public:
	Input* controllerInput;
	Vector2D bounds;

	// Number of available active laser slots for aliens and player
	int AlienLasers = 10;
	int PlayerLasers = 4;

	PlayField(Vector2D iBounds) : bounds(iBounds) {};
	const std::vector<GameObject*>& GameObjects() { return gameObjects; }

	void Update()
	{
		// Update list of active objects in the world
		for (auto it : GameObjects())
		{
			it->Update(*this);
		}
	}

	GameObject* GetPlayerObject()
	{
		auto it = std::find_if(gameObjects.begin(), gameObjects.end(), [](GameObject* in) { return (strcmp(in->m_objType, "playerShip") == 0); });
		if (it != gameObjects.end())
			return (*it);
		else
			return nullptr;
	}

	void SpawnLaser(GameObject* newObj)
	{
		if (strcmp(newObj->m_objType, "AlienLaser") == 0)
			AlienLasers--;

		else if (strcmp(newObj->m_objType, "PlayerLaser") == 0)
			PlayerLasers--;

		AddObject(newObj);
	}

	void DespawnLaser(GameObject* newObj)
	{
		if (strcmp(newObj->m_objType, "AlienLaser") == 0)
			AlienLasers++;

		else if (strcmp(newObj->m_objType, "PlayerLaser") == 0)
			PlayerLasers++;

		RemoveObject(newObj);
	}

	void AddObject(GameObject* newObj)
	{
		gameObjects.push_back(newObj);
	}

	void RemoveObject(GameObject* newObj)
	{
		auto it = std::find(gameObjects.begin(), gameObjects.end(), newObj); // , [&](GameObject* in) { return (in == newObj); });
		delete* it;
		//gameObjects.erase(it);
	}
	
};

class AlienLaser : public GameObject
{
public:
	AlienLaser() { m_objType = new char[64]; strcpy(m_objType, "AlienLaser"); sprite = RS_AlienLaser; }
	~AlienLaser() { delete[] m_objType; }

	void Update(PlayField& world)
	{
		bool deleted = false;
		pos.y += 1.f;
		if (pos.y > world.bounds.y)
		{
			deleted = true;
		}

		GameObject* player = world.GetPlayerObject();
		if (pos.IntCmp(player->pos))
		{
			deleted = true;
			world.RemoveObject(player);
		}

		if (deleted)
		{
			world.DespawnLaser(this);
			//world.DespawnLaser((GameObject*)this);
		}
	}
};

class PlayerLaser : public GameObject
{
public:
	PlayerLaser() { m_objType = new char[64]; strcpy(m_objType, "PlayerLaser"); sprite = RS_PlayerLaser; }
	~PlayerLaser() { delete[] m_objType; }

	void Update(PlayField& world)
	{
		bool deleted = false;
		pos.y -= 1.f;
		if (pos.y < 0)
		{
			deleted = true;
		}

		if (deleted)
		{
			world.DespawnLaser(this);
			//delete this;
		}
	}
};

class Alien : public GameObject
{
public:
	Alien() { m_objType = new char[64]; strcpy(m_objType, "AlienShip"); sprite = RS_Alien; }
	~Alien() { delete m_objType; }

private:
	float health = 1.f;
	float energy = 0.f;
	float direction = 1.f;
	float velocity = 0.5f;

	bool DecreaseHealth() { health -= 1.f; return health <= 0; }

	void Update(PlayField& world)
	{
		pos.x += direction * velocity;
		// Border check
		if (pos.x < 0 || pos.x >= world.bounds.x - 1)
		{
			direction = -direction;
			pos.y += 1;
		}

		// Border check vertical:
		if (pos.y >= world.bounds.y - 1)
		{
			// kill player
			GameObject* player = world.GetPlayerObject();
			if (pos.IntCmp(player->pos))
			{
				world.RemoveObject(player);
			}
		}

		floatRand fireRate(0, 1);
		if (fireRate(rGen) < 0.5 && world.AlienLasers > 0)
		{
			//Spawn laser
			//GameObject& newLaser = *(new AlienLaser);
			//newLaser.pos = pos;
			//world.SpawnLaser(&newLaser);
		}
	}
};

class PlayerShip : public GameObject
{
public:
	PlayerShip() { m_objType = new char[64]; strcpy(m_objType, "PlayerShip"); sprite = RS_Player; }
	~PlayerShip() { delete m_objType; }

	void Update(PlayField& world)
	{
		if(!world.controllerInput)
			return;
		if (world.controllerInput->Left())
			pos.x -= 1;
		else if (world.controllerInput->Right())
			pos.x += 1;

		if (world.controllerInput->Fire() && world.PlayerLasers > 0)
		{
			//Spawn laser
			/*GameObject& newLaser = *(new PlayerLaser);
			newLaser.pos = pos;
			world.SpawnLaser(&newLaser);*/
		}
	}
};

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
	intRand yCoord(0, 10);

	// Populate aliens
	for (int k = 0; k < 20; k++)
	{
		Alien* a = new Alien();
		a->pos.x = (float)xCoord(rGen);
		a->pos.x = (float)yCoord(rGen);
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