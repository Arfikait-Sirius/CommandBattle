#include "Sisters.h"

#include "CommandBattle.h"
#include "GameMessage.h"


// Call Sisters
void callSisters( void ){

     Emily = callEmily() ;
     Louise = callLouise() ;
     Veera = callVeera() ;
     Dorothy = callDorothy() ;
     Sylvia = callSylvia() ;

     return ;
}

// Game Loop
int main( void ){
     callSisters() ;

     string cmd ;
     bool result ;

     Emily.fnDispLine( MSG_MENU_CMD_PANE ) ;
     cmd = Emily.fnGetLine( MSG_INPUT_LABEL ) ;
     result = spPlay( cmd ) ;
     while( result ){
          Emily.fnDispLine( MSG_MENU_CMD_PANE ) ;
          cmd = Emily.fnGetLine( MSG_INPUT_LABEL ) ;
          result = spPlay( cmd ) ;
     }

     return CHAO ;
}

// Dispatch Command
bool spPlay( string cmd ){
     bool result ;

     string lowerCmd ;

     lowerCmd = Louise.fnLowerAll( cmd ) ;

     if( Louise.isEqual( lowerCmd, "end" ) || Louise.isEqual( lowerCmd, "e" ) ){
          spClearBackLine( 2 ) ;
          Emily.fnDispLine( MSG_GAME_OVER ) ;
          Emily.fnDispLine( MSG_GAME_END ) ;
          result = false ;
     } else if( Louise.isEqual( lowerCmd, "battle" ) || Louise.isEqual( lowerCmd, "b" ) ){
          result = spBattle() ;
     } else if( Louise.isEqual( lowerCmd, "item" ) || Louise.isEqual( lowerCmd, "i" ) ){
          result = spUseItem() ;
     } else if( Louise.isEqual( lowerCmd, "status" ) || Louise.isEqual( lowerCmd, "s" ) ){
          result = spCheckStatus() ;
     } else {
          spError( MSG_ERR_CMD ) ;
          spClearBackLine( 3 ) ;
          result = true ;
     }

     return result ;
}

bool spBattle( void ){
     bool continueFlag ;

     spBackLine( 2 ) ;
     spDispAnimationRandom( 'B' ) ;
     spDispAnimationClear() ;
     continueFlag = spBattleMain() ;
     spBackLine( MAX_LINE ) ;
     spDispAnimationLine( 'B' ) ;
     spDispAnimationClear() ;

     return continueFlag ;
}

bool spBattleMain( void ){
     bool result ;
     int i ;
     int srcf ;
     string s ;
     string info ;
     string tmp ;
     Player player ;
     Target target ;

     Emily.fnDispLine( "[ バトル ]" ) ;

     player = spLoadPlayerProfile() ;

     player.partyFlg = true ;
     if( player.partyFlg ){
          player.rate = spDispSkill( player.skills ) ;
     } else {
          player.rate = 1 ;
     }

     srcf = Dorothy.fnOpen( "./resources/data.res" ) ;
     if( Dorothy.isError( srcf ) ){
          return false ;
     }
     s = Dorothy.fnReadLine( srcf ) ;
     info = Louise.fnFix( s ) ;
     Dorothy.fnClose( srcf ) ;

     target = spGetTargetInfo( info ) ;

     Emily.fnDispLineCustom( "相手: ", target.name, NULL ) ;
     Emily.fnDispLineCustom( "魔力: ", target.mp, NULL ) ;
     tmp = Louise.fnGetSubstring( "MG=%s+", info ) ;
     if( !Louise.isEmpty( tmp ) ){
          Emily.fnDispLine( tmp ) ;
     } else {
          Emily.fnNewLine() ;
     }
     spNextLine( 2 ) ;
     Emily.fnGetLine( MSG_BATTLE_START ) ;
     for( i = 0 ; i < 3 ; i++ ){
          result = spBattleAction( player, target, info ) ;
          if( result ){
               break ;
          }
     }

     return true ;
}

int spDispSkill( int skills[] ){
     int result = 1 ;

     return result ;
}

Target spGetTargetInfo( string info ){
     Target target ;
     string tmp ;
     string point ;

     tmp = Louise.fnGetSubstring( info, "N=%s+" ) ;
     target.name = Louise.fnFix( tmp ) ;

     tmp = Louise.fnGetSubstring( info, "A=%s+" ) ;
     target.mp = Louise.fnFix( tmp ) ;

     tmp = Louise.fnGetSubstring( info, "C=%s+" ) ;
     target.criteria = Louise.fnFix( tmp ) ;

     tmp = Louise.fnGetSubstring( info, "L=%s+" ) ;
     point = Louise.fnFix( tmp ) ;
     target.maxLp = Sylvia.fnStrToNum( point ) ;

     tmp = Louise.fnGetSubstring( info, "F=%s+" ) ;
     point = Louise.fnFix( tmp ) ;
     target.maxFp = Sylvia.fnStrToNum( point ) ;

     return target ;
}

bool spBattleAction( Player player, Target target, string info ){
     string tmp ;
     string format ;
     char actionMsg[80] ;
     int lp ;
     int fp ;
     int selectedAction ;

     static string actionList[NUM_OF_ACTION] = INIT_ACTION ;

     spClearBackLine( 5 ) ;
     tmp = Louise.fnGetSubstring( info, "MN=%s+" ) ;
     Emily.fnDispLineCustom( "「", tmp, "」" ) ;
     Emily.fnDispLine( MSG_LONG_LINE ) ;
     Emily.fnDispLine( MSG_BATTLE_CMD_PANE ) ;
     Emily.fnDispLine( MSG_LONG_LINE ) ;
     tmp = Emily.fnGetLine( MSG_INPUT_LABEL ) ;
     selectedAction = Sylvia.fnStrToNum( tmp ) ;
     if( 0 < selectedAction && selectedAction < 5 ){
          player.action = actionList[selectedAction - 1] ;
     } else {
          player.action = ACTION_ERROR ;
     }
     spBackLine( 5 ) ;
     spClearLine() ;
     spNextLine( 3 ) ;
     spClearLine() ;
     sprintf( actionMsg, "%s%s%s", player.name, player.action, MSG_SYS_WAIT_ANY_KEY ) ;
     Emily.fnGetLine( actionMsg ) ;
     lp = spCalcLp( player, target ) ;
     fp = spCalcFp( player, target ) ;
     if( ( target.maxLp < lp || lp == 0 ) && ( target.maxFp < fp || fp == 0 ) ){
          return true ;
     }

     return false ;
}

int spCalcLp( Player player, Target target ){
     int lp = 1 ;

     return lp ;
}

int spCalcFp( Player player, Target target ){
     int fp = 1 ;

     return fp ;
}

bool spUseItem( void ){

     spBackLine( 2 ) ;
     spDispAnimationRandom( 'I' ) ;
     spDispAnimationClear() ;

     Emily.fnDispLine( "[ アイテム ]" ) ;

     Emily.fnDispStr( "アイテムを使用した！" ) ;
     Emily.fnGetLine( MSG_SYS_WAIT_ANY_KEY ) ;
     
     spBackLine( 2 ) ;
     spDispAnimationLine( 'I' ) ;
     spDispAnimationClear() ;

     return true ;
}

bool spCheckStatus( void ){
     bool continueFlag ;

     spBackLine( 2 ) ;
     spDispAnimationRandom( 'S' ) ;
     spDispAnimationClear() ;

     continueFlag = spStatusMain() ;

     sleep( 1 ) ;

     spBackLine( MAX_LINE ) ;
     spDispAnimationLine( 'S' ) ;
     spDispAnimationClear() ;

     return continueFlag ;
}

bool spStatusMain( void ){

     Emily.fnDispLine( "[ ステータス ]" ) ;

     Emily.fnNewLine() ;
     Emily.fnNewLine() ;
     Emily.fnNewLine() ;
     Emily.fnNewLine() ;
     Emily.fnNewLine() ;
     Emily.fnNewLine() ;
     Emily.fnNewLine() ;

     return true ;
}


Player spLoadPlayerProfile(){
     Player player ;

     player.name = "あなた" ;

     return player ;
}


void spError( string msg ){

     Emily.fnDispStrCustom( "[ エラー ]: ", msg, MSG_SYS_WAIT_ANY_KEY ) ;
     Emily.fnGetLine( NULL ) ;

     return ;
}


// ===== Line Controls ===== //

void spNextLine( int num ){
     int i ;

     printf( "\n" ) ;
     for( i = 0 ; i < num ; i++ ){
          printf( "\n" ) ;
     }

     return ;
}

void spBackLine( int num ){
     int i ;

     printf( "\n" ) ;
     for( i = 0 ; i < num + 1 ; i++ ){
          printf( "\x1B[1A" ) ;
     }

     return ;
}

void spClearLine( void ){

     printf( "\x1B[0K" ) ;

     return ;
}

void spClearBackLine( int num ){
     int i ;

     printf( "\n" ) ;
     for( i = 0 ; i < num + 1 ; i++ ){
          printf( "\x1B[1A" ) ;
          printf( "\x1B[0K" ) ;
     }

     return ;
}


// ===== Animations ===== //

void spDispAnimationClear( void ){
     spDispAnimationLine( SPACE ) ;

     return ;
}

void spDispAnimationLine( char c ){
     int i ;
     int j ;
     char zero[100 + 1] ;

     for( i = 0 ; i < 8 ; i++ ){
          printf( "\n" ) ;
          for( j = 0 ; j < 100 ; j++ ){
               printf( "\x1B[1A" ) ;
               printf( "\x1B[0K" ) ;
               zero[j] = c ;
               zero[j + 1] = NL ;
               printf( "%s\n", zero ) ;
               usleep( 500 ) ;
          }
     }
     for( i = 0 ; i < 8 ; i++ ){
          printf( "\x1B[1A" ) ;
     }

     return ;
}

void spDispAnimationRandom( char c ){
     int i ;
     int j ;
     int num ;
     char zero[800 + 1] ;
     int line ;
     bool tmpFlag = false ;

     Veera.fnInit() ;

     for( i = 0 ; i < 800 ; i++ ){
          zero[i] = SPACE ;
     }
     for( i = 0 ; i < 800 ; i++ ){
          num = Veera.fnRandom( 800 ) ;
          while( zero[num] != SPACE ){
               num = Veera.fnRandom( 800 ) ;
          }
          if( num < 100 ){
               line = 100 ;
          } else if( 100 <= num && num < 200 ){
               line = 200 ;
          } else if( 200 <= num && num < 300 ){
               line = 300 ;
          } else if( 300 <= num && num < 400 ){
               line = 400 ;
          } else if( 400 <= num && num < 500 ){
               line = 500 ;
          } else if( 500 <= num && num < 600 ){
               line = 600 ;
          } else if( 600 <= num && num < 700 ){
               line = 700 ;
          } else if( 700 <= num && num < 800 ){
               line = 800 ;
          }
          if( zero[line] != SPACE ){
               tmpFlag = true ;
          }
          zero[line] = NL ;
          zero[num] = c ;
          for( j = 1 ; j < ( line / 100 ) ; j++ ){
               printf( "\n" ) ;
          }
          printf( "\x1B[0K" ) ;
          printf( "%s\n", &zero[line - 100] ) ;
          usleep( 500 ) ;
          for( j = 0 ; j < ( line / 100 ) + 1 ; j++ ){
               printf( "\x1B[1A" ) ;
          }
          printf( "\n" ) ;
          if( tmpFlag ){
               tmpFlag = false ;
               zero[line] = c ;
          } else {
               zero[line] = SPACE ;
          }
     }

     return ;
}
