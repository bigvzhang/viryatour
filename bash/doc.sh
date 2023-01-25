#!/bin/bash
<<DOCUMENT
#{arg}
#Command Line Arguments in Bash
|----------------|-------------------------------------------------------------|
|Special Variable| Variable Details                                            |
|:---------------|!------------------------------------------------------------|
| $1 to $n       | $1 is the first arguments, $2 is second                     | 
|                | argument till $n n'th arguments. From                       | 
|                | 10' th argument, you must need to inclose them in braces    | 
|                | like ${10}, ${11} and so on                                 |
|----------------|-------------------------------------------------------------|
| $0             | The name of script itself                                   |
| $$             | Process id of current shell                                 |
| $*             | Values of all the arguments                                 |
| $#             | Total number of arguments passed to script                  |
| $@             | $@==$* but "$@"!="$*", propagate parametrers through "$@"   |
| $?             | Exit status id of last command                              |
| $!             | Process id of last command                                  |
|----------------|-------------------------------------------------------------|
[REFERENC](https://tecadmin.net/tutorial/bash-scripting/bash-command-arguments/)
DOCUMENT

<<DOCUMENT
FUNCNAME BASH_LINENO BASH_SOURCE
    An array variable containing the names of all shell functions currently in the execution call stack. The element with index 0 is the name of any currently-executing shell function. The bottom-most element (the one with the highest index) is "main". This variable exists only when a shell function is executing. Assignments to FUNCNAME have no effect and return an error status. If FUNCNAME is unset, it loses its special properties, even if it is subsequently reset.

    This variable can be used with BASH_LINENO and BASH_SOURCE. Each element of FUNCNAME has corresponding elements in BASH_LINENO and BASH_SOURCE to describe the call stack. For instance, ${FUNCNAME[$i]} was called from the file ${BASH_SOURCE[$i+1]} at line number ${BASH_LINENO[$i]}. The caller builtin displays the current call stack using this information.

[REFERENCE](https://stackoverflow.com/questions/1835943/how-to-determine-function-name-from-inside-a-function)
DOCUMENT

<<DOCUMENT
NOTES
    1.  [OK] local var; var=... || return
	    [NO] local var=... || return 
DOCUMENT


