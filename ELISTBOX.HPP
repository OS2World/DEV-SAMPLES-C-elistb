// $Header: h:/include/RCS/elistbox.hpp 1.3 93/06/02 16:01:17 Steve Exp $

//NOTE:  This code is UNSUPPORTED!  Mail will not be answered unless you are
//	 a "registered contributor".   Ypu can become a registered contributor
//	 by submitting a real bug (preferably with a fix) or a useful extension.
//
//	 The author, for want of a more rational judge :-), will decide which
//	 bugs and extensions qualify.
//
//	 After reading this message DO NOT DELETE IT, rather "comment it out" so
//	 that any line references will be consistent.

//  (C) Copyright Stephen B. Behman, 1993 -- All Rights Reserved
//  You may modify and extend it but you may NOT SELL derivative works without
//  the author's permission.
//  It is not intended that this code be put into the Public Domain NOW,
//  when the code is finished it will be.


#ifndef __EXTENDED_LISTBOX__
#define __EXTENDED_LISTBOX__
#ifndef __OS2_H__

// PM includes
#define INCL_PM
#define INCL_WIN
#include <os2.h>
#endif

#ifndef ___SBB___
#include <common.h>
#endif
#ifndef __stdlib_h
#include <stdlib.h>
#endif

#define NULLCOL ( Column* )0

class Column
  {
   protected:
   char *head;
   int startpos;
   int width;
   char *ptr;
   int offset;
   long justify;
   public:
   inline Column(char * h, int s, int w , char *p, int o=0, long j=DT_LEFT )
	   { head=h; startpos=s; width=w; ptr=p; offset=o; justify=j;}
   void  drawheading( HPS ps, const RECTL& r )
     {
      RECTL t;
      t.xLeft=r.xLeft+startpos*SysCharWidth;
      t.xRight=r.xLeft+width*SysCharWidth;
      t.yTop=r.yTop;
      t.yBottom=r.yBottom;
      WinDrawText( ps, -1, head, &t, SYSCLR_HELPTEXT , SYSCLR_ENTRYFIELD,
		   DT_CENTER | DT_TOP | DT_UNDERSCORE );
      POINTL p;
      p.x=t.xRight+SysCharWidth/2;
      p.y=t.yTop;
      GpiMove( ps, &p );
      p.y=t.yBottom;
      GpiLine( ps, &p );
     }
   virtual void draw( HPS ps, int ndx, const RECTL& r, int sel=0 )=0;
   void setptr( char* p ){ ptr=p;}
  };

class TextColumn : public Column
  {
   public:
    inline TextColumn( char * h, int s, int w, char *tt, int i=4, long j=DT_LEFT )
     : Column( h, s, w, tt, i, j ){}
    void draw( HPS ps, int ndx, const RECTL& r, int sel=0 )
      {
       RECTL t;
       t.yTop=r.yTop;
       t.yBottom=r.yBottom;
       t.xLeft=r.xLeft+startpos*SysCharWidth;
       t.xRight=r.xLeft+width*SysCharWidth;
       char * tch=ptr+ndx*offset;
       WinDrawText( ps, -1, tch, &t, CLR_BLACK,
		    sel ? CLR_PALEGRAY : SYSCLR_ENTRYFIELD,
		    justify | DT_VCENTER );
       POINTL p;
       p.x=t.xRight+SysCharWidth/2;
       p.y=t.yTop;
       GpiMove( ps, &p );
       p.y=t.yBottom;
       GpiLine( ps, &p );
      }
  };

class CharColumn : public Column
  {
   public:
    inline CharColumn( char * h, int s, int w, char *tt, int i=1,
		       long j=DT_CENTER ) : Column( h, s, w, tt, i, j ){}
    void draw( HPS ps, int ndx, const RECTL& r, int sel=0 )
      {
       RECTL t;
       t.yTop=r.yTop;
       t.yBottom=r.yBottom;
       t.xLeft=r.xLeft+startpos*SysCharWidth;
       t.xRight=r.xLeft+width*SysCharWidth;
       char * tch=ptr+ndx*offset;
       WinDrawText( ps, 1, tch, &t, CLR_BLACK,
		    sel ? CLR_PALEGRAY : SYSCLR_ENTRYFIELD,
		    justify | DT_VCENTER );
       POINTL p;
       p.x=t.xRight+SysCharWidth/2;
       p.y=t.yTop;
       GpiMove( ps, &p );
       p.y=t.yBottom;
       GpiLine( ps, &p );
      }
  };

class TextPtrColumn : public Column
  {
   public:
    inline TextPtrColumn( char * h, int s, int w, char **tt, int i=4, long j=DT_LEFT )
     : Column( h, s, w, ( char*)tt, i, j ){}
    void draw( HPS ps, int ndx, const RECTL& r, int sel=0 )
      {
       RECTL t;
       t.yTop=r.yTop;
       t.yBottom=r.yBottom;
       t.xLeft=r.xLeft+startpos*SysCharWidth;
       t.xRight=r.xLeft+width*SysCharWidth;
       char * tch=*( char** )(ptr+ndx*offset);
       WinDrawText( ps, -1, tch, &t, CLR_BLACK,
		    sel ? CLR_PALEGRAY : SYSCLR_ENTRYFIELD,
		    justify | DT_VCENTER );
       POINTL p;
       p.x=t.xRight+SysCharWidth/2;
       p.y=t.yTop;
       GpiMove( ps, &p );
       p.y=t.yBottom;
       GpiLine( ps, &p );
      }
  };

class LongColumn : public Column
  {
  public:

   LongColumn( char * h, int s, int w, long *tt, int i=4, long j=DT_RIGHT )
	      : Column( h, s, w, ( char * )tt, i, j ){}
   void draw( HPS ps, int ndx, const RECTL& r, int sel=0 )
     {
      char tmp[30];
      RECTL t;
      t.yTop=r.yTop;
      t.yBottom=r.yBottom;
      t.xLeft=r.xLeft+startpos*SysCharWidth;
      t.xRight=r.xLeft+width*SysCharWidth;
      long  tch=*( long* )(ptr+ndx*offset);
      ltoa( tch, tmp, 10 );
      WinDrawText( ps, -1, tmp, &t, ( tch<0 ) ? CLR_RED : CLR_BLACK,
		   sel ? CLR_PALEGRAY : SYSCLR_ENTRYFIELD,
		   justify | DT_VCENTER );
      POINTL p;
      p.x=t.xRight+SysCharWidth/2;
      p.y=t.yTop;
      GpiMove( ps, &p );
      p.y=t.yBottom;
      GpiLine( ps, &p );
     }
  };

class MoneyColumn: public Column
  {
  public:
    MoneyColumn( char * h, int s, int w, double *tt, int i=4, long j=DT_RIGHT )
    : Column( h, s, w, ( char * )tt, i, j ){}
   void draw( HPS ps, int ndx, const RECTL& r, int sel=0 )
     {
      int decimal;
      int sign;
      char prt[30];
      char *tmp=prt;
      RECTL t;
      t.yTop=r.yTop;
      t.yBottom=r.yBottom;
      t.xLeft=r.xLeft+startpos*SysCharWidth;
      t.xRight=r.xLeft+width*SysCharWidth;
      double  tch=*( double* )(ptr+ndx*offset);

      char *str=fcvt( tch, 2, &decimal, &sign );
      if( sign ) *(tmp++)='-';
      if( decimal>0 )
	 while( (decimal--)>0 ) *(tmp++)=*(str++);
      else *(tmp++)='0';
      *(tmp++)='.';
      *(tmp++)=decimal==0 ? *(str++) : '0';
      *(tmp++)=*(str++);
      *(tmp++)=0;
      WinDrawText( ps, -1, prt, &t, ( sign ) ? CLR_RED : CLR_BLACK,
		   sel ? CLR_PALEGRAY : SYSCLR_ENTRYFIELD,
		   justify | DT_VCENTER );
      POINTL p;
      p.x=t.xRight+SysCharWidth/2;
      p.y=t.yTop;
      GpiMove( ps, &p );
      p.y=t.yBottom;
      GpiLine( ps, &p );
     }
  };

class Row
  {
  public:
   Column **c;
   long cnt;
   inline Row( Column ** t , long i){c=t;cnt=i;}
   inline Row( Row *t ){c=t->c;cnt=t->cnt;}
   inline long count(  ){ return cnt;}
   inline void show( const HPS ps, const int ndx, const RECTL& r, int sel=0 )
     {
      for( int i=0; c[i]!=NULL; i++ ) c[i]->draw( ps, ndx, r, sel );
     }

   inline void drawheading( const HPS ps, const RECTL& r )
     {

      for( int i=0; c[i]!=NULL; i++ )
	c[i]->drawheading( ps, r );
     }

  };

STDPROC( ExtendedListBoxProc );
#define ELB_SELCHANGED WM_USER+1
#define ELB_SEARCH     WM_USER+2
#define ELB_DBLCLK     WM_USER+3
#define ELB_ENTER      VK_ENTER
#define WM_SETACTIVE   WM_USER+2
class ExtendedListBox
  {
   Row& row;
   long active;
   long rows;
   long top;
   HWND scrollbar;
   HWND parent;
   long style;
   long tot;
   long& selected;
   char *selvect;
   ULONG id;
   int scroll;
   int old;
  public:
   ExtendedListBox( HWND Wnd, ULONG i, Row& rr, long& l, char* cp ):
	row(rr),selected(l), selvect(cp)
     {				      // find scrollbar and initialize it
      tot=row.count();
      id=i;
      parent=WinQueryWindow( Wnd, QW_PARENT);
      top=selected=active=0;
      scroll=0;
      HWND hEnum=WinBeginEnumWindows( Wnd );
      do
	{				  // look for V scroll bar
	 scrollbar=WinGetNextWindow( hEnum );
	 if( scrollbar )
	   {
	    ULONG ulStyle=WinQueryWindowULong( scrollbar, QWL_STYLE );
	    if ( ulStyle & SBS_VERT ) break;
	   }
	}while ( scrollbar );
      WinEndEnumWindows( hEnum );
      FONTMETRICS fm;
      HPS ps=WinGetPS( HWND_DESKTOP );	  // Get handle to presentation space
      GpiQueryFontMetrics( ps, (LONG) sizeof( FONTMETRICS ), &fm );
      SysCharHeight=fm.lMaxBaselineExt;
      SysCharWidth=fm.lAveCharWidth;
      WinReleasePS(ps); 		  // Release the presentation space
      SWP w;
      WinQueryWindowPos( Wnd, &w );
      rows=min(tot, w.cy/SysCharHeight-1);
      WinSendMsg( scrollbar, SBM_SETSCROLLBAR, (MPARAM)0,
		  MPFROM2SHORT( 0, tot-1 ) );
      WinEnableWindow( scrollbar, tot>rows ? TRUE : FALSE );
     }
//***
   void paint( HWND Wnd, int outside=0 )
	{
	 SWP sb;
	 WinQueryWindowPos( scrollbar, &sb );
	 SWP s;
	 WinQueryWindowPos( Wnd, &s );
	 HPS hps;
	 RECTL	r;
	 RECTL	rp;
	 r.xLeft=s.x;
	 r.xRight=s.x+s.cx-sb.cx+1;
	 r.yBottom=s.y+1;
	 r.yTop=s.y+s.cy;
	 hps=WinGetPS( parent );
	 if( old<top || old>=top+rows ) outside=1;
	 if( outside )
	   WinDrawBorder( hps, &r, 1, 1, CLR_BLACK,
			  SYSCLR_ENTRYFIELD, DB_STANDARD|DB_INTERIOR );
	 row.drawheading( hps, r);
	 rp=r;
	 r.yBottom=r.yTop-SysCharHeight;
	 if( scroll )
	   {
	    rp.yTop-=SysCharHeight;
	    WinScrollWindow( parent, 0, SysCharHeight*scroll, &rp, &rp,
			     NULLHANDLE,( PRECTL )NULL,0 );
	    scroll=0;
	   }
	 for( int i=top; i < rows+top; i++)
	   {
	    r.yTop-=SysCharHeight;
	    r.yBottom-=SysCharHeight;
	    if( outside || i==old || i==active )
	      {
	       WinDrawBorder( hps, &r, 1, 0, CLR_BLACK,
			      SYSCLR_ENTRYFIELD, DB_STANDARD|DB_INTERIOR );
	       if( (!selvect && i==selected ) || (selvect && selvect[i] ) )
		 {
		  WinFillRect( hps, &r, CLR_PALEGRAY );
		  WinDrawBorder( hps, &r, 1,0, CLR_BLACK, CLR_PALEGRAY, 0 );
		  row.show( hps, i, r, 0);
		 }
	       else
		  row.show( hps, i, r, 0);
	       if( i==active )
		 {
		  GpiSetLineType( hps, LINETYPE_DOT );
		  POINTL p={r.xLeft,r.yBottom };
		  GpiMove( hps, &p );
		  p.x=r.xRight-1;
		  GpiLine( hps, &p );
		  p.y=r.yTop-1;
		  GpiMove( hps, &p );
		  p.x=r.xLeft;
		  GpiLine( hps, &p );
		  GpiSetLineType( hps, LINETYPE_DEFAULT );
		 }
	      }
	   }
	 WinReleasePS( hps );
	}

//***
   void setselect( HWND Wnd  )
     {
      if( !selvect ) selected=active;
      else
	{
	 selvect[active]=( char )(!selvect[active]);
	 WinPostMsg( Wnd, WM_CONTROL, MPFROM2SHORT( id, ELB_SELCHANGED ),
		     ( MPARAM )active );
	}
     }

//***
   void newactive( MPARAM mp2  )
     {
      old=active;
      switch( S2(mp2) )
	{
	 case SB_LINEUP:
	   active=max( active-1, 0 );
	   if( active<top )
	     {
	      top=active;
	      scroll=-1;
	     }
	   break;
	 case SB_LINEDOWN:
	   active=min( active+1, tot-1 );
	   if( active>top+rows-1 )
	     {
	      top=min( top+1, tot-rows );
	      scroll=1;
	     }
	   break;
	 case SB_PAGEUP:
	   active=max( top-1, 0 );
	   top=max( top-rows, 0 );
	   break;
	 case SB_PAGEDOWN:
	   active=min( top+rows, tot-1 );
	   top=min( top+rows, tot-rows );
	   break;
	 case SB_SLIDERPOSITION:
	 case SB_SLIDERTRACK:
	   active=S1(mp2);
	   if( active>top+rows-1 )top=min( active-rows+1, tot-rows );
	   else if( active<top ) top=active;
	   break;
	 case SB_ENDSCROLL:
	 break;
	}
      if( !selvect )selected=active;
      WinSendMsg( scrollbar, SBM_SETSCROLLBAR, (MPARAM)active,
		  MPFROM2SHORT( 0, tot-1 ) );
     }
   friend STDPROC( ExtendedListBoxProc );
  };


//***
void WinCreateELB( HWND Wnd, ULONG id, Row& rr, long& ll,
		   char* selp=( char * )NULL )
  {
   HWND elb= WinWindowFromID( Wnd, id );
   WinSubclassWindow( elb, ( PFNWP )ExtendedListBoxProc);
   ExtendedListBox * telb=( ExtendedListBox * )WinQueryWindowULong( elb, QWL_USER );
   if( telb ) delete telb;
   ExtendedListBox *t=new ExtendedListBox( elb, id, rr, ll, selp );
   WinSendMsg( elb, WM_CREATE, ( MPARAM )t, 0 );
//   WinSendMsg( elb, WM_PAINT, 0, 0 );
  }


STDPROC( ExtendedListBoxProc )
  {
   if( MSG == WM_CREATE )
	{
	 WinSetWindowULong( Wnd, QWL_USER, ( ULONG )mp1 );
	 returnF;
	}
   ExtendedListBox *t=( ExtendedListBox* )WinQueryWindowULong( Wnd, QWL_USER );
   HWND owner=WinQueryWindow( Wnd, QW_OWNER );
   switch( MSG )
     {
      case WM_BUTTON1CLICK:
	{
	 int k=S2(mp1),j=0;
	 SWP s;
	 WinQueryWindowPos( Wnd, &s );
	 for( long i=s.cy-2*SysCharHeight; i>0; i-=SysCharHeight, j++ )
	   if( k > i ) break;
	 t->newactive( MPFROM2SHORT( t->top+j, SB_SLIDERPOSITION ) );
	 t->setselect( owner );
	 t->paint( Wnd );
	 returnT;
	}
//***
      case WM_SETACTIVE:
	  t->newactive( MPFROM2SHORT( S1( mp1 ), SB_SLIDERPOSITION )  );
	  t->paint( Wnd, 1 );
	  returnT;
      case WM_BUTTON1DBLCLK:
	WinPostMsg( owner, WM_CONTROL, MPFROM2SHORT( t->id, ELB_DBLCLK ),
		    ( MPARAM )t->active );
	returnT;
      case WM_SETFOCUS:
	WinFocusChange( HWND_DESKTOP, t->scrollbar, FC_NOLOSEFOCUS );
	returnT;
      case WM_DESTROY:
	delete t;
	break;
//***
      case WM_CHAR:
	{
	 long flags=S1( mp1 );
	 if( flags & KC_CHAR && !( flags & ( KC_KEYUP | KC_VIRTUALKEY ) ) )
	   {
	    WinPostMsg( owner, WM_CONTROL, MPFROM2SHORT( t->id, ELB_SEARCH ),
			MPFROM2SHORT( t->active, S1( mp2 ) ) );
	    returnT;
	   }

	 if( flags & KC_VIRTUALKEY && !( flags & KC_KEYUP ) )
	   {
	    switch( S2( mp2 ) )
	      {
		case VK_UP:
		  t->newactive( MPFROM2SHORT(0, SB_LINEUP) );
		  break;
		case VK_DOWN:
		  t->newactive( MPFROM2SHORT( 0, SB_LINEDOWN ) );
		  break;
		case VK_PAGEUP:
		  t->newactive( MPFROM2SHORT( 0, SB_PAGEUP ) );
		  break;
		case VK_PAGEDOWN:
		  t->newactive( MPFROM2SHORT( 0, SB_PAGEDOWN ) );
		  break;
		case VK_END:
		  t->newactive( MPFROM2SHORT( t->tot-1, SB_SLIDERPOSITION ) );
		  t->paint( Wnd, 1 );
		  returnT;
		case VK_HOME:
		  t->newactive( MPFROM2SHORT( 0, SB_SLIDERPOSITION )  );
		  t->paint( Wnd, 1 );
		  returnT;
		case VK_SPACE:
		  t->setselect( owner );
		  break;
		case VK_ENTER:
		case VK_NEWLINE:
		  WinPostMsg( owner , WM_CONTROL, MPFROM2SHORT(t->id,ELB_ENTER),
			      ( MPARAM )t->active );
		  returnT;
		case VK_TAB:
		case VK_BACKTAB:
		  returnDWP;
		default:
		  returnF;
	      }
	    t->paint( Wnd );
	    returnT;
	   }
	 returnT;
	}

      case WM_VSCROLL:
	t->newactive( mp2 );
	t->paint( Wnd );
	break;
      case WM_PAINT:
	t->paint( Wnd, 1 );
     }
   returnDWP;
  }

#endif
