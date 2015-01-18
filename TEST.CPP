// This code tests the thing
#define __MAIN__

// PM includes
#define INCL_PM
#define INCL_WIN
#include <os2.h>

// Functional includes
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

#include "elistbox.hpp"

// include dialog headers
#include "dialog.h"



//  Test data
#include "t.tab"                      // a table with a long and char*
double dbl[70];


TextPtrColumn  Col( "Who", 2,35,&names[0].name,sizeof( _ARR) );
TextPtrColumn  nCol( "Who", 10,45,&names[6].name ,sizeof (struct _ARR ));
LongColumn  Lcol( "Amount", 37,46, &names[0].l, sizeof (struct _ARR) );
LongColumn  nLcol( "Amount", 2,9, ( long * )&names[0].l, sizeof (struct _ARR) );
MoneyColumn mon("Amount",37,50, dbl, sizeof( double ));
Column *C[]={&Col,&mon,( Column * )NULL};
Column *Cc[]={&nLcol,&nCol,( Column * )NULL};
Row R( C, 40 );
Row R2( Cc, 60 );
//***

STDPROC( MAIN_WINDOWProc );
int  main(void)
{
 HAB hAB;
 HMQ hMQ;
 for( int i=0; i<70; i++ ) names[i].l=i*(1-2*(i%2));
 for( i=0; i<70; i++ ) dbl[i]=i*.5*(1-2*(i%2));
 hAB = WinInitialize(0L);
 if(hAB == 0) return(FALSE);
 hMQ=WinCreateMsgQueue(hAB, 0L);
 if(hMQ == 0)	return(FALSE);
 HWND wnd=WinLoadDlg(
		HWND_DESKTOP,
		HWND_DESKTOP,
		( PFNWP )MAIN_WINDOWProc,
		NULLHANDLE,
		D2 ,
		NULL
	       );

 WinProcessDlg( wnd );
 WinDestroyWindow( wnd );
 WinDestroyMsgQueue(hMQ);
 WinTerminate(hAB);
 return 1;
}

long ssel;
char vect[100]; 		      // multiselect vector

MRESULT EXPENTRY MAIN_WINDOWProc( STDPARMS )
{
 static char d[50];
 static int i;
 static double ddd=0;
 switch( MSG )
   {
    case  WM_INITDLG:
      WinCreateELB( Wnd, ELB, R, ssel, vect );
      break;
    case ELB_CHANGESEL:
      {
       char t[30];
       long l=( long )mp2;
       if( !(l%10) ) dbl[l]=ddd;
       ddd+=dbl[l]*( vect[l] ? 1 : -1 );
       sprintf( t, "%8.2f", ddd );
       WinSetDlgItemText( Wnd, EF, t );
      }
      break;
    case  WM_CONTROL:		      // strong visual que of reinit!!
if( ( ULONG )mp1==ELB )
  {
   ssel=i%3*9;
   WinCreateELB( Wnd, ELB, i++%2 ? R : R2, ssel, i%2 ? vect : (char*)NULL );
  }
    case  WM_COMMAND:
    case  WM_SYSCOMMAND:
    break;
   }
 return( WinDefDlgProc( Wnd, MSG, mp1, mp2) );
}


