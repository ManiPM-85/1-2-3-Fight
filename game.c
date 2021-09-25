#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// UTILLS BEGIN
void randomize()
{
	srand(time(0));
}

int randint(int min, int max)
{
	return (rand() % (max - min + 1)) + min;
}
// UTILLS END

// TURN BEGIN
enum Turn
{
	PLAYER,
	OPPONENT
};
// TURN END

// FIGHTERS BEGIN
struct Player
{
	char name[10];
	int health;
	int attackDamage;
};

struct Opponent
{
	char name[7];
	int health;
	int attackDamage;
};

struct Player Player_init(const char *name)
{
	struct Player self;

	strcpy(self.name, name);
	self.health = 50;
	self.attackDamage = randint(2, 8);

	return self;
}

void Player_attack(struct Player* self, struct Opponent* other)
{
	other->health -= self->attackDamage;
	printf(" %s punched %s! Damage: %d\n", self->name, other->name, self->attackDamage);	// Attack dealed!
}

struct Opponent Opponent_init()
{
	struct Opponent self;
	
	strcpy(self.name, "Hasan_R");
	self.health = 50;
	self.attackDamage = randint(2, 8);
	
	return self;
}

void Opponent_attack(struct Opponent* self, struct Player* other)
{
	other->health -= self->attackDamage;
	printf(" %s punched %s! Damage: %d\n", self->name, other->name, self->attackDamage);	// Attack dealed!
}
// FIGHTERS END

// GAME BEGIN
struct Game
{
	struct Player player;
	struct Opponent opponent;
	enum Turn turn;
	int running;
};

struct Game Game_init()
{
	struct Game self;
	
	switch(randint(0, 1))
	{
	case 0:
		self.turn = PLAYER;
		break;
	case 1:
		self.turn = OPPONENT;
		break;
	}
	
	char playerName[0];
	printf(" 3, 2, 1, Fight!\n");
	printf(" Enter your name:\n ");
	scanf("%s", playerName);
	self.player = Player_init(playerName);
	printf(" Hello, %s! Let's Play!\n\n", playerName);
	self.opponent = Opponent_init();
	
	self.running = 0;
	
	return self;
}

void Game_annonceStats(struct Game* self)
{
	printf(" %s's Stats:\n", self->player.name);
	printf(" health: %d\n", self->player.health);
	printf(" attackDanage: %d\n\n", self->player.attackDamage);
	
	printf(" %s's Stats:\n", self->opponent.name);
	printf(" health: %d\n", self->opponent.health);
	printf(" attackDanage: %d\n\n", self->opponent.attackDamage);
}

void Game_start(struct Game* self)
{
	self->running = 1;
	Game_annonceStats(self);
	while(self->running)
	{
		switch(self->turn)
		{
		case PLAYER:
			Player_attack(&self->player, &self->opponent);
			Game_annonceStats(self);
			self->turn = OPPONENT;
			break;
		case OPPONENT:
			Opponent_attack(&self->opponent, &self->player);
			Game_annonceStats(self);
			self->turn = PLAYER;
			break;
		}
		if(self->player.health <= 0)
		{
			printf(" Game has ended!\n\n");
			printf(" Winner is %s!\n", self->opponent.name);
			self->running = 0;
		}
		else if(self->opponent.health <= 0)
		{
			printf(" Game has ended!\n\n");
			printf(" Winner is %s!\n", self->player.name);
			self->running = 0;
		}
	}
}
// GAME END

int main(int argc, char *argv[])
{
	randomize();
	struct Game game = Game_init();
	Game_start(&game);
	return 0;
}