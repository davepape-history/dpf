#include <Performer/pf/pfTraverser.h>
#include "dpfSpriteGroup.h"

static int sgPreDraw(pfTraverser *trav,void *);
static int sgPostDraw(pfTraverser *trav,void *);

pfType *dpfSpriteGroup::classType_ = NULL; 

void dpfSpriteGroup::init(void)
{
 if (classType_ == NULL)
	{
        pfGroup::init();
        classType_ =  new pfType(pfGroup::getClassType(), "dpfSpriteGroup");
	}
}

dpfSpriteGroup::dpfSpriteGroup(void)
{
 setType(classType_);  // set the Performer type of this instance
 sprite_ = new pfSprite;
 setTravFuncs(PFTRAV_DRAW,sgPreDraw,sgPostDraw);
}

static int sgPreDraw(pfTraverser *trav,void *)
{
 dpfSpriteGroup *sg = (dpfSpriteGroup *)trav->getNode();
 sg->sprite()->begin();
 return PFTRAV_CONT;
}

static int sgPostDraw(pfTraverser *trav,void *)
{
 dpfSpriteGroup *sg = (dpfSpriteGroup *)trav->getNode();
 sg->sprite()->end();
 return PFTRAV_CONT;
}

