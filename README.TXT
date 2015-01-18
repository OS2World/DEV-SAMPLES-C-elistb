Revision 1.3

Contains fixes for flickering, searching and cleans up the message processing.
Read this carefully if you looked at the first version (1.0 but not id'd as
such.)

Thanks to Rick Fishman whose suggestions made things much better.


NOTE:  This code is UNSUPPORTED!  Mail will not be answered unless you are
       a "registered contributor".   You can become a registered contributor
       by submitting a real bug (preferably with a fix) or a useful extension.

       The author, for want of a more rational judge :-) will decide which
       bugs and extensions qualify.

The message, above, is repeated in ELISTBOX.HPP.

It is present without being "commented" so that you cannot compile the code
without seeing the message!


  Support for Extended List Boxes

  There are several classes needed to support ELBs: Row, Column and the
  subclasses of Column for specific data types and the ELB class itself.

  These classes in some sense encapsulate arrays of structures.
  A column is identified by a ( char* ) which points to the first element
  of the (sub)array of the things to be displayed and an offset to the "next"
  element in the (sub)array in a "true" array the offset will be 0 in a
  subarray of an array of structures the offset will be sizeof( struct ).

  Thereafter the variables are dealt with as "indexed vectors" (i.e.
  they are used as if they were strictly one dimensional.)

  ELB's (Extended List Boxes) have somewhat less structure than do regular
  list boxes.  They do, however, have sufficient
  structure so that the more ordinary uses of list boxes can be accomplished
  with no more code than is required for an ordinary LB and in many cases
  somewhat less.  Almost all of the data in the ELB is SHARED BETWEEN the
  user and the control -- this gives more freedom and concommitently requires
  more responsibility of the programmer.  Caveat Programmer, you'll have more
  chances to get into trouble but not if you stick to the beaten path.	I.e.
  don't do things that you probably wouldn't do with LBs.


  Constructing an ELB

  The author being ignorant and lazy picked the most convenient of the
  standard controls to subclass to obtain the ELB -- the MLE control
  has all of the needed stuff (and probably a lot more.)  The most important
  feature of the MLE is that the Dialog Editor knows how to put it on the
  screen (halleluja!)

  Make an MLE box with a Vert scrollbar (I do it with the dialog editor)
  then execute WinCreateELB to make it into an ELB.

  WinCreateELB is the function which transforms a Multiline entry Box
  control in a dialog template into an extended list box.
  This function should (usually) be executed in the WM_INITDLG message in the
  proceedure which manages the dialog containing the ELB.

   void WinCreateELB( HWND Wnd, ULONG id, Row& row, long& lastchangendx,
		      char* selectvectorptr=( char * )NULL );

   the creating function supplies a Row reference which in turn describes
   (holds) the Columns to be displayed and a minimal amount of additional
   info -- that which is common to all columns (e.g. their length since all
   displayed Columns must have a common (minimum) length.)  The Columns are
   all subclasses of the Column class and know how to index and draw
   themselves, they also know the Header and position to be displayed in the
   ELB.

Note: Perhaps the heading and display position should be in the Row.

   ELB's like list boxes can be "Single Select" or "Multi Select."
   The way the code contained here works is: if the Selection Vector (an
   array of characters) has a NULL descriptor in the Row which describes
   the ELB the ELB is taken to be Single Select.


   ELB Processing

   The ELB posts the following messages to its owner in a WM_CONTROL message:

   The active row index is 0 based and indicates the row on which the "Cursor"
   is currently set.

   All of the messages are of the same form:
     Message==WM_CONTROL, mp1==MPFROM2SHORT( ELBID, ELB_MSG ) and
     mp2==message specific (see below)


   ELB_SELCHANGED -- Tells the owner that the selection has been changed
		     mp2 == the index of the item whose selection state
		     is being changed -- single sel ELB's this is the message
		     is NOT SENT it is redundant for single sel ELBs.

   ELB_SEARCH	  -- Tells the owner that an ascii key has been struck while
		     the ELB has the Focus.  This is so that the programmer
		     can give their own behavior to the "search function" in
		     an ordinary LB.  This is one of the cases where I gave up
		     trying to figure out a rational default behavior.	It is
		     the authors belief that the standard LB search behavior
		     is by NO MEANS RATIONAL.

		mp2==MPFROM2SHORT(  index of the active row, the char struck )

   ELB_DBLCLK and ELB_ENTER   -- Tell the owner that something the user did is
		     is in some sense URGENT and they want the program's
		     attention.

		    mp2==the index of the active row


   The first Click of a dblclick sends an ELB_SELCHANGED
   before it sends ELB_DBLCLK.	Enter does not send an ELB_SELCHANGED
   nor does it change selection state of the then active line as does the
   dblclick!

   The ONLY KEY which will change the selection state of a multisel ELB row									     *
   is the space key.  This is a behavior of Multisel LBs.

   Since the ELB and the procs which manipulate it share access to the data
   in the columns displayed and to the selection vector (when present)
   any manipulation of the data, selection state and other parameters of an
   ELB can be accomplished by manipulating the data in the shared data.

   There is one message the ELB understands and that is:

   WM_SETACTIVE -- this message will force the row designated by the setting
   of mp1 which is MPFROM2SHORT( new active, 0 ), mp2 is not used and should
   be zero (I should, but don't, look at it!)

   ELB's work with arrays of structures -- which I use a lot!
   The use of column classes which use the starting address and offset to the
   next element is the basic implementation technique to accomplish this
   function.  Let the COMPILER DO THE WORK!  The Column class contains the
   column header, and the display starting and ending points expressed in avg
   character widths -- a reversion to pre-PM days.



Function draw() in each class derived from Column has considerable code in
common with the others.  This seems like the best way to do this even though
"inline" functions could have been used.

The only differences in these subclasses are the defaulted parameters and
the method of "finding" the indexed element and, of course, the actual
presentation.

Pardon the bizarre behavior of the test program.  I wanted to test as much
as I could with as little code as possible!
