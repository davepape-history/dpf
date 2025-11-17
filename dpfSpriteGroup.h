#ifndef _dpfSpriteGroup_h_
#define _dpfSpriteGroup_h_

#include <Performer/pf/pfGroup.h>
#include <Performer/pr/pfSprite.h>

class dpfSpriteGroup : public pfGroup
	{
	public:
	 dpfSpriteGroup(void);
	 virtual inline pfSprite * sprite(void) { return sprite_; }
	private:
	 pfSprite * sprite_;
	/* Stuff required to make this a Performer class */
	public:
	 static void init(void);
	 static pfType* getClassType(void){ return classType_; };
	private:
	 static pfType* classType_;
	};

#endif
