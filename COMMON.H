#ifndef ___SBB___
#define ___SBB___
#ifndef __NOPM__
#ifdef __cplusplus
  inline USHORT S1( MPARAM mp ){ return *(USHORT*)&mp;}
  inline USHORT S2( MPARAM mp ){ return *( (USHORT*)&mp+1 );}

  inline UCHAR	C4( MPARAM mp ){ return *(UCHAR*)&mp;}
  inline UCHAR	C3( MPARAM mp ){ return *((UCHAR*)&mp+1);}
  inline UCHAR	C2( MPARAM mp ){ return *((UCHAR*)&mp+2);}
  inline UCHAR	C1( MPARAM mp ){ return *((UCHAR*)&mp+3);}
  inline MPARAM S2( USHORT h, USHORT l )
   {return ( MPARAM )((ULONG)(((USHORT)(l)) | ((ULONG)((USHORT)(h))) << 16));}

#endif

  #define STDPROC( procname ) MRESULT EXPENTRY procname ( HWND Wnd, ULONG MSG, MPARAM mp1, MPARAM mp2 )
  #define STDPARMS  HWND Wnd, ULONG MSG, MPARAM mp1, MPARAM mp2
  #define STDARGS   Wnd, MSG, mp1, mp2

  #define returnT return ( MPARAM )1
  #define returnF return ( MPARAM )0
  #define returnDDP return WinDefDlgProc( STDARGS )
  #define returnDWP return WinDefWindowProc( STDARGS )

#endif

#ifdef __MAIN__
  #define EXTERN
#else
  #define EXTERN    extern
#endif
  EXTERN long SysCharHeight, SysCharWidth;
#endif
