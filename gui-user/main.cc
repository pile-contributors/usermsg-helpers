#include <QApplication>
#include "mainwindow.h"

/* ------------------------------------------------------------------------- */
void  printUsage   ()
{
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool  parseArgs   (
        int argc, char *argv[], int * ret_val)
{

    int b = 0;

    for ( int i = 1; i < argc; i++ ) {
		printUsage ();
		
    }

    return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int   main(int argc, char *argv[])
{

    int ret_val = 0;

    /* prepare to start */
    QApplication apl(argc, argv);

    /* prepare the ground for easy access to settings */
    QCoreApplication::setOrganizationName("CutTiles");
    QCoreApplication::setOrganizationDomain("cuttiles.com");
    QCoreApplication::setApplicationName("cuttiles");

	for (;;) {
		if (!parseArgs (argc, argv, &ret_val)) break;
        MainWindow mw;
        mw.show ();
        apl.exec ();
		break;
	}
	
    return ret_val;
}
/* ========================================================================= */
