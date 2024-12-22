#pragma once

// enum for interpret_command results
typedef enum res{ EXIT, LINE, UNDO, SAVE, UNKNOWN, ERRNONINT, ERRLACKARGS, NOCOMMAND} Result;
// Result 型に応じて出力するメッセージを返す
char *strresult(Result res);