#include "stdafx.h"
#include "MyGame.h"

CMyGame::CMyGame(void)  :
	startScreen(400,300,"menu.png",0)
	// to initialise more sprites here use a comma-separated list
{
	// TODO: add initialisation here
}

CMyGame::~CMyGame(void)
{
	// TODO: add destruction code here
}

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	// do not run game logic when in menu mode
	if (IsMenuMode()) return;

	Uint32 t = GetTime();

	// TODO: add the game update code here

	//FIRST LEVEL
	//-ZORO
	if (whatlvl == 1)
	{	
		if (player.HitTest(&caveLine))
		{
			bmusic.Pause();
			zorotheme.Play("zorotheme.wav");

			player.SetSpeed(0);
			textbox.LoadImage("textbox.png", "textbox", 5, 1, 0, 0, CColor::White());
			textbox.AddImage("textbox.png", "textbox", 5, 1, 0, 0, 4, 0, CColor::White());
			textbox.SetAnimation("textbox", 10);
			textbox.SetPosition(1950, 200);

			text1.LoadImage("text1.png", "textstatic1", 9, 1, 8, 0, CColor::White());
			text1.AddImage("text1.png", "text1", 9, 1, 0, 0, 8, 0, CColor::White());
			text1.SetAnimation("text1", 10);
			text1.SetPosition(1900, 200);

			pressE.LoadImage("pressE.png", "pressE", CColor::White());
			pressE.SetImage("pressE");
			pressE.SetPosition(1970, 175);

			caveLine.SetPosition(-10000000000, -1000000000);
		}
		if (text1.GetCurrentAnimationFrame() == 8)
		{
			text1.SetImage("textstatic1");
		}
		if (IsKeyDown(SDLK_e))
		{
			text1.Delete();
			text2.LoadImage("text2.png", "textstatic2", 19, 1, 18, 0, CColor::White());
			text2.AddImage("text2.png", "text2", 19, 1, 0, 0, 18, 0, CColor::White());
			text2.SetAnimation("text2", 10);
			text2.SetPosition(1950, 200);
		}
		if (text2.GetCurrentAnimationFrame() == 18)
		{
			text2.SetImage("textstatic2");
			isPressed1TimeZoro = true;
		}
		if (IsKeyDown(SDLK_e) && isPressed1TimeZoro == true)
		{
			textbox.Delete();
			text2.Delete();
			pressE.Delete();

			zorotheme.Stop();
			bmusic.Resume();

			isPressed2ndTimeZoro = true;
		}
	}
	if (whatlvl == 1 && zorohealth > 0)
	{
		if (skeletonspawnList.size() <= 0)
		{
			if (samuraiPreAttack1.IsDead() && !samuraiAttack5.IsDying())
			{
				isZoroTpAttack = true;
				samuraiAttack5.LoadImage("zorotpattack.png", "zorotpattack", CColor::Black());
				samuraiAttack5.SetImage("zorotpattack", CColor::Black());
				samuraiAttack5.Die(1000);
				samuraiAttack5.SetPosition(player.GetX() - 100, player.GetY());

				slash.LoadImage("slash.png", "slash", 4, 1, 0, 0, CColor::Black());
				slash.AddImage("slash.png", "slash", 4, 1, 0, 0, 3, 0, CColor::Black());
				slash.SetAnimation("slash", 10);
				slash.Die(400);
				slash.SetPosition(player.GetPosition());

				zoroattack3.Play("zoro_blade.wav");
			}
			if (samuraiAttack5.IsDead())
			{
				isZoroTpAttack = false;
				samurai.UnDelete();
				samurai.AddImage("zorostand.png", "zorostand", CColor::Black());
				samurai.SetPosition(samurai.GetX(), samurai.GetY());
				samuraiAttack5.UnDie();
				samuraiAttack5.UnDelete();
				samuraiPreAttack1.UnDie();
				samuraiPreAttack1.UnDelete();
				slash.UnDie();
				slash.UnDelete();
				samuraiAttack5.SetY(5000);
				samuraiPreAttack1.SetY(5000);
				slash.SetY(5000);
			}
		}
		if (samuraiAttack1.IsDead())
		{
			isZoroFirstAttack = false;
			samurai.UnDelete();
			samurai.AddImage("zorostand.png", "zorostand", CColor::Black());
			samurai.SetImage("zorostand");
			samurai.SetPosition(samuraiAttack1.GetX(), samuraiAttack1.GetY() - 40);
			samuraiAttack1.UnDie();
			samuraiAttack1.UnDelete();
			samuraiAttack1.SetY(5000);
		}

		if (samuraiAttack2.IsDead())
		{
			isZoroSecondAttack = false;
			samurai.UnDelete();
			samurai.AddImage("zorostand.png", "zorostand", CColor::Black());
			samurai.SetImage("zorostand");
			samurai.SetPosition(samuraiAttack2.GetX(), samuraiAttack2.GetY());
			samuraiAttack2.UnDie();
			samuraiAttack2.UnDelete();
			samuraiAttack2.SetY(5000);
		}
	}
	//-skeleton
	for (CSprite* skeleton : skeletonspawnList)
	{
		if (skeleton->GetCurrentAnimationFrame() == 47)
		{
			if (spawncounter == 0)
			{
				CSprite* skeleton1 = new CSprite(skeleton->GetX(), skeleton->GetY(), 0, 0, GetTime());
				skeleton1->AddImage("skeletonWalk.png", "skeletonwalk", 4, 1, 0, 0, 3, 0, CColor::Black());
				skeleton1->SetAnimation("skeletonwalk", 10);
				skeleton1->SetDirection(270);
				skeleton1->SetSpeed(50);
				skeleton1->SetHealth(skeleton->GetHealth());
				skeletonspawnList.push_back(skeleton1);

				spawncounter = 30;
			}
		}
	}
	for (CSprite* skeleton2 : skeletonAttackList)
	{
		if (skeleton2->GetCurrentAnimationFrame() == 2)
		{
			if (attackcounter == 0)
			{
				CSprite* skeletonswing = new CSprite(skeleton2->GetX() - 20, skeleton2->GetY(), "samuraiSwing.png", CColor::Black(), GetTime());
				skeletonswing->SetDirection(270);
				skeletonswing->SetSpeed(300);
				skeletonswing->Die(600);
				skeletonSwingList.push_back(skeletonswing);

				swinging.Play("slash.wav");

				attackcounter = 10;
			}
		}
	}
	for (CSprite* skeletonswing : skeletonSwingList)
	{
		if (skeletonswing->HitTest(&tower1))
		{
			if (damagecounter == 0)
			{
				skeletonswing->SetY(50000);
				tower1health -= damage;

				damagecounter = 30;
			}
		}
	}

	//SECOND LEVEL
	//-tree attacks
	//--tree first attack
	if (whatlvl == 2)
	{
		if (rootAttack.GetCurrentAnimationFrame() == 5)
		{
			rootAttack.Delete();
			rootAttackEnds.UnDelete();

			rootAttackEnds.LoadImage("rootAttack.png", "rootattackends", 6, 1, 0, 0, CColor::Black());
			rootAttackEnds.AddImage("rootAttack.png", "rootattackends", 6, 1, 5, 0, 0, 0, CColor::Black());
			rootAttackEnds.SetAnimation("rootattackends");
			rootAttackEnds.SetPosition(rootAttack.GetX(), rootAttack.GetY());

			if (player.HitTest(&rootAttack))
			{
				isDamaged = true;
				if (damagecounter == 0)
				{
					if (isDamaged == true)
					{
						playerhealth -= rootdamage;
						isDamaged = false;
						damagecounter = 30;
					}
				}
			}
		}
		if (rootAttackEnds.GetCurrentAnimationFrame() == 5)
		{
			rootAttackEnds.Delete();
			rootAttack.UnDelete();
		}
		//after tree's death
		if (treehealth <= 0)
		{
			rootAttack.Delete();
			rootAttackEnds.Delete();
			hitbox.Delete();
		}
	}
	//--tree second attack
	if (whatlvl == 2)
	{
		for (CSprite* energyBall : magicList)
		{
			if (player.GetX() < 2040)
			{
				if (player.HitTest(energyBall) && player.GetStatus() != BLOCK)
				{
					isDamaged = true;
					if (isDamaged == true)
					{
						energyBall->Delete();
						playerhealth -= damage;
						isDamaged = false;
					}
				}
				if (player.HitTest(energyBall) && player.GetStatus() == BLOCK)
				{
					isDamaged = false;
					energyBall->Delete();
				}
			}
		}
	}
	//-spider
	for (CSprite* spider : spiderspawnList)
	{
		if (spider->GetY() < 80)
		{
			spider->SetDirection(270);
			spider->SetSpeed(50);
		}
	}
	for (CSprite* spider1 : spiderAttackList)
	{
		if (spider1->HitTest(110, 80) && spider1->GetCurrentAnimationFrame() == 6)
		{
			if (damagecounter == 0)
			{
				tower2health -= damage;

				damagecounter = 30;
			}
		}
	}

	//THIRD LEVEL
	//-boss
	//--begins attack
	if (player.HitTest(&hellLine))
	{
		magician.SetAnimation("magicattack", 2);
		hellLine.SetPosition(-10000000000, -1000000000);
	}
	//--boss' attack
	if (whatlvl == 3)
	{
		for (CSprite* fireBall : magicList)
		{
			if (player.GetX() < 2040)
			{
				if (player.HitTest(fireBall) && player.GetStatus() != BLOCK)
				{
					isDamaged = true;
					if (isDamaged == true)
					{
						fireBall->Delete();
						playerhealth -= damage;
						isDamaged = false;
					}
				}
				if (player.HitTest(fireBall) && player.GetStatus() == BLOCK)
				{
					isDamaged = false;
					fireBall->Delete();
				}
			}
		}
	}

	//functions
	PlayerControl();
	BossControl();
	EnemyControl();
	DeathControl();
	SpawnControl();
	isFirstLvl();
	isSecondLvl();

	//player do after swings
	if (player.GetCurrentAnimationFrame() == 4)
	{
		if (player.GetStatus() == STANDRIGHT)
		{
			player.SetAnimation("standright", 4);
		}
		else if (player.GetStatus() == STANDLEFT)
		{
			player.SetAnimation("standleft", 4);
		}	
	}
	//moving to the next level
	if (player.HitTest(&doorToLvl2))
	{
		tower1.SetPosition(-1000000000, -10000000);
		doorToLvl2.SetPosition(-10000000, -100000000);
		SetupLevel2();
	}
	if (player.HitTest(&doorToLvl3))
	{
		tower2.SetPosition(-1000000000, -10000000);
		doorToLvl3.SetPosition(-10000000000, -1000000000);
		tree.SetPosition(-10000000000, -10000000000);
		SetupLevel3();
	}

	//counters
	if (swingcounter > 0)
	{
		swingcounter--;
	}

	if (spawncounter > 0)
	{
		spawncounter--;
	}

	if (attackcounter > 0)
	{
		attackcounter--;
	}

	if (damagecounter > 0)
	{
		damagecounter--;
	}

	if (animationcounter > 0)
	{
		animationcounter--;
	}

	if (energyballcounter > 0)
	{
		energyballcounter--;
	}

	//drop potions after defeating bosses
	if (whatlvl == 1)
	{
		if (zorohealth <= 0)
		{
			hpPotion.SetImage("hp");
			hpPotion.SetPosition(hitbox.GetX() + 15, hitbox.GetY()-40);

			strengthPotion.SetImage("strength");
			strengthPotion.SetPosition(hitbox.GetX() - 15, hitbox.GetY()-40);
		}
	}
	if (whatlvl == 2)
	{
		if (treehealth <= 0)
		{
			hpPotion.SetImage("hp");
			hpPotion.SetPosition(hitbox.GetX() + 15, hitbox.GetY()-40);

			strengthPotion.SetImage("strength");
			strengthPotion.SetPosition(hitbox.GetX() - 15, hitbox.GetY()-40);
		}
	}

	//what potions do
	if (player.HitTest(&strengthPotion))
	{
		strengthPotion.Delete();
		playerdamage1 = 30;
	}
	if (player.HitTest(&hpPotion))
	{
		hpPotion.Delete();
		playerhealth = 100;
	}

	//random spawn position of hp potion on 3rd lvl to help player 
	if (whatlvl == 3 && magicianhealth > 0)
	{
		if (rand() % 100 == 0)
		{
			hpPotion.SetImage("hp");
			hpPotion.SetPosition(1000 + rand() % 1500, 100);
			hpPotion.UnDelete();
		}
	}
	
	//GAME WIN
	if (whatlvl == 3)
	{
		if (player.HitTest(&hellLine1))
		{
			chest.SetAnimation("chestopen");
			bmusic.Stop();
			victory.Play("victory.wav");
			hellLine1.SetY(50000);
		}
		if (chest.GetCurrentAnimationFrame() == 9)
		{
			gamewon = true;
			GameOver();
			PauseGame();
		}
	}

	//GAME OVER
	if (tower1health <= 0)
	{
		GameOver();
		PauseGame();
		bmusic.Stop();
		gameover.Play("gameover.wav");
	}
	if (tower2health <= 0)
	{
		GameOver();
		PauseGame();
		bmusic.Stop();
		gameover.Play("gameover.wav");
	}
	if (player.GetStatus() == DEATH)
	{
		bmusic.Stop();
		gameover.Play("gameover.wav");
		if (player.GetCurrentAnimationFrame() == 2)
		{
			player.SetImage("death");
			GameOver();
			PauseGame();
		}
	}


	magicList.delete_if(deleted);
	skeletonAttackList.delete_if(deleted);
	spiderAttackList.delete_if(deleted);
	spiderspawnList.delete_if(deleted);
	skeletonspawnList.delete_if(deleted);
	mobDeathList.delete_if(deleted);
	firstSwingList.delete_if(deleted);
	secondSwingList.delete_if(deleted);

	for (CSprite* swing : firstSwingList) swing->Update(t);
	for (CSprite* swing1 : secondSwingList) swing1->Update(t);

	for (CSprite* mobdeath : mobDeathList) mobdeath->Update(t);

	for (CSprite* spider : spiderspawnList) spider->Update(t);
	for (CSprite* spider1 : spiderAttackList) spider1->Update(t);

	for (CSprite* skeleton : skeletonspawnList) skeleton->Update(t);
	for (CSprite* skeleton1 : skeletonspawnList) skeleton1->Update(t);
	for (CSprite* skeleton2 : skeletonAttackList) skeleton2->Update(t);

	for (CSprite* energyBall : magicList) energyBall->Update(t);
	for (CSprite* fireBall : magicList) fireBall->Update(t);

	for (CSprite* skeletonswing : skeletonSwingList)skeletonswing->Update(t);
	

	magician.Update(t);

	samurai.Update(t);
	samuraiAttack1.Update(t);
	samuraiAttack2.Update(t);
	samuraiPreAttack1.Update(t);
	samuraiAttack5.Update(t);
	tree.Update(t);
	treeAttack.Update(t);

	textbox.Update(t);
	text1.Update(t);
	text2.Update(t);
	pressE.Update(t);

	swing.Update(t);
	slash.Update(t);
	hitbox.Update(t);
	rootAttackEnds.Update(t);
	rootAttack.Update(t);
	energyBall.Update(t);

	hpPotion.Update(t);
	strengthPotion.Update(t);

	chest.Update(t);

	caveLine.Update(t);
	hellLine1.Update(t);
	hellLine.Update(t);

	tower1.Update(t);
	tower2.Update(t);

	player.Update(t);
}

void CMyGame::OnDraw(CGraphics* g)
{
	// draw menu when in menu mode
	if (IsMenuMode())
	{
		startScreen.Draw(g);
		return;
	}



	// ----- scrolling -------------------------------
    // game world (background image) is of size 2400x600
	int leftScreenLimit = 300;
	int rightScreenLimit = 1900; // 2400-800+300
	int scrolloffset = 0;
	
	// do not scroll if left to the left limit
	if (player.GetX() < leftScreenLimit)
	{
		scrolloffset = 0;
		g->SetScrollPos(0, 0);  
	}
    // we scroll the whole game world according to the player position
	// unless we reached the left or right screen limits
	else if (player.GetX() >= leftScreenLimit && player.GetX() <= rightScreenLimit)
	{
		scrolloffset = leftScreenLimit - player.GetX();
		g->SetScrollPos(leftScreenLimit - player.GetX(), 0);
	}
	// we stop scrolling with the player once we have reached the right limit
	// and remain in that fixedscrolling position at the right limit
	else if (player.GetX() > rightScreenLimit)
	{
		scrolloffset = leftScreenLimit - rightScreenLimit;
		g->SetScrollPos(leftScreenLimit-rightScreenLimit, 0);
	}

	//CHANGES SCREENLIMIT FOR EACH LEVEL BEFORE FIGHTING BOSS
	if (whatlvl == 1 && skeletonspawnList.size() > 0)
	{
		int leftScreenLimit = 300;
		int rightScreenLimit = 1100;
		int scrolloffset = 0;
		if (player.GetX() < leftScreenLimit)
		{
			scrolloffset = 0;
			g->SetScrollPos(0, 0);
		}
		else if (player.GetX() >= leftScreenLimit && player.GetX() <= rightScreenLimit)
		{
			scrolloffset = leftScreenLimit - player.GetX();
			g->SetScrollPos(leftScreenLimit - player.GetX(), 0);
		}
		else if (player.GetX() > rightScreenLimit)
		{
			scrolloffset = leftScreenLimit - rightScreenLimit;
			g->SetScrollPos(leftScreenLimit - rightScreenLimit, 0);
		}
	}
	if (whatlvl == 2 && spiderspawnList.size() > 0)
	{
		int leftScreenLimit = 300;
		int rightScreenLimit = 1100;
		int scrolloffset = 0;
		if (player.GetX() < leftScreenLimit)
		{
			scrolloffset = 0;
			g->SetScrollPos(0, 0);
		}
		else if (player.GetX() >= leftScreenLimit && player.GetX() <= rightScreenLimit)
		{
			scrolloffset = leftScreenLimit - player.GetX();
			g->SetScrollPos(leftScreenLimit - player.GetX(), 0);
		}
		else if (player.GetX() > rightScreenLimit)
		{
			scrolloffset = leftScreenLimit - rightScreenLimit;
			g->SetScrollPos(leftScreenLimit - rightScreenLimit, 0);
		}
	}
	if (whatlvl == 3 && magicianIsDead == false)
	{
		int leftScreenLimit = 300;
		int rightScreenLimit = 1100;
		int scrolloffset = 0;
		if (player.GetX() < leftScreenLimit)
		{
			scrolloffset = 0;
			g->SetScrollPos(0, 0);
		}
		else if (player.GetX() >= leftScreenLimit && player.GetX() <= rightScreenLimit)
		{
			scrolloffset = leftScreenLimit - player.GetX();
			g->SetScrollPos(leftScreenLimit - player.GetX(), 0);
		}
		else if (player.GetX() > rightScreenLimit)
		{
			scrolloffset = leftScreenLimit - rightScreenLimit;
			g->SetScrollPos(leftScreenLimit - rightScreenLimit, 0);
		}
	}


	hitbox.Draw(g);

	caveLine.Draw(g);
	hellLine1.Draw(g);
	hellLine.Draw(g);

	background.Draw(g);

	doorToLvl2.Draw(g);
	doorToLvl3.Draw(g);

	chest.Draw(g);

	magician.Draw(g);

	samurai.Draw(g);
	samuraiAttack1.Draw(g);
	samuraiAttack2.Draw(g);
	samuraiPreAttack1.Draw(g);
	samuraiAttack5.Draw(g);
	tree.Draw(g);
	treeAttack.Draw(g);
	energyBall.Draw(g);

	textbox.Draw(g);
	text1.Draw(g);
	text2.Draw(g);
	pressE.Draw(g);


	hpPotion.Draw(g);
	strengthPotion.Draw(g);

	tower1.Draw(g);
	tower2.Draw(g);

	rootAttackEnds.Draw(g);
	rootAttack.Draw(g);


	//shows player's hp
	*g << font(15) << color(CColor::Green()) << xy(player.GetX()-10, player.GetY()+20) << player.GetHealth();

	//shows everything else's hp
	if (whatlvl == 1)
	{
		for (CSprite* skeleton1 : skeletonspawnList)
		{
			if (skeleton1->GetHealth() > 0) *g << font(15) << color(CColor::Red()) << xy(skeleton1->GetX() + 25, skeleton1->GetY() + 15) << skeleton1->GetHealth();
		}

		*g << font(30) << color(CColor::Green()) << xy(tower1.GetX() - 30, tower1.GetY() + 110) << tower1health;

		for (CSprite* skeleton2 : skeletonAttackList)
		{
			if (skeleton2->GetHealth() > 0) *g << font(15) << color(CColor::Red()) << xy(skeleton2->GetX() + 25, skeleton2->GetY() + 15) << skeleton2->GetHealth();
		}

		if (samurai.GetHealth()>0)*g << font(15) << color(CColor::Red()) << xy(samurai.GetX()-15, samurai.GetY() + 70) << samurai.GetHealth();
	}
	
	if (whatlvl == 2)
	{
		for (CSprite* spider : spiderspawnList)
		{
			if (spider->GetHealth()>0) *g << font(15) << color(CColor::Red()) << xy(spider->GetX() - 10, spider->GetY()) << spider->GetHealth();
		}

		*g << font(30) << color(CColor::Green()) << xy(tower2.GetX() - 25, tower2.GetY() + 110) << tower2health;

		for (CSprite* spider1 : spiderAttackList)
		{
			if (spider1->GetHealth() > 0) *g << font(15) << color(CColor::Red()) << xy(spider1->GetX() - 10, spider1->GetY()) << spider1->GetHealth();
		}
		
		if (tree.GetHealth() > 0) *g << font(15) << color(CColor::Red()) << xy(tree.GetX() - 10, tree.GetY() + 20) << tree.GetHealth();
	}

	if (whatlvl == 3)
	{
		if (magician.GetHealth() > 0) *g << font(15) << color(CColor::Red()) << xy(magician.GetX() - 10, magician.GetY() + 50) << magician.GetHealth();
	}

	//text for levels
	if (whatlvl == 1 || whatlvl == 2)
	{
		*g << font(50) << color(CColor::White()) << xy(600, 450) << "PROTECT TOWER FROM ENEMIES";
		*g << font(15) << color(CColor::White()) << xy(1350, 300) << "Defeat all enemies to go further";
	}
	if (whatlvl == 3)
	{
		*g << font(50) << color(CColor::Black()) << xy(600, 450) << "DEFEAT THE BOSS";
	}


	for (CSprite* swing : firstSwingList) swing->Draw(g);
	for (CSprite* swing1 : secondSwingList) swing1->Draw(g);

	for (CSprite* mobdeath : mobDeathList) mobdeath->Draw(g);

	for (CSprite* spider : spiderspawnList) spider->Draw(g);
	for (CSprite* spider1 : spiderAttackList) spider1->Draw(g);

	for (CSprite* skeleton : skeletonspawnList) skeleton->Draw(g);
	for (CSprite* skeleton1 : skeletonspawnList) skeleton1->Draw(g);
	for (CSprite* skeleton2 : skeletonAttackList) skeleton2->Draw(g);

	for (CSprite* energyBall : magicList) energyBall->Draw(g);
	for (CSprite* fireBall : magicList) fireBall->Draw(g);

	for (CSprite* skeletonswing : skeletonSwingList)skeletonswing->Draw(g);

	swing.Draw(g);
	
	player.Draw(g);

	slash.Draw(g);

	 // don't scroll the overlay screen
	 g->SetScrollPos(0, 0);

	 *g << font(28) << color(CColor::White()) << xy(10, 570) << "score: " << score;

	 if (IsGameOverMode())
	 {
		 if (gamewon)
		 {
			 *g << font(46) << color(CColor::Green()) << vcenter << center << " GAME WON ";
		 }
		 else
		 {
			 *g << font(46) << color(CColor::Red()) << vcenter << center << " GAME OVER ";
		 }
	 }
	
}

void CMyGame::PlayerControl()
{

	float hwalkSpeed = 225; // horizontal walking speed
	float vwalkSpeed = 100; // vertical walking speed

	float lowerlimit = 100;  // setting the limits
	float upperlimit = 100;
	float leftlimit = 30;
	float rightlimit = 2400 - 30;
	
	/* 
	  player status variable is used to indicate which state the player is in

	  0: None
	  1: standing left looking
	  2: standing right looking
	  3: walking left
	  4: walking right
	*/

	// preserving the current status
    int old_animation_status = player.GetStatus();
    
	// resetting the player to standing each time and then
	// changing this according to state and keyboard input
    player.SetMotion(0, 0);
	if (player.GetStatus()==WALKLEFT) player.SetStatus(STANDLEFT);
	if (player.GetStatus()==WALKRIGHT) player.SetStatus(STANDRIGHT);
	if (player.GetStatus() == BLOCK) player.SetStatus(STANDRIGHT);
	
	// setting the speeds and animation status according to the keyboard controls
	if (IsKeyDown(SDLK_d)) { player.SetXVelocity(hwalkSpeed); player.SetStatus(WALKRIGHT); }
	if (IsKeyDown(SDLK_a)) { player.SetXVelocity(-hwalkSpeed); player.SetStatus(WALKLEFT); }
	if (IsKeyDown(SDLK_SPACE)) { player.SetStatus(BLOCK); }
	if (playerhealth<=0) { player.SetStatus(DEATH); }
	// changing animation sequences if different from previous status
	if (player.GetStatus() != old_animation_status)
	{
		if (player.GetStatus() == WALKLEFT) player.SetAnimation("walkleft", 10);
		if (player.GetStatus() == WALKRIGHT) player.SetAnimation("walkright", 10);
		if (player.GetStatus() == STANDRIGHT) player.SetAnimation("standright",5);
		if (player.GetStatus() == STANDLEFT) player.SetAnimation("standleft",5);
		if (player.GetStatus() == BLOCK) player.SetImage("block");
		if (player.GetStatus() == DEATH) player.SetAnimation("dying",5);
	}

	// setting the player movement limits
	if (player.GetY() > upperlimit) player.SetY(upperlimit);
	if (player.GetY() < lowerlimit) player.SetY(lowerlimit);
	if (player.GetX() < leftlimit) player.SetX(leftlimit);
	if (player.GetX() > rightlimit) player.SetX(rightlimit);

	//CHANGES LIMITS FOR EACH LEVEL BEFORE FIGHTING BOSS
	if (whatlvl == 1 && skeletonspawnList.size() > 0)
	{
		float leftlimit = 30;
		float rightlimit = 1500;

		if (player.GetY() > upperlimit) player.SetY(upperlimit);
		if (player.GetY() < lowerlimit) player.SetY(lowerlimit);
		if (player.GetX() < leftlimit) player.SetX(leftlimit);
		if (player.GetX() > rightlimit) player.SetX(rightlimit);
	}
	if (whatlvl == 2  && spiderspawnList.size() > 0)
	{
		float leftlimit = 30;
		float rightlimit = 1500;

		if (player.GetY() > upperlimit) player.SetY(upperlimit);
		if (player.GetY() < lowerlimit) player.SetY(lowerlimit);
		if (player.GetX() < leftlimit) player.SetX(leftlimit);
		if (player.GetX() > rightlimit) player.SetX(rightlimit);
	}
	if (whatlvl == 3 &&  magicianIsDead == false)
	{
		float leftlimit = 30;
		float rightlimit = 1500;

		if (player.GetY() > upperlimit) player.SetY(upperlimit);
		if (player.GetY() < lowerlimit) player.SetY(lowerlimit);
		if (player.GetX() < leftlimit) player.SetX(leftlimit);
		if (player.GetX() > rightlimit) player.SetX(rightlimit);
	}

	player.SetHealth(playerhealth);
	player.SetSpeed(300);

	player.Update(GetTime());
}

void CMyGame::BossControl()
{
	if (whatlvl == 1 && zorohealth > 0 && isPressed2ndTimeZoro == true)
	{
		if (skeletonspawnList.size() <= 0)
		{
			if (rand() % 50 == 0)
			{
				if (rand() % 5 == 0)
				{
					if (!isZoroSecondAttack && !isZoroTpAttack)
					{
						if (attackcounter == 0)
						{
							isZoroFirstAttack = true;
							samurai.Delete();
							samuraiAttack1.LoadImage("zoroattack1.png", "zoroattack1", 13, 1, 12, 0, CColor::Black());
							samuraiAttack1.AddImage("zoroattack1.png", "zoroattack1", 13, 1, 12, 0, 0, 0, CColor::Black());
							samuraiAttack1.SetAnimation("zoroattack1", 10);
							samuraiAttack1.SetPosition(samurai.GetX(), samurai.GetY() + 40);
							samuraiAttack1.SetHealth(zorohealth);
							samuraiAttack1.Die(1100);

							zoroattack1.Play("zoro_blade.wav");

							attackcounter = 30;

						}
					}
				}
				if (!isZoroFirstAttack && !isZoroTpAttack)
				{
					if (rand() % 5 == 1)
					{
						if (attackcounter == 0)
						{
							isZoroSecondAttack = true;
							samurai.Delete();
							samuraiAttack2.LoadImage("zoroattack2.png", "zoroattack2", 6, 1, 5, 0, CColor::Black());
							samuraiAttack2.AddImage("zoroattack2.png", "zoroattack2", 6, 1, 5, 0, 0, 0, CColor::Black());
							samuraiAttack2.SetAnimation("zoroattack2", 10);
							samuraiAttack2.SetPosition(samurai.GetX(), samurai.GetY());
							samuraiAttack2.SetHealth(zorohealth);
							samuraiAttack2.Die(600);

							zoroattack2.Play("zoroark.wav");

							attackcounter = 30;

						}
					}
				}
			}
			if (player.GetX() > 1520)
			{
				if (!isZoroFirstAttack && !isZoroSecondAttack)
				{
					if (rand() % 200 == 0)
					{
						if (attackcounter == 0)
						{
							isZoroTpAttack = true;
							samurai.Delete();
							samuraiPreAttack1.LoadImage("zoropreattack.png", "zoropreattack", CColor::Black());
							samuraiPreAttack1.AddImage("zoropreattack.png", "zoropreattack", CColor::Black());
							samuraiPreAttack1.SetImage("zoropreattack");
							samuraiPreAttack1.SetPosition(samurai.GetX(), samurai.GetY());
							samuraiPreAttack1.SetHealth(zorohealth);
							samuraiPreAttack1.Die(200);

							zoroonigiri.Play("zoroonigiri.wav");

							attackcounter = 60;
						}
					}
				}
			}
		}
		if (isZoroTpAttack == true && player.GetStatus() != BLOCK)
		{
			if (damagecounter == 0)
			{
				playerhealth -= damage;

				damagecounter = 120;
			}
		}
		if (isZoroFirstAttack == true && player.GetStatus() != BLOCK)
		{
			if (samuraiAttack1.HitTest(&player) && samuraiAttack1.GetCurrentAnimationFrame() == 3)
			{
				if (damagecounter == 0)
				{
					playerhealth -= damage;

					damagecounter = 60;
				}
			}
			if (samuraiAttack1.HitTest(&player) && samuraiAttack1.GetCurrentAnimationFrame() == 9)
			{
				if (damagecounter == 0)
				{
					playerhealth -= damage;

					damagecounter = 60;
				}
			}
		}
		if (isZoroSecondAttack == true && player.GetStatus() != BLOCK)
		{
			if (samuraiAttack2.HitTest(&player) && samuraiAttack2.GetCurrentAnimationFrame() == 3)
			{
				if (damagecounter == 0)
				{
					playerhealth -= damage;

					damagecounter = 60;
				}
			}
		}
	}

	if (whatlvl == 2)
	{
		if (player.GetX() > 1540)
		{
			if (attackcounter == 0)
			{
				rootAttack.LoadImage("rootAttack.png", "rootattack", 6, 1, 0, 0, CColor::Black());
				rootAttack.AddImage("rootAttack.png", "rootattack", 6, 1, 0, 0, 5, 0, CColor::Black());
				rootAttack.SetAnimation("rootattack");
				rootAttack.SetPosition(player.GetX() + rand() % 20, 60);

				attackcounter = 60;
			}
		}
		if (player.GetX() > 1540)
		{
			if (energyballcounter == 0)
			{
				CSprite* energyBall = new CSprite(tree.GetX()-10, tree.GetY()-35, 0, 0, GetTime());
				energyBall->AddImage("energyBall.png", "energyball", 35, 1, 0, 0, 34, 0, CColor::Black());
				energyBall->SetAnimation("energyball", 10);
				energyBall->SetDirection(270);
				energyBall->SetSpeed(200);
				magicList.push_back(energyBall);

				energyballcounter = 240;
			}
		}
	}

	if (whatlvl == 3)
	{
		if (player.GetX() > 300)
		{
			if (magician.GetCurrentAnimationFrame() == 2)
			{
				if (attackcounter == 0)
				{
					CSprite* fireBall = new CSprite(700 + rand() % 800, 620, 0, 0, GetTime());
					fireBall->LoadImage("fireball.png", "fireball", CColor::Black());
					fireBall->SetImage("fireball");
					fireBall->SetDirection(player.GetPosition() - fireBall->GetPosition());
					fireBall->SetSpeed(200);
					magicList.push_back(fireBall);

					attackcounter = 10;
					if (magicianIsDead == true)
					{
						fireBall->Delete();
					}
				}
			}
		}
	}

	magicList.delete_if(deleted);
}

void CMyGame::EnemyControl()
{
	for (CSprite* skeleton1 : skeletonspawnList)
	{
		if (skeleton1->GetX() < 150 + rand() % 200)
		{
			if (animationcounter == 0)
			{
				skeleton1->Delete();
				CSprite* skeleton2 = new CSprite(skeleton1->GetX(), skeleton1->GetY(), 0, 0, GetTime());
				skeleton2->AddImage("skeletonAttack.png", "skeletonattack", 4, 1, 0, 0, 3, 0, CColor::Black());
				skeleton2->SetAnimation("skeletonattack", 10);
				skeleton2->SetHealth(skeleton1->GetHealth());
				skeletonAttackList.push_back(skeleton2);

				animationcounter = 10;
			}
		}
	}
	for (CSprite* spider : spiderspawnList)
	{
		if (spider->HitTest(110,80))
		{
			if (animationcounter == 0)
			{
				spider->Delete();
				CSprite* spider1 = new CSprite(spider->GetX(), spider->GetY(), 0, 0, GetTime());
				spider1->AddImage("spiderAttack.png", "spiderattack", 9, 1, 0, 0, 8, 0, CColor::White());
				spider1->SetAnimation("spiderattack", 10);
				spider1->SetHealth(spider->GetHealth());
				spider1->Die(1000);
				spiderAttackList.push_back(spider1);

				animationcounter = 10;
			}
		}
	}

	skeletonspawnList.delete_if(deleted);
	spiderspawnList.delete_if(deleted);
}


void CMyGame::SpawnControl()
{
	if (whatlvl == 1)
	{
		if (score <= 200)
		{
			if (rand() % 100 == 0)
			{
				CSprite* skeleton = new CSprite(700 + rand() % 800, 80, 0, 0, GetTime());
				skeleton->AddImage("skeletonSpawn.png", "skeletonspawn", 48, 1, 0, 0, 47, 0, CColor::Black());
				skeleton->SetAnimation("skeletonspawn", 10);
				skeleton->SetHealth(50);
				skeleton->Die(4750);
				skeletonspawnList.push_back(skeleton);
			}
		}
	}

	if (whatlvl == 2)
	{
		if (score <= 600)
		{
			if (rand() % 100 == 0)
			{
				CSprite* spider = new CSprite(700 + rand() % 800, 810, 0, 0, GetTime());
				spider->AddImage("spiderWalkingL.png", "spiderwalking", 4, 1, 0, 0, 3, 0, CColor::White());
				spider->SetAnimation("spiderwalking", 10);
				spider->SetDirection(180);
				spider->SetSpeed(400);
				spider->SetHealth(50);
				spiderspawnList.push_back(spider);
			}
		}
	}


	skeletonspawnList.delete_if(deleted);
	spiderspawnList.delete_if(deleted);
}

void CMyGame::DeathControl()
{
	for (CSprite* swing : firstSwingList)
	{
		for (CSprite* spider : spiderspawnList)
		{
			if (swing->HitTest(spider))
			{
				swing->Delete();
				spider->SetHealth(spider->GetHealth()-10);
				hitbox.SetImage("hitbox");
				hitbox.SetPosition(spider->GetX(), spider->GetY());
				if (spider->GetHealth() <= 0)
				{
					score = score + 10;
					spider->Delete();
					CSprite* mobdeath = new CSprite(hitbox.GetX(), hitbox.GetY(), 0, 0, GetTime());
					mobdeath->AddImage("mobdeath.png", "mobdeath", 6, 1, 0, 0, 5, 0, CColor::Black());
					mobdeath->SetAnimation("mobdeath", 10);
					mobdeath->Die(540);
					mobDeathList.push_back(mobdeath);

					explosion.Play("explosion.wav");
					hitbox.Delete();
				}
			}
			
		}
		for (CSprite* spider1 : spiderAttackList)
		{
			if (swing->HitTest(spider1))
			{
				swing->Delete();
				spider1->SetHealth(spider1->GetHealth() - 10);
				hitbox.SetImage("hitbox");
				hitbox.SetPosition(spider1->GetX(), spider1->GetY());
				if (spider1->GetHealth() <= 0)
				{
					score = score + 10;
					spider1->Delete();
					CSprite* mobdeath = new CSprite(hitbox.GetX(), hitbox.GetY(), 0, 0, GetTime());
					mobdeath->AddImage("mobdeath.png", "mobdeath", 6, 1, 0, 0, 5, 0, CColor::Black());
					mobdeath->SetAnimation("mobdeath", 10);
					mobdeath->Die(540);
					mobDeathList.push_back(mobdeath);
					explosion.Play("explosion.wav");
					hitbox.Delete();
				}
			}
		}
		if (swing->HitTest(&tree))
		{
			swing->Delete();
			tree.SetHealth(treehealth -= playerdamage1);
			hitbox.SetImage("hitbox");
			hitbox.SetPosition(tree.GetX(), tree.GetY());
			if (tree.GetHealth() <= 0)
			{
				score = score + 100;
				tree.SetPosition(-100000000, -10000000);
				CSprite* mobdeath = new CSprite(hitbox.GetX(), hitbox.GetY(), 0, 0, GetTime());
				mobdeath->AddImage("mobdeath.png", "mobdeath", 6, 1, 0, 0, 5, 0, CColor::Black());
				mobdeath->SetAnimation("mobdeath", 10);
				mobdeath->Die(540);
				mobDeathList.push_back(mobdeath);
				explosion.Play("explosion.wav");
				hitbox.Delete();
				rootAttack.Delete();
			}
		}
		for (CSprite* skeleton : skeletonspawnList)
		{
			if (swing->HitTest(skeleton))
			{
				swing->Delete();
				skeleton->SetHealth(skeleton->GetHealth() - 10);
				hitbox.SetImage("hitbox");
				hitbox.SetPosition(skeleton->GetX()+ 30, skeleton->GetY());
				if (skeleton->GetHealth() <= 0)
				{
					score = score + 10;
					skeleton->Delete();
					CSprite* mobdeath = new CSprite(hitbox.GetX(), hitbox.GetY(), 0, 0, GetTime());
					mobdeath->AddImage("mobdeath.png", "mobdeath", 6, 1, 0, 0, 5, 0, CColor::Black());
					mobdeath->SetAnimation("mobdeath", 10);
					mobdeath->Die(540);
					mobDeathList.push_back(mobdeath);
					explosion.Play("explosion.wav");
					hitbox.Delete();
				}
			}
		}
		for (CSprite* skeleton2 : skeletonAttackList)
		{
			if (swing->HitTest(skeleton2))
			{
				swing->Delete();
				skeleton2->SetHealth(skeleton2->GetHealth() - 10);
				hitbox.SetImage("hitbox");
				hitbox.SetPosition(skeleton2->GetX() + 30, skeleton2->GetY());
				if (skeleton2->GetHealth() <= 0)
				{
					score = score + 10;
					skeleton2->Delete();
					CSprite* mobdeath = new CSprite(hitbox.GetX(), hitbox.GetY(), 0, 0, GetTime());
					mobdeath->AddImage("mobdeath.png", "mobdeath", 6, 1, 0, 0, 5, 0, CColor::Black());
					mobdeath->SetAnimation("mobdeath", 10);
					mobdeath->Die(540);
					mobDeathList.push_back(mobdeath);
					explosion.Play("explosion.wav");
					hitbox.Delete();
				}
			}
		}
		if (swing->HitTest(&magician))
		{
			swing->Delete();
			magician.SetHealth(magicianhealth -= playerdamage1);
			hitbox.SetImage("hitbox");
			hitbox.SetPosition(magician.GetX(), magician.GetY());
			if (magician.GetHealth() <= 0)
			{
				magicianIsDead = true;
				score = score + 100;
				magician.SetPosition(-100000000, -10000000);
				CSprite* mobdeath = new CSprite(hitbox.GetX(), hitbox.GetY(), 0, 0, GetTime());
				mobdeath->AddImage("mobdeath.png", "mobdeath", 6, 1, 0, 0, 5, 0, CColor::Black());
				mobdeath->SetAnimation("mobdeath", 10);
				mobdeath->Die(540);
				mobDeathList.push_back(mobdeath);
				explosion.Play("explosion.wav");
				hitbox.Delete();
			}
		}
		if (swing->HitTest(&samurai))
		{
			swing->Delete();
			samurai.SetHealth(zorohealth -= playerdamage1);
			hitbox.SetImage("hitbox");
			hitbox.SetPosition(samurai.GetX(), samurai.GetY());
			if (samurai.GetHealth() <= 0)
			{
				score = score + 100;
				samurai.SetPosition(-100000000, -10000000);
				CSprite* mobdeath = new CSprite(hitbox.GetX(), hitbox.GetY(), 0, 0, GetTime());
				mobdeath->AddImage("mobdeath.png", "mobdeath", 6, 1, 0, 0, 5, 0, CColor::Black());
				mobdeath->SetAnimation("mobdeath", 10);
				mobdeath->Die(540);
				mobDeathList.push_back(mobdeath);
				explosion.Play("explosion.wav");
				hitbox.Delete();
			}
		}
		if (swing->HitTest(&samuraiAttack1))
		{
			swing->Delete();
			samuraiAttack1.SetHealth(zorohealth -= playerdamage1);
			hitbox.SetImage("hitbox");
			hitbox.SetPosition(samurai.GetX(), samurai.GetY());
			if (samuraiAttack1.GetHealth() <= 0)
			{
				score = score + 100;
				samuraiAttack1.SetPosition(-100000000, -10000000);
				CSprite* mobdeath = new CSprite(hitbox.GetX(), hitbox.GetY(), 0, 0, GetTime());
				mobdeath->AddImage("mobdeath.png", "mobdeath", 6, 1, 0, 0, 5, 0, CColor::Black());
				mobdeath->SetAnimation("mobdeath", 10);
				mobdeath->Die(540);
				mobDeathList.push_back(mobdeath);
				explosion.Play("explosion.wav");
				hitbox.Delete();
			}
		}
		if (swing->HitTest(&samuraiPreAttack1))
		{
			swing->Delete();
			samuraiAttack2.SetHealth(zorohealth -= playerdamage1);
			hitbox.SetImage("hitbox");
			hitbox.SetPosition(samurai.GetX(), samurai.GetY());
			if (samuraiAttack2.GetHealth() <= 0)
			{
				score = score + 100;
				samuraiAttack2.SetPosition(-100000000, -10000000);
				CSprite* mobdeath = new CSprite(hitbox.GetX(), hitbox.GetY(), 0, 0, GetTime());
				mobdeath->AddImage("mobdeath.png", "mobdeath", 6, 1, 0, 0, 5, 0, CColor::Black());
				mobdeath->SetAnimation("mobdeath", 10);
				mobdeath->Die(540);
				mobDeathList.push_back(mobdeath);
				explosion.Play("explosion.wav");
				hitbox.Delete();
			}
		}
		if (swing->HitTest(&samuraiAttack2))
		{
			swing->Delete();
			samuraiAttack2.SetHealth(zorohealth -= playerdamage1);
			hitbox.SetImage("hitbox");
			hitbox.SetPosition(samurai.GetX(), samurai.GetY());
			if (samuraiAttack2.GetHealth() <= 0)
			{
				score = score + 100;
				samuraiAttack2.SetPosition(-100000000, -10000000);
				CSprite* mobdeath = new CSprite(hitbox.GetX(), hitbox.GetY(), 0, 0, GetTime());
				mobdeath->AddImage("mobdeath.png", "mobdeath", 6, 1, 0, 0, 5, 0, CColor::Black());
				mobdeath->SetAnimation("mobdeath", 10);
				mobdeath->Die(540);
				mobDeathList.push_back(mobdeath);
				explosion.Play("explosion.wav");
				hitbox.Delete();
			}
		}
		if (swing->HitTest(&samuraiAttack5))
		{
			swing->Delete();
			samuraiAttack5.SetHealth(zorohealth -= playerdamage1);
			hitbox.SetImage("hitbox");
			hitbox.SetPosition(samurai.GetX(), samurai.GetY());
			if (samuraiAttack5.GetHealth() <= 0)
			{
				score = score + 100;
				samuraiAttack5.SetPosition(-100000000, -10000000);
				CSprite* mobdeath = new CSprite(hitbox.GetX(), hitbox.GetY(), 0, 0, GetTime());
				mobdeath->AddImage("mobdeath.png", "mobdeath", 6, 1, 0, 0, 5, 0, CColor::Black());
				mobdeath->SetAnimation("mobdeath", 10);
				mobdeath->Die(540);
				mobDeathList.push_back(mobdeath);
				explosion.Play("explosion.wav");
				hitbox.Delete();
			}
		}
	}
	


	for (CSprite* swing1 : secondSwingList)
	{
		for (CSprite* spider : spiderspawnList)
		{
			if (swing1->HitTest(spider))
			{
				spider->SetHealth(spider->GetHealth() - 1);
				hitbox.SetImage("hitbox");
				hitbox.SetPosition(spider->GetX(), spider->GetY());
				if (spider->GetHealth() <= 0)
				{
					score = score + 10;
					spider->Delete();
					CSprite* mobdeath = new CSprite(hitbox.GetX(), hitbox.GetY(), 0, 0, GetTime());
					mobdeath->AddImage("mobdeath.png", "mobdeath", 6, 1, 0, 0, 5, 0, CColor::Black());
					mobdeath->SetAnimation("mobdeath", 10);
					mobdeath->Die(540);
					mobDeathList.push_back(mobdeath);
					explosion.Play("explosion.wav");
					hitbox.Delete();

				}
			}
			
		}
		for (CSprite* spider1 : spiderAttackList)
		{
			if (swing1->HitTest(spider1))
			{
				spider1->SetHealth(spider1->GetHealth() - 1);
				hitbox.SetImage("hitbox");
				hitbox.SetPosition(spider1->GetX(), spider1->GetY());
				if (spider1->GetHealth() <= 0)
				{
					score = score + 10;
					spider1->Delete();
					CSprite* mobdeath = new CSprite(hitbox.GetX(), hitbox.GetY(), 0, 0, GetTime());
					mobdeath->AddImage("mobdeath.png", "mobdeath", 6, 1, 0, 0, 5, 0, CColor::Black());
					mobdeath->SetAnimation("mobdeath", 10);
					mobdeath->Die(540);
					mobDeathList.push_back(mobdeath);
					explosion.Play("explosion.wav");
					hitbox.Delete();
				}
			}
		}
		if (swing1->HitTest(&tree))
		{
			tree.SetHealth(treehealth -= playerdamage2);
			hitbox.SetImage("hitbox");
			hitbox.SetPosition(tree.GetX(), tree.GetY());
			if (tree.GetHealth() <= 0)
			{
				score = score + 100;
				tree.SetPosition(-100000000, -10000000);
				CSprite* mobdeath = new CSprite(hitbox.GetX(), hitbox.GetY(), 0, 0, GetTime());
				mobdeath->AddImage("mobdeath.png", "mobdeath", 6, 1, 0, 0, 5, 0, CColor::Black());
				mobdeath->SetAnimation("mobdeath", 10);
				mobdeath->Die(540);
				mobDeathList.push_back(mobdeath);
				explosion.Play("explosion.wav");
				rootAttack.Delete();
				hitbox.Delete();
			}
		}
		for (CSprite* skeleton : skeletonspawnList)
		{
			if (swing1->HitTest(skeleton))
			{
				skeleton->SetHealth(skeleton->GetHealth() - 1);
				hitbox.SetImage("hitbox");
				hitbox.SetPosition(skeleton->GetX() + 30, skeleton->GetY());
				if (skeleton->GetHealth() <= 0)
				{
					score = score + 10;
					skeleton->Delete();
					CSprite* mobdeath = new CSprite(hitbox.GetX(), hitbox.GetY(), 0, 0, GetTime());
					mobdeath->AddImage("mobdeath.png", "mobdeath", 6, 1, 0, 0, 5, 0, CColor::Black());
					mobdeath->SetAnimation("mobdeath", 10);
					mobdeath->Die(540);
					mobDeathList.push_back(mobdeath);
					explosion.Play("explosion.wav");
					hitbox.Delete();
				}
			}
		}
		for (CSprite* skeleton2 : skeletonAttackList)
		{
			if (swing1->HitTest(skeleton2))
			{
				skeleton2->SetHealth(skeleton2->GetHealth() - 1);
				hitbox.SetImage("hitbox");
				hitbox.SetPosition(skeleton2->GetX() + 30, skeleton2->GetY());
				if (skeleton2->GetHealth() <= 0)
				{
					score = score + 10;
					skeleton2->Delete();
					CSprite* mobdeath = new CSprite(hitbox.GetX(), hitbox.GetY(), 0, 0, GetTime());
					mobdeath->AddImage("mobdeath.png", "mobdeath", 6, 1, 0, 0, 5, 0, CColor::Black());
					mobdeath->SetAnimation("mobdeath", 10);
					mobdeath->Die(540);
					mobDeathList.push_back(mobdeath);
					explosion.Play("explosion.wav");
					hitbox.Delete();
				}
			}
		}
		if (swing1->HitTest(&magician))
		{
			magician.SetHealth(magicianhealth -= playerdamage2);
			hitbox.SetImage("hitbox");
			hitbox.SetPosition(tree.GetX(), tree.GetY());
			if (magician.GetHealth() <= 0)
			{
				magicianIsDead = true;
				score = score + 100;
				magician.SetPosition(-100000000, -10000000);
				CSprite* mobdeath = new CSprite(hitbox.GetX(), hitbox.GetY(), 0, 0, GetTime());
				mobdeath->AddImage("mobdeath.png", "mobdeath", 6, 1, 0, 0, 5, 0, CColor::Black());
				mobdeath->SetAnimation("mobdeath", 10);
				mobdeath->Die(540);
				mobDeathList.push_back(mobdeath);
				explosion.Play("explosion.wav");
				hitbox.Delete();
			}
		}
		if (swing1->HitTest(&samurai))
		{
			samurai.SetHealth(zorohealth -= playerdamage2);
			hitbox.SetImage("hitbox");
			hitbox.SetPosition(samurai.GetX(), samurai.GetY());
			if (samurai.GetHealth() <= 0)
			{
				score = score + 100;
				samurai.SetPosition(-100000000, -10000000);
				CSprite* mobdeath = new CSprite(hitbox.GetX(), hitbox.GetY(), 0, 0, GetTime());
				mobdeath->AddImage("mobdeath.png", "mobdeath", 6, 1, 0, 0, 5, 0, CColor::Black());
				mobdeath->SetAnimation("mobdeath", 10);
				mobdeath->Die(540);
				mobDeathList.push_back(mobdeath);
				explosion.Play("explosion.wav");
				hitbox.Delete();
			}
		}
		if (swing1->HitTest(&samuraiAttack1))
		{
			samuraiAttack1.SetHealth(zorohealth -= playerdamage2);
			hitbox.SetImage("hitbox");
			hitbox.SetPosition(samurai.GetX(), samurai.GetY());
			if (samuraiAttack1.GetHealth() <= 0)
			{
				score = score + 100;
				samuraiAttack1.SetPosition(-100000000, -10000000);
				CSprite* mobdeath = new CSprite(hitbox.GetX(), hitbox.GetY(), 0, 0, GetTime());
				mobdeath->AddImage("mobdeath.png", "mobdeath", 6, 1, 0, 0, 5, 0, CColor::Black());
				mobdeath->SetAnimation("mobdeath", 10);
				mobdeath->Die(540);
				mobDeathList.push_back(mobdeath);
				explosion.Play("explosion.wav");
				hitbox.Delete();
			}
		}
		if (swing1->HitTest(&samuraiPreAttack1))
		{
			samuraiAttack2.SetHealth(zorohealth -= playerdamage2);
			hitbox.SetImage("hitbox");
			hitbox.SetPosition(samurai.GetX(), samurai.GetY());
			if (samuraiAttack2.GetHealth() <= 0)
			{
				score = score + 100;
				samuraiAttack2.SetPosition(-100000000, -10000000);
				CSprite* mobdeath = new CSprite(hitbox.GetX(), hitbox.GetY(), 0, 0, GetTime());
				mobdeath->AddImage("mobdeath.png", "mobdeath", 6, 1, 0, 0, 5, 0, CColor::Black());
				mobdeath->SetAnimation("mobdeath", 10);
				mobdeath->Die(540);
				mobDeathList.push_back(mobdeath);
				explosion.Play("explosion.wav");
				hitbox.Delete();
			}
		}
		if (swing1->HitTest(&samuraiAttack2))
		{
			samuraiAttack2.SetHealth(zorohealth -= playerdamage2);
			hitbox.SetImage("hitbox");
			hitbox.SetPosition(samurai.GetX(), samurai.GetY());
			if (samuraiAttack2.GetHealth() <= 0)
			{
				score = score + 100;
				samuraiAttack2.SetPosition(-100000000, -10000000);
				CSprite* mobdeath = new CSprite(hitbox.GetX(), hitbox.GetY(), 0, 0, GetTime());
				mobdeath->AddImage("mobdeath.png", "mobdeath", 6, 1, 0, 0, 5, 0, CColor::Black());
				mobdeath->SetAnimation("mobdeath", 10);
				mobdeath->Die(540);
				mobDeathList.push_back(mobdeath);
				explosion.Play("explosion.wav");
				hitbox.Delete();
			}
		}
		if (swing1->HitTest(&samuraiAttack5))
		{
			samuraiAttack5.SetHealth(zorohealth -= playerdamage2);
			hitbox.SetImage("hitbox");
			hitbox.SetPosition(samurai.GetX(), samurai.GetY());
			if (samuraiAttack5.GetHealth() <= 0)
			{
				score = score + 100;
				samuraiAttack5.SetPosition(-100000000, -10000000);
				CSprite* mobdeath = new CSprite(hitbox.GetX(), hitbox.GetY(), 0, 0, GetTime());
				mobdeath->AddImage("mobdeath.png", "mobdeath", 6, 1, 0, 0, 5, 0, CColor::Black());
				mobdeath->SetAnimation("mobdeath", 10);
				mobdeath->Die(540);
				mobDeathList.push_back(mobdeath);
				explosion.Play("explosion.wav");
				hitbox.Delete();
			}
		}
	}

	magicList.delete_if(deleted);
	skeletonspawnList.delete_if(deleted);
	spiderspawnList.delete_if(deleted);
	mobDeathList.delete_if(deleted);
	firstSwingList.delete_if(deleted);
	secondSwingList.delete_if(deleted);
}

/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{   
	// loading the game map
	background.LoadImage("cave.png", "map1", CColor::Black());
	background.SetImage("map1"); background.SetPosition(1200, 200);


	// configuring the animations for the player sprite
	player.LoadImage("standingR.png", "standright", 4, 1, 0, 0, CColor::Black());
	player.AddImage("standingR.png", "standright", 4, 1, 0, 0, 3, 0, CColor::Black());
	player.AddImage("runningR.png", "walkright", 4, 1, 0, 0, 3, 0, CColor::Black());
	player.AddImage("standingL.png", "standleft", 4, 1, 3, 0, 0, 0, CColor::Black());
	player.AddImage("runningL.png", "walkleft", 4, 1, 3, 0, 0, 0, CColor::Black());
	player.AddImage("firstAttackR.png", "firstattackright", 5, 1, 0, 0, 4, 0, CColor::Black());
	player.AddImage("firstAttackL.png", "firstattackleft", 5, 1, 4, 0, 0, 0, CColor::Black());
	player.AddImage("secondAttackR.png", "secondattackright", 5, 1, 0, 0, 4, 0, CColor::Black());
	player.AddImage("secondAttackL.png", "secondattackleft", 5, 1, 4, 0, 0, 0, CColor::Black());
	player.AddImage("death.png", "dying", 3, 1, 0, 0, 2, 0, CColor::Black());

	player.LoadImage("block.png", "block");

	player.LoadImage("death.png", "death",3, 1, 2, 0, CColor::Black());

	player.SetImage("standright");
	player.SetStatus(2);

	hitbox.LoadImage("hitbox.png", "hitbox", CColor::Black());

	hpPotion.LoadImage("hp.png", "hp", CColor::Black());

	strengthPotion.LoadImage("strength.png", "strength", CColor::Black());

	bmusic.Play("sao music.wav",-1);
}

// called when a new game is requested (e.g. when F2 pressed)
// use this function to prepare a menu or a welcome screen
void CMyGame::OnDisplayMenu()
{
	level = 1;
}


void CMyGame::SetupLevel1()
{


	samurai.LoadImage("zorostand.png", "zorostand", CColor::Black());
	samurai.SetImage("zorostand");
	samurai.SetHealth(zorohealth);
	samurai.SetPosition(2100, 100);

	doorToLvl2.LoadImage("doorToLvL2.png", "door1");
	doorToLvl2.SetImage("door1");
	doorToLvl2.SetPosition(2440, 100);

	caveLine.LoadImage("caveLine.png", "caveline1");
	caveLine.SetImage("caveline1");
	caveLine.SetPosition(1780, 100);

	tower1.LoadImageW("tower1.png", "tower1");
	tower1.SetImage("tower1");
	tower1.SetHealth(tower1health);
	tower1.SetPosition(100, 135);


}

// setting up a level 
void CMyGame::SetupLevel2()
{
	background.LoadImage("forest.png", "map2", CColor::Black());
	background.SetImage("map2"); background.SetPosition(1200, 285);

	doorToLvl3.LoadImage("doorToLvL3.png", "door2", CColor::Black());
	doorToLvl3.SetImage("door2");
	doorToLvl3.SetPosition(2440,100);

	player.SetPosition(300, 100);
	player.SetMotion(0, 0);
	player.SetImage("standright");
	player.SetStatus(2);

	tree.LoadImage("tree.png", "treestand", CColor::White());
	tree.AddImage("tree.png", "treestand", 4, 1, 0, 0, 3, 0, CColor::White());
	tree.SetAnimation("treestand", 5);
	tree.SetPosition(2100, 105);
	tree.SetHealth(treehealth);

	tower2.LoadImageW("tower2.png", "tower2");
	tower2.SetImage("tower2");
	tower2.SetHealth(tower2health);
	tower2.SetPosition(100, 135);
}

void CMyGame::SetupLevel3()
{
	background.LoadImage("hell.png", "map3", CColor::Black());
	background.SetImage("map3"); background.SetPosition(1200, 250);

	hellLine.LoadImage("hellLine.png", "hellline1");
	hellLine.SetImage("hellline1");
	hellLine.SetPosition(1000, 150);

	hellLine1.LoadImage("hellLine.png", "hellline1");
	hellLine1.SetImage("hellline1");
	hellLine1.SetPosition(1900, 150);

	player.SetPosition(300, 100);
	player.SetMotion(0, 0);
	player.SetImage("standright");
	player.SetStatus(2);

	magician.LoadImage("magicianStand.png", "magicianstand", CColor::White());
	magician.AddImage("magicAttack.png", "magicattack", 3, 1, 0, 0, 2, 0, CColor::White());
	magician.SetImage("magicianstand");
	magician.SetHealth(magicianhealth);
	magician.SetPosition(1350, 100);

	chest.LoadImage("chest.png", "chestclosed",10,1,0,0, CColor::Black());
	chest.AddImage("chest.png", "chestopen", 10,1, 0, 0, 9, 0, CColor::Black());
	chest.SetImage("chestclosed");
	chest.SetPosition(2100, 80);
}

void CMyGame::isFirstLvl()
{
	if (whatlvl == 1)
	{
		if (player.HitTest(&doorToLvl2))
		{
			whatlvl = 2;
		}
	}
}

void CMyGame::isSecondLvl()
{
	if (whatlvl == 2)
	{
		if (player.HitTest(&doorToLvl3))
		{
			whatlvl = 3;
		}
	}
}

// called when a new game is started
// as a second phase after a menu or a welcome screen
void CMyGame::OnStartGame()
{
	score = 0;

	firstSwingList.delete_all();
	secondSwingList.delete_all();

	mobDeathList.delete_all();

	skeletonspawnList.delete_all();
	skeletonAttackList.delete_all();

	spiderspawnList.delete_all();
	spiderAttackList.delete_all();

	magicList.delete_all();

	skeletonSwingList.delete_all();

    player.SetPosition(300, 100);
	player.SetMotion(0, 0);
	player.SetImage("standright");
	player.SetStatus(2);

	if (level == 1)
	{
		whatlvl = 1;
		SetupLevel1();
	}
	if (level == 2)
	{
		whatlvl = 2;
		SetupLevel2();
		doorToLvl2.SetPosition(-100000, -10000000);
		caveLine.SetPosition(-100000, -10000000);
		hellLine1.SetPosition(-100000, -10000000);
		hellLine.SetPosition(-100000000, -100000000);
		magician.SetPosition(-100000000, -100000000);
	}
	if (level == 3)
	{
		whatlvl = 3;
		SetupLevel3();
		doorToLvl2.SetPosition(-100000, -10000000);
		caveLine.SetPosition(-100000, -10000000);

		doorToLvl3.SetPosition(-100000, -10000000);
		spider.SetPosition(-100000, -10000000);
		tree.SetPosition(-100000, -10000000);
	}
}

// called when a new level started - first call for nLevel = 1
void CMyGame::OnStartLevel(Sint16 nLevel)
{
}

// called when the game is over
void CMyGame::OnGameOver()
{
}

// one time termination code
void CMyGame::OnTerminate()
{
}

/////////////////////////////////////////////////////
// Keyboard Event Handlers

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	if (sym == SDLK_F2)
	{
		NewGame();

		firstSwingList.delete_all();
		secondSwingList.delete_all();

		mobDeathList.delete_all();

		skeletonspawnList.delete_all();
		skeletonAttackList.delete_all();

		spiderspawnList.delete_all();
		spiderAttackList.delete_all();

		magicList.delete_all();

		skeletonSwingList.delete_all();
	}
		
	if (sym == SDLK_F1)
		StartGame();

	if (IsMenuMode())
	{
		if (sym == SDLK_1)
		{
			level = 1;
			StartGame();
		}
		else if (sym == SDLK_2)
		{
			level = 2;
			StartGame();
		}
		else if (sym == SDLK_3)
		{
			level = 3;
			StartGame();
		}
	}
	
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
}


/////////////////////////////////////////////////////
// Mouse Events Handlers

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{
	if (player.GetStatus() == STANDRIGHT)
	{
		if (swingcounter == 0)
		{
			player.SetAnimation("firstattackright", 10);

			CSprite* swing = new CSprite(player.GetX() + 20, player.GetY(), "swingR.png", CColor::White(), GetTime());
			swing->SetDirection(90);
			swing->SetSpeed(300);
			swing->Die(600);
			firstSwingList.push_back(swing);

			swinging.Play("slash.wav");

			swingcounter = 30;
		}
	}

	firstSwingList.delete_if(deleted);

	if (player.GetStatus() == STANDLEFT)
	{
		if (swingcounter == 0)
		{
			player.SetAnimation("firstattackleft", 10);

			CSprite* swing = new CSprite(player.GetX() - 20, player.GetY(), "swingL.png", CColor::White(), GetTime());
			swing->SetDirection(270);
			swing->SetSpeed(300);
			swing->Die(600);
			firstSwingList.push_back(swing);

			swinging.Play("slash.wav");

			swingcounter = 30;
		}
	}
	
	firstSwingList.delete_if(deleted);
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
	
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{

	if (player.GetStatus() == STANDRIGHT)
	{

		if (swingcounter == 0)
		{ 
			player.SetAnimation("secondattackright", 10);

			CSprite* swing1 = new CSprite(player.GetX() + 20, player.GetY() - 10, "sword thrustR.png", CColor::White(), GetTime());
			swing1->SetDirection(90);
			swing1->SetSpeed(300);
			swing1->Die(500);
			secondSwingList.push_back(swing1);

			swinging.Play("slash.wav");

			swingcounter = 30;
		}
		
	}
	secondSwingList.delete_if(deleted);

	if (player.GetStatus() == STANDLEFT)
	{

		if (swingcounter == 0)
		{
			player.SetAnimation("secondattackleft", 10);

			CSprite* swing1 = new CSprite(player.GetX() - 20, player.GetY() - 10, "sword thrustL.png", CColor::White(), GetTime());
			swing1->SetDirection(270);
			swing1->SetSpeed(300);
			swing1->Die(500);
			secondSwingList.push_back(swing1);

			swinging.Play("slash.wav");

			swingcounter = 30;
		}
	}

	secondSwingList.delete_if(deleted);
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}
