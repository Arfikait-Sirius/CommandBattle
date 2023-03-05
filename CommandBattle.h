#ifndef _S_STARS_
#define _S_STARS_


#define MAX_LINE 8
#define NUM_OF_ACTION 4


typedef struct player_def{
     string name ;
     string action ;
     bool partyFlg ;
     int rate ;
     int skills[5] ;
}Player ;

typedef struct target_def{
     string name ;
     string mp ;
     int maxLp ;
     int maxFp ;
     int guard ;
     string criteria ;
}Target ;


// Special Functions
bool spPlay( string ) ;

bool spBattle( void ) ;
bool spBattleMain( void ) ;
Target spGetTargetInfo( string ) ;
int spDispSkill( int[] ) ;
bool spBattleAction( Player, Target, string ) ;
int spCalcLp( Player, Target ) ;
int spCalcFp( Player, Target ) ;

bool spUseItem( void ) ;

bool spCheckStatus( void ) ;
bool spStatusMain( void ) ;

Player spLoadPlayerProfile( void ) ;

void spError( string ) ;

void spNextLine( int ) ;
void spBackLine( int ) ;
void spClearLine( void ) ;
void spClearBackLine( int ) ;

void spDispAnimationClear( void ) ;
void spDispAnimationLine( char ) ;
void spDispAnimationRandom( char ) ;

#endif
