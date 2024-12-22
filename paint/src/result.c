#include <stdio.h>
#include "result.h"

char *strresult(Result res){
    switch(res) {
    case EXIT:
	break;
    case SAVE:
	return "history saved";
    case LINE:
	return "1 line drawn";
    case UNDO:
	return "undo!";
    case UNKNOWN:
	return "error: unknown command";
    case ERRNONINT:
	return "Non-int value is included";
    case ERRLACKARGS:
	return "Too few arguments";
    case NOCOMMAND:
	return "No command in history";
    }
    return NULL;
}