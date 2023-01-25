#!/bin/bash
<<DOCUMENT
SYNTAX
1. prune 
          |--------------------------------expression 1     |--------------------expression 2
          |             |------------------whattodonext     |                    
          |             |       |----------current action   |       |------------current action
find tmp  -name testd1 -prune -exec echo ignore \{\} \;  -o -type d -exec echo Good \{\} \;
DOCUMENT
source shtour_common.sh
print_document #try_help

